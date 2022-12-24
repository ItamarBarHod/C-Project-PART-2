#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "product.h"
#include "customer.h"
#include "stringfuncs.h"
#include "address.h"

typedef struct {
	char* marketName;
	Address marketAddress;
	Customer* customerArr;
	int customerArrSize;
	Product** productArr;
	int productArrSize;
}Supermarket;

int createSuperMarket(Supermarket* pSupermarket);

// main funcs
void printMarket(const Supermarket* pSupermarket);
void addProduct(Supermarket* pSupermarket);
void addCustomer(Supermarket* pSupermarket);
void startShopping(Supermarket* pSupermarket);
void printCustomerShoppingCart(const Supermarket* pSupermarket);
void customerCheckout(const Supermarket* pSuperMarket);
void printProductType(const Supermarket* pSupermarket);
void exitMarket(Supermarket* pSupermarket);
void freeSuperMarket(Supermarket* pSupermarket);

// helpers / extra
void printCustomers(const Supermarket* pSupermarket);
int addProductHelper(Supermarket* pSupermarket, Product* pProduct);
int addCustomerHelper(Supermarket* pSupermarket, Customer* pCustomer);
void customerShopping(Supermarket* pSupermarket, const Customer* pCustomer);
Product* getExistingProductFromUser(const Supermarket* pSupermarket);
void printProductTypeHelper(const Supermarket* pSupermarket, int type);

// general functions
int isSupermarketEmpty(const Supermarket* pSupermarket);
Product* checkProductExists(const Supermarket* pSupermarket, const char* productName);
Customer* checkCustomerExists(const Supermarket* pSupermarket, const char* pCustomer);
int checkValidMarket(const Supermarket* pSupermarket);