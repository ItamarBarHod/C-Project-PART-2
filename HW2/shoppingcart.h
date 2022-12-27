#pragma once

#include <stdlib.h>
#include "shoppingitem.h"

typedef struct {
	Shoppingitem** itemsArr;
	int shoppingCartSize;
}Shoppingcart;

void printShoppingCart(const Shoppingcart* pShoppingCart);
Shoppingcart* initShoppingCart();
int addItemToCart(Shoppingcart* pCart, Product* pProduct, int amount);
void printAndReturnCart(Shoppingcart* pCart);
int addItemToCartHelper(Shoppingcart* pShoppingCart, Shoppingitem* newItem);
double calcShoppingCart(const Shoppingcart* pShoppingCart);
Shoppingitem* checkItemExists(const Shoppingcart* pShoppingCart, const Product* pProduct);
void freeShoppingCart(Shoppingcart* pShoppingCart);
