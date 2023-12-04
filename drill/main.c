#include "../sudoku/solve.h"
#include "../epurator/epurate.h"
#include "../separator/separate.h"
#include <err.h>
#include "../neural_net/ocr.h"
#include "../neural_net/load_image.h"
#include "../character_detection/detection.h"
#include <stdio.h>
#include "../sudoku/solve.h"

int main(int argc, char** argv)
{
  if(argc < 1)
    errx(1, "main()");
  separate(argv[1]);
  epure(0);
  int* sudoku = calloc(81, sizeof(int));
  prepare(sudoku);

  //creation of the file

  FILE *file = fopen("../sudoku/grids/grid_00", "w");

  if(file == NULL)
  {
    perror("Error opening file");
    return 1;
  }

  int len = 9*9;
  unsigned int *begin = sudoku, *end = sudoku + len;

  for(int i = 0; begin+i < end; i++)
  {
    if(i%3 == 0 && i%9 != 0)
      fprintf(file, " ");
    if(i%27 == 0 && i!=0)
      fprintf(file, "\n");
    if(i%9 != 8)
    {
      if(*(sudoku +  i) != 0)
        fprintf(file, "%i", *(sudoku + i));
      else
        fprintf(file, ".");
    }
    else
    {
      if(*(sudoku + i) != 0)
        fprintf(file, "%i\n", *(sudoku + i));
      else
        fprintf(file, ".\n");
    }
  }

  fclose(file);
  free(sudoku);
  solve("../sudoku/grids/grid_00");

  
  return 0;
}
