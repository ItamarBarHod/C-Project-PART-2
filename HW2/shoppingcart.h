#pragma once

#include <stdlib.h>
#include "shoppingitem.h"

typedef struct {
	Shoppingitem** itemsArr;
	int shoppingCartSize;
}Shoppingcart;

void printShoppingCart(const Shoppingcart* pShoppingCart);
Shoppingcart* initShoppingCart();
int addItemToCart(Shoppingcart* pShoppingCart, const Product* pProduct, int numberToPurchase);
double calcShoppingCart(const Shoppingcart* pShoppingCart);
int getItemPos(const Shoppingcart* pShoppingCart, const Product* pProduct);
int checkItemExists(const Shoppingcart* pShoppingCart, const Product* pProduct);
void deleteShoppingCart(Shoppingcart* pShoppingCart);
