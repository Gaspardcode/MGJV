#ifndef DETECTION_H
#define DETECTION_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../neural_net/load_image.h"
#include "../neural_net/ocr.h"
#include "../neural_net/testfile.h"


int prepare(int* sudoku)
{
  for(int i = 0; i < 9; i++)
  {
    for(int j = 1; j < 10; j++)
    {
      char file[] = "../images/caracters/case__.bmp";
      file[24] = i + '0';
      file[25] = j + '0';
      SDL_Surface *surface = IMG_Load(file);
      SDL_Surface *surf = 
        SDL_ConvertSurfaceFormat(surface, 
            SDL_PIXELFORMAT_RGB888, 0);

      Uint32* map = surf->pixels;
      int nb = 0;
      for(int u =0; u < 28; u++)
      {
        for(int v = 0; v < 28; v++)
        {
          Uint8 r, g, b;
          SDL_GetRGB(map[u*28 + v], surf->format, &r,&g,&b);

          if(r < 128)
            nb++;
        }

      }
      
      if(nb > 10)
      {
        double* matrice = load_image(file);
        double* outputs = predict(matrice);
        size_t max = 0;
        for(size_t resp = 0; resp < 10; resp++)
        {
          if(outputs[resp] > outputs[max])
          {
            max = resp;
          }
        }
        sudoku[i + ((j-1)*9)] = max;
      }
      else
      {
        sudoku[i + ((j-1)*9)] = 0;
      }
      SDL_FreeSurface(surface);


    }
    
  }
  
}

#endif




