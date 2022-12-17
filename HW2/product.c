#include "product.h"

void printProduct(const Product* pProduct)
{
	printf("%-*s %-*s %-*s %-*.2f %d\n", 27, pProduct->productName, 9, pProduct->barcode, 16, productTypes[pProduct->type], 14, pProduct->price, pProduct->stock);
}

Product* insertProductData(Product* pProduct)
{
	printf("Please enter a product name, maximum size %d\n", PRODUCT_SIZE - 1);
	char* tempProdName = getNameFromUser(PRODUCT_SIZE);
	if (!tempProdName)
	{
		return NULL;
	}
	strcpy(pProduct->productName, tempProdName);
	free(tempProdName);

	pProduct->type = getProductTypeFromUser();
	printf("Please enter the price: ");
	pProduct->price = getNumberFromUser();
	printf("Please enter the amount (stock count): ");
	pProduct->stock = (int)getNumberFromUser();
	return pProduct;
}

Product* createNewProduct()
{
	Product* tempProd = (Product*)malloc(sizeof(Product));
	if (!tempProd)
	{
		printf("MEMORY ERROR\n");
		return NULL;
	}
	printBarcodeInstructions();
	char* tempBarcode;
	tempBarcode = getBarcodeFromUser();
	if (!tempBarcode)
	{
		free(tempProd);
		return NULL;
	}
	strcpy(tempProd->barcode, tempBarcode);
	free(tempBarcode);
	return tempProd;
}

void freeProduct(Product* pProduct)
{
	free(pProduct);
}

void printBarcodeInstructions()
{
	printf("Enter product barcode Code should be of 7 length exactly\n");
	printf("UPPER CASE letter and digits\n");
	printf("Must have 3 to 5 digits\n");
	printf("First and last chars must be UPPER CASE letter\n");
	printf("For example A12B40C\n\n");
}
