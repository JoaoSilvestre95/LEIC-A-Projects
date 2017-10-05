package org.komparator.supplier.ws.it;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.assertTrue;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;

import org.junit.After;
import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;
// import org.komparator.supplier.domain.Purchase;
import org.komparator.supplier.ws.*;

/**
 * Test suite
 */
public class BuyProductIT extends BaseIT {

	// static members

	// one-time initialization and clean-up
	@BeforeClass
	public static void oneTimeSetUp() {
		client.clear();
	}

	@AfterClass
	public static void oneTimeTearDown() {
		client.clear();
	}

	// members

	// initialization and clean-up for each test
	@Before
	public void setUp() throws BadProductId_Exception, BadProduct_Exception {
		client.clear();
		// fill-in test products
		// (since getProduct is read-only the initialization below
		// can be done once for all tests in this suite)
		{
			ProductView product = new ProductView();
			product.setId("X1");
			product.setDesc("Basketball");
			product.setPrice(10);
			product.setQuantity(10);
			client.createProduct(product);
		}
		{
			ProductView product = new ProductView();
			product.setId("Y2");
			product.setDesc("Baseball");
			product.setPrice(20);
			product.setQuantity(20);
			client.createProduct(product);
		}
		{
			ProductView product = new ProductView();
			product.setId("Z3");
			product.setDesc("Soccer ball");
			product.setPrice(30);
			product.setQuantity(30);
			client.createProduct(product);
		}
	}

	@After
	public void tearDown() {
		client.clear();
	}

	// tests
	// assertEquals(expected, actual);

	// public String buyProduct(String productId, int quantity)
	// throws BadProductId_Exception, BadQuantity_Exception,
	// InsufficientQuantity_Exception {

	// bad input tests

	@Test(expected = BadProductId_Exception.class)
	public void buyProductNullTest() throws BadProductId_Exception, BadQuantity_Exception, InsufficientQuantity_Exception {
		client.buyProduct(null, 3);
	}

	@Test(expected = BadProductId_Exception.class)
	public void buyProductEmptyTest() throws BadProductId_Exception, BadQuantity_Exception, InsufficientQuantity_Exception {
		client.buyProduct("", 3);
	}

	@Test(expected = BadProductId_Exception.class)
	public void buyProductWhitespaceTest() throws BadProductId_Exception, BadQuantity_Exception, InsufficientQuantity_Exception {
		client.buyProduct(" ", 3);
	}

	@Test(expected = BadProductId_Exception.class)
	public void buyProductTabTest() throws BadProductId_Exception, BadQuantity_Exception, InsufficientQuantity_Exception {
		client.buyProduct("\t",3);
	}

	@Test(expected = BadProductId_Exception.class)
	public void buyProductNewlineTest() throws BadProductId_Exception, BadQuantity_Exception, InsufficientQuantity_Exception {
		client.buyProduct("\n",3);
	}
	
	@Test(expected = BadQuantity_Exception.class)
	public void buyProductZeroQtTest() throws BadProductId_Exception, BadQuantity_Exception, InsufficientQuantity_Exception {
		client.buyProduct("Z3",0);
	}
	@Test(expected = BadQuantity_Exception.class)
	public void buyProductNegQtTest() throws BadProductId_Exception, BadQuantity_Exception, InsufficientQuantity_Exception {
		client.buyProduct("Z3",-4);
	}
	
	@Test(expected = InsufficientQuantity_Exception.class)
	public void buyProductBigQtTest() throws BadProductId_Exception, BadQuantity_Exception, InsufficientQuantity_Exception {
		client.buyProduct("Z3",70);
	}

	

	// main tests
	@Test
	public void buyOneProductTest() throws BadProductId_Exception, BadQuantity_Exception, InsufficientQuantity_Exception {
		String p = client.buyProduct("X1",5);
		List <PurchaseView> purchases = client.listPurchases();
		assertEquals(1, purchases.size());
		for (PurchaseView e: purchases){
			if (e.getId() == p){
				assertEquals(p, e.getId());
				assertEquals("X1", e.getProductId());
				assertEquals(5, e.getQuantity());
				assertEquals(10, e.getUnitPrice());}
			}
		}
	
	@Test
	public void buyMoreThanOneProductTest() throws BadProductId_Exception, BadQuantity_Exception, InsufficientQuantity_Exception {
		String p = client.buyProduct("X1",5);
		String p2 = client.buyProduct("Y2",3);
		String p3 = client.buyProduct("Z3",4);
		List <PurchaseView> purchases = client.listPurchases();
		assertEquals(3, purchases.size());
		for (PurchaseView e : purchases){
			if (e.getId() == p){
				assertEquals(p, e.getId());
				assertEquals("X1", e.getProductId());
				assertEquals(5, e.getQuantity());
				assertEquals(10, e.getUnitPrice());}
			if (e.getId() == p2){
				assertEquals(p2, e.getId());
				assertEquals("Y2", e.getProductId());
				assertEquals(3, e.getQuantity());
				assertEquals(20, e.getUnitPrice());}
			if (e.getId() == p3){
				assertEquals(p3, e.getId());
				assertEquals("Z3", e.getProductId());
				assertEquals(4, e.getQuantity());
				assertEquals(30, e.getUnitPrice());}
			}
	}
	
	@Test(expected = BadProductId_Exception.class)
	public void buyProductInexistentIdTest() throws BadProductId_Exception, BadQuantity_Exception, InsufficientQuantity_Exception {
		client.buyProduct("ProductDontExists",1);
	}
	
	@Test(expected = BadProductId_Exception.class)
	public void buyProductLowercaseNotExistsTest() throws BadProductId_Exception, BadQuantity_Exception, InsufficientQuantity_Exception {
		client.buyProduct("x1",5);
	}

}
