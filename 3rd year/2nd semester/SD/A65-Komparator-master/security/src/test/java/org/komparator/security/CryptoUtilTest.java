package org.komparator.security;

import java.io.*;
import java.security.*;
import javax.crypto.*;
import javax.security.cert.CertificateException;

import java.util.*;
import java.security.cert.Certificate;

import org.junit.*;


import static org.junit.Assert.*;

public class CryptoUtilTest {

    // static members
	
	final static String CERTIFICATE = "example.cer";
	final static String KEYSTORE = "example.jks";
	final static String STOREPASSWORD = "1nsecure";
	final static String PASSWORD = "ins3cur3";
	final static String ALIAS = "example";
	
	
	private static CertUtil cert = null;
	private static CryptoUtil crypto = null;
	
	/** Plain text to digest. */
	private final String plainText = "This is the plain text!";
	/** Plain text bytes. */
	private static byte[] plainBytes;

	// one-time initialization and clean-up
    @BeforeClass
    public static void oneTimeSetUp() {
        // runs once before all tests in the suite
    }

    @AfterClass
    public static void oneTimeTearDown() {
        // runs once after all tests in the suite
    }

    // members

    // initialization and clean-up for each test
    @Before
    public void setUp() {
        // runs before each test
    	cert = new CertUtil();
    	crypto = new CryptoUtil();
    	plainBytes = plainText.getBytes();
    }

    

    // tests
    @Test

    public void sucess() throws IOException, CertificateException, UnrecoverableKeyException, KeyStoreException, java.security.cert.CertificateException {

    	PublicKey keypublic = null;
    	PrivateKey keyprivate = null;
    	Certificate certificate = null;
    	
    	

		certificate = CertUtil.getX509CertificateFromResource(CERTIFICATE);
		
    	
    	keypublic = CertUtil.getPublicKeyFromCertificate(certificate);
    	
		keyprivate = CertUtil.getPrivateKeyFromKeyStoreResource(KEYSTORE, STOREPASSWORD.toCharArray(), ALIAS, PASSWORD.toCharArray());

		
    	
    	byte[] cipherBytes = crypto.asymCipher(plainBytes, keypublic);
    	byte[] decipheredBytes = crypto.asymDecipher(cipherBytes, keyprivate);
    	
		System.out.print("Text: ");
		String newPlainText = new String(decipheredBytes);
		System.out.println(newPlainText);

		assertEquals(plainText, newPlainText);

    }
    
   
    //wrong keystore test
    @Test
    public void wrongTest() throws java.security.cert.CertificateException, IOException, UnrecoverableKeyException, KeyStoreException {
    	
    	PublicKey keypublic = null;
    	PrivateKey keyprivate = null;
    	Certificate certificate = null;
    	
    	

		certificate = CertUtil.getX509CertificateFromResource(CERTIFICATE);
		
    	
    	keypublic = CertUtil.getPublicKeyFromCertificate(certificate);
    	
		keyprivate = CertUtil.getPrivateKeyFromKeyStoreResource(KEYSTORE, STOREPASSWORD.toCharArray(), ALIAS, PASSWORD.toCharArray());

		
    	
    	byte[] cipherBytes = crypto.asymCipher(plainBytes, keypublic);
    	cipherBytes[3]=12;
    	byte[] decipheredBytes = crypto.asymDecipher(cipherBytes, keyprivate);
    	assertNull(decipheredBytes);
    }
    
    @After
    public void tearDown() {
        // runs after each test
    	
    }
    
}
