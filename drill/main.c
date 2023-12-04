#include "../sudoku/solve.h"
#include "../epurator/epurate.h"
#include "../separator/separate.h"
#include <err.h>
#include "../neural_net/ocr.h"
#include "../neural_net/load_image.h"
#include "../character_detection/detection.h"

int main(int argc, char** argv)
{
  if(argc < 1)
    errx(1, "main()");
  separate(argv[1]);
  epure(0);
  int* sudoku = calloc(81, sizeof(int));
  prepare(sudoku);
  
  int len = 9*9;
	unsigned int *begin = sudoku, *end = sudoku + len;

	for(int i = 0; begin+i < end; i++)
	{
		if(i%3 == 0 && i%9 != 0)
			printf(" ");
		if(i%27 == 0 && i!=0)
			printf("\n");
		if(i%9 != 8)
			printf("%i", *(sudoku + i));
		else
			printf("%i\n", *(sudoku + i));
	}
  free(sudoku);
  return 1;
}
