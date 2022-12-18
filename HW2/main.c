#include "supermarket.h"

int main()
{
	Supermarket market;
	createSuperMarket(&market);
	if (!&market)
	{
		printf("MEMORY ERROR\n");
		return 0;
	}
	int flag = 1;
	int option;
	while (flag)
	{
		printf("\nPlease choose one of the following options:\n1 - Show SuperMarket\n2 - Add Product\n3 - Add Customer\n4 - Customer Shopping\n5 - Print Shopping Cart\n6 - Customer Pay\n7 - Print Product By Type\n8 - Quit\n\n");
		scanf(" %d", &option);
		switch (option)
		{
		case 1:
			printMarket(&market);
			break;
		case 2:
			addProduct(&market);
			break;
		case 3:
			addCustomer(&market);
			break;
		case 4:
			customerShopping(&market);
			break;
		case 5:
			printCustomerShoppingCart(&market);
			break;
		case 6:
			customerCheckout(&market);
			break;
		case 7:
			printProductType(&market);
			break;
		case 8:
			flag = 0;
			exitMarket(&market); // free
			printf("Bye bye!\n");
			break;
		default:
			printf("Error: no such option!\n");
			break;
		}
	}
}
