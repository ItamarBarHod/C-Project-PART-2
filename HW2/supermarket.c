#include "supermarket.h"

void createSuperMarket(Supermarket* pSupermarket)
{
	printf("Enter supermarket name\n");
	pSupermarket->marketName = getNameFromUser(MAX_SIZE);
	if (!pSupermarket->marketName)
	{
		return;
	}
	printAddressInstructions();
	pSupermarket->marketAddress = *getAddressData();
	if (!&pSupermarket->marketAddress)
	{
		return;
	}
	pSupermarket->customerArr = NULL;
	pSupermarket->customerArrSize = 0;
	pSupermarket->productArr = NULL;
	pSupermarket->productArrSize = 0;
}

void printMarket(const Supermarket* pSupermarket)
{
	printf("Market name: %s | ", pSupermarket->marketName);
	printAddress(&pSupermarket->marketAddress);
	printf("There are %d products\n", pSupermarket->productArrSize);
	printf("Product Name ------------ | BARCODE | Type  -------- | Price ------ | Stock \n");
	printf("----------------------------------------------------------------------------\n");
	for (int i = 0; i < pSupermarket->productArrSize; i++)
	{
		printProduct(pSupermarket->productArr[i]);
	}
	printf("\nThere are %d listed customers\n", pSupermarket->customerArrSize);
	if (pSupermarket->customerArrSize > 0)
	{
		printCustomers(pSupermarket);
	}
	printf("\n");
}

void addProduct(Supermarket* pSupermarket)
{
	Product* newProduct = createNewProduct(); // malloc
	if (!newProduct)
	{
		return;
	}
	Product* isProductExist = checkProductExists(pSupermarket, newProduct); // doesnt malloc
	if (!isProductExist)
	{
		printf("Adding product with barcode %s:\n", newProduct->barcode);
		int reallocSuccess = addProductHelper(pSupermarket, newProduct);
		if (!reallocSuccess)
		{
			freeProduct(newProduct); // free
		}
		return;
	}
	addAmountToExistingProduct(pSupermarket, newProduct);
	freeProduct(newProduct); // free
}

int addProductHelper(Supermarket* pSupermarket, Product* pProduct)
{
	insertProductData(pProduct);
	if (!pProduct->productName)
	{
		freeProduct(pProduct);
		return 0;
	}
	int arrSize = pSupermarket->productArrSize;
	Product** newProductArr = (Product**)realloc(pSupermarket->productArr, (arrSize + 1) * sizeof(Product*));
	if (!newProductArr)
	{
		printf("MEMORY ERROR!\n");
		return 0;
	}
	newProductArr[arrSize] = pProduct;
	pSupermarket->productArrSize++;
	pSupermarket->productArr = newProductArr;
	return 1;
}

void addAmountToExistingProduct(Supermarket* pSupermarket, const Product* pProduct)
{
	Product* ProdExists = checkProductExists(pSupermarket, pProduct);
	printf("Product with barcode %s already exists under the name: %s\n", ProdExists->barcode, ProdExists->productName);
	printf("Type amount to add to product:\n");
	int addAmount = (int)getNumberFromUser();
	int productPosition = getProductPos(pSupermarket, pProduct);
	pSupermarket->productArr[productPosition]->stock += addAmount;
}

void addCustomer(Supermarket* pSupermarket)
{
	printf("Please enter customer name to add\n");
	Customer* newCustomer = createNewCustomer(); // malloc
	if (!newCustomer)
	{
		return;
	}
	Customer* isCustomerExist = checkCustomerExists(pSupermarket, newCustomer);
	if (!isCustomerExist)
	{
		int reallocSuccess = addCustomerHelper(pSupermarket, newCustomer); // add new customer
		if (!reallocSuccess)
		{
			freeCustomer(newCustomer); // free
		}
		return;
	}
	printf("Error: Customer with this name already exists, returning\n");
	freeCustomer(newCustomer); // free
}

int addCustomerHelper(Supermarket* pSupermarket, Customer* pCustomer)
{
	int arrSize = pSupermarket->customerArrSize;
	Customer* newCustomerArr = (Customer*)realloc(pSupermarket->customerArr, (arrSize + 1) * sizeof(Customer));
	if (newCustomerArr == NULL)
	{
		printf("MEMORY ERROR!\n");
		return 0;
	}
	newCustomerArr[arrSize] = *pCustomer;
	pSupermarket->customerArrSize++;
	pSupermarket->customerArr = newCustomerArr;
	printf("Added customer: %s\n", pCustomer->name);
	return 1;
}

void customerShopping(Supermarket* pSupermarket)
{
	int isValidMarket = checkValidMarket(pSupermarket);
	if (!isValidMarket)
	{
		return; // prints errors inside
	}
	printMarket(pSupermarket);
	printf("Please enter existing customer name to start shopping\n");
	Customer* shoppingCustomer = createNewCustomer(); // malloc
	if (shoppingCustomer == NULL)
	{
		return;
	}
	Customer* isCustomerExist = checkCustomerExists(pSupermarket, shoppingCustomer);
	if (isCustomerExist == NULL)
	{
		printf("Error: Customer doesnt exist, returning\n");
		freeCustomer(shoppingCustomer); // free
		return;
	}
	customerShoppingHelper(pSupermarket, shoppingCustomer);
	freeCustomer(shoppingCustomer); // free
}

void customerShoppingHelper(Supermarket* pSupermarket, const Customer* pCustomer)
{
	int isEmptySupermarket = isSupermarketEmpty(pSupermarket);
	if (isEmptySupermarket)
	{
		printf("Error: Market out of stock! returning\n");
		return; // will free
	}
	Product* isProductExist = getExistingProductFromUser(pSupermarket);
	if (!isProductExist)
	{
		printf("MEMORY ERROR\n");
		return; // will free
	}
	int amount = getAmountToBuyFromUser(pSupermarket, isProductExist);
	if (amount != 0)
	{
		putItemInCustomerCart(pSupermarket, pCustomer, isProductExist, amount);
	}
	printf("Would you like to continue shopping?\n");
	int proceedShopping = askUserToContinue();
	if (proceedShopping)
	{
		customerShoppingHelper(pSupermarket, pCustomer);
	}
}

int getAmountToBuyFromUser(const Supermarket* pSupermarket, const Product* pProduct)
{
	int productPos = getProductPos(pSupermarket, pProduct);
	int itemStock = pSupermarket->productArr[productPos]->stock;
	int amount;
	do {
		printf("Please enter the amount to buy, cant be more than %d (or less than 0)\n", itemStock);
		amount = (int)getNumberFromUser();
	} while (amount > itemStock || amount < 0);
	return amount;
}

void putItemInCustomerCart(Supermarket* pSupermarket, const Customer* pCustomer, const Product* pProduct, int amount)
{
	int customerPos = getCustomerPos(pSupermarket, pCustomer);
	Shoppingcart* pCart = pSupermarket->customerArr[customerPos].cart;
	int newStock = pProduct->stock - amount;
	printf("Product: %s (%s) stock left: %d\n", pProduct->productName, pProduct->barcode, newStock);
	int isItemExists = checkItemExists(pCart, pProduct);
	int itemPos = getItemPos(pCart, pProduct);
	if (isItemExists)
	{
		int itemPos = getItemPos(pCart, pProduct);
		pCart->itemsArr[itemPos]->amount += amount;
	}
	else
	{
		int reallocSuccess = addItemToCart(pCart, pProduct, amount);
		if (!reallocSuccess)
		{
			printf("Error: couldnt add item to shopping cart\n");
			return;
		}
	}
	int productPos = getProductPos(pSupermarket, pProduct);
	pSupermarket->productArr[productPos]->stock -= amount; // reduce from stock
}

Product* getExistingProductFromUser(const Supermarket* pSupermarket)
{
	Product* tempProduct = NULL;
	Product* isProductExist; // local
	do {
		Product* tempProduct = createNewProduct(); // malloc
		if (!tempProduct)
		{
			return NULL;
		}
		isProductExist = checkProductExists(pSupermarket, tempProduct);
		if (!isProductExist)
		{
			printf("Error: Barcode does not exist! please re-enter\n");
			freeProduct(tempProduct); // free
		}
	} while (!isProductExist);
	return isProductExist;
}

int checkBarcodeExists(const Supermarket* pSupermarket, const char* barcode)
{
	for (int i = 0; i < pSupermarket->productArrSize; i++)
	{
		int equal = strcmp(pSupermarket->productArr[i]->barcode, barcode);
		if (equal == 0)
		{
			return i;
		}
	}
	return -1;
}

int isSupermarketEmpty(const Supermarket* pSupermarket)
{
	int stockCounter = 0;
	for (int i = 0; i < pSupermarket->productArrSize; i++)
	{
		stockCounter += pSupermarket->productArr[i]->stock;
		if (stockCounter > 0) // not empty
		{
			return 0;
		}
	}
	return 1;
}

int checkValidMarket(const Supermarket* pSupermarket)
{
	if (pSupermarket->productArrSize == 0)
	{
		printf("Error: No products exist yet, returning\n");
		return 0;
	}
	int isEmptySupermarket = isSupermarketEmpty(pSupermarket);
	if (isEmptySupermarket)
	{
		printf("Error: No stock is available, returning\n");
		return 0;
	}
	if (pSupermarket->customerArrSize == 0)
	{
		printf("Error: No cusomters exist yet, returning\n");
		return 0;
	}
	return 1;
}

void printCustomerShoppingCart(const Supermarket* pSupermarket)
{
	printf("Printing existing customers:\n");
	printCustomers(pSupermarket);
	Customer* tempCustomer = createNewCustomer(); // malloc
	if (!tempCustomer)
	{
		return;
	}
	int customerPos = getCustomerPos(pSupermarket, tempCustomer);
	Customer* isCustomerExist = checkCustomerExists(pSupermarket, tempCustomer);
	if (!isCustomerExist)
	{
		printf("Error: customer with this name does not exist, returning to main menu\n");
		freeCustomer(tempCustomer); // free
		return;
	}
	Shoppingcart* pCart = pSupermarket->customerArr[customerPos].cart;
	if (pCart->shoppingCartSize == 0)
	{
		printf("Error: customer has no items in his cart yet!\n");
		freeCustomer(tempCustomer); // free
		return;
	}
	printf("Printing customer %s cart:\n", isCustomerExist->name);
	printCustomer(&pSupermarket->customerArr[customerPos]);
	printShoppingCart(pCart);
	printf("Price of all items in cart: %.2lf\n", calcShoppingCart(pCart));
	freeCustomer(tempCustomer); // free
}

void printCustomers(const Supermarket* pSupermarket)
{
	for (int i = 0; i < pSupermarket->customerArrSize; i++)
	{
		printf("%d: ", i + 1);
		printCustomer(&pSupermarket->customerArr[i]);
	}
}

void customerCheckout(const Supermarket* pSupermarket)
{
	if (pSupermarket->customerArrSize == 0)
	{
		printf("Error: No customers exist yet\n");
		return;
	}
	printf("Printing existing customers:\n");
	printCustomers(pSupermarket);
	Customer* tempCustomer = createNewCustomer(); // malloc
	if (!tempCustomer)
	{
		return;
	}
	Customer* isCustomerExist = checkCustomerExists(pSupermarket, tempCustomer); // doesnt malloc
	if (!isCustomerExist)
	{
		printf("Error: No such customer exists, returning to main menu\n");
		freeCustomer(tempCustomer); // free
		return;
	}
	customerCheckoutHelper(pSupermarket, tempCustomer);
	freeCustomer(tempCustomer); // free
}

void customerCheckoutHelper(const Supermarket* pSupermarket, const Customer* pCustomer)
{
	int customerPos = getCustomerPos(pSupermarket, pCustomer); // already exists
	Shoppingcart* pCart = pSupermarket->customerArr[customerPos].cart;
	if (pCart->shoppingCartSize > 0)
	{
		printShoppingCart(pCart);
		printf("Paying! Price of to pay: %.2lf\n", calcShoppingCart(pCart));
		deleteShoppingCart(pCart);
		printf("Returned shopping cart!\n");
		printf("--------PAYMENT DONE--------\n");
		return;
	}
	// else no items in cart
	printf("Error: This customer has no items yet, returning to main menu\n");

}

void printProductType(const Supermarket* pSupermarket)
{
	if (pSupermarket->productArrSize == 0)
	{
		printf("Error: No products exist yet\n");
		return;
	}
	int type = getProductTypeFromUser();
	printf("\nPrinting product of type: %s\n\n", productTypes[type]);
	printf("Product Name ------------ | BARCODE | Type  -------- | Price ------ | Stock \n");
	printf("----------------------------------------------------------------------------\n");
	printProductTypeHelper(pSupermarket, type);
}

void printProductTypeHelper(const Supermarket* pSupermarket, int type)
{
	int counter = 0;
	for (int i = 0; i < pSupermarket->productArrSize; i++)
	{
		if (pSupermarket->productArr[i]->type == type)
		{
			printProduct(pSupermarket->productArr[i]);
			counter++;
		}
	}
	if (counter == 0)
	{
		printf("Error: No products of type %s exist yet\n", productTypes[type]);
	}
	printf("\n");
}

int getCustomerPos(const Supermarket* pSupermarket, const Customer* pCustomer)
{
	for (int i = 0; i < pSupermarket->customerArrSize; i++)
	{
		int equal = strcmp(pSupermarket->customerArr[i].name, pCustomer->name);
		if (equal == 0)
		{
			return i;
		}
	}
	return -1;
}

int getProductPos(const Supermarket* pSupermarket, const Product* pProduct)
{
	for (int i = 0; i < pSupermarket->productArrSize; i++)
	{
		int equal = strcmp(pSupermarket->productArr[i]->barcode, pProduct->barcode);
		if (equal == 0)
		{
			return i;
		}
	}
	return -1;
}

Product* checkProductExists(const Supermarket* pSupermarket, const Product* pProduct)
{
	for (int i = 0; i < pSupermarket->productArrSize; i++)
	{
		int equal = strcmp(pSupermarket->productArr[i]->barcode, pProduct->barcode);
		if (equal == 0)
		{
			return pSupermarket->productArr[i];
		}
	}
	return NULL;
}

Customer* checkCustomerExists(const Supermarket* pSupermarket, const Customer* pCustomer)
{
	for (int i = 0; i < pSupermarket->customerArrSize; i++)
	{
		int equal = strcmp(pSupermarket->customerArr[i].name, pCustomer->name);
		if (equal == 0)
		{
			return &pSupermarket->customerArr[i];
		}
	}
	return NULL;
}

void exitMarket(Supermarket* pSupermarket)
{
	for (int i = 0; i < pSupermarket->customerArrSize; i++)
	{
		if (pSupermarket->customerArr[i].cart->shoppingCartSize > 0)
		{
			printf("Customer %s payment\n", pSupermarket->customerArr[i].name);
			Shoppingcart* cart = pSupermarket->customerArr[i].cart;
			if (cart->shoppingCartSize > 0)
			{
				printShoppingCart(cart);
				printf("Price: %.2lf\n", calcShoppingCart(cart));
				printf("-----PAYMENT DONE-----\n\n");
			}
		}
	}
	deleteSuperMarket(pSupermarket);
}

void deleteSuperMarket(Supermarket* pSupermarket)
{
	free(pSupermarket->marketName); // name
	pSupermarket->marketName = NULL;
	freeAddress(&pSupermarket->marketAddress); // address sections
	for (int i = 0; i < pSupermarket->customerArrSize; i++) // customers and shopping items
	{
		freeCustomer(&pSupermarket->customerArr[i]);
	}
	free(pSupermarket->customerArr);
	pSupermarket->customerArr = NULL;
	for (int i = 0; i < pSupermarket->productArrSize; i++) // products
	{
		freeProduct(pSupermarket->productArr[i]);
	}
	free(pSupermarket->productArr);
	pSupermarket->productArr = NULL;
}

