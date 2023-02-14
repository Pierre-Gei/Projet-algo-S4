#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <math.h>
#include "affichage.h"
#include "fonctions.h"
#include "init.h"

int niveau1 (SDL_Window *window, SDL_Renderer *renderer)
{

    SDL_Texture *image = NULL;
    SDL_Rect position;
    SDL_Rect rectangle;
    SDL_Surface *perso = IMG_Load("sprites/aventurier1.png");
    SDL_Rect position_perso;
    SDL_Texture *texture = NULL;
    SDL_Texture *texture2 = NULL;
    SDL_Texture *texture3 = NULL;
    bool jeu = true;
    int statut = background(&window, &renderer, &image, &position);
    initVariable(&position, &rectangle, &position_perso, perso);
    SDL_SetRenderDrawColor(renderer,0,255,255,255);                 //A supprimer
    texture = SDL_CreateTextureFromSurface(renderer, perso);
    SDL_FreeSurface(perso);
    perso = IMG_Load("sprites/aventurier2.png");
    texture2 = SDL_CreateTextureFromSurface(renderer, perso);
    SDL_FreeSurface(perso);
    SDL_QueryTexture(texture, NULL, NULL, &position_perso.w, &position_perso.h);
    texture3 = texture;

    if (statut == -1)
        goto Quit;
    while (jeu)
    {
        SDL_Delay(39);
        SDL_Event event;
        affichage_background(&renderer,&image,&position);
        SDL_RenderDrawRect(renderer,&rectangle);
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            // case SDL_QUIT:
            //     jeu = false;
            //     break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    statut = menu_jeu(window, renderer, 75, 20);
                    if (statut == -1)
                        goto Quit;
                    else if(statut == 0)
                    {
                        printf("continue");
                    }
                   

                    break;
                case SDLK_RIGHT:

                    texture3 = deplacement_droit(&position_perso, &position, texture, texture2, texture3);
                    break;

                case SDLK_LEFT:
                    texture3 = deplacement_gauche(&position_perso, &position, texture, texture2, texture3);
                    break;

                case SDLK_UP:
                    if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_RIGHT] && SDL_GetKeyboardState(NULL)[SDL_SCANCODE_UP])
                    {
                        saut_parabolique(&position_perso, &position, texture, texture2, texture3, renderer, image, 1);
                    }
                    else if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_LEFT] && SDL_GetKeyboardState(NULL)[SDL_SCANCODE_UP])
                    {
                        saut_parabolique(&position_perso, &position, texture, texture2, texture3, renderer, image, -1);
                    }
                    else
                    {
                        saut_parabolique(&position_perso, &position, texture, texture2, texture3, renderer, image, 0);
                    }
                    break;
                }
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.sym)
                {
                case SDLK_RIGHT:
                    texture3 = texture;
                    break;
                case SDLK_LEFT:
                    texture3 = texture;
                    break;
                }
                break;
            }
        }
        SDL_RenderCopy(renderer, texture3, NULL, &position_perso);
        SDL_RenderPresent(renderer);
    }

Quit:

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, image, NULL, &position);
    if (image != NULL)
        SDL_DestroyTexture(image);
    if (texture != NULL)
        SDL_DestroyTexture(texture);
    if (texture2 != NULL)
        SDL_DestroyTexture(texture2);
    if (texture3 != NULL)
        SDL_DestroyTexture(texture3);
    

    // if (renderer != NULL)
    //     SDL_DestroyRenderer(renderer);
    // if (window != NULL)
    //     SDL_DestroyWindow(window);
    // SDL_Quit();
    return statut;
}