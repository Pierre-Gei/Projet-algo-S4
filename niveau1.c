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
#include "structure.h"
#include "affichage.h"
#include "fonctions.h"
#include "init.h"

#define MAX_RECOMPENSES 300

int niveau1(SDL_Window *window, SDL_Renderer *renderer, int *morts, int *meilleur_temps, int *recompenses, int x, int TAILLE_POLICE)
{
    Astronaute astronaute;
    astronaute = initAstronaute(astronaute);
    Ennemi ennemi;
    ennemi = initEnnemi(ennemi);
    SDL_Texture *image = NULL;
    SDL_Rect position;
    SDL_Rect sol_rect;
    SDL_Rect sol_rect2;
    SDL_Rect sol_rect3;
    SDL_Rect sol_rect4;
    SDL_Rect sol_rect5;
    SDL_Rect sol_rect6;
    SDL_Rect sol_rect7;
    SDL_Rect sol_rect8;
    SDL_Rect vict_rect;

    SDL_Rect position_ennemi;

    SDL_Texture *sol = NULL;
    SDL_Texture *sol2 = NULL;
    SDL_Texture *sol3 = NULL;
    SDL_Texture *sol4 = NULL;
    SDL_Texture *sol5 = NULL;
    SDL_Texture *sol6 = NULL;
    SDL_Texture *sol7 = NULL;
    SDL_Texture *sol8 = NULL;
    SDL_Texture *vict = NULL;

    SDL_Color couleur = {255, 255, 255, 255};
    bool jeu = true;
    int statut = background(&window, &renderer, &image, &position);
    int collisionPerso = 0;
    int collisionPerso2 = 0;
    int collisionPerso3 = 0;
    int collisionPerso4 = 0;
    int collisionPerso5 = 0;
    int collisionPerso6 = 0;
    int collisionPerso7 = 0;
    int collisionPerso8 = 0;
    position.x = 0;
    position.y = 0;
    SDL_Rect fond_position_initiale = position;
    SDL_Rect *Lniv[8];

    // Remplir les champs et charger les textures de l'astronaute
    astronaute = setAstronaute("sprites/aventurier1.png", "sprites/aventurier2.png", "sprites/aventurier_mort1.png", "sprites/aventurier_mort2.png", "sprites/aventurier_mort3.png", 1, renderer, 6, 12);

    // Remplir les champs et charger les textures de l'ennemi
    ennemi = setEnnemi("sprites/ennemi1.png", "sprites/ennemi2.png", renderer);

    sol = loadTexturePNG("background/sol.png", renderer, &sol_rect);
    sol2 = loadTexturePNG("background/sol.png", renderer, &sol_rect2);
    sol3 = loadTexturePNG("background/sol.png", renderer, &sol_rect3);
    sol4 = loadTexturePNG("background/sol.png", renderer, &sol_rect4);
    sol5 = loadTexturePNG("background/sol.png", renderer, &sol_rect5);
    sol6 = loadTexturePNG("background/sol.png", renderer, &sol_rect6);
    sol7 = loadTexturePNG("background/sol.png", renderer, &sol_rect7);
    sol8 = loadTexturePNG("background/sol.png", renderer, &sol_rect8);
    vict = loadTexturePNG("background/sol.png", renderer, &vict_rect);
    sol_rect.x = 0;
    sol_rect.y = position.h - sol_rect.h;
    sol_rect.w = position.w; // pour faire des tests avec un sol de largeur d'écran
    Lniv[0] = &sol_rect;
    sol_rect2.x = position.w + 2 * astronaute.position.w;
    sol_rect2.y = position.h - sol_rect2.h;
    sol_rect2.w = position.w; // pour faire des tests avec un sol de largeur d'écran
    Lniv[1] = &sol_rect2;
    sol_rect3.x = 2 * position.w + astronaute.position.w;
    sol_rect3.y = position.h - sol_rect.h - astronaute.position.h - astronaute.position.h / 2;
    sol_rect3.w = astronaute.position.w * 4; // pour faire des tests avec un sol de largeur d'écran
    Lniv[2] = &sol_rect3;
    sol_rect4.x = 2 * position.w + astronaute.position.w * 4;
    sol_rect4.y = position.h - sol_rect.h - astronaute.position.h * 3;
    sol_rect4.w = astronaute.position.w * 4; // pour faire des tests avec un sol de largeur d'écran
    Lniv[3] = &sol_rect4;
    sol_rect5.x = 2 * position.w + astronaute.position.w * 7;
    sol_rect5.y = position.h - sol_rect.h - astronaute.position.h - astronaute.position.h / 2;
    sol_rect5.w = astronaute.position.w * 4; // pour faire des tests avec un sol de largeur d'écran
    Lniv[4] = &sol_rect5;
    sol_rect6.x = 2 * position.w + astronaute.position.w * 10;
    sol_rect6.y = position.h - sol_rect2.h;
    sol_rect6.w = position.w / 2; // pour faire des tests avec un sol de largeur d'écran
    Lniv[5] = &sol_rect6;
    sol_rect7.x = 2 * position.w + astronaute.position.w * 9 + position.w / 2;
    sol_rect7.y = position.h - sol_rect.h - astronaute.position.h - astronaute.position.h / 2;
    sol_rect7.w = position.w / 2; // pour faire des tests avec un sol de largeur d'écran
    Lniv[6] = &sol_rect7;
    // sol_rect8.x = 3 * position.w + astronaute.position.w * 8;
    // sol_rect8.y = position.h - sol_rect.h;
    // sol_rect8.w = position.w / 2; // pour faire des tests avec un sol de largeur d'écran
    // Lniv[7] = &sol_rect8;
    astronaute.position.x = astronaute.position.w;
    astronaute.position.y = sol_rect.y - astronaute.position.h;
    ennemi.position.x = 1200;
    ennemi.position.w = 108;
    ennemi.position.h = 100;
    ennemi.position.y = sol_rect.y - ennemi.position.h;
    vict_rect.x = 0;
    vict_rect.y = position.h - sol_rect.h - 10;
    vict_rect.w = 10; // pour faire des tests avec un sol de largeur d'écran
    vict_rect.h = 10;
    Lniv[7] = &vict_rect;

    int vie_restante = 1;

    // chronomètre
    SDL_Rect position_chrono;
    SDL_Texture *tChrono = NULL;
    Uint32 temps_debut = SDL_GetTicks();
    Uint32 temps_ecoule = 0;
    char temps[20];

    // compteur de morts
    SDL_Rect position_morts;
    SDL_Texture *tMorts = NULL;
    char morts_str[20];

    int gravite = 7;

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
                    statut = menu_jeu(window, renderer, TAILLE_POLICE, 20, x, image, fond_position_initiale);
                    if (statut == -1 || statut == 1)
                        goto Quit;

                    // reprendre le chrono
                    temps_debut += SDL_GetTicks() - temps_pause;
                    break;
                case SDLK_RIGHT:
                    vx = astronaute.vitesse_max;
                    dir = 1;
                    break;

                case SDLK_LEFT:
                    vx = -astronaute.vitesse_max;
                    dir = -1;
                    break;

                case SDLK_UP:
                    if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_RIGHT] && SDL_GetKeyboardState(NULL)[SDL_SCANCODE_UP])
                    {
                        dir = 1;
                        if (collisionPerso == 1 || collisionPerso2 == 1 || collisionPerso3 == 1 || collisionPerso4 == 1 || collisionPerso5 == 1 || collisionPerso6 == 1 || collisionPerso7 == 1 || collisionPerso8 == 1)
                        {
                            saut_duree = 20;
                        }
                    }
                    else if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_LEFT] && SDL_GetKeyboardState(NULL)[SDL_SCANCODE_UP])
                    {
                        dir = -1;
                        if (collisionPerso == 1 || collisionPerso2 == 1 || collisionPerso3 == 1 || collisionPerso4 == 1 || collisionPerso5 == 1 || collisionPerso6 == 1 || collisionPerso7 == 1 || collisionPerso8 == 1)
                        {
                            saut_duree = 20;
                        }
                    }
                    else
                    {
                        if (collisionPerso == 1 || collisionPerso2 == 1 || collisionPerso3 == 1 || collisionPerso4 == 1 || collisionPerso5 == 1 || collisionPerso6 == 1 || collisionPerso7 == 1 || collisionPerso8 == 1)
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
        temps_ecoule = SDL_GetTicks() - temps_debut;
        int minutes = (int)(temps_ecoule / 1000) / 60;
        int secondes = (int)(temps_ecoule / 1000) % 60;
        int temps_secondes = (int)(temps_ecoule / 1000);

        // Affichage du temps écoulé
        sprintf(temps, "%02d:%02d", minutes, secondes);
        affichage_text_niveau(&tChrono, TAILLE_POLICE, &position_chrono, 0, 0, &renderer, temps, couleur);

        // Affichage du nombre de morts
        sprintf(morts_str, "Morts: %03d", *morts);
        affichage_text_niveau(&tMorts, TAILLE_POLICE, &position_morts, position.w - position_morts.w, 0, &renderer, morts_str, couleur);

        astronaute.position.x += vx;
        // Déplacement de l'arrière plan quand le personnage atteint les 3/4 de l'écran
        if (astronaute.position.x >= (position.w / 4) * 3)
        {
            position.x -= 3;
            astronaute.position.x -= vx;
            for (int i = 0; i < 8; i++)
            {
                Lniv[i]->x -= 6;
            }
            astronaute.position.x = (position.w / 4) * 3 - 1;
        }
        if (saut_duree > 0)
        {
            astronaute.position.y -= astronaute.vitesse_saut;

            saut_duree--;
        }
        else
        {
            astronaute.position.y += gravite;
        }

        collision_ecran(&astronaute.position, position, &astronaute.vie);

        collisionPerso = collision(&astronaute.position, &sol_rect);
        collisionPerso2 = collision(&astronaute.position, &sol_rect2);
        collisionPerso3 = collision(&astronaute.position, &sol_rect3);
        collisionPerso4 = collision(&astronaute.position, &sol_rect4);
        collisionPerso5 = collision(&astronaute.position, &sol_rect5);
        collisionPerso6 = collision(&astronaute.position, &sol_rect6);
        collisionPerso7 = collision(&astronaute.position, &sol_rect7);
        collisionPerso8 = collision(&astronaute.position, &sol_rect8);

        // Enregistrement du temps si c'est le meilleur
        if (collision(&astronaute.position, &vict_rect) != 0)
        {
            if (*meilleur_temps == 0)
            {
                *meilleur_temps = temps_secondes;
            }
            else if (temps_secondes < *meilleur_temps)
            {
                *meilleur_temps = temps_secondes;
            }
            *recompenses = *recompenses + MAX_RECOMPENSES - temps_secondes;
            statut = menu_victoire(window, renderer, TAILLE_POLICE, 20, x, image, fond_position_initiale);

            // Animation victoire

            goto Quit;
        }

        // Collision enemis avec le perso
        if (collision_enemis(&astronaute.position, &ennemi.position, &ennemi.sprite1, &astronaute.vie) == -1)
        {
            animation_mort(renderer, astronaute, image, position);
        }
        if (astronaute.vie != 1)
        {
            (*morts)++;
            statut = menu_game_over(window, renderer, TAILLE_POLICE, 20, x, image, fond_position_initiale);
            goto Quit;
        }

        // Toutes les 100ms on change de sprite
        if (SDL_GetTicks() - texture_temps > 100)
        {
            changement_sprites(&astronaute.sprite_finale, astronaute.sprite1, astronaute.sprite2);
            texture_temps = SDL_GetTicks();
        }

        // Toutes les 100ms on change de sprite
        if (SDL_GetTicks() - ennemi_temps > 250)
        {
            changement_sprites(&ennemi.sprite_finale, ennemi.sprite1, ennemi.sprite2);
            ennemi_temps = SDL_GetTicks();
        }

        SDL_Delay(10);
        SDL_RenderClear(renderer);

        // SDL_SetTextureColorMod (aventurier_texture, 255, 0, 0); // Pour changer la couleur du perso
        affichage_background(&renderer, &image, &position);
        // Affichage de l'ennemi en fonction de la position du perso
        position_perso_ennemi(astronaute.position, &ennemi.position, &ennemi.sprite_finale, &renderer, 2, 600);
        SDL_RenderCopy(renderer, sol, NULL, &sol_rect);
        SDL_RenderCopy(renderer, sol2, NULL, &sol_rect2);
        SDL_RenderCopy(renderer, sol3, NULL, &sol_rect3);
        SDL_RenderCopy(renderer, sol4, NULL, &sol_rect4);
        SDL_RenderCopy(renderer, sol5, NULL, &sol_rect5);
        SDL_RenderCopy(renderer, sol6, NULL, &sol_rect6);
        SDL_RenderCopy(renderer, sol7, NULL, &sol_rect7);
        SDL_RenderCopy(renderer, sol8, NULL, &sol_rect8);
        SDL_RenderCopy(renderer, tMorts, NULL, &position_morts);
        SDL_RenderCopy(renderer, tChrono, NULL, &position_chrono);

        // Affichage du personnage
        affiche_perso(&renderer, astronaute.sprite_finale, astronaute.sprite1, astronaute.position, vx, dir);

        SDL_RenderPresent(renderer);
    }

Quit:
    destroyAstronaute(&astronaute);
    destroyEnnemi(&ennemi);
    if (image != NULL)
        SDL_DestroyTexture(image);
    if (tMorts != NULL)
        SDL_DestroyTexture(tMorts);
    if (tChrono != NULL)
        SDL_DestroyTexture(tChrono);
    if (sol != NULL)
        SDL_DestroyTexture(sol);
    if (sol2 != NULL)
        SDL_DestroyTexture(sol2);
    if (sol3 != NULL)
        SDL_DestroyTexture(sol3);
    if (sol4 != NULL)
        SDL_DestroyTexture(sol4);
    if (sol5 != NULL)
        SDL_DestroyTexture(sol5);
    if (sol6 != NULL)
        SDL_DestroyTexture(sol6);
    if (sol7 != NULL)
        SDL_DestroyTexture(sol7);
    if (sol8 != NULL)
        SDL_DestroyTexture(sol8);

    return statut;
}