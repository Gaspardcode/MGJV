#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <err.h>
#include <stdlib.h>
#include <string.h>
void file_to_array(char path[],unsigned int *array )
{
	FILE *file;
	file = fopen(path, "r");

	char c = fgetc(file);

	int index = 0;
	while(c != EOF)
	{
		printf("%c", c);
		if(c == '.')
		{
			array[index] = 0;
			index++;
		}
		else if (c <= '9' && c >= '0' )
		{
			array[index] = c - '0';
			index++;
		}

		c = fgetc(file);

	}
	fclose(file);
	printf("\n");

}

int solvable(unsigned int *array, unsigned int len)
{
	unsigned int value; 
	unsigned int line = sqrt(len); // line is the length of the square
	unsigned int loop = 0; // the loop is usefull to know where we want to see in the array

	// LINE LOOP
	//!first loop!
	//line * loop : the nth line
	for(unsigned int index = 0 + (line * loop); index < (line + (loop+1)); index++)
	{

		//init the value
		//line * loop : the nth line
		value = *(array + index);
		//if the value is not already discovered we don't care about
		if(value != 0)
		{
			// know we need to conpare the value with the rest of the line, v will be the name of the other value
			for(unsigned int i = index+1; i < (line*loop); i++)
			{
				unsigned int v = *(array + i);
				if(v != 0 && v == value)
				{
					return 1;
				}
			}
		}
	}

	return 0;

}

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		return 1;
	}
	unsigned int len = 9*9;
	unsigned int *array = calloc(len, sizeof (unsigned int));
	unsigned int *begin = array, *end = array + len;
	file_to_array(argv[1], array);
	for(int i = 0; begin+i < end; i++)
	{
		if(i%9 != 8)
			printf("%i ", *(array + i));
		else
			printf("%i\n", *(array + i));

	}
	return 0;

}
