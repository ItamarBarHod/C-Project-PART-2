#include "customer.h"

void printCustomer(const Customer* pCustomer)
{
	printf("Customer name: %s\n", pCustomer->name);
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
		freeCustomer(tempCustomer); // free
		return NULL;
	}
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
	tempCustomer->name = _strdup(customerName);
	if (!tempCustomer->name)
	{
		freeCustomer(tempCustomer); // free
		return NULL;
	}
	return tempCustomer;
}

void freeCustomer(Customer* pCustomer)
{
	free(pCustomer->name);
	pCustomer->name = NULL;
	deleteShoppingCart(pCustomer->cart);
	pCustomer->cart = NULL;
	free(pCustomer);
	pCustomer = NULL;
}