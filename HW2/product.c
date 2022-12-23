#include "product.h"

void printProduct(const Product* pProduct)
{
	printf("%-*s %-*s %-*s %-*.2f %d\n", 27, pProduct->productName, 9, pProduct->barcode, 16, productTypes[pProduct->type], 14, pProduct->price, pProduct->stock);
}

Product* createNewProduct(char* barcode)
{
	Product* tempProd = (Product*)malloc(sizeof(Product));
	if (!tempProd)
	{
		printf("MEMORY ERROR\n");
		return NULL;
	}
	strcpy(tempProd->barcode, barcode);

	printf("Please enter a product name, maximum size %d\n", PRODUCT_SIZE - 1);
	char* prodName = getNameFromUser(PRODUCT_SIZE); // malloc 
	if (!prodName)
	{
		return NULL;
	}
	strcpy(tempProd->productName, prodName); // dynamic to static
	free(prodName);

	tempProd->type = getProductTypeFromUser();
	printf("Please enter the price: ");
	tempProd->price = getNumberFromUser();
	printf("Please enter the amount (stock count): ");
	tempProd->stock = (int)getNumberFromUser();
	return tempProd;
}

void freeProduct(Product* pProduct)
{
	free(pProduct);
	pProduct = NULL;
}

void printBarcodeInstructions()
{
	printf("Enter product barcode Code should be of 7 length exactly\n");
	printf("UPPER CASE letter and digits\n");
	printf("Must have 3 to 5 digits\n");
	printf("First and last chars must be UPPER CASE letter\n");
	printf("For example A12B40C\n\n");
}
