#include "sudoku_solver.h"
#include "sudoku_backtracking.h"

void file_to_array(char path[],unsigned int *array )
{
	FILE *file;
	file = fopen(path, "r");

	char c = fgetc(file);

	int index = 0;
	while(c != EOF)
	{
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

}

void array_to_file(char path[],unsigned int *array )
{
	FILE *file;
	file = fopen(path, "w");

	int len = 9*9;
	unsigned int *begin = array, *end = array + len;

	for(int i = 0; begin+i < end; i++)
	{
		if(i%3 == 0 && i%9 != 0)
			fprintf(file, " ");
		if(i%27 == 0 && i!=0)
			fprintf(file, "\n");
		if(i%9 != 8)
			fprintf(file ,"%i", *(array + i));
		else
			fprintf(file, "%i\n", *(array + i));
	}


	fclose(file);

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
	/*for(int i = 0; begin+i < end; i++)
	  {
	  if(i%9 != 8)
	  printf("%i ", *(array + i));
	  else
	  printf("%i\n", *(array + i));

	  }*/
	int r = solveSudo(array, 0, 0, 9);
	for(int i = 0; begin+i < end; i++)
	{
		if(i%9 != 8)
			printf("%i ", *(array + i));
		else
			printf("%i\n", *(array + i));

	}
	if(r == 0)
		printf("fail");
	array_to_file(strcat(argv[1],".result"), array);
	return 0;

}
