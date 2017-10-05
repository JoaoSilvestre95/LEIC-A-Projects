package org.komparator.security;

import java.io.*;
import java.security.*;
import javax.crypto.*;
import javax.security.cert.CertificateException;

import java.util.*;

import java.io.File;
import java.security.cert.Certificate;
import java.security.cert.CertificateFactory;

public class CryptoUtil {
	/** print some error messages to standard error. */
	public static boolean outputFlag = true;

    // TODO add security helper methods
	public static byte[] asymCipher(byte[] message, PublicKey publickey){
		Cipher c = null;
		byte[] cipherBytes = null;
		
		try {
			c = Cipher.getInstance("RSA/ECB/PKCS1Padding");
		} catch (NoSuchAlgorithmException e1) {
			e1.printStackTrace();
		} catch (NoSuchPaddingException e1) {
			e1.printStackTrace();
		}
		try {
			c.init(Cipher.ENCRYPT_MODE, publickey);
		} catch (InvalidKeyException e) {
			e.printStackTrace();
		}
		try {
			cipherBytes = c.doFinal(message);
		} catch (IllegalBlockSizeException | BadPaddingException e) {
			e.printStackTrace();
		}
		return cipherBytes;
	} 
	
	public static byte[] asymDecipher(byte[] criptMessage, PrivateKey privatekey){
		Cipher c = null;
		byte[] plainBytes = null;
		
		try {
			c = Cipher.getInstance("RSA/ECB/PKCS1Padding");
		} catch (NoSuchAlgorithmException e1) {
			e1.printStackTrace();
		} catch (NoSuchPaddingException e1) {
			e1.printStackTrace();
		}
		try {
			c.init(Cipher.DECRYPT_MODE, privatekey);
		} catch (InvalidKeyException e) {
			e.printStackTrace();
		}
		try {
			plainBytes = c.doFinal(criptMessage);
		} catch (IllegalBlockSizeException | BadPaddingException e) {
			e.printStackTrace();
		}
		return plainBytes;
	}
	
	public boolean decipherCompare(byte[] original, byte[] chiferd) throws Exception {

		// compare digests
		if (original.length != chiferd.length)
			return false;

		for (int i = 0; i < original.length; i++)
			if (original[i] != chiferd[i])
				return false;
		return true;
	}

}
