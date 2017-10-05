package org.komparator.security.handler;

import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;
import java.util.Iterator;
import java.util.List;
import java.util.Set;

import javax.management.RuntimeErrorException;
import javax.xml.namespace.QName;
import javax.xml.soap.Name;
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

/**
 * This is the handler client class of the Relay example.
 *
 * #2 The client handler receives data from the client (via message context). #3
 * The client handler passes data to the server handler (via outbound SOAP
 * message header).
 *
 * *** GO TO server handler to see what happens next! ***
 *
 * #10 The client handler receives data from the server handler (via inbound
 * SOAP message header). #11 The client handler passes data to the client (via
 * message context).
 *
 * *** GO BACK TO client to see what happens next! ***
 */

public class FreshnessHandler implements SOAPHandler<SOAPMessageContext> {
	public static final String TIMESTAMP_HEADER = "uniqueTime";
	public static final String TIMESTAMP_NS = "ut";

	public boolean handleMessage(SOAPMessageContext smc) {
		Boolean outbound = (Boolean) smc.get(MessageContext.MESSAGE_OUTBOUND_PROPERTY);
		if (outbound) {
			// outbound message
			// put token in response SOAP header
			try {
				// get SOAP envelope
				SOAPMessage msg = smc.getMessage();
				SOAPPart sp = msg.getSOAPPart();
				SOAPEnvelope se = sp.getEnvelope();

				// add header
				SOAPHeader sh = se.getHeader();
				if (sh == null)
					sh = se.addHeader();

				// add header element (name, namespace prefix, namespace)
				Name name = se.createName(TIMESTAMP_HEADER, "e", TIMESTAMP_NS);
				SOAPHeaderElement element = sh.addHeaderElement(name);

			    //add data and time
			    DateFormat df = new SimpleDateFormat("MM/dd/yyyy HH:mm:ss");
			
				Date today = Calendar.getInstance().getTime();        
				// Using DateFormat format method we can create a string 
				// representation of a date with the defined format.
				String reportDate = df.format(today);
				
				// *** #9 ***
				// add header element value				
				element.addTextNode(reportDate);
				
			} catch (SOAPException e) {
				System.out.printf("Failed to add SOAP header because of %s%n", e);
			}
		
		} else {
			// inbound message

			// get token from request SOAP header
			try {
				// get SOAP envelope header
				SOAPMessage msg = smc.getMessage();
				SOAPPart sp = msg.getSOAPPart();
				SOAPEnvelope se = sp.getEnvelope();
				SOAPHeader sh = se.getHeader();

				// check header
				if (sh == null) {
					System.out.println("Header not found.");
					return true;
				}			
				
				
				// get first header element
				Name name = se.createName(TIMESTAMP_HEADER, "e", TIMESTAMP_NS);
				Iterator it = sh.getChildElements(name);
				// check header element
				
				if (!it.hasNext()) {
					System.out.printf("Header element %s not found.%n", TIMESTAMP_NS);
					return true;
				}
				SOAPElement element = (SOAPElement) it.next();

				// *** #4 ***
				// get header element value
				String headerValue = element.getValue();
				
				DateFormat formatter = new SimpleDateFormat("dd/MM/yyyy HH:mm:ss");
				
				System.out.println(headerValue + "\n");			
								
				Date date = null;
				try {
					date = formatter.parse(headerValue);
				} catch (ParseException e) {
					e.printStackTrace();
				}
				Date atual = new Date();
				if (date.getTime() - atual.getTime() > 3000){
					throw new RuntimeException();					
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
