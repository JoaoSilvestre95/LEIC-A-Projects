package org.komparator.mediator.ws;

import java.util.Date;
import java.util.TimerTask;

import javax.xml.ws.WebServiceException;

import org.komparator.mediator.ws.cli.MediatorClient;
import org.komparator.mediator.ws.cli.MediatorClientException;

public class LifeProof extends TimerTask{

    MediatorEndpointManager port;
    private String url = "http://localhost:8072/mediator-ws/endpoint";
    private String urlP = "http://localhost:8071/mediator-ws/endpoint";
    public static final int LIMIT = 5000;     
    public static Date date = new Date();

    public LifeProof (MediatorEndpointManager port) {
        this.port = port;
    }
    
	
	public void run(){		
		if(port.getIsPrimary()){
			MediatorClient client = null;
			try {
				client = new MediatorClient(url);
				client.imAlive();	
			} catch (WebServiceException e) {
				System.out.println("Secondary mediator not active!!!");
			} catch (MediatorClientException e) {
				System.out.println("Secondary mediator client problem!!!");
			}
			
		}
		else{
			Date now = new Date();
			if(now.getTime() - date.getTime() > LIMIT){
				System.out.println("Primary mediator not active!!! Secondary taking is place");
				port.setIsPrimary(true);
				try {
					port.publishToUDDI();
				} catch (Exception e1) {
					System.out.println("Cannot publish To UDDI!!!");
				}
			}			
		}
	}
}