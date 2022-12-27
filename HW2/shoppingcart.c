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
		printf("MEMORY ERROR: Could not init cart\n");
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

int addItemToCart(Shoppingcart* pCart, Product* pProduct, int amount)
{
	Shoppingitem* itemExists = checkItemExists(pCart, pProduct);
	if (itemExists)
	{
		itemExists->amount += amount;
	}
	else
	{
		Shoppingitem* newItem = initShoppingItem(pProduct, amount); // malloc
		if (!newItem)
		{
			return 0;
		}
		int reallocSuccess = addItemToCartHelper(pCart, newItem);
		if (!reallocSuccess)
		{
			freeShoppingItem(newItem); // free
			return 0;
		}
	}
	pProduct->stock -= amount; // reduce from stock (pProduct cant be const)
	printf("Product: %s (%s) stock left: %d\n", pProduct->productName, pProduct->barcode, pProduct->stock);
	return 1;
}

int addItemToCartHelper(Shoppingcart* pShoppingCart, Shoppingitem* newItem)
{
	int newCartSize = pShoppingCart->shoppingCartSize + 1;
	Shoppingitem** tempArr = (Shoppingitem**)realloc(pShoppingCart->itemsArr, newCartSize * sizeof(Shoppingitem*)); // malloc
	if (!tempArr)
	{
		printf("MEMORY ERROR: Could not add item to cart\n");
		return 0;
	}
	tempArr[newCartSize - 1] = newItem;
	pShoppingCart->shoppingCartSize++;
	pShoppingCart->itemsArr = tempArr;
	return 1;
}

void printAndReturnCart(Shoppingcart* pCart)
{
	if (pCart->shoppingCartSize > 0)
	{
		printShoppingCart(pCart);
		printf("Paying! Price of to pay: %.2lf\n", calcShoppingCart(pCart));
		Shoppingcart* tempCart = pCart;
		freeShoppingCart(pCart); // free
		tempCart = initShoppingCart(); // malloc
		if (!pCart)
		{
			printf("MEMORY ERROR\n");
			return;
		}
		printf("Returned shopping cart!\n");
		printf("--------PAYMENT DONE--------\n");
		return;
	}
	// else no items in cart
	printf("Error: This customer has no items yet, returning to main menu\n");
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