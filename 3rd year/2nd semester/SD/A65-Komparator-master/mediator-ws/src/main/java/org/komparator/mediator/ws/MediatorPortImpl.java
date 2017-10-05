package org.komparator.mediator.ws;

import javax.jws.HandlerChain;
import javax.jws.WebService;
import javax.xml.ws.WebServiceException;

import org.komparator.mediator.ws.cli.MediatorClient;
import org.komparator.mediator.ws.cli.MediatorClientException;
import org.komparator.supplier.ws.BadProductId_Exception;
import org.komparator.supplier.ws.BadQuantity_Exception;
import org.komparator.supplier.ws.BadText_Exception;
import org.komparator.supplier.ws.InsufficientQuantity_Exception;
import org.komparator.supplier.ws.ProductView;
import org.komparator.supplier.ws.cli.SupplierClient;
import org.komparator.supplier.ws.cli.SupplierClientException;

import pt.ulisboa.tecnico.sdis.ws.cli.CreditCardClient;
import pt.ulisboa.tecnico.sdis.ws.cli.CreditCardClientException;
import pt.ulisboa.tecnico.sdis.ws.uddi.UDDINaming;
import pt.ulisboa.tecnico.sdis.ws.uddi.UDDINamingException;
import pt.ulisboa.tecnico.sdis.ws.uddi.UDDIRecord;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.Comparator;
import java.util.Date;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.concurrent.atomic.AtomicInteger;

@WebService(
		endpointInterface = "org.komparator.mediator.ws.MediatorPortType", 
		wsdlLocation = "mediator.wsdl", 
		name = "MediatorWebService", 
		portName = "MediatorPort", 
		targetNamespace = "http://ws.mediator.komparator.org/", 
		serviceName = "MediatorService"
)
@HandlerChain(file = "/mediator-ws_handler-chain.xml")
public class MediatorPortImpl implements MediatorPortType{

	private static final String URLS = "http://localhost:8072/mediator-ws/endpoint";
	// end point manager
	private MediatorEndpointManager endpointManager;
	private List<CartView> carts = new ArrayList<CartView>();
	private List<ShoppingResultView> shopList = new ArrayList<ShoppingResultView>();
	
	//Ids from addToCartOperation
	private HashSet<String> addToCartIds = new HashSet<String>();
	//Ids and result from buyCartOperation
	private HashMap<String, ShoppingResultView> buyCartId = new HashMap<String, ShoppingResultView>();
	
	//Flag primary or secondary
	private boolean isPrimary = true;
	
	//Secondary Mediator Client
	private MediatorClient mediatorClient = null;
	/**
	 * Global purchase identifier counter. Uses lock-free thread-safe single
	 * variable.
	 */
	private int shoppingResultViewIdCounter = 0;

	public MediatorPortImpl(MediatorEndpointManager endpointManager) {
		this.endpointManager = endpointManager;
	}

	// Main operations -------------------------------------------------------

		
	@Override
	public List<ItemView> getItems(String productId) throws InvalidItemId_Exception{		
		if(productId == null) throwItemIdException("productId cannot be null!");
		productId = productId.trim();
		if (productId.length() == 0) throwItemIdException("productId cannot be empty or whitespace!");
		
		List<SupplierClient> listSupplier = this.getAllSuppliers();
		List<ItemView> items = new ArrayList<ItemView>();
		ProductView product = null;
		for(SupplierClient sp : listSupplier){
			try {
				product = sp.getProduct(productId);
				if(product != null)
					items.add(this.createItemView(product,sp));
			} catch (BadProductId_Exception e1) {
				e1.printStackTrace();
			}
		}
		Collections.sort(items, new Comparator<ItemView>(){
			@Override
			public int compare(ItemView x, ItemView y){
				return x.getPrice() - y.getPrice();
			}
		});		
		return items;
	}
	
	
	@Override
	synchronized public List<ItemView> searchItems(String descText) throws InvalidText_Exception {
		List<SupplierClient> listSupplier = this.getAllSuppliers();
		List<ItemView> items = new ArrayList<ItemView>();
		List<ProductView> products = null;
		//test description
		if(descText == null)
			throwInvalidTextException("Text cannot be null!");
		descText = descText.trim();
		if (descText.length() == 0)
			throwInvalidTextException("Text cannot be empty or whitespace!");
		
		for(SupplierClient sp : listSupplier){
			try {
				synchronized(sp){
					try {
						products = sp.searchProducts(descText);
					} catch (BadText_Exception e) {
						e.printStackTrace();
					}
					for(ProductView p : products){
						items.add(this.createItemView(p, sp));
					}
				}
			} catch (BadProductId_Exception e) {
				e.printStackTrace();
			}
		}
		Collections.sort(items, new Comparator<ItemView>(){
			@Override
	        public int compare(ItemView x, ItemView y) {
	            String p1 = x.getItemId().getProductId();
	            String p2 = y.getItemId().getProductId();
	            int comp = p1.compareTo(p2);

	            if (comp != 0) {
	               return comp;
	            } else {
	               return x.getPrice() - y.getPrice();
	            }
	    }});	
		return items;
	}
	
	
	
	@Override
	synchronized public ShoppingResultView buyCart(String operationId, String cartId, String creditCardNr) throws EmptyCart_Exception, InvalidCartId_Exception, InvalidCreditCard_Exception {
		if(operationId != null){
			if(buyCartId.containsKey(operationId)){
				return this.buyCartId.get(operationId);
			}
		}
			
		CreditCardClient credit = this.getCreditCard();
		SupplierClient supplier = null;
		ShoppingResultView shopping = null;
		boolean flag = false;
		//cartID test
		if(cartId == null) throwInvalidCartIdException("Text cannot be null!");
		cartId = cartId.trim();
		if (cartId.length() == 0) throwInvalidCartIdException("Text cannot be empty or whitespace!");
		//creditCardNr test
		if(creditCardNr == null) throwInvalidCreditCardId("cartId cannot be null!");
		creditCardNr = creditCardNr.trim();
		if (creditCardNr.length() == 0)	throwInvalidCreditCardId("creditCardNr cannot be empty or whitespace!");		
		
		if(credit.validateNumber(creditCardNr)){					
			for(CartView cart : this.carts){
				if(cart.getCartId().equals(cartId)){
					shopping = new ShoppingResultView();	
					flag = true;
					for(CartItemView item : cart.getItems()){		
						supplier = getSupplierByItem(item.getItem());
						synchronized(supplier){
							try {
								supplier.buyProduct(item.getItem().getItemId().getProductId(), item.getQuantity());
								registerPurchase(item, shopping);
							} catch (BadProductId_Exception e) {
								this.registerDropped(item, shopping);
								continue;
							} catch (BadQuantity_Exception e) {
								this.registerDropped(item, shopping);
								continue;
							} catch (InsufficientQuantity_Exception e) {
								this.registerDropped(item, shopping);
								continue;
							}
						}
					}
				}			
			}
			if(flag == false)
				throwInvalidCartIdException("No cart id exists");
			shopping.setId(this.generateShoppingResultViewId());
			this.addToHistory(shopping);
		}
		else{
			throwInvalidCreditCardId("Invalid CardId!");
		}
		this.buyCartId.put(operationId, shopping);
		this.updateShopHistory(operationId, this.shopHistory());
		this.updateCart(operationId, this.carts);
		return shopping;
	}
	
	@Override
	public void addToCart(String operationId, String cartId, ItemIdView itemId, int itemQty) throws InvalidCartId_Exception, InvalidItemId_Exception, InvalidQuantity_Exception, NotEnoughItems_Exception {
		if(operationId != null){
			if(addToCartIds.contains(operationId))
				return;
		}
		
		ItemView item = null;
		SupplierClient supplierItem = null;		
		ProductView product = null;
		//cartID test
		if(cartId == null) throwInvalidCartIdException("cartId cannot be null!");
		cartId = cartId.trim();
		if (cartId.length() == 0) throwInvalidCartIdException("cartId cannot be empty or whitespace!");
		//itemID test
		if(itemId == null) throwInvalidItemIdException("Invalid ItemID");
		//quantity test
		if (itemQty <= 0) throwInvalidQuantityException("Quantity must be a positive number!");
		//testNullSupplierId
		if (itemId.getSupplierId() == null) throwInvalidItemIdException("SupplierId must not be null!");
		//testEmptySupplierId
		if (itemId.getSupplierId().trim().length() == 0) throwInvalidItemIdException("SupplierId must not be empty!");
		//quantity available test		
		
		supplierItem = this.getSupplierClient(itemId.getSupplierId());
		if(supplierItem == null)
			throwInvalidItemIdException("Supplier Null!");		
		
		try {
			product = supplierItem.getProduct(itemId.getProductId());
		} catch (BadProductId_Exception e1) {
			e1.printStackTrace();
		}					
		if(product != null){
			if(itemQty > product.getQuantity())
				throwNotEnoughItemsException("To many Items!!");			
		}
		else 
			throwInvalidItemIdException("Product Null!");
		
		
		//addToExistCart
		for(CartView cart : this.carts){
			if(cart.getCartId().equals(cartId)){
				for(CartItemView cartView : cart.getItems()){
					if(cartView.getItem().getItemId().getProductId().equals(itemId.getProductId()) && cartView.getItem().getItemId().getSupplierId().equals(itemId.getSupplierId())){
						if((cartView.getQuantity() + itemQty) > product.getQuantity())
							throwNotEnoughItemsException("To many Items!!");
						cartView.setQuantity(cartView.getQuantity() + itemQty);
						return;
					}
				}				
				try {
					item = this.createItemView(product, supplierItem);
				} catch (BadProductId_Exception e) {
					e.printStackTrace();
				}				
				cart.getItems().add(createCartItemView(item, itemQty));
				return;
			}			
		}
		//Create new Cart
		try {
			item = this.createItemView(supplierItem.getProduct(itemId.getProductId()), supplierItem);
		} catch (BadProductId_Exception e) {
			e.printStackTrace();
		}
		carts.add(this.createCartView(item, cartId, itemQty));	
		this.addToCartIds.add(operationId);
		this.updateCart(operationId, this.carts);
	}
	
	public void imAlive(){
		if(endpointManager.getIsPrimary()){}
			//Do nothing
		else {
			LifeProof.date = new Date();
			System.out.println("Secundary Mediator: Saving Time!");
			System.out.println("Secundary Mediator: Time: " + LifeProof.date.getTime());
		}			
	}
	
	public void updateShopHistory(String operationId, List<ShoppingResultView> shopHistory){
		if(getIsPrimary()){
			if(mediatorClient == null){
				try {
					mediatorClient = new MediatorClient(URLS);
				} catch (MediatorClientException e1) {
					System.out.println("Cannot create mediator client!");
				}
			}
			if(Integer.parseInt(endpointManager.getWsI()) == 1){
				try {
					mediatorClient.updateShopHistory(operationId, this.shopHistory());
				} catch (WebServiceException e) {
					System.out.println("Secondary Mediator not Online");
				}
			}
		}
		else{
			this.setShopHistory(shopHistory);
			this.buyCartId.put(operationId, shopHistory.get(-1));
		}		
	}

	public void updateCart(String operationId, List<CartView> cartList){
		if(getIsPrimary()){
			if(mediatorClient == null){
				try {
					mediatorClient = new MediatorClient(URLS);
				} catch (MediatorClientException e1) {
					System.out.println("Cannot create mediator client!");
				}
			}
			if(Integer.parseInt(endpointManager.getWsI()) == 1){
				try {
					mediatorClient.updateCart(operationId, this.carts);
				} catch (WebServiceException e) {
					System.out.println("Secondary Mediator not Online");
				}
			}
		}
		else{
			this.setCartList(cartList);
			this.addToCartIds.add(operationId);
		}		
	}
	
    
	// Auxiliary operations --------------------------------------------------	
	
	@Override
	public String ping(String name) {
		List<SupplierClient> listSupplier = getAllSuppliers();
		StringBuilder builder = new StringBuilder();
		for(SupplierClient i : listSupplier){
			builder.append(i.ping(name));
		}		
		return builder.toString();
	}
	
	private String generateShoppingResultViewId() {
		// relying on AtomicInteger to make sure assigned number is unique
		this.shoppingResultViewIdCounter++;
		return Integer.toString(shoppingResultViewIdCounter);
	}

	@Override
	public List<CartView> listCarts(){
		return this.carts;		
	}
	
	@Override
	public void clear(){
		this.carts.clear();
		this.shopList.clear();
		this.shoppingResultViewIdCounter = 0;
		List<SupplierClient> listSupplier = getAllSuppliers();
		for(SupplierClient i : listSupplier){
			i.clear();
		}	
		
	}
	
	public SupplierClient getSupplierByItem(ItemView item){
		List<SupplierClient> listSupplier = getAllSuppliers();
		for(SupplierClient i : listSupplier){
			if(i.getWsName().equals(item.getItemId().getSupplierId())){
				return i;
			}
		}
		return null;
	}
	
	public SupplierClient getSupplierClient(String wsname){
		List<SupplierClient> listSupplier = new ArrayList<SupplierClient>();
		UDDINaming naming = endpointManager.getUddiNaming();
		Collection<UDDIRecord> collection = null;
		try{
			collection = naming.listRecords(wsname);
		}catch(UDDINamingException e){}
		for(UDDIRecord record : collection){
			try{
				SupplierClient supplier = new SupplierClient(record.getUrl(), record.getOrgName());
				listSupplier.add(supplier);
			}catch(SupplierClientException e){}
		}
		return listSupplier.get(0);
	}
	
	public List<SupplierClient> getAllSuppliers(){
		List<SupplierClient> listSupplier = new ArrayList<SupplierClient>();
		UDDINaming naming = endpointManager.getUddiNaming();
		Collection<UDDIRecord> collection = null;
		try{
			collection = naming.listRecords("A65_Supplier%");
		}catch(UDDINamingException e){}
		
		for(UDDIRecord record : collection){
			try{
				SupplierClient supplier = new SupplierClient(record.getUrl(), record.getOrgName());
				listSupplier.add(supplier);
			}catch(SupplierClientException e){}
		}
		return listSupplier;
	}
	
	public CreditCardClient getCreditCard(){
		UDDINaming naming = endpointManager.getUddiNaming();
		CreditCardClient card = null;
		String collection = null;
		try{
			collection = naming.lookup("CreditCard");
		}catch(UDDINamingException e){}
		try {
			card =  new CreditCardClient(collection);
		} catch (CreditCardClientException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return card;
	}
	
	@Override
	public List<ShoppingResultView> shopHistory(){
		return this.shopList;
	}
	
	public void addToHistory(ShoppingResultView r){
		if(r.getDroppedItems().size() == 0)
			r.setResult(Result.COMPLETE);		
		else if(r.getPurchasedItems().size() == 0)
			r.setResult(Result.EMPTY);
		else if(r.getDroppedItems().size() > 0)
			r.setResult(Result.PARTIAL);
		shopList.add(0, r);
	}
	public void registerDropped(CartItemView item, ShoppingResultView shopping){
		shopping.getDroppedItems().add(item);		
	}
	
	public void registerPurchase(CartItemView item, ShoppingResultView shopping){
		shopping.getPurchasedItems().add(item);
		shopping.setTotalPrice(shopping.getTotalPrice() + (item.getQuantity()*item.getItem().getPrice()));
	}
	
	public void setIsPrimary(boolean flag){
		this.isPrimary = flag;
	}
	
	public boolean getIsPrimary(){
		return this.isPrimary;
	}
	
	
	
	// View helpers -----------------------------------------------------
	
    public ItemView createItemView(ProductView prod, SupplierClient client) throws BadProductId_Exception{
    	
    	String wsName = client.getWsName();
    	String id = prod.getId();
    	
    	ItemIdView i = new ItemIdView();
    	i.setProductId(id);
    	i.setSupplierId(wsName);
    	
    	int price = prod.getPrice();
    	String desc = prod.getDesc();
    	
    	ItemView item = new ItemView();
    	
    	item.setItemId(i);
    	item.setPrice(price);
    	item.setDesc(desc);
    	
    	return item;
    }
    public CartItemView createCartItemView(ItemView item, int quantity){
    	CartItemView cart = new CartItemView();
    	cart.setItem(item);
    	cart.setQuantity(quantity);
    	return cart;
    }
    
    
    public CartView createCartView(ItemView item, String cartId, int quantity){
    	//Creates new CartView
    	CartView cartView = new CartView();
    	CartItemView cart = this.createCartItemView(item, quantity);
    	cartView.setCartId(cartId);
    	cartView.getItems().add(cart);    	
    	return cartView;
    } 
    
    
    public void setShopHistory(List<ShoppingResultView> shopList){
    	this.shopList = shopList;
    }

    public void setCartList(List<CartView> cartList){
    	this.carts = cartList;
    }
    
  

    
    
	// Exception helpers -----------------------------------------------------

    private void throwInvalidTextException(final String message) throws InvalidText_Exception {
		InvalidText faultInfo = new InvalidText();
		faultInfo.message = message;
		throw new InvalidText_Exception(message, faultInfo);
	}
    
    private void throwInvalidCreditCardId(final String message) throws InvalidCreditCard_Exception {
		InvalidCreditCard faultInfo = new InvalidCreditCard();
		faultInfo.message = message;
		throw new InvalidCreditCard_Exception(message, faultInfo);
	}
    private void throwInvalidCartIdException(final String message) throws InvalidCartId_Exception {
		InvalidCartId faultInfo = new InvalidCartId();
		faultInfo.message = message;
		throw new InvalidCartId_Exception(message, faultInfo);
	}
    private void throwItemIdException(final String message) throws InvalidItemId_Exception {
    	InvalidItemId faultInfo = new InvalidItemId();
		faultInfo.message = message;
		throw new InvalidItemId_Exception(message, faultInfo);
	}
    private void throwInvalidQuantityException(final String message) throws InvalidQuantity_Exception {
    	InvalidQuantity faultInfo = new InvalidQuantity();
		faultInfo.message = message;
		throw new InvalidQuantity_Exception(message, faultInfo);
	}
    private void throwInvalidItemIdException(final String message) throws InvalidItemId_Exception {
    	InvalidItemId faultInfo = new InvalidItemId();
		faultInfo.message = message;
		throw new InvalidItemId_Exception(message, faultInfo);
	}
    private void throwNotEnoughItemsException(final String message) throws NotEnoughItems_Exception{
    	NotEnoughItems faultInfo = new NotEnoughItems();
		faultInfo.message = message;
		throw new NotEnoughItems_Exception(message, faultInfo);
	}
    
    
}
