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
// import org.komparator.supplier.domain.Purchase;
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
public class SearchItemsIT extends BaseIT {

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
		//A65_Supplier1
		{			
			ProductView product = new ProductView();
			product.setId("X1");
			product.setDesc("Basketball");
			product.setPrice(10);
			product.setQuantity(10);
			supplierClients.get(0).createProduct(product);
		}
		{			
			ProductView product = new ProductView();
			product.setId("X2");
			product.setDesc("Football");
			product.setPrice(5);
			product.setQuantity(10);
			supplierClients.get(0).createProduct(product);
		}
		//A65_Supplier2
		{
			ProductView product = new ProductView();
			product.setId("Y1");
			product.setDesc("Tenis");
			product.setPrice(10);
			product.setQuantity(20);
			supplierClients.get(1).createProduct(product);
		}
		{
			ProductView product = new ProductView();
			product.setId("X1");
			product.setDesc("Basketball");
			product.setPrice(5);
			product.setQuantity(20);
			supplierClients.get(1).createProduct(product);
		}
		//A65_Supplier3
		{
			ProductView product = new ProductView();
			product.setId("Z1");
			product.setDesc("Soccer ball");
			product.setPrice(30);
			product.setQuantity(30);
			supplierClients.get(2).createProduct(product);
		}
		{
			ProductView product = new ProductView();
			product.setId("Z2");
			product.setDesc("Rugby");
			product.setPrice(30);
			product.setQuantity(30);
			supplierClients.get(2).createProduct(product);
		}
		{
			ProductView product = new ProductView();
			product.setId("Z3");
			product.setDesc("Tenis");
			product.setPrice(10);
			product.setQuantity(20);
			supplierClients.get(2).createProduct(product);
		}
	}

	@After
	public void tearDown() {
		mediatorClient.clear();
	}	
	//Input Tests
	@Test(expected = InvalidText_Exception.class)
	public void searchItemsNullTest() throws InvalidText_Exception{
		mediatorClient.searchItems(null);
	}

	@Test(expected = InvalidText_Exception.class)
	public void searchItemsEmptyTest() throws InvalidText_Exception {
		mediatorClient.searchItems("");
	}

	@Test(expected = InvalidText_Exception.class)
	public void searchItemsWhitespaceTest() throws InvalidText_Exception {
		mediatorClient.searchItems(" ");
	}

	@Test(expected = InvalidText_Exception.class)
	public void searchItemsTabTest() throws InvalidText_Exception {
		mediatorClient.searchItems("\t");
	}

	@Test(expected = InvalidText_Exception.class)
	public void searchItemsNewlineTest() throws InvalidText_Exception {
		mediatorClient.searchItems("\n");
	}
	
	
	@Test
	public void searchItemsResultTest() throws InvalidText_Exception{
		List<ItemView> result = mediatorClient.searchItems("Football");
		assertNotNull(result);
	}
	
	@Test
	public void searchItemsNoItemTest() throws InvalidText_Exception{
		List<ItemView> result = mediatorClient.searchItems("12345");
		assertNotNull(result);
		assertTrue(result.isEmpty());
	}
	
	@Test
	public void searchItemsOneItemTest() throws InvalidText_Exception{
		List<ItemView> result = mediatorClient.searchItems("Football");
		assertNotNull(result);
		assertEquals(1, result.size());
		
		ItemView item = result.get(0);
		assertEquals("Football", item.getDesc());
		assertEquals(5, item.getPrice());
		assertEquals("X2", item.getItemId().getProductId());
		assertEquals("A65_Supplier1", item.getItemId().getSupplierId());		
	}
	@Test
	public void searchItemsTwoItemsOrderedAlphabeticTest() throws InvalidText_Exception{
		List<ItemView> result = mediatorClient.searchItems("Tenis");
		assertNotNull(result);
		assertEquals(2, result.size());
		
		ItemView item1 = result.get(0);
		ItemView item2 = result.get(1);
		assertEquals("Tenis", item1.getDesc());
		assertEquals(10, item1.getPrice());
		assertEquals("Y1", item1.getItemId().getProductId());
		assertEquals("A65_Supplier2", item1.getItemId().getSupplierId());
		
		assertEquals("Tenis", item2.getDesc());
		assertEquals(10, item2.getPrice());
		assertEquals("Z3", item2.getItemId().getProductId());
		assertEquals("A65_Supplier3", item2.getItemId().getSupplierId());	
	}
	@Test
	public void searchItemsOrderedAlphabeticAndNumericTwoItemsTest() throws InvalidText_Exception{
		List<ItemView> result = mediatorClient.searchItems("Basketball");
		assertNotNull(result);
		assertEquals(2, result.size());
		
		ItemView item1 = result.get(0);
		ItemView item2 = result.get(1);
		assertEquals("Basketball", item1.getDesc());
		assertEquals(5, item1.getPrice());
		assertEquals("X1", item1.getItemId().getProductId());
		assertEquals("A65_Supplier2", item1.getItemId().getSupplierId());
		
		assertEquals("Basketball", item2.getDesc());
		assertEquals(10, item2.getPrice());
		assertEquals("X1", item2.getItemId().getProductId());
		assertEquals("A65_Supplier1", item2.getItemId().getSupplierId());	
	}
	
	
	
	

}