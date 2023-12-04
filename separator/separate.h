#ifndef SEPARATE_H
#define SEPARATE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <err.h>

void resize(char * path, int h, int w)
{
  SDL_Surface * src = IMG_Load(path);
  SDL_Surface * dst = SDL_CreateRGBSurface(0,w,h,32,0,0,0,0);
  int e = SDL_BlitScaled(src,NULL,dst,NULL);
  if(e == -1)
    errx(EXIT_FAILURE,"resize failed");
  IMG_SavePNG(dst,"../images/resized.png");
}

int calculate_board(SDL_Surface* surface,  int w)
{
  Uint32 *surf_map = surface->pixels;
  int count = 0;
  for(int i = 0; i < 28; i++)
  {
    Uint8 r, g, b;
    SDL_GetRGB(surf_map[(w/2)*(w/2) + i], surface->format, &r,&g,&b);
    if(r > 128 && g > 128 && b > 128)
    {
      count += 1;
    }
  }
  printf("\n");
  return count;
}

void cut_and_save(SDL_Surface* surface, int x, int y, int nb1, int nb2) 
{
  int w = surface->w;
  //int h = surface->h;
  Uint32 *surf_map = surface->pixels;
  SDL_Surface *imageN = NULL;
  int nw= 252/9; 
  int nh = 252/9;
  imageN = SDL_CreateRGBSurface(0, nw, nh, 32, 0, 0, 0, 0);
  SDL_Surface *image = 
    SDL_ConvertSurfaceFormat(imageN, SDL_PIXELFORMAT_RGB888, 0);
  SDL_LockSurface(image);
  SDL_LockSurface(surface);
  Uint32* surf_image = image->pixels;
  //x and y are not good there are dimensions problematics

  for (int j = 0; j < nh; j++)
  {
    for(int i = 0; i < nw; i++)
    {
      Uint8 r, g, b;
      SDL_GetRGB(surf_map[(i+x) + ((j+y)*w)], 
          surface->format, &r,&g,&b);
      surf_image[i + j*nw] = 
        SDL_MapRGB(image->format, r, g, b);
    }
  }
  SDL_UnlockSurface(image);
  SDL_UnlockSurface(surface);
  char name[] = "../images/cases/case__.bmp";
  name[21] = (nb2%10)+'0';
  name[20] = (nb1) + '0';
  SDL_SaveBMP(image, name);
  SDL_FreeSurface(image);
}

SDL_Surface* board_regularization(SDL_Surface * surface, int h, int w)
{
  Uint32 *surf_map = surface->pixels;
  SDL_Surface *new_board = NULL;
  new_board = SDL_CreateRGBSurface(0, w-4, h-4, 32, 0, 0, 0, 0);
  Uint32 *new_map = new_board->pixels;
  SDL_LockSurface(new_board);
  SDL_LockSurface(surface);
  for(int i = 2; i < h-2; i++)
  {
    for(int j = 2; j < w-2; j++)
    {
      new_map[(i-2)*(w-4) + j-2] = surf_map[i*(w) + j];
    }
  }
  SDL_UnlockSurface(new_board);
  SDL_UnlockSurface(surface);
  return new_board;
}

int separate(char* path)
{
  resize(path, 28*18, 28*18);
  SDL_Surface *surface = IMG_Load("../images/resized.png");
  while(calculate_board(surface, surface->w) > 4)
  {
    surface = board_regularization(surface, surface->h, surface->w);
    IMG_SavePNG(surface,"../images/operated.png");

  }

  resize("../images/operated.png", 28*9, 28*9);

  surface = IMG_Load("../images/resized.png");

  SDL_Surface *surf = 
    SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGB888, 0);
  for(int i = 0; i < 9; i++)
  {
    for(int j = 1; j < 10; j++)
    {
      cut_and_save(surf, i*28, (j-1)*28, i, j);
    }
  }
  //SDL_FreeSurface(surface);
  return 0;
}

#endif
