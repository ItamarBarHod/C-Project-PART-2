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
void customerShopping(Supermarket* pSupermarket);
void printCustomerShoppingCart(const Supermarket* pSupermarket);
void customerCheckout(const Supermarket* pSuperMarket);
void printProductType(const Supermarket* pSupermarket);
void exitMarket(Supermarket* pSupermarket);
void deleteSuperMarket(Supermarket* pSupermarket);

// helpers / extra
// 1: printMarket
void printCustomers(const Supermarket* pSupermarket);
// 2: addProduct
int addProductHelper(Supermarket* pSupermarket, Product* pProduct);
// 3: addCustomer
int addCustomerHelper(Supermarket* pSupermarket, Customer* pCustomer);
// 4: customerShopping
void customerShoppingHelper(Supermarket* pSupermarket, const Customer* pCustomer);
Product* getExistingProductFromUser(const Supermarket* pSupermarket);
void putItemInCustomerCart(Supermarket* pSupermarket, const Customer* pCustomer, Product* pProduct, int amount);
// 5: printCustomerShoppingCart - none
// 6: customerCheckout
void customerCheckoutHelper(const Supermarket* pSupermarket, Customer* pCustomer);
// 7: printProductType
void printProductTypeHelper(const Supermarket* pSupermarket, int type);

// general functions
int isSupermarketEmpty(const Supermarket* pSupermarket);
Product* checkProductExists(const Supermarket* pSupermarket, const char* productName);
Customer* checkCustomerExists(const Supermarket* pSupermarket, const char* pCustomer);
int checkValidMarket(const Supermarket* pSupermarket);