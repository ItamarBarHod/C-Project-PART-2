#pragma once

#include <string.h>
#include "stringfuncs.h"

char* getAddressFromUser();
char* getNameFromUser(int maxNameSize);
char* getBarcodeFromUser();
float getNumberFromUser();
int getProductTypeFromUser();
int askUserToContinue();