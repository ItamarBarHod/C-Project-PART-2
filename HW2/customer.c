#include "customer.h"

void printCustomer(const Customer* pCustomer)
{
	if (pCustomer->cart->shoppingCartSize == 0)
	{
		printf("Customer name: %s --- shopping cart is empty!\n", pCustomer->name);
	}
	else
	{
		printf("Customer name: %s --- is currently doing shopping!\n", pCustomer->name);
	}
}

Customer* initCustomer()
{
	Customer* tempCustomer = (Customer*)malloc(sizeof(Customer)); // malloc
	if (!tempCustomer)
	{
		printf("Customer MEMORY ERROR\n");
		return NULL;
	}
	tempCustomer->cart = initShoppingCart(); // malloc
	if (!tempCustomer->cart)
	{
		printf("Customer MEMORY ERROR\n");
		freeTempCustomer(tempCustomer); // free
		return NULL;
	}
	tempCustomer->name = NULL;
	return tempCustomer;
}

Customer* createNewCustomer(char* customerName)
{
	if (strlen(customerName) == 0)
	{
		printf("ERROR: cant have enter as a customer\n");
		return NULL;
	}
	Customer* tempCustomer = initCustomer();
	if (!tempCustomer)
	{
		return NULL;
	}
	tempCustomer->name = _strdup(customerName); // malloc
	if (!tempCustomer->name)
	{
		printf("Customer MEMORY ERROR\n");
		freeTempCustomer(tempCustomer); // free
		return NULL;
	}
	return tempCustomer;
}

void printCustomerCartHelper(Customer* pCustomer)
{
	printf("Printing customer %s cart:\n", pCustomer->name);
	printShoppingCart(pCustomer->cart);
	printf("Price of all items in cart: %.2lf\n", calcShoppingCart(pCustomer->cart));
}

void freeTempCustomer(Customer* pCustomer)
{
	free(pCustomer->name);
	freeShoppingCart(pCustomer->cart);
	pCustomer->cart = NULL;
	free(pCustomer);
	pCustomer = NULL;
}

void freeCustomer(Customer* pCustomer)
{
	free(pCustomer->name);
	pCustomer->name = NULL;
	freeShoppingCart(pCustomer->cart);
	pCustomer->cart = NULL;
}