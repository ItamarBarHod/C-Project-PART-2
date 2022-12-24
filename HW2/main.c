#include "supermarket.h"

int main()
{
	Supermarket market;
	int isInitMarket = createSuperMarket(&market);
	if (!isInitMarket)
	{
		printf("MARKET MEMORY ERROR\n");
		return 0;
	}
	int flag = 1;
	int option;
	while (flag)
	{
		printf("\nPlease choose one of the following options:\n0 - Show SuperMarket\n1 - Add Product\n2 - Add Customer\n3 - Customer Shopping\n4 - Print Shopping Cart\n5 - Customer Pay\n6 - Print Product By Type\n-1 - Quit\n\n");
		scanf(" %d", &option);
		getchar(); // clear \n
		switch (option)
		{
		case 0:
			printMarket(&market);
			break;
		case 1:
			addProduct(&market);
			break;
		case 2:
			addCustomer(&market);
			break;
		case 3:
			startShopping(&market);
			break;
		case 4:
			printCustomerShoppingCart(&market);
			break;
		case 5:
			customerCheckout(&market);
			break;
		case 6:
			printProductType(&market);
			break;
		case -1:
			flag = 0;
			exitMarket(&market); // force payments and free market
			break;
		default:
			printf("Error: no such option!\n");
			break;
		}
	}
}
