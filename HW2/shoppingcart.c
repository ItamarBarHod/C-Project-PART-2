#include "shoppingcart.h"

void printShoppingCart(const Shoppingcart* pShoppingCart)
{
	for (int i = 0; i < pShoppingCart->shoppingCartSize; i++)
	{
		printShoppingItem(pShoppingCart->itemsArr[i]);
	}
	printf("\n");
}

Shoppingcart* initShoppingCart()
{
	Shoppingcart* tempCart = (Shoppingcart*)malloc(sizeof(Shoppingcart));
	if (!tempCart)
	{
		printf("MEMORY ERROR\n");
		return NULL;
	}
	tempCart->shoppingCartSize = 0;
	tempCart->itemsArr = NULL;
	return tempCart;
}

double calcShoppingCart(const Shoppingcart* pShoppingCart)
{
	double sum = 0;
	for (int i = 0; i < pShoppingCart->shoppingCartSize; i++)
	{
		int amount = pShoppingCart->itemsArr[i]->amount;
		double price = pShoppingCart->itemsArr[i]->price;
		sum += amount * price;
	}
	return sum;
}

void freeShoppingCart(Shoppingcart* pShoppingCart)
{
	for (int i = 0; i < pShoppingCart->shoppingCartSize; i++)
	{
		freeShoppingItem(pShoppingCart->itemsArr[i]);
	}
	free(pShoppingCart->itemsArr);
	pShoppingCart->itemsArr = NULL;
	free(pShoppingCart);
	pShoppingCart = NULL;
}

int addItemToCart(Shoppingcart* pShoppingCart, Product* pProduct, int numberToPurchase)
{
	Shoppingitem* newItem = initShoppingItem(); // malloc
	if (!newItem)
	{
		printf("MEMORY ERROR\n");
		return 0;
	}
	int cartSize = pShoppingCart->shoppingCartSize + 1;
	Shoppingitem** tempArr = (Shoppingitem**)realloc(pShoppingCart->itemsArr, cartSize * sizeof(Shoppingitem*)); // malloc
	if (!tempArr)
	{
		printf("MEMORY ERROR\n");
		return 0;
	}
	strcpy(newItem->barcode, pProduct->barcode);
	newItem->amount = numberToPurchase;
	newItem->price = pProduct->price;
	tempArr[cartSize - 1] = newItem;
	pShoppingCart->shoppingCartSize++;
	pShoppingCart->itemsArr = tempArr;
	return 1;
}

Shoppingitem* checkItemExists(const Shoppingcart* pShoppingCart, const Product* pProduct)
{
	for (int i = 0; i < pShoppingCart->shoppingCartSize; i++)
	{
		int equal = strcmp(pShoppingCart->itemsArr[i]->barcode, pProduct->barcode);
		if (equal == 0)
		{
			return pShoppingCart->itemsArr[i];
		}
	}
	return NULL;
}