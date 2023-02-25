#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <math.h>
#include "affichage.h"
#include "fonctions.h"
#include "init.h"

#define TAILLE_POLICE 60

int niveau1(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *police, int *morts, int x)
{
    SDL_Texture *image = NULL;
    SDL_Rect position;
    SDL_Rect sol_rect;
    SDL_Rect rectangle2;

    rectangle2.x = 1100;
    rectangle2.y = 700;
    rectangle2.w = 100;
    rectangle2.h = 100;
    SDL_Surface *perso = IMG_Load("sprites/aventurier1.png");
    SDL_Surface *enemi1 = IMG_Load("sprites/aventurier1.png");
    SDL_Rect position_perso;
    SDL_Texture *texture = NULL;
    SDL_Texture *texture2 = NULL;
    SDL_Texture *texture3 = NULL;
    SDL_Texture *enemi = NULL;

    SDL_Color couleur = {255, 255, 255, 255};
    bool jeu = true;
    int statut = background(&window, &renderer, &image, &position);
    initVariable(&position, &sol_rect, &position_perso, perso);
    SDL_Rect fond_position_initiale = position;
    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255); // A supprimer
    texture = SDL_CreateTextureFromSurface(renderer, perso);
    SDL_FreeSurface(perso);
    perso = IMG_Load("sprites/aventurier2.png");
    enemi = SDL_CreateTextureFromSurface(renderer, enemi1);
    texture2 = SDL_CreateTextureFromSurface(renderer, perso);
    SDL_FreeSurface(perso);
    SDL_QueryTexture(texture, NULL, NULL, &position_perso.w, &position_perso.h);
    texture3 = texture;

    int vie_initiale = 1;
    int vie_restante = vie_initiale;

    // chronomètre
    SDL_Rect position_chrono;
    SDL_Texture *tChrono = NULL;
    Uint32 temps_début = SDL_GetTicks();
    Uint32 temps_ecoule = 0;
    char temps[20];

    // compteur de morts
    SDL_Rect position_morts;
    SDL_Texture *tMorts = NULL;
    char morts_str[20];

    int gravite = 5;
    int vitesse_saut = 12;
    int vitesse_max = 5;
    int dir = 1;
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
        SDL_RenderDrawRect(renderer, &sol_rect);
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
                    vx = 0;
                    Uint32 temps_pause = SDL_GetTicks();
                    statut = menu_jeu(window, renderer, 75, 20, x, image, fond_position_initiale);
                    if (statut == -1)
                        goto Quit;
                    else if (statut == 1)
                    {
                        position_perso.x = position.w/2 - position_perso.w/2;
                        position_perso.y = sol_rect.y - position_perso.h;
                        temps_début = SDL_GetTicks();
                        texture3 = texture2;
                        dir = 1;
                    }
                    if (statut != 1)
                    {
                        // reprendre le chrono
                        temps_début += SDL_GetTicks() - temps_pause;
                    }
                    break;
                case SDLK_RIGHT:
                    vx = vitesse_max;
                    dir = 1;
                    break;

                case SDLK_LEFT:
                    vx = -vitesse_max;
                    dir = -1;
                    break;

                case SDLK_UP:
                    if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_RIGHT] && SDL_GetKeyboardState(NULL)[SDL_SCANCODE_UP])
                    {
                        dir = 1;
                        if (SDL_GetTicks() - dernier_saut > 1500)
                        {
                            saut_duree = 20;
                            dernier_saut = SDL_GetTicks();
                        }
                    }
                    else if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_LEFT] && SDL_GetKeyboardState(NULL)[SDL_SCANCODE_UP])
                    {
                        dir = -1;
                        if (SDL_GetTicks() - dernier_saut > 1500)
                        {
                            saut_duree = 20;
                            dernier_saut = SDL_GetTicks();
                        }
                    }
                    else
                    {
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
                    vx = 0;
                    break;
                case SDLK_LEFT:
                    vx = 0;
                    break;
                }
                break;
            }
        }
        // Calcul du temps écoulé
        temps_ecoule = SDL_GetTicks() - temps_début;
        int minutes = (int)(temps_ecoule / 1000) / 60;
        int secondes = (int)(temps_ecoule / 1000) % 60;

        // Affichage du temps écoulé
        sprintf(temps, "%02d:%02d", minutes, secondes);
        affichage_text_niveau(&tChrono, police, &position_chrono, 0, 0, &renderer, temps, couleur);

        // Affichage du nombre de morts
        sprintf(morts_str, "Morts: %03d", *morts);
        affichage_text_niveau(&tMorts, police, &position_morts, position.w - position_morts.w, 0, &renderer, morts_str, couleur);

        position_perso.x += vx;
        // Déplacement de l'arrière plan quand le personnage atteint les 3/4 de l'écran
        if (position_perso.x >= (position.w / 4) * 3)
        {
            position.x -= 7;
            position_perso.x -= vx;
        }

        // if (position.x == -(position.w))
        // {
        //     position.x = 0;
        // }

        if (saut_duree > 0)
        {
            position_perso.y -= vitesse_saut;

            saut_duree--;
        }
        else
        {
            position_perso.y += gravite;
        }

        collision_ecran(&position_perso, position, &vie_restante);

        collision(&position_perso, &sol_rect);
        // collision(&position_perso, &rectangle2);

        // Collision enemis avec le perso
        collision_enemis(&position_perso, &rectangle2, &enemi, &vie_restante);
        if (vie_restante != vie_initiale)
        {
            (*morts)++;
            statut = menu_game_over(window, renderer, 75, 20, x, image, fond_position_initiale);
            if (statut == -1)
                goto Quit;
            else if (statut == 1)
            {
                position_perso.x = 560;
                position_perso.y = sol_rect.y - position_perso.h;
                temps_début = SDL_GetTicks();
                texture3 = texture2;
                dir = 1;
                vx = 0;
                saut_duree = 0;
            }
            vie_restante++;
        }

        // Toutes les 100ms on change de sprite
        if (SDL_GetTicks() - texture_temps > 100)
        {
            changement_sprites(&texture3, texture, texture2);
            texture_temps = SDL_GetTicks();
        }

        SDL_Delay(10);

        SDL_RenderCopy(renderer, tMorts, NULL, &position_morts);
        SDL_RenderCopy(renderer, tChrono, NULL, &position_chrono);
        SDL_RenderCopy(renderer, enemi, NULL, &rectangle2);

        // Affichage du personnage
        if (vx > 0)
        {
            SDL_RenderCopy(renderer, texture3, NULL, &position_perso);
        }
        else if (vx < 0)
        {
            SDL_RenderCopyEx(renderer, texture3, NULL, &position_perso, 0, NULL, SDL_FLIP_HORIZONTAL);
        }
        else if (vx == 0 && dir == 1)
        {
            SDL_RenderCopy(renderer, texture, NULL, &position_perso);
        }
        else if (vx == 0 && dir == -1)
        {
            SDL_RenderCopyEx(renderer, texture, NULL, &position_perso, 0, NULL, SDL_FLIP_HORIZONTAL);
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
    if (tMorts != NULL)
        SDL_DestroyTexture(tMorts);
    if (tChrono != NULL)
        SDL_DestroyTexture(tChrono);
    if (enemi != NULL)
        SDL_DestroyTexture(enemi);

    return statut;
}