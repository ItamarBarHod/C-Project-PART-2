#pragma once

#include "shoppingcart.h"
#include "stringfuncs.h"
#include "userinput.h"

typedef struct {
	char* name;
	Shoppingcart* cart;
}Customer;

void printCustomer(const Customer* pCustomer);
Customer* initCustomer();
Customer* createNewCustomer(char* customerName);
void printCustomerCartHelper(Customer* pCustomer);
void freeTempCustomer(Customer* pCustomer);
void freeCustomer(Customer* pCustomer);