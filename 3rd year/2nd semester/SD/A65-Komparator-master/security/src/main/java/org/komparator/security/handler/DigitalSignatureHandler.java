package org.komparator.security.handler;

import static javax.xml.bind.DatatypeConverter.parseBase64Binary;
import static javax.xml.bind.DatatypeConverter.printBase64Binary;

import java.io.ByteArrayOutputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.security.KeyStoreException;
import java.security.PrivateKey;
import java.security.PublicKey;
import java.security.UnrecoverableKeyException;
import java.security.cert.Certificate;
import java.security.cert.CertificateException;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.Iterator;
import java.util.Set;

import javax.xml.bind.DatatypeConverter;
import javax.xml.namespace.QName;
import javax.xml.soap.Name;
import javax.xml.soap.Node;
import javax.xml.soap.SOAPBody;
import javax.xml.soap.SOAPElement;
import javax.xml.soap.SOAPEnvelope;
import javax.xml.soap.SOAPException;
import javax.xml.soap.SOAPHeader;
import javax.xml.soap.SOAPHeaderElement;
import javax.xml.soap.SOAPMessage;
import javax.xml.soap.SOAPPart;
import javax.xml.ws.handler.MessageContext;
import javax.xml.ws.handler.soap.SOAPHandler;
import javax.xml.ws.handler.soap.SOAPMessageContext;

import org.komparator.security.CertUtil;
import org.komparator.security.CryptoUtil;
import org.komparator.security.GlobalSingleton;
import org.w3c.dom.NodeList;

import pt.ulisboa.tecnico.sdis.ws.cli.CAClient;
import pt.ulisboa.tecnico.sdis.ws.cli.CAClientException;

public class DigitalSignatureHandler implements SOAPHandler<SOAPMessageContext>{
	
	public static CAClient caclient;
	
	public static PublicKey publicKey;
	public static PrivateKey privateKey;
	
	public static final String CA_URL = "http://sec.sd.rnl.tecnico.ulisboa.pt:8081/ca";
	
	public static final String CERTIFICATE = "ca.cer";
	
	public static final String KEYSTOREPASSWORD = "ZATAC2XZ";
	public static final String PASSWORD = "ZATAC2XZ";

	public static final String SIGNATURE_HEADER = "signature";
	public static final String SIGNATURE_NS = "sg";
	
	public static final String SERVICE_HEADER = "servicename";
	public static final String SERVICE_NS = "sn";
	
	
	@Override
	public boolean handleMessage(SOAPMessageContext smc) {
	
		Boolean outbound = (Boolean) smc.get(MessageContext.MESSAGE_OUTBOUND_PROPERTY);
		
		try {
			caclient = new CAClient(CA_URL);
		} catch (CAClientException e) {
			e.printStackTrace();
		}
		String certificateName = null;
		Certificate certificateCA = null;
		Certificate certificate = null;
		if (outbound) {
			// outbound message

			// put token in response SOAP header
			try {
				//get CA certificate
				String service = GlobalSingleton.wsname;
				certificateName = caclient.getCertificate(service);				
				try {
					certificate = CertUtil.getX509CertificateFromPEMString(certificateName);
				} catch (CertificateException e) {
					e.printStackTrace();
				}		
				
				//get certificate  			    	
				try {
					certificateCA = CertUtil.getX509CertificateFromResource(CERTIFICATE);
				} catch (CertificateException | IOException e) {
					e.printStackTrace();
				}				
				CertUtil.verifySignedCertificate(certificate, certificateCA);
				
				try {
					privateKey = CertUtil.getPrivateKeyFromKeyStoreResource(service + ".jks", KEYSTOREPASSWORD.toCharArray(),service.toLowerCase(), PASSWORD.toCharArray());
				} catch (UnrecoverableKeyException | FileNotFoundException | KeyStoreException e) {
					e.printStackTrace();
				}				
				
				// get SOAP envelope
				SOAPMessage msg = smc.getMessage();
				SOAPPart sp = msg.getSOAPPart();				
				SOAPEnvelope se = sp.getEnvelope();
				SOAPBody sb = se.getBody();
				// add header
				SOAPHeader sh = se.getHeader();
				if (sh == null)
					sh = se.addHeader();	
				
				// add header element (name, namespace prefix, namespace)
				Name name1 = se.createName(SERVICE_HEADER, "e", SERVICE_NS);
				SOAPHeaderElement element1 = sh.addHeaderElement(name1);	
				
				// add header element value serviceName				
				element1.addTextNode(service);		
				msg.saveChanges();
				
				ByteArrayOutputStream out = new ByteArrayOutputStream();
				try {
					msg.writeTo(out);
				} catch (IOException e) {
					e.printStackTrace();
				}
				
				byte[] messageBytes = out.toByteArray();				
				
				byte[] signature = CertUtil.makeDigitalSignature("SHA256withRSA", privateKey, messageBytes);
				
				String signatureString = DatatypeConverter.printBase64Binary(signature);
				
				// add header element (name, namespace prefix, namespace)
				Name name2 = se.createName(SIGNATURE_HEADER, "e", SIGNATURE_NS);
				SOAPHeaderElement element2 = sh.addHeaderElement(name2);	
				
				// add header element value signature		
				element2.addTextNode(signatureString);
				
			} catch (SOAPException e) {
				System.out.printf("Failed to add SOAP header because of %s%n", e);
			}
		
		} else {
			// inbound message

			// get token from request SOAP header
			try {
				// get SOAP envelope
				SOAPMessage msg = smc.getMessage();
				SOAPPart sp = msg.getSOAPPart();				
				SOAPEnvelope se = sp.getEnvelope();
				SOAPBody sb = se.getBody();
				// add header
				SOAPHeader sh = se.getHeader();
				// check header
				if (sh == null) {
					System.out.println("Header not found.");
					return true;
				}				
				
				// get first header element
				Name name1 = se.createName(SERVICE_HEADER, "e", SERVICE_NS);
				Iterator it1 = sh.getChildElements(name1);
				// check header element				
				if (!it1.hasNext()) {
					System.out.printf("Header element %s not found.%n", SERVICE_HEADER);
					return true;
				}
				SOAPElement element1 = (SOAPElement) it1.next();

				// *** #4 ***
				// get header element value
				String service = element1.getValue();
				
				//get CA certificate		
				certificateName = caclient.getCertificate(service);				
				try {
					certificate = CertUtil.getX509CertificateFromPEMString(certificateName);
				} catch (CertificateException e) {
					e.printStackTrace();
				}				
				
				//get certificate  			    	
				try {
					certificateCA = CertUtil.getX509CertificateFromResource(CERTIFICATE);
				} catch (CertificateException | IOException e) {
					e.printStackTrace();
				}				
				CertUtil.verifySignedCertificate(certificate, certificateCA);				
				
				publicKey = CertUtil.getPublicKeyFromCertificate(certificate);
				
				
				// get first header element
				Name name2 = se.createName(SIGNATURE_HEADER, "e", SIGNATURE_NS);
				Iterator it2 = sh.getChildElements(name2);
				// check header element				
				if (!it2.hasNext()) {
					System.out.printf("Header element %s not found.%n", SIGNATURE_HEADER);
					return true;
				}
				SOAPElement element2 = (SOAPElement) it2.next();

				// *** #4 ***
				// get header element value
				String signatureString = element2.getValue();
				
				sh.removeChild(element2);
				msg.saveChanges();
				
				byte[] signature = DatatypeConverter.parseBase64Binary(signatureString);
				
				ByteArrayOutputStream out = new ByteArrayOutputStream();
				try {
					msg.writeTo(out);
				} catch (IOException e) {
					e.printStackTrace();
				}
				
				byte[] messageBytes = out.toByteArray();
				
				if(!CertUtil.verifyDigitalSignature("SHA256withRSA", publicKey, messageBytes, signature)){
					//throw exception
				}
			} catch (SOAPException e) {
				System.out.printf("Failed to get SOAP header because of %s%n", e);
			}

		}

		return true;
	}

	public boolean handleFault(SOAPMessageContext smc) {
		return true;
	}

	public Set<QName> getHeaders() {
		return null;
	}

	public void close(MessageContext messageContext) {
	}

}
