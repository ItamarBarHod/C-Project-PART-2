#pragma once

#include <stdlib.h>
#include "stringfuncs.h"
#include "userinput.h"

#define PRODUCT_SIZE 21
#define BARCODE_SIZE 8

typedef enum { eShelf, eFrozen, eFridge, eFruitVegetable, eNofEnum } productType;
static const char* productTypes[eNofEnum] = { "Shelf", "Frozen", "Fridge", "FruitVegetable" };

typedef struct {
	char productName[PRODUCT_SIZE];
	char barcode[BARCODE_SIZE];
	productType type;
	float price;
	int stock;
}Product;

void printProduct(const Product* pProduct);
Product* insertProductData(Product* pProduct);
Product* createNewProduct();
void freeProduct(Product* pProduct);
void printBarcodeInstructions();