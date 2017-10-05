package org.komparator.mediator.ws.it;

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
import org.komparator.mediator.ws.*;
import org.komparator.supplier.ws.BadProductId_Exception;
import org.komparator.supplier.ws.BadProduct_Exception;
import org.komparator.supplier.ws.BadQuantity_Exception;
import org.komparator.supplier.ws.InsufficientQuantity_Exception;
import org.komparator.supplier.ws.ProductView;
import org.komparator.supplier.ws.cli.SupplierClient;

/**
 * Test suite
 */

public class GetItemsIT extends BaseIT {

	// static members

	// one-time initialization and clean-up
	@BeforeClass
	public static void oneTimeSetUp() {
		mediatorClient.clear();
	}

	@AfterClass
	public static void oneTimeTearDown() {
		mediatorClient.clear();
	}

	// members

	// initialization and clean-up for each test
	@Before
	public void setUp() throws BadProductId_Exception, BadProduct_Exception{
		mediatorClient.clear();
		// fill-in test products
		// (since getProduct is read-only the initialization below
		// can be done once for all tests in this suite)
		{			
			ProductView product = new ProductView();
			product.setId("A1");
			product.setDesc("Pencil");
			product.setPrice(20);
			product.setQuantity(10);
			supplierClients.get(0).createProduct(product);
		}
		{			
			ProductView product = new ProductView();
			product.setId("A2");
			product.setDesc("Ruler");
			product.setPrice(5);
			product.setQuantity(10);
			supplierClients.get(0).createProduct(product);
		}
		{
			ProductView product = new ProductView();
			product.setId("A1");
			product.setDesc("Pencil");
			product.setPrice(10);
			product.setQuantity(20);
			supplierClients.get(1).createProduct(product);
		}
		{
			ProductView product = new ProductView();
			product.setId("B2");
			product.setDesc("Pen");
			product.setPrice(20);
			product.setQuantity(20);
			supplierClients.get(1).createProduct(product);
		}
		{
			ProductView product = new ProductView();
			product.setId("A1");
			product.setDesc("Pencil");
			product.setPrice(5);
			product.setQuantity(30);
			supplierClients.get(2).createProduct(product);
		}
		{
			ProductView product = new ProductView();
			product.setId("C2");
			product.setDesc("Calculator");
			product.setPrice(30);
			product.setQuantity(30);
			supplierClients.get(2).createProduct(product);
		}
	}

	@After
	public void tearDown() {
		mediatorClient.clear();
	}	
	//Input Tests
	@Test(expected = InvalidItemId_Exception.class)
	public void getItemsNullTest() throws InvalidItemId_Exception{
		mediatorClient.getItems(null);
	}

	@Test(expected = InvalidItemId_Exception.class)
	public void getItemsEmtpyStringTest() throws InvalidItemId_Exception{
		mediatorClient.getItems("");
	}
	@Test(expected = InvalidItemId_Exception.class)
	public void getItemsBlankSpacesTest() throws InvalidItemId_Exception{
		mediatorClient.getItems("   ");
	}
	@Test(expected = InvalidItemId_Exception.class)
	public void getItemsTabTest() throws InvalidItemId_Exception{
		mediatorClient.getItems("\t");
	}
	
	@Test(expected = InvalidItemId_Exception.class)
	public void getItemsNewLineTest() throws InvalidItemId_Exception{
		mediatorClient.getItems("\n");
	}
	
	// main tests
	
	@Test
	public void getItemsOneMatchTest() throws InvalidItemId_Exception{
		
		List<ItemView> items = mediatorClient.getItems("C2");
		ItemView item = items.get(0);
		assertEquals(1,items.size());
		
		assertEquals("C2", item.getItemId().getProductId());
		assertEquals(30, item.getPrice());
		assertEquals("Calculator", item.getDesc());
		assertEquals("A65_Supplier3",item.getItemId().getSupplierId());
	}
	
	
	@Test
	public void getItemsItemNotFoundTest() throws InvalidItemId_Exception {
		List<ItemView> items = mediatorClient.getItems("AAAAA3");
		assertTrue(items.isEmpty());
	}
	
	@Test
	public void getItemsThreeMatchesTest() throws InvalidItemId_Exception{
		
		List<ItemView> items = mediatorClient.getItems("A1");
		ItemView item = items.get(0);
		ItemView item2 = items.get(1);
		ItemView item3 = items.get(2);
		assertEquals(3,items.size());
		
		assertEquals("A1", item.getItemId().getProductId());
		assertEquals(5, item.getPrice());
		assertEquals("A65_Supplier3",item.getItemId().getSupplierId());
		
		assertEquals("A1", item.getItemId().getProductId());
		assertEquals(10,item2.getPrice());
		assertEquals("A65_Supplier2",item2.getItemId().getSupplierId());

		assertEquals("A1", item.getItemId().getProductId());
		assertEquals(20,item3.getPrice());
		assertEquals("A65_Supplier1",item3.getItemId().getSupplierId());
		
	}
		
	@Test
	public void lowerCaseNotExistsTest() throws InvalidItemId_Exception {
		
		List<ItemView> items = mediatorClient.getItems("c2");
		assertTrue(items.isEmpty());
	}	
	
}