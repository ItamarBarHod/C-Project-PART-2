#include "stringfuncs.h"

int isValidBarcode(const char* str)
{
	if (strlen(str) == 1) // buffer fix 
	{
		return 0;
	}
	int digits = checkDigitsCount(str);
	if ((digits > 5 || digits < 3) || strlen(str) != BARCODE_SIZE - 1 || isLowercase(str) || !isValidCharacterPosition(str) || !IsAlphanumeric(str))
	{
		printf("Bad Barcode! Please follow the rules\n");
		return 0;
	}
	return 1;
}

int isValidAddressFormat(const char* str)
{
	int isValidTokenFormat = validTokens(str);
	int isValidSections = isValidAddressSections(str);
	if (isValidTokenFormat && isValidSections)
	{
		return 1;
	}
	return 0;
}

int checkDigitsCount(const char* str)
{
	int counter = 0;
	while (*str)
	{
		int isDigit = isdigit(*str);
		if (isDigit)
		{
			counter++;
		}
		str++;
	}
	return counter;
}

int isLowercase(const char* str)
{
	while (*str) {
		int isLowerCase = islower(*str);
		if (isLowerCase)
		{
			return 1;
		}
		str++;
	}
	return 0;
}

int isValidCharacterPosition(const char* str)
{
	return (isupper(*str) && isupper(str[BARCODE_SIZE - 2])); // First and last chars
}

int IsAlphanumeric(const char* str)
{
	while (*str)
	{
		int isAlphaNumeric = isalnum(*str) || isspace(*str);
		if (!isAlphaNumeric)
		{
			return 0;
		}
		str++;
	}
	return 1;
}

int isOnlySpaces(const char* str)
{
	while (*str)
	{
		int isSpace = isspace(*str);
		if (!isSpace)
		{
			return 0;
		}
		str++;
	}
	return 1;
}

int isOnlyNumbers(const char* str)
{
	while (*str)
	{
		int isNumber = isdigit(*str);
		if (!isNumber)
		{
			return 0;
		}
		str++;
	}
	return 1;
}

int isValidAddressSections(const char* str) // split to 3 sections and check
{
	char* temp = _strdup(str); // malloc
	if (!temp)
	{
		printf("MEMORY ERROR\n");
		return 0;
	}
	const char* delimiter = "#";
	char* street = strtok(temp, delimiter);
	char* streetNum = strtok(NULL, delimiter);
	char* city = strtok(NULL, delimiter);
	if (!street || !IsAlphanumeric(street) || isOnlySpaces(street))
	{
		return 0;
	}
	if (!streetNum || !isOnlyNumbers(streetNum))
	{
		return 0;
	}
	if (!city || !IsAlphanumeric(city) || isOnlySpaces(city))
	{
		return 0;
	}
	free(temp); // free
	return 1;
}

int validTokens(const char* str)
{
	int tokenCounter = 0;
	const char delimiter = '#';
	while (*str)
	{
		if (*str == delimiter)
		{
			tokenCounter++;
		}
		str++;
	}
	if (tokenCounter != 2)
	{
		return 0;
	}
	return 1;
}

char* fixAddressStreetAndCity(char* str)
{
	char tempString[MAX_SIZE] = "";
	const char* delimiter = " ";
	char* token, * lastWord, * firstWord;
	firstWord = str;
	token = strtok(str, delimiter); // cant be NULL
	lastWord = token;
	int index = 0;
	while (token)
	{
		*token = toupper(*token);
		strcat(tempString, token);
		strcat(tempString, "  ");
		index += (int)(strlen(token) + 2);
		lastWord = token;
		token = strtok(NULL, delimiter);
	}
	index -= (int)(strlen(lastWord) + 2); // cant be 0
	tempString[index] = tolower(tempString[index]);
	index += (int)strlen(lastWord);
	tempString[index] = '\0';
	tempString[0] = toupper(tempString[0]);
	char* fixedString = _strdup(tempString); // malloc
	if (!fixedString)
	{
		printf("MEMORY ERROR\n");
		return NULL;
	}
	return fixedString;
}
