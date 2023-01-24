#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "affichage.h"
#include "fonctions.h"
int main()
{
    SDL_Window *window = NULL;
    SDL_Texture *image = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Rect *position;
    position = malloc(sizeof(SDL_Rect));
    position->x = 0;
    position->y = 0;
    bool jeu = true;
    int statut = background(&window, &renderer, &image, &position);
    SDL_Surface *perso = NULL;
    SDL_Rect *position_perso;
    SDL_Texture *texture = NULL;
    SDL_Texture *texture2 = NULL;
    SDL_Texture *texture3 = NULL;
    perso = IMG_Load("sprites/aventurier1.png");
    position_perso = malloc(sizeof(SDL_Rect));
    position_perso->x = position->w / 2 - perso->w / 2;
    position_perso->y = 850;
    texture = SDL_CreateTextureFromSurface(renderer, perso);
    SDL_FreeSurface(perso);
    perso = IMG_Load("sprites/aventurier2.png");
    texture2 = SDL_CreateTextureFromSurface(renderer, perso);
    SDL_FreeSurface(perso);
    SDL_QueryTexture(texture, NULL, NULL, &position_perso->w, &position_perso->h);
    texture3 = texture;

    if (statut == -1)
        goto Quit;
    while (jeu)
    {
        SDL_Delay(39);
        SDL_Event event;
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, image, NULL, position);
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
                case SDLK_RIGHT:
                    if (position_perso->x < position->w - position_perso->w)
                        position_perso->x += 7;

                    if (texture3 == texture)
                    {
                        texture3 = texture2;
                    }
                    else
                    {
                        texture3 = texture;
                    }
                    break;
                case SDLK_LEFT:
                    if (position_perso->x > 0)
                        position_perso->x -= 7;
                    break;

                case SDLK_UP:
                
        
                    break;
                }
                break;
            }
        }
        SDL_RenderCopy(renderer, texture3, NULL, position_perso);
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
    free(position);
    return statut;
}