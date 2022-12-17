#include "customer.h"
#include "userinput.h"

void printCustomer(const Customer* pCustomer)
{
	printf("Customer name: %s\n", pCustomer->name);
}

Customer* createNewCustomer()
{
	Customer* tempCustomer = (Customer*)malloc(sizeof(Customer));
	if (!tempCustomer)
	{
		printf("MEMORY ERROR\n");
		return NULL;
	}
	tempCustomer->cart = initShoppingCart();
	if (!tempCustomer->cart)
	{
		printf("MEMORY ERROR\n");
		return NULL;
	}
	printf("Enter customer name\n");
	tempCustomer->name = getNameFromUser(MAX_SIZE);
	if (!tempCustomer->name)
	{
		deleteShoppingCart(tempCustomer->cart);
		free(tempCustomer);
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
}