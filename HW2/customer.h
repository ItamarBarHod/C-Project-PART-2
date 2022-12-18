#pragma once

#include "shoppingcart.h"
#include "stringfuncs.h"
#include "userinput.h"

typedef struct {
	char* name;
	Shoppingcart* cart;
}Customer;

void printCustomer(const Customer* pCustomer);
Customer* createNewCustomer();
void freeCustomer(Customer* pCustomer);