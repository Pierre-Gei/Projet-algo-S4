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

    SDL_Rect position_ennemi;

    SDL_Rect position_perso;
    SDL_Texture *aventurier_sprite1 = NULL;
    SDL_Texture *aventurier_sprite2 = NULL;
    SDL_Texture *aventurier_texture = NULL;
    SDL_Texture *ennemi_sprite1 = NULL;
    SDL_Texture *ennemi_sprite2 = NULL;
    SDL_Texture *ennemi_texture = NULL;
    SDL_Texture *sol = NULL;

    SDL_Color couleur = {255, 255, 255, 255};
    bool jeu = true;
    int statut = background(&window, &renderer, &image, &position);
    int collisionPerso = 0;
    position.x = 0;
    position.y = 0;
    SDL_Rect fond_position_initiale = position;

    aventurier_sprite1 = loadTexturePNG("sprites/aventurier1.png", renderer, &position_perso);
    aventurier_sprite2 = loadTexturePNG("sprites/aventurier2.png", renderer, &position_perso);
    aventurier_texture = aventurier_sprite1;
    sol = loadTexturePNG("background/sol.png", renderer, &sol_rect);
    ennemi_sprite1 = loadTexturePNG("sprites/ennemi1.png", renderer, &position_ennemi);
    ennemi_sprite2 = loadTexturePNG("sprites/ennemi2.png", renderer, &position_ennemi);
    ennemi_texture = ennemi_sprite1;
    sol_rect.x = 0;
    sol_rect.y = position.h - sol_rect.h;
    sol_rect.w = position.w; // pour faire des tests avec un sol de largeur d'écran
    position_perso.x = position.w / 2 - position_perso.w / 2;
    position_perso.y = sol_rect.y - position_perso.h;
    position_ennemi.x = 1200;
    position_ennemi.w = 108;
    position_ennemi.h = 100;
    position_ennemi.y = sol_rect.y - position_ennemi.h;

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

    int gravite = 7;
    int vitesse_saut = 12;
    int vitesse_max = 6;
    int dir = 1;
    int saut_duree = 0;
    int dernier_saut = 0;
    int vx = 0;
    int texture_temps = 0;
    int ennemi_temps = 0;
    SDL_Event event;
    if (statut == -1)
        goto Quit;
    while (jeu)
    {
        affichage_background(&renderer, &image, &position);
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
                        position_perso.x = position.w / 2 - position_perso.w / 2;
                        position_perso.y = sol_rect.y - position_perso.h;
                        temps_début = SDL_GetTicks();
                        aventurier_texture = aventurier_sprite2;
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
                        if (collisionPerso == 1)
                        {
                            saut_duree = 20;
                        }
                    }
                    else if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_LEFT] && SDL_GetKeyboardState(NULL)[SDL_SCANCODE_UP])
                    {
                        dir = -1;
                        if (collisionPerso == 1)
                        {
                            saut_duree = 20;
                        }
                    }
                    else
                    {
                        if (collisionPerso == 1)
                        {
                            saut_duree = 20;
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

        collisionPerso = collision(&position_perso, &sol_rect);

        // Collision enemis avec le perso
        collision_enemis(&position_perso, &position_ennemi, &ennemi_sprite1, &vie_restante);
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
                aventurier_texture = aventurier_sprite2;
                dir = 1;
                vx = 0;
                saut_duree = 0;
            }
            vie_restante++;
        }

        // Toutes les 100ms on change de sprite
        if (SDL_GetTicks() - texture_temps > 100)
        {
            changement_sprites(&aventurier_texture, aventurier_sprite1, aventurier_sprite2);
            texture_temps = SDL_GetTicks();
        }

        // Toutes les 100ms on change de sprite
        if (SDL_GetTicks() - ennemi_temps > 250)
        {
            changement_sprites(&ennemi_texture, ennemi_sprite1, ennemi_sprite2);
            ennemi_temps = SDL_GetTicks();
        }

        SDL_Delay(10);
        // Affichage de l'ennemi en fonction de la position du perso
        position_perso_ennemi(position_perso, &position_ennemi, &ennemi_texture, &renderer, 2, 300);
        SDL_RenderCopy(renderer, sol, NULL, &sol_rect);
        SDL_RenderCopy(renderer, tMorts, NULL, &position_morts);
        SDL_RenderCopy(renderer, tChrono, NULL, &position_chrono);

        // Affichage du personnage
        affiche_perso(&renderer, aventurier_texture, aventurier_sprite1, position_perso, vx, dir);

        SDL_RenderPresent(renderer);
    }

Quit:
    if (image != NULL)
        SDL_DestroyTexture(image);
    if (aventurier_sprite1 != NULL)
        SDL_DestroyTexture(aventurier_sprite1);
    if (aventurier_sprite2 != NULL)
        SDL_DestroyTexture(aventurier_sprite2);
    if (aventurier_texture != NULL)
        SDL_DestroyTexture(aventurier_texture);
    if (tMorts != NULL)
        SDL_DestroyTexture(tMorts);
    if (tChrono != NULL)
        SDL_DestroyTexture(tChrono);
    if (ennemi_sprite1 != NULL)
        SDL_DestroyTexture(ennemi_sprite1);
    if (ennemi_sprite2 != NULL)
        SDL_DestroyTexture(ennemi_sprite2);
    if (ennemi_texture != NULL)
        SDL_DestroyTexture(ennemi_texture);
    if (sol != NULL)
        SDL_DestroyTexture(sol);

    return statut;
}