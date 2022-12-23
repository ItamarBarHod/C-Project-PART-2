#pragma once

#include <stdlib.h>
#include "shoppingitem.h"

typedef struct {
	Shoppingitem** itemsArr;
	int shoppingCartSize;
}Shoppingcart;

void printShoppingCart(const Shoppingcart* pShoppingCart);
Shoppingcart* initShoppingCart();
int addItemToCart(Shoppingcart* pShoppingCart, Product* pProduct, int numberToPurchase);
double calcShoppingCart(const Shoppingcart* pShoppingCart);
Shoppingitem* checkItemExists(const Shoppingcart* pShoppingCart, const Product* pProduct);
void freeShoppingCart(Shoppingcart* pShoppingCart);
