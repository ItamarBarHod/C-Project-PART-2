#include "address.h"

void printAddress(const Address* pAdd)
{
	printf("Address: %s, %d, %s\n", pAdd->streetName, pAdd->streetNum, pAdd->city);
}

Address* initAddress()
{
	char* tempAddress = getAddressFromUser(); // malloc string
	if (!tempAddress)
	{
		return NULL;
	}
	Address* newAddress = (Address*)malloc(sizeof(Address)); // malloc
	if (!newAddress)
	{
		printf("MEMORY ERROR: Could not init address\n");
		free(tempAddress); // free 
		return NULL;
	}
	int isValid = fixValidAddress(newAddress, tempAddress);
	if (!isValid)
	{
		free(tempAddress); // free
		freeAddress(newAddress);
		free(newAddress); // freeaddress is made for supermarket abstraction
		return NULL;
	}
	return newAddress;
}

void freeAddress(Address* pAdd)
{
	free(pAdd->city);
	pAdd->city = NULL;
	free(pAdd->streetName);
	pAdd->streetName = NULL;
	pAdd = NULL; // part of supermarket in this exercise
}

int fixValidAddress(Address* pAdd, char* address)
{
	const char* delimiter = "#";
	char* street = strtok(address, delimiter);
	char* streetNum = strtok(NULL, delimiter);
	char* city = strtok(NULL, delimiter);
	pAdd->streetName = fixAddressStreetAndCity(street); // malloc
	if (!pAdd->streetName)
	{
		return 0;
	}
	pAdd->streetNum = atoi(streetNum);
	pAdd->city = fixAddressStreetAndCity(city); // malloc
	if (!pAdd->city)
	{
		return 0;
	}
	return 1;
}

void printAddressInstructions()
{
	printf("Enter address data\n");
	printf("Format: street#house number#city\n");
	printf("House number must only be a number\n");
	printf("Street and city must only be alphanumeric\n");
	printf("Street and city can have spaces\n");
	printf("Example: vitkin#9#herzelia\n");
}

