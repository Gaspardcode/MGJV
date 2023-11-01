#include <stdlib.h>
#include <math.h>
#include <err.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

float normalize(float min, float max, float val)
{
    return (val-min)/(max-min);
}

SDL_Surface* load_image(const char* path)
{
	SDL_Surface* surface = IMG_Load(path);
	SDL_Surface* converted = SDL_ConvertSurfaceFormat(surface,SDL_PIXELFORMAT_RGB888,0);
	SDL_FreeSurface(surface);
	return converted;
}

void convert_accumulator_to_lines(SDL_Surface* surface, SDL_Texture* texture, SDL_Renderer* renderer, SDL_Window* window, unsigned int **accumulator_array, double width, double height, double min, double max, double threshold)
{

    SDL_SetWindowPosition(window, 0, 0);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer,texture,NULL,NULL);

    // pas de parametre diagonal car la diagonal c'est la hauteur / 2
    int diag = height/2;
    // On parcourt l'accumulateur
    // SI la valeur est superieur au seuil
    // A partir des x0,y0, on calcule (x1,y1) et (x2, y2)
    for(int h = -diag; h<diag; h++)
    {
        for(int w = 0; w<180; w++)
        {
            if(normalize(min, max, accumulator_array[h+diag][w]) >= threshold)
            {
                double cosT = cos(w * (M_PI / 180));
                double sinT = sin(w * (M_PI / 180)); 

                int x0 = h*cosT;
                int y0 = h*sinT;
                int x1 = x0 + diag * (-sinT);
                int y1 = y0 + diag * cosT;
                int x2 = x0 - diag * (-sinT);
                int y2 = y0 - diag * cosT; 

                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

                SDL_RenderDrawLine(renderer, x1,y1,x2,y2);
            }
        }
    }
    // Updates the display.
    SDL_RenderPresent(renderer);
}

void draw_accumulator(SDL_Renderer* renderer, SDL_Window* window, unsigned int **accumulator_array, double width, double height, double min, double max, int w_w, int w_h)
{
    // On met l'arriere plan en Noir
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    for(size_t h = 0; h<height; h++)
	{
		for(size_t w = 0; w<720; w++) // un cercle pour pourvoir voir de maniere plus concrete l'accumulateur
        {
            Uint8 pix = (Uint8)(255*normalize(min,max, accumulator_array[h][w]));
            SDL_SetRenderDrawColor(renderer, pix, pix, pix, 255);

            SDL_RenderDrawPoint(renderer, w_w*normalize(0, 720, w), w_h*normalize(0, height, h));
        }
    }
    //SDL_RenderSetLogicalSize(renderer, 1080, 1080);

    // Updates the display.
    SDL_RenderPresent(renderer);
    return;
}

unsigned int accumulator(SDL_Surface *surface, SDL_Texture* texture, SDL_Renderer* renderer, SDL_Window* window)
{

    double im_w = surface->w, im_h = surface->h;
    double diag = sqrt(im_w * im_w + im_h * im_h);

    double rho_axis = (diag * 2);
    double theta_axis = rho_axis;

    Uint32 *pixels = surface->pixels;
    SDL_PixelFormat* format = surface->format;

    // INITIALISATION DE L'ACCUMULATEUR
    // AXE Y DE TAILLE rho_axis =  diag*2
    // AXE X DE TAILLE theta_axis =  diag*2
    unsigned int** accumulator_array;
    accumulator_array = malloc((rho_axis+1) * (sizeof *accumulator_array) + 1);
    for (unsigned int i=0; i<rho_axis; i++)
    {
        accumulator_array[i] = malloc((theta_axis + 1) * (sizeof *accumulator_array[i]) + 1);
    }

    // On met les valeurs de l'accumulateur à 0

    for(unsigned int r = 0; r<rho_axis; r++)
    {
        for(unsigned int t = 0; t<theta_axis; t++)
        {
            accumulator_array[r][t] = 0;
        }
    }


    // on remplit l'aaccumulateur
    for(int y = 0; y<im_h; y++)
    {
        for(int x = 0; x<im_w; x++)
        {
            Uint32 pixel = pixels[y * surface->w + x];
            Uint8 r, g, b;
            SDL_GetRGB(pixel, format, &r, &g, &b);
            // On regarde si le pixel est blanc
            if(r >= 250 && g >= 250 && b >= 250)
            {
                for(int th = 0; th<theta_axis; th++)
                {
                    double rho = x*cos(th * (M_PI / 180)) + y*sin(th * (M_PI / 180));
                    accumulator_array[(int)(rho+diag)][th]+=1;
                }
            }
        }
    }

    // On recup le min et le max
    double min = accumulator_array[0][0], max = accumulator_array[0][0];
    for(int r = 0; r < rho_axis; r++)
    {
        for(int t = 0; t<180; t++)
		{
            if(accumulator_array[r][t] < min) 
                min = accumulator_array[r][t];
            else if(accumulator_array[r][t] > max) 
                max = accumulator_array[r][t];
        }
    }
    int w_w, w_h;
    if (SDL_QueryTexture(texture, NULL, NULL, &w_w, &w_h) != 0)
        errx(EXIT_FAILURE, "%s", SDL_GetError());

    //ON RESIZE LA TAILLE DE LA FENETRE AVEC LES VALEURS DE L'ACCUMULATEUR
    SDL_SetWindowSize(window, w_w, w_h);
    printf("Width: %i, Height: %i\n\n", im_w,im_h);

    // Variable pour les differents evenements.
    SDL_Event event;
    //draw_accumulator(renderer, window,accumulator_array, rho_axis, theta_axis, min, max, w_w, w_h);
    //convert_accumulator_to_lines(surface, texture, renderer, window, accumulator_array, theta_axis, rho_axis, min, max, 0.40);
    int out = 1;
    while (out == 1)
    {
        // Waits for an event.
        SDL_WaitEvent(&event);

        switch (event.type)
        {
            // If the "quit" button is pushed, ends the event loop.
            case SDL_QUIT:
                out = 0;

        }
    }

}

int main(int argc, char** argv)
{
    	// Checks the number of arguments.
	if (argc != 2)
    		errx(EXIT_FAILURE, "Usage: image-file");

    // - Initialize the SDL.
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        errx(EXIT_FAILURE, "%s", SDL_GetError());

    // - Create a window.
	SDL_Window* window = SDL_CreateWindow("Dynamic Fractal Canopy", 0, 0, 0, 0, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    // - Create a renderer.
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // - Create a surface from the colored image.
	SDL_Surface* surface = load_image(argv[1]);
    SDL_Texture* texture = IMG_LoadTexture(renderer, argv[1]);

    accumulator(surface, texture, renderer, window);

    return EXIT_SUCCESS;
}
