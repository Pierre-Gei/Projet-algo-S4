#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
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

    int gravite = 6;
    int vitesse_saut = 15;
    int vitesse_max = 7;
    int saut_dir = 0;
    int saut_duree = 0;
    int dernier_saut = 0;
    int vx = 0;
    SDL_Event event;
    if (statut == -1)
        goto Quit;
    while (jeu)
    {
        // SDL_Delay(39);

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
                    // saut_dir = 1;

                    texture3 = deplacement_droit(&position_perso, &position, texture, texture2, texture3);
                    // collision(&position_perso, &rectangle2);
                    break;

                case SDLK_LEFT:
                    // texture3 = deplacement_gauche(&position_perso, &position, texture, texture2, texture3);
                    // collision(&position_perso, &rectangle2);
                    vx = -vitesse_max;
                    // saut_dir = -1;
                    break;

                case SDLK_UP:
                    if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_RIGHT] && SDL_GetKeyboardState(NULL)[SDL_SCANCODE_UP])
                    {
                        // saut_parabolique(&position_perso, &position, texture, texture2, texture3, renderer, image, 1);
                        saut_dir = 1;
                        if (SDL_GetTicks() - dernier_saut > 1500)
                        {
                            saut_duree = 20;
                            dernier_saut = SDL_GetTicks();
                        }
                    }
                    else if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_LEFT] && SDL_GetKeyboardState(NULL)[SDL_SCANCODE_UP])
                    {
                        // saut_parabolique(&position_perso, &position, texture, texture2, texture3, renderer, image, -1);
                        saut_dir = -1;
                        if (SDL_GetTicks() - dernier_saut > 1500)
                        {
                            saut_duree = 20;
                            dernier_saut = SDL_GetTicks();
                        }
                    }
                    else
                    {
                        // saut_parabolique(&position_perso, &position, texture, texture2, texture3, renderer, image, 0);
                        // saut_dir = 0;
                        if (SDL_GetTicks() - dernier_saut > 1500)
                        {
                            saut_duree = 20;
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
                    // texture3 = texture;
                    vx = 0;
                    break;
                case SDLK_LEFT:
                    // texture3 = texture;
                    vx = 0;
                    break;
                case SDLK_UP:
                    saut_dir = 0;
                    break;
                }
                break;
            }

            //  saut_duree--;
        }
        position_perso.x += vx;
        if (position_perso.x >= (position.w / 4) * 3)
        {
            position.x -= 10;
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

        SDL_RenderCopy(renderer, texture3, NULL, &position_perso);
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