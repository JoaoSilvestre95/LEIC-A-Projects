package org.komparator.security.handler;

import java.security.cert.CertificateException;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.Iterator;
import java.util.Set;

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
import javax.xml.ws.handler.MessageContext.Scope;
import javax.xml.ws.handler.soap.SOAPHandler;
import javax.xml.ws.handler.soap.SOAPMessageContext;

import static javax.xml.bind.DatatypeConverter.parseBase64Binary;
import static javax.xml.bind.DatatypeConverter.printBase64Binary;

import org.komparator.security.CertUtil;
import org.komparator.security.CryptoUtil;
import org.w3c.dom.NodeList;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.security.KeyStoreException;
import java.security.PrivateKey;
import java.security.PublicKey;
import java.security.UnrecoverableKeyException;
import java.security.cert.Certificate;

import pt.ulisboa.tecnico.sdis.ws.cli.CAClient;
import pt.ulisboa.tecnico.sdis.ws.cli.CAClientException;

public class CipherCcHandler implements SOAPHandler<SOAPMessageContext>{

	public static CAClient caclient;

	public static PublicKey publicKey;
	public static PrivateKey privateKey;

	public static final String CA_URL = "http://sec.sd.rnl.tecnico.ulisboa.pt:8081/ca";

	public static final String CERTIFICATE = "ca.cer";

	public static final String KEYSTORERESOURCE = "A65_Mediator.jks";
	public static final String ALIAS = "a65_mediator";
	public static final String KEYSTOREPASSWORD = "ZATAC2XZ";
	public static final String PASSWORD = "ZATAC2XZ";

	public static final String BUY_CART = "buyCart";

	public static final String CREDITCARD_ARGUMENT = "creditCardNr";

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
				certificateName = caclient.getCertificate("A65_Mediator");
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


				// get SOAP envelope
				SOAPMessage msg = smc.getMessage();
				SOAPPart sp = msg.getSOAPPart();
				SOAPEnvelope se = sp.getEnvelope();
				SOAPBody sb = se.getBody();
				// add header
				SOAPHeader sh = se.getHeader();
				if (sh == null)
					sh = se.addHeader();

				QName svcn = (QName) smc.get(MessageContext.WSDL_SERVICE);
				QName opn = (QName) smc.get(MessageContext.WSDL_OPERATION);

				if (!opn.getLocalPart().equals(BUY_CART)) {
					return true;
				}

				NodeList children = sb.getFirstChild().getChildNodes();
				for (int i = 0; i < children.getLength(); i++) {
					Node argument = (Node) children.item(i);
					if (argument.getNodeName().equals(CREDITCARD_ARGUMENT)) {
							String secretArgument = argument.getTextContent();
							// cipher message with symmetric key
							byte[] cipheredArgument = CryptoUtil.asymCipher(parseBase64Binary(secretArgument), publicKey);
							String encodedSecretArgument = printBase64Binary(cipheredArgument);
							argument.setTextContent(encodedSecretArgument);
							msg.saveChanges();
					}
					return true;
				}


			} catch (SOAPException e) {
				System.out.printf("Failed to add SOAP header because of %s%n", e);
			}

		} else {
			// inbound message

			// get token from request SOAP header
			try {
				//get CA certificate
				certificateName = caclient.getCertificate("A65_Mediator");
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
					privateKey = CertUtil.getPrivateKeyFromKeyStoreResource(KEYSTORERESOURCE, KEYSTOREPASSWORD.toCharArray(), ALIAS, PASSWORD.toCharArray());
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

				QName svcn = (QName) smc.get(MessageContext.WSDL_SERVICE);
				QName opn = (QName) smc.get(MessageContext.WSDL_OPERATION);

				if (!opn.getLocalPart().equals(BUY_CART)) {
					return true;
				}

				NodeList children = sb.getFirstChild().getChildNodes();
				for (int i = 0; i < children.getLength(); i++) {
					Node argument = (Node) children.item(i);
					if (argument.getNodeName().equals(CREDITCARD_ARGUMENT)) {
							String secretArgument = argument.getTextContent();
							// cipher message with symmetric key
							byte[] uncipheredArgument = CryptoUtil.asymDecipher(parseBase64Binary(secretArgument), privateKey);
							String decodedSecretArgument = printBase64Binary(uncipheredArgument);
							argument.setTextContent(decodedSecretArgument);
							msg.saveChanges();
					}
					return true;
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
