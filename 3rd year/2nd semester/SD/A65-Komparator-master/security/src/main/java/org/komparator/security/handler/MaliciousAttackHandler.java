package org.komparator.security.handler;

import static javax.xml.bind.DatatypeConverter.printBase64Binary;

import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;
import java.util.Iterator;
import java.util.List;
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
import javax.xml.ws.handler.soap.SOAPHandler;
import javax.xml.ws.handler.soap.SOAPMessageContext;

import org.komparator.security.CryptoUtil;
import org.w3c.dom.NodeList;

public class MaliciousAttackHandler implements SOAPHandler<SOAPMessageContext>{	
	public static final String GET_PRODUCT = "getProduct";

	public static final String PRODUCT_ID = "productId";
	public static final String PRODUCT_PRICE = "price";
	public static final String ATTACK = "attack";


	public boolean handleMessage(SOAPMessageContext smc) {
		Boolean outbound = (Boolean) smc.get(MessageContext.MESSAGE_OUTBOUND_PROPERTY);
		boolean attacked = false;
		if (outbound) {
			// outbound message
			// put token in response SOAP header
			try {
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
				
				if (!opn.getLocalPart().equals(GET_PRODUCT)) {
					return true;
				}
				
				NodeList children = sb.getFirstChild().getChildNodes();
				for (int i = 0; i < children.getLength(); i++) {
					Node argument = (Node) children.item(i);
					if (argument.getNodeName().equals(PRODUCT_ID)) {
						if(argument.getValue().equals(ATTACK))
							attacked = true;					
					}
					if(argument.getNodeName().equals(PRODUCT_PRICE)){
						if(attacked){
							int price = Integer.parseInt(argument.getValue());
							price += 100;
							argument.setNodeValue(String.valueOf(price));
						}
					}		
					
				}
				return true;
				
			} catch (SOAPException e) {
				System.out.printf("Failed to add SOAP header because of %s%n", e);
			}
		
		} else {
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
