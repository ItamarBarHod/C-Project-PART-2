#include "address.h"

void printAddress(const Address* pAdd)
{
	printf("Address: %s, %d, %s\n", pAdd->streetName, pAdd->streetNum, pAdd->city);
}

Address* getAddressData()
{
	char* address = getAddressFromUser();
	if (!address)
	{
		return NULL;
	}
	Address* newAddress = (Address*)malloc(sizeof(Address));
	if (!newAddress)
	{
		printf("MEMORY ERROR\n");
		free(address);
		return NULL;
	}
	fixValidAddress(newAddress, address);
	return newAddress;
}

void freeAddress(Address* pAdd)
{
	free(pAdd->city);
	free(pAdd->streetName);
	pAdd = NULL;
}

void fixValidAddress(Address* pAdd, char* address)
{
	const char* delimiter = "#";
	char* street = strtok(address, delimiter);
	char* streetNum = strtok(NULL, delimiter);
	char* city = strtok(NULL, delimiter);
	pAdd->streetName = fixAddressStreetAndCity(street); // malloc
	if (!pAdd->streetName)
	{
		return;
	}
	pAdd->streetNum = atoi(streetNum);
	pAdd->city = fixAddressStreetAndCity(city); // malloc
	if (!pAdd->city)
	{
		return;
	}
}

void printAddressInstructions()
{
	printf("Enter address data\n");
	printf("Format: street#house number#city\n");
	printf("House number must only be a number\n");
	printf("Street and city must only be alphanumeric\n");
	printf("Street and city can have spaces\n");
}