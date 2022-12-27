#include "supermarket.h"

int createSuperMarket(Supermarket* pSupermarket)
{
	printf("Enter supermarket name\n");
	pSupermarket->marketName = getNameFromUser(MAX_SIZE);
	if (!pSupermarket->marketName)
	{
		return 0;
	}
	printAddressInstructions();
	pSupermarket->marketAddress = *initAddress();
	if (!&pSupermarket->marketAddress)
	{
		return 0;
	}
	pSupermarket->customerArr = NULL;
	pSupermarket->customerArrSize = 0;
	pSupermarket->productArr = NULL;
	pSupermarket->productArrSize = 0;
	return 1;
}

void printMarket(const Supermarket* pSupermarket)
{
	printf("Market name: %s | ", pSupermarket->marketName);
	printAddress(&pSupermarket->marketAddress);
	printf("There are %d product(s)\n", pSupermarket->productArrSize);
	printf("Product Name ------------ | BARCODE | Type  -------- | Price ------ | Stock \n");
	printf("----------------------------------------------------------------------------\n");
	printMarketProducts(pSupermarket);
	printf("There are %d listed customer(s)\n", pSupermarket->customerArrSize);
	printMarketCustomers(pSupermarket);
}

void addProduct(Supermarket* pSupermarket)
{
	char* barcode = getBarcodeFromUser(); // malloc barcode
	if (!barcode)
	{
		return; //  prints errors inside
	}
	Product* isProductExist = checkProductExists(pSupermarket, barcode);
	if (!isProductExist)
	{
		Product* newProduct = createNewProduct(barcode); // malloc product
		if (!newProduct)
		{
			return;
		}
		int reallocSuccess = addProductHelper(pSupermarket, newProduct);
		if (!reallocSuccess)
		{
			freeProduct(newProduct); // free product
		}
	}
	else
	{
		addAmountToExistingProduct(isProductExist);
	}
	free(barcode); // free barcode
}

int addProductHelper(Supermarket* pSupermarket, Product* pProduct)
{
	int newArrSize = pSupermarket->productArrSize + 1;
	Product** newProductArr = (Product**)realloc(pSupermarket->productArr, newArrSize * sizeof(Product*));
	if (!newProductArr)
	{
		printf("MEMORY ERROR: Could not add product\n");
		return 0;
	}
	newProductArr[newArrSize - 1] = pProduct;
	pSupermarket->productArrSize++;
	pSupermarket->productArr = newProductArr;
	return 1;
}

void addCustomer(Supermarket* pSupermarket)
{
	printf("Please enter customer name to add\n");
	char tempCustomerName[MAX_SIZE]; // local
	if (!myGets(tempCustomerName, MAX_SIZE))
	{
		printf("fgets Error\n");
		return;
	}
	Customer* isCustomerExist = checkCustomerExists(pSupermarket, tempCustomerName);
	if (!isCustomerExist)
	{
		Customer* newCustomer = createNewCustomer(tempCustomerName); // malloc customer
		if (!newCustomer)
		{
			return;
		}
		printf("Adding customer: %s\n", tempCustomerName);
		int reallocSuccess = addCustomerHelper(pSupermarket, newCustomer); // add new customer
		if (!reallocSuccess)
		{
			printf("ERROR: Could not add customer\n");
			freeTempCustomer(newCustomer); // free customer
		}
		return;
	}
	printf("Error: Customer with this name already exists, returning\n");
}

int addCustomerHelper(Supermarket* pSupermarket, Customer* pCustomer)
{
	int newArrSize = pSupermarket->customerArrSize + 1;
	Customer* newCustomerArr = (Customer*)realloc(pSupermarket->customerArr, newArrSize * sizeof(Customer));
	if (!newCustomerArr)
	{
		printf("MEMORY ERROR: Could not add customer\n");
		return 0;
	}
	newCustomerArr[newArrSize - 1] = *pCustomer;
	pSupermarket->customerArrSize++;
	pSupermarket->customerArr = newCustomerArr;
	return 1;
}

void startShopping(Supermarket* pSupermarket)
{
	int isValidMarket = checkValidMarket(pSupermarket);
	if (!isValidMarket)
	{
		return; // prints errors inside
	}
	printMarket(pSupermarket);
	printf("Please enter existing customer name to start shopping\n");
	char tempCustomerName[MAX_SIZE];
	if (!myGets(tempCustomerName, MAX_SIZE))
	{
		printf("fgets Error\n");
		return;
	}
	Customer* isCustomerExist = checkCustomerExists(pSupermarket, tempCustomerName);
	if (!isCustomerExist)
	{
		printf("Error: Customer doesnt exist, returning\n");
	}
	else
	{
		customerShopping(pSupermarket, isCustomerExist); // start customer shopping
	}
}

void customerShopping(Supermarket* pSupermarket, const Customer* pCustomer)
{
	int isEmptyMarket = isSupermarketEmpty(pSupermarket);
	if (isEmptyMarket)
	{
		printf("Error: Market out of stock! returning\n");
		return;
	}
	Product* isProductExist = getExistingProductFromUser(pSupermarket);
	if (!isProductExist)
	{
		printf("MEMORY ERROR\n");
		return;
	}
	int amount = getAmountToBuyFromUser(isProductExist);
	if (amount != 0)
	{
		int isAdded = addItemToCart(pCustomer->cart, isProductExist, amount);
		if (!isAdded)
		{
			return; // adding failed - prints error inside
		}
	}
	printf("Would you like to continue shopping?\n");
	int proceedShopping = askUserToContinue();
	if (proceedShopping)
	{
		customerShopping(pSupermarket, pCustomer);
	}
}

void printMarketProducts(const Supermarket* pSupermarket)
{
	for (int i = 0; i < pSupermarket->productArrSize; i++)
	{
		printProduct(pSupermarket->productArr[i]);
	}
	printf("\n");
}
Product* getExistingProductFromUser(const Supermarket* pSupermarket)
{
	Product* isProductExist = NULL;
	do {
		char* barcode = getBarcodeFromUser(); // malloc
		isProductExist = checkProductExists(pSupermarket, barcode);
		if (!isProductExist)
		{
			printf("Error: Barcode does not exist! please enter an existing one from the list:\n\n");
			printMarketProducts(pSupermarket);
			free(barcode); // free
		}
	} while (!isProductExist);
	return isProductExist;
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
	int isEmptyMarket = isSupermarketEmpty(pSupermarket);
	if (isEmptyMarket)
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
	printMarketCustomers(pSupermarket);
	printf("Please enter an existing customer name:\n");
	char tempCustomerName[MAX_SIZE];
	if (!myGets(tempCustomerName, MAX_SIZE))
	{
		printf("fgets Error\n");
		return;
	}
	Customer* isCustomerExist = checkCustomerExists(pSupermarket, tempCustomerName);
	if (!isCustomerExist)
	{
		printf("Error: customer with this name does not exist, returning to main menu\n");
		return;
	}
	Shoppingcart* pCart = isCustomerExist->cart;
	if (pCart->shoppingCartSize == 0)
	{
		printf("Error: customer has no items in his cart yet!\n");
		return;
	}
	printf("Printing customer %s cart:\n", isCustomerExist->name);
	printShoppingCart(pCart);
	printf("Price of all items in cart: %.2lf\n", calcShoppingCart(pCart));
}

void printMarketCustomers(const Supermarket* pSupermarket)
{
	for (int i = 0; i < pSupermarket->customerArrSize; i++)
	{
		printf("%d: ", i + 1);
		printCustomer(&pSupermarket->customerArr[i]);
	}
	printf("\n");
}

void customerCheckout(const Supermarket* pSupermarket)
{
	if (pSupermarket->customerArrSize == 0)
	{
		printf("Error: No customers exist yet\n");
		return;
	}
	printf("Printing existing customers:\n");
	printMarketCustomers(pSupermarket);
	printf("Please enter a customer name to checkout\n");
	char tempCustomerName[MAX_SIZE];
	if (!myGets(tempCustomerName, MAX_SIZE))
	{
		printf("fgets Error\n");
		return;
	}
	Customer* isCustomerExist = checkCustomerExists(pSupermarket, tempCustomerName); // doesnt malloc
	if (!isCustomerExist)
	{
		printf("Error: No such customer exists, returning to main menu\n");
		return;
	}
	printAndReturnCart(isCustomerExist->cart);
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

Product* checkProductExists(const Supermarket* pSupermarket, const char* productName)
{
	for (int i = 0; i < pSupermarket->productArrSize; i++)
	{
		int equal = strcmp(pSupermarket->productArr[i]->barcode, productName);
		if (equal == 0)
		{
			return pSupermarket->productArr[i];
		}
	}
	return NULL;
}

Customer* checkCustomerExists(const Supermarket* pSupermarket, const char* pCustomerName)
{
	for (int i = 0; i < pSupermarket->customerArrSize; i++)
	{
		int equal = strcmp(pSupermarket->customerArr[i].name, pCustomerName);
		if (equal == 0)
		{
			return &pSupermarket->customerArr[i];
		}
	}
	return NULL;
}

void exitMarket(Supermarket* pSupermarket)
{
	printf("\nEXITING MARKET\n");
	for (int i = 0; i < pSupermarket->customerArrSize; i++)
	{
		Shoppingcart* pCart = pSupermarket->customerArr[i].cart;
		if (pCart->shoppingCartSize > 0)
		{
			printf("\nCustomer %s payment\n", pSupermarket->customerArr[i].name);
			printShoppingCart(pCart);
			printf("Price: %.2lf\n", calcShoppingCart(pCart));
			printf("--------PAYMENT DONE--------\n\n");
		}
	}
	freeSuperMarket(pSupermarket);
	printf("\nBye bye!\n");
}

void freeSuperMarket(Supermarket* pSupermarket)
{
	free(pSupermarket->marketName); // name
	pSupermarket->marketName = NULL;
	freeAddress(&pSupermarket->marketAddress); // address sections
	for (int i = 0; i < pSupermarket->customerArrSize; i++)
	{
		freeCustomer(&pSupermarket->customerArr[i]);
	}
	free(pSupermarket->customerArr); // free customer arr
	pSupermarket->customerArr = NULL;
	for (int i = 0; i < pSupermarket->productArrSize; i++) // products
	{
		freeProduct(pSupermarket->productArr[i]);
	}
	free(pSupermarket->productArr);
	pSupermarket->productArr = NULL;
	pSupermarket = NULL;
}

