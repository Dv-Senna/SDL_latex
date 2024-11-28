#include <stdlib.h>
#include <string.h>

#include "SDL2/TEX_hash.h"



void TEX_Hash(const char *string, char *output, int size)
{
	int lengthOfString = strlen(string);
	char *newString = malloc(sizeof(char) * (lengthOfString + 1));
	newString[lengthOfString] = 0;

	for (int i = 0; i < lengthOfString; i++)
		newString[i] = (string[i] + size) % 26 + 65;

	while (1)
	{
		if (lengthOfString == 16)
		{
			output[16] = 0;
			for (int i = 0; i < 16; i++)
				output[i] = newString[i];
			free(newString);
			return;
		}
		
		if (lengthOfString > 16)
		{
			for (int i = 0; i < lengthOfString; i += 2)
				newString[i] = (newString[i] + newString[i + 1]) % 26 + 'A';

			lengthOfString /= 2;
		}

		else
		{
			output[16] = 0;
			for (int i = 0; i < lengthOfString; i++)
				output[i] = newString[i];
			for (int i = lengthOfString; i < 16; i++)
				output[i] = 'a';
			free(newString);
			return;
		}
	}
}
