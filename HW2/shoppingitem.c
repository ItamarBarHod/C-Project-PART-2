#include "shoppingitem.h"

void printShoppingItem(const Shoppingitem* pShoppingItem)
{
	printf("BARCODE: %s, Price: %.2f, Stock: %d\n", pShoppingItem->barcode, pShoppingItem->price, pShoppingItem->amount);
}

Shoppingitem* initShoppingItem(Product* pProduct)
{
	Shoppingitem* tempItem = (Shoppingitem*)malloc(sizeof(Shoppingitem));
	if (!tempItem)
	{
		printf("MEMORY ERROR\n");
		return NULL;
	}
	tempItem->amount = pProduct->stock;
	tempItem->price = pProduct->price;
	strcpy(tempItem->barcode, pProduct->barcode);
	return tempItem;
}

void freeShoppingItem(Shoppingitem* pShoppingItem)
{
	free(pShoppingItem);
	pShoppingItem = NULL;
}