#include "shoppingitem.h"

void printShoppingItem(const Shoppingitem* pShoppingItem)
{
	printf("BARCODE: %s, Price: %.2f, Stock: %d\n", pShoppingItem->barcode, pShoppingItem->price, pShoppingItem->amount);
}

Shoppingitem* initShoppingItem()
{
	Shoppingitem* tempItem = (Shoppingitem*)malloc(sizeof(Shoppingitem));
	if (!tempItem)
	{
		printf("MEMORY ERROR\n");
		return NULL;
	}
	return tempItem;
}

void freeShoppingItem(Shoppingitem* pShoppingItem)
{
	free(pShoppingItem);
}