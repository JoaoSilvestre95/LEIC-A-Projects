package org.komparator.mediator.ws.it;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.assertNull;
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



public class BuyCartIT extends BaseIT{

	
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
	public void setUp() throws BadProductId_Exception, BadProduct_Exception, InvalidCartId_Exception, InvalidItemId_Exception, InvalidQuantity_Exception, NotEnoughItems_Exception{
		
		mediatorClient.clear();
					
			ProductView product = new ProductView();
			product.setId("X1");
			product.setDesc("Basketball");
			product.setPrice(10);
			product.setQuantity(10);
			supplierClients.get(0).createProduct(product);
			
			ProductView product2 = new ProductView();
			product2.setId("Y2");
			product2.setDesc("Shorts");
			product2.setPrice(5);
			product2.setQuantity(20);
			supplierClients.get(1).createProduct(product2);
			
			ProductView product3 = new ProductView();
			product3.setId("Z3");
			product3.setDesc("Shorts");
			product3.setPrice(5);
			product3.setQuantity(20);
			supplierClients.get(1).createProduct(product3);
			
			

			ItemIdView itemid = new ItemIdView();
			itemid.setProductId("X1");
			itemid.setSupplierId("A65_Supplier1");
			mediatorClient.addToCart("cart1", itemid, 8);
			mediatorClient.addToCart("cart2", itemid, 8);
			mediatorClient.addToCart("cart3", itemid, 8);
			
			ItemIdView itemid2 = new ItemIdView();
			itemid2.setProductId("Y2");
			itemid2.setSupplierId("A65_Supplier2");
			mediatorClient.addToCart("cart2", itemid2, 1);;

		
	}
	
	@After
	public void tearDown() {
		mediatorClient.clear();
	}	
	
	
	//Input Tests
	@Test(expected = InvalidCartId_Exception.class)
	public void BuyCartNullCartIdTest() throws InvalidText_Exception, EmptyCart_Exception, InvalidCartId_Exception, InvalidCreditCard_Exception{
		mediatorClient.buyCart(null,"4024007102923926");
	}
	
	@Test(expected = InvalidCartId_Exception.class)
	public void BuyCartEmptyStringCartIdTest() throws InvalidText_Exception, EmptyCart_Exception, InvalidCartId_Exception, InvalidCreditCard_Exception{
		mediatorClient.buyCart("","4024007102923926");
	}
	
	@Test(expected = InvalidCartId_Exception.class)
	public void BuyCartBlankSpacesCartIdTest() throws InvalidText_Exception, EmptyCart_Exception, InvalidCartId_Exception, InvalidCreditCard_Exception{
		mediatorClient.buyCart("   ","4024007102923926");
	}
	
	@Test(expected = InvalidCartId_Exception.class)
	public void BuyCartNewLineCartIdTest() throws InvalidText_Exception, EmptyCart_Exception, InvalidCartId_Exception, InvalidCreditCard_Exception{
		mediatorClient.buyCart("\n","4024007102923926");
	}
	
	@Test(expected = InvalidCartId_Exception.class)
	public void BuyCartTabCartIdTest() throws InvalidText_Exception, EmptyCart_Exception, InvalidCartId_Exception, InvalidCreditCard_Exception{
		mediatorClient.buyCart("\t","4024007102923926");
	}
	@Test(expected = InvalidCreditCard_Exception.class)
	public void BuyCartNullCreditCardTest() throws InvalidText_Exception, EmptyCart_Exception, InvalidCartId_Exception, InvalidCreditCard_Exception{
		mediatorClient.buyCart("cart1",null);
	}
	
	@Test(expected = InvalidCreditCard_Exception.class)
	public void BuyCartEmptyStringCreditCardTest() throws InvalidText_Exception, EmptyCart_Exception, InvalidCartId_Exception, InvalidCreditCard_Exception{
		mediatorClient.buyCart("cart1","");
	}
	
	@Test(expected = InvalidCreditCard_Exception.class)
	public void BuyCartBlankSpacesCreditCardTest() throws InvalidText_Exception, EmptyCart_Exception, InvalidCartId_Exception, InvalidCreditCard_Exception{
		mediatorClient.buyCart("cart1","     ");
	}
	
	@Test(expected = InvalidCreditCard_Exception.class)
	public void BuyCartNewLineCreditCardTest() throws InvalidText_Exception, EmptyCart_Exception, InvalidCartId_Exception, InvalidCreditCard_Exception{
		mediatorClient.buyCart("cart1","\n");
	}
	
	@Test(expected = InvalidCreditCard_Exception.class)
	public void BuyCartTabCreditCardTest() throws InvalidText_Exception, EmptyCart_Exception, InvalidCartId_Exception, InvalidCreditCard_Exception{
		mediatorClient.buyCart("cart1","\t");
	}
	
	// main tests
	
	
		@Test
		public void buyCartRegisterHistoryTest() throws EmptyCart_Exception, InvalidCartId_Exception, InvalidCreditCard_Exception{
		
			mediatorClient.buyCart("cart1","4024007102923926");
			List<ShoppingResultView> shopList = mediatorClient.shopHistory();
			assertEquals(1,shopList.size());
			
		}
		
		@Test
		public void buyCartCompleteTest() throws EmptyCart_Exception, InvalidCartId_Exception, InvalidCreditCard_Exception{
			
			ShoppingResultView shop = mediatorClient.buyCart("cart1","4024007102923926");
			assertEquals(Result.COMPLETE,shop.getResult());
			
		}
		
		@Test
		public void buyCartPartialTest() throws EmptyCart_Exception, InvalidCartId_Exception, InvalidCreditCard_Exception{
			
			mediatorClient.buyCart("cart1", "4024007102923926");
			ShoppingResultView shop2 = mediatorClient.buyCart("cart2", "4024007102923926");
			assertEquals(Result.PARTIAL,shop2.getResult());
			
		}
		@Test
		public void buyCartEmptyTest() throws EmptyCart_Exception, InvalidCartId_Exception, InvalidCreditCard_Exception{
			
			mediatorClient.buyCart("cart1", "4024007102923926");
			ShoppingResultView shop2 = mediatorClient.buyCart("cart3", "4024007102923926");
			assertEquals(Result.EMPTY,shop2.getResult());
		}
		
		//4024007102923926
		
		@Test(expected = InvalidCartId_Exception.class)
		public void InexistentCartTest() throws EmptyCart_Exception, InvalidCartId_Exception, InvalidCreditCard_Exception{
			
			ShoppingResultView shop = mediatorClient.buyCart("leeeeeeeeel", "4024007102923926");	
		}	
}
