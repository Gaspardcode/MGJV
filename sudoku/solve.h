# ifndef SOLVE_H
# define SOLVE_H

#include "sudoku_solver.h"
#include "sudoku_backtracking.h"
#include "err.h"

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
  if(file == NULL)
  {
    errx(1, "fopen()");
  }


  for(int i = 0; i < 81; i++)
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

int solve(char *arg)
{
  unsigned int len = 9*9;
  unsigned int *array = calloc(len, sizeof (unsigned int));
  file_to_array(arg, array);
  /*for(int i = 0; i < 81; i++)
  {
    if(i%9 != 8)
      printf("%i ", *(array + i));
    else
      printf("%i\n", *(array + i));

  }*/
  int r = solveSudo(array, 0, 0, 9);


  if(r == 0)
    printf("fail");
  array_to_file("../sudoku/grids/grid_00.result", array);
  free(array);
  return 0;

}
# endif

