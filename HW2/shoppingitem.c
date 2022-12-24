#include "shoppingitem.h"

void printShoppingItem(const Shoppingitem* pShoppingItem)
{
	printf("BARCODE: %s, Price: %.2f, Stock: %d\n", pShoppingItem->barcode, pShoppingItem->price, pShoppingItem->amount);
}

Shoppingitem* initShoppingItem(Product* pProduct, int amount)
{
	Shoppingitem* newItem = (Shoppingitem*)malloc(sizeof(Shoppingitem));
	if (!newItem)
	{
		printf("MEMORY ERROR: Could not init item\n");
		return NULL;
	}
	strcpy(newItem->barcode, pProduct->barcode);
	newItem->price = pProduct->price;
	newItem->amount = amount;

	return newItem;
}

void freeShoppingItem(Shoppingitem* pShoppingItem)
{
	free(pShoppingItem);
	pShoppingItem = NULL;
}