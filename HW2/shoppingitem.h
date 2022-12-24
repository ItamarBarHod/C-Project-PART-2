#pragma once

#include "product.h"
#include "stringfuncs.h"

typedef struct {
	char barcode[BARCODE_SIZE];
	float price;
	int amount;
}Shoppingitem;

void printShoppingItem(const Shoppingitem* pShoppingItem);
Shoppingitem* initShoppingItem();
void freeShoppingItem(Shoppingitem* pShoppingItem);