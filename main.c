#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include "affichage.h"
#include "fonctions.h"
#include <SDL2/SDL.h>

int main()
{
    SDL_Window *window = NULL;
    SDL_Texture *image = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Rect * position;
    position = malloc(sizeof(SDL_Rect));
    position->x = 0;
    position->y = 0;
    int statut = EXIT_FAILURE;
    bool jeu = true;
    if(init(&window, &renderer) != 0)
    {
        goto Quit;
    }
    image = loadTexture("background/background.bmp", renderer);
    if(image == NULL)
    {
        goto Quit;
    }
    statut = EXIT_SUCCESS;
    SDL_GetWindowSize(window, &position->x, &position->y);
    position->x = position->x / 2 - 960;
    position->y = position->y / 2 - 540;
    SDL_QueryTexture(image, NULL, NULL, &position->w, &position->h);
    while(jeu)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    jeu = false;
                    break;
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                            jeu = false;
                            break;

                    }
                    break;
            }
        }
        SDL_RenderCopy(renderer, image, NULL, position);
        SDL_RenderPresent(renderer);
    }








    Quit:
    if(image!=NULL)
        SDL_DestroyTexture(image);
    if(renderer!=NULL)
        SDL_DestroyRenderer(renderer);
    if(window!=NULL)
        SDL_DestroyWindow(window);
    SDL_Quit();
    return statut;
}