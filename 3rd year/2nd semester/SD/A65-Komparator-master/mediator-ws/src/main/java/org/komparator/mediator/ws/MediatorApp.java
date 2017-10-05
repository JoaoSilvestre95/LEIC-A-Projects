package org.komparator.mediator.ws;

import java.util.Timer;

import org.komparator.security.GlobalSingleton;

public class MediatorApp {
	private final static int DELAY = 10000;

	public static void main(String[] args) throws Exception {
		// Check arguments
		if (args.length == 0 || args.length == 2) {
			System.err.println("Argument(s) missing!");
			System.err.println("Usage: java " + MediatorApp.class.getName() + " wsURL OR uddiURL wsName wsURL");
			return;
		}
		String uddiURL = null;
		String wsName = null;
		String wsURL = null;
		String wsI = null;
		LifeProof life;
		Timer timer = null;

		// Create server implementation object, according to options
		MediatorEndpointManager endpoint = null;
		if (args.length == 1) {
			wsURL = args[0];
			endpoint = new MediatorEndpointManager(wsURL);
		} else if (args.length >= 3) {			
			uddiURL = args[0];
			wsName = args[1];
			wsURL = args[2];
			wsI = args[3];
			
			endpoint = new MediatorEndpointManager(uddiURL, wsName, wsURL, wsI);
			endpoint.setVerbose(true);
			
		}

		try {			
			endpoint.start();
			life = new LifeProof(endpoint);
			timer = new Timer(true);
			timer.schedule(life, /*delay*/ DELAY, /*period*/ LifeProof.LIMIT);			
			endpoint.awaitConnections();
		} finally {
			if(timer != null)
				timer.cancel();
			endpoint.stop();
		}

	}

}
