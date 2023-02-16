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

int niveau1()
{
    SDL_Window *window = NULL;
    SDL_Texture *image = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Rect position;
    SDL_Rect rectangle;
    SDL_Rect rectangle2;
    rectangle2.x = 1100;
    rectangle2.y = 800;
    rectangle2.w = 100;
    rectangle2.h = 100;
    SDL_Surface *perso = IMG_Load("sprites/aventurier1.png");
    SDL_Rect position_perso;
    SDL_Texture *texture = NULL;
    SDL_Texture *texture2 = NULL;
    SDL_Texture *texture3 = NULL;
    bool jeu = true;
    int statut = background(&window, &renderer, &image, &position);
    initVariable(&position, &rectangle, &position_perso, perso);
    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255); // A supprimer
    texture = SDL_CreateTextureFromSurface(renderer, perso);
    SDL_FreeSurface(perso);
    perso = IMG_Load("sprites/aventurier2.png");
    texture2 = SDL_CreateTextureFromSurface(renderer, perso);
    SDL_FreeSurface(perso);
    SDL_QueryTexture(texture, NULL, NULL, &position_perso.w, &position_perso.h);
    texture3 = texture;

    int gravite = 5;
    int vitesse_saut = 10;
    int vitesse_max = 5;
    int saut_dir = 0;
    int saut_duree = 0;
    int dernier_saut = 0;
    int vx = 0;
    int texture_temps = 0;
    SDL_Event event;
    if (statut == -1)
        goto Quit;
    while (jeu)
    {
        affichage_background(&renderer, &image, &position);
        SDL_RenderDrawRect(renderer, &rectangle);
        SDL_RenderDrawRect(renderer, &rectangle2);
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
                    vx = vitesse_max;
                    break;

                case SDLK_LEFT:
                    vx = -vitesse_max;
                    break;

                case SDLK_UP:
                    if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_RIGHT] && SDL_GetKeyboardState(NULL)[SDL_SCANCODE_UP])
                    {
                        saut_dir = 1;
                        if (SDL_GetTicks() - dernier_saut > 1500)
                        {
                            saut_duree = 25;
                            dernier_saut = SDL_GetTicks();
                        }
                    }
                    else if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_LEFT] && SDL_GetKeyboardState(NULL)[SDL_SCANCODE_UP])
                    {
                        saut_dir = -1;
                        if (SDL_GetTicks() - dernier_saut > 1500)
                        {
                            saut_duree = 25;
                            dernier_saut = SDL_GetTicks();
                        }
                    }
                    else
                    {
                        if (SDL_GetTicks() - dernier_saut > 1500)
                        {
                            saut_duree = 25;
                            dernier_saut = SDL_GetTicks();
                        }
                    }
                    break;
                }
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.sym)
                {
                case SDLK_RIGHT:
                    vx = 0;
                    break;
                case SDLK_LEFT:
                    vx = 0;
                    break;
                case SDLK_UP:
                    saut_dir = 0;
                    break;
                }
                break;
            }
        }
        position_perso.x += vx;
        if (position_perso.x >= (position.w / 4) * 3)
        {
            position.x -= 7;
            position_perso.x -= vx;
        }

        if (position.x == -(position.w))
        {
            position.x = 0;
        }
        collision(&position_perso, &rectangle2);
        if (saut_duree > 0)
        {
            position_perso.y -= vitesse_saut;

            saut_duree--;
        }
        else
        {
            position_perso.y += gravite;
        }

        if (position_perso.y >= 800)
        {
            position_perso.y = 800;
        }

        if (SDL_GetTicks() - texture_temps > 100)
        {
            if (texture3 == texture)
            {
                texture3 = texture2;
            }
            else
            {
                texture3 = texture;
            }
            texture_temps = SDL_GetTicks();
        }

        if (vx > 0)
        {
            SDL_RenderCopy(renderer, texture3, NULL, &position_perso);
        }
        else if (vx < 0)
        {
            SDL_RenderCopyEx(renderer, texture3, NULL, &position_perso, 0, NULL, SDL_FLIP_HORIZONTAL);
        }
        else
        {
            SDL_RenderCopy(renderer, texture, NULL, &position_perso);
        }

        SDL_RenderPresent(renderer);
    }

Quit:
    if (image != NULL)
        SDL_DestroyTexture(image);
    if (texture != NULL)
        SDL_DestroyTexture(texture);
    if (texture2 != NULL)
        SDL_DestroyTexture(texture2);
    if (texture3 != NULL)
        SDL_DestroyTexture(texture3);
    if (renderer != NULL)
        SDL_DestroyRenderer(renderer);
    if (window != NULL)
        SDL_DestroyWindow(window);
    SDL_Quit();
    return statut;
}