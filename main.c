#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "niveau1.h"
#include "affichage.h"
#include "fonctions.h"
#include "init.h"

int main()
{
   SDL_Window *window = NULL;
    SDL_Texture *image = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Rect rectangle;
    bool jeu = true;
    rectangle.x = 0;
    rectangle.y = 0;
    rectangle.w = 100;
    rectangle.h = 100;
    init(&window, &renderer);

    SDL_SetRenderDrawColor(renderer,0,255,255,255);                 //A supprimer

    while (jeu)
    {
        SDL_Delay(39);
        SDL_Event event;
        SDL_RenderDrawRect(renderer,&rectangle);
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                jeu = false;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    jeu = false;
                    break;
                }
                break;
            }
        }
        SDL_RenderPresent(renderer);
    }

Quit:
    if (image != NULL)
        SDL_DestroyTexture(image);
    if (renderer != NULL)
        SDL_DestroyRenderer(renderer);
    if (window != NULL)
        SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
    
    return 0;
}