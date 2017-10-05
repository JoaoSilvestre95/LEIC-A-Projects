package org.komparator.mediator.ws.it;
import static org.junit.Assert.*;

import java.util.List;

import org.junit.After;
import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;
import org.komparator.mediator.ws.CartItemView;
import org.komparator.mediator.ws.CartView;
//import org.komparator.supplier.domain.Purchase;
import org.komparator.mediator.ws.InvalidCartId_Exception;
import org.komparator.mediator.ws.InvalidItemId_Exception;
import org.komparator.mediator.ws.InvalidQuantity_Exception;
import org.komparator.mediator.ws.ItemIdView;
import org.komparator.mediator.ws.ItemView;
import org.komparator.mediator.ws.NotEnoughItems_Exception;
import org.komparator.supplier.ws.BadProductId_Exception;
import org.komparator.supplier.ws.BadProduct_Exception;
import org.komparator.supplier.ws.ProductView;


public class AddToCartIT extends BaseIT{
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
	
	@Before
	public void setUp() throws BadProductId_Exception, BadProduct_Exception{
		mediatorClient.clear();
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
			product.setId("Y1");
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
	
	// input tests
	// InvalidCartId_Exception, InvalidItemId_Exception, InvalidQuantity_Exception, NotEnoughItems_Exception
	
	@Test(expected = InvalidCartId_Exception.class)
	public void addToCartNullTest() throws InvalidItemId_Exception, InvalidCartId_Exception, InvalidQuantity_Exception, NotEnoughItems_Exception{
		ItemIdView itemId = new ItemIdView();
		itemId.setProductId("X1");
		itemId.setSupplierId("A65_Supplier1");
		mediatorClient.addToCart(null,itemId,3);
	}

	@Test(expected = InvalidCartId_Exception.class)
	public void addToCartEmptyTest() throws InvalidItemId_Exception, InvalidCartId_Exception, InvalidQuantity_Exception, NotEnoughItems_Exception{
		ItemIdView itemId = new ItemIdView();
		itemId.setProductId("X1");
		itemId.setSupplierId("A65_Supplier1");
		mediatorClient.addToCart("",itemId,3);
	}
	
	@Test(expected = InvalidCartId_Exception.class)
	public void addToCartBlankSpacesTest() throws InvalidItemId_Exception, InvalidCartId_Exception, InvalidQuantity_Exception, NotEnoughItems_Exception{
		ItemIdView itemId = new ItemIdView();
		itemId.setProductId("X1");
		itemId.setSupplierId("A65_Supplier1");
		mediatorClient.addToCart("  ",itemId,3);
	}
	
	
	@Test(expected = InvalidCartId_Exception.class)
	public void addToCartTabTest() throws InvalidItemId_Exception, InvalidCartId_Exception, InvalidQuantity_Exception, NotEnoughItems_Exception{
		ItemIdView itemId = new ItemIdView();
		itemId.setProductId("X1");
		itemId.setSupplierId("A65_Supplier1");
		mediatorClient.addToCart("\t",itemId,3);
	}
	
	@Test(expected = InvalidCartId_Exception.class)
	public void addToCartNewLineTest() throws InvalidItemId_Exception, InvalidCartId_Exception, InvalidQuantity_Exception, NotEnoughItems_Exception{
		ItemIdView itemId = new ItemIdView();
		itemId.setProductId("X1");
		itemId.setSupplierId("A65_Supplier1");
		mediatorClient.addToCart("\n",itemId,3);
	}
	
	@Test(expected = InvalidQuantity_Exception.class)
	public void addToCartZeroQuantityTest() throws InvalidItemId_Exception, InvalidCartId_Exception, InvalidQuantity_Exception, NotEnoughItems_Exception{
		ItemIdView itemId = new ItemIdView();
		itemId.setProductId("X1");
		itemId.setSupplierId("A65_Supplier1");
		mediatorClient.addToCart("idvalido",itemId,0);
	}
	
	@Test(expected = InvalidQuantity_Exception.class)
	public void addToCartNegativeQuantity() throws InvalidItemId_Exception, InvalidCartId_Exception, InvalidQuantity_Exception, NotEnoughItems_Exception{
		ItemIdView itemId = new ItemIdView();
		itemId.setProductId("X1");
		itemId.setSupplierId("A65_Supplier1");
		mediatorClient.addToCart("idvalido",itemId,-1);
	}
	
	@Test(expected = InvalidItemId_Exception.class)
	public void addToCartNullItemId() throws InvalidItemId_Exception, InvalidCartId_Exception, InvalidQuantity_Exception, NotEnoughItems_Exception{
		mediatorClient.addToCart("idvalido",null,3);
	}	
	
	@Test
	public void addOneItemToCartAllTest() throws InvalidCartId_Exception, InvalidItemId_Exception, InvalidQuantity_Exception, NotEnoughItems_Exception{
		ItemIdView itemIdView = new ItemIdView();
		itemIdView.setProductId("X1");
		itemIdView.setSupplierId("A65_Supplier1");
		mediatorClient.addToCart("cart1",itemIdView,3);
		List<CartView> cartList = mediatorClient.listCarts();	
		assertEquals(1, cartList.size());
		CartView cart = cartList.get(0);
		assertEquals("cart1", cart.getCartId());		
		List<CartItemView> items = cart.getItems();
		assertEquals(1, items.size());
		CartItemView item = items.get(0);
		assertEquals("X1", item.getItem().getItemId().getProductId());
		assertEquals("A65_Supplier1", item.getItem().getItemId().getSupplierId());
		assertEquals(3, item.getQuantity());
		assertEquals(10, item.getItem().getPrice());
		assertEquals("Basketball", item.getItem().getDesc());	
	}
	@Test
	public void addTwoItemSameCartTest() throws InvalidCartId_Exception, InvalidItemId_Exception, InvalidQuantity_Exception, NotEnoughItems_Exception{
		ItemIdView itemIdView1 = new ItemIdView();
		ItemIdView itemIdView2 = new ItemIdView();
		itemIdView1.setProductId("X1");
		itemIdView1.setSupplierId("A65_Supplier1");
		itemIdView2.setProductId("X2");
		itemIdView2.setSupplierId("A65_Supplier1");
		mediatorClient.addToCart("cart1",itemIdView1,3);
		mediatorClient.addToCart("cart1",itemIdView2,4);
		List<CartView> cartList = mediatorClient.listCarts();	
		assertEquals(1, cartList.size());
		CartView cart = cartList.get(0);
		assertEquals("cart1", cart.getCartId());		
		List<CartItemView> items = cart.getItems();
		assertEquals(2, items.size());
		assertEquals("X1", items.get(0).getItem().getItemId().getProductId());
		assertEquals("X2", items.get(1).getItem().getItemId().getProductId());
		assertEquals(3, items.get(0).getQuantity());
		assertEquals(4, items.get(1).getQuantity());
	}
	@Test
	public void addTwoItemDifferentCartTest() throws InvalidCartId_Exception, InvalidItemId_Exception, InvalidQuantity_Exception, NotEnoughItems_Exception{
		ItemIdView itemIdView1 = new ItemIdView();
		itemIdView1.setProductId("X1");
		itemIdView1.setSupplierId("A65_Supplier1");
		mediatorClient.addToCart("cart1",itemIdView1,2);
		mediatorClient.addToCart("cart2",itemIdView1,2);
		List<CartView> cartList = mediatorClient.listCarts();	
		assertEquals(2, cartList.size());
	}
	@Test
	public void addTwoSameItemSameCartSumTest() throws InvalidCartId_Exception, InvalidItemId_Exception, InvalidQuantity_Exception, NotEnoughItems_Exception{
		ItemIdView itemIdView1 = new ItemIdView();
		itemIdView1.setProductId("X1");
		itemIdView1.setSupplierId("A65_Supplier1");
		mediatorClient.addToCart("cart1",itemIdView1,5);
		mediatorClient.addToCart("cart1",itemIdView1,5);
		List<CartView> cartList = mediatorClient.listCarts();	
		assertEquals(1, cartList.size());
		CartView cart = cartList.get(0);
		assertEquals("cart1", cart.getCartId());		
		List<CartItemView> items = cart.getItems();
		assertEquals(1, items.size());
		assertEquals(10, items.get(0).getQuantity());
	}
	@Test(expected = NotEnoughItems_Exception.class)
	public void addOneItemExcedQtyCartTest() throws InvalidCartId_Exception, InvalidItemId_Exception, InvalidQuantity_Exception, NotEnoughItems_Exception{
		ItemIdView itemIdView1 = new ItemIdView();
		itemIdView1.setProductId("X1");
		itemIdView1.setSupplierId("A65_Supplier1");
		mediatorClient.addToCart("cart1",itemIdView1,11);
	}
	
	@Test(expected = NotEnoughItems_Exception.class)
	public void addTwoItemExcedQtyCartTest() throws InvalidCartId_Exception, InvalidItemId_Exception, InvalidQuantity_Exception, NotEnoughItems_Exception{
		ItemIdView itemIdView1 = new ItemIdView();
		itemIdView1.setProductId("X1");
		itemIdView1.setSupplierId("A65_Supplier1");
		mediatorClient.addToCart("cart1",itemIdView1,10);
		mediatorClient.addToCart("cart1",itemIdView1,1);
	}
	
}
