#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "structure.h"
#include "affichage.h"
#include "menus.h"
#include "fonctions.h"
#include "init.h"

#define MAX_RECOMPENSES 300

int niveau1(SDL_Window *window, SDL_Renderer *renderer, int *morts, int *meilleur_temps, int *recompenses, int *niveau, int x, int TAILLE_POLICE, int choix_skin)
{
    Astronaute astronaute;
    astronaute = initAstronaute(astronaute);
    Ennemi ennemi;
    ennemi = initEnnemi(ennemi);
    vaisseau vaisseau;
    vaisseau = initvaisseau(vaisseau);
    vaisseau = setVaisseau(vaisseau, "sprites/vaisseau1.png", "sprites/vaisseau2.png", "sprites/vaisseau3.png", renderer);
    SDL_Texture *image = NULL;
    SDL_Texture *tMort_logo = NULL;
    SDL_Rect positionMort_logo;
    tMort_logo = loadTexturePNG("sprites/mort.png", renderer, &positionMort_logo);
    SDL_Rect position;
    Mix_Music *musique;
    musique = Mix_LoadMUS("Musiques/InGame.mp3");
    plateforme Lniv[3];
    for (int i = 0; i < 3; i++)
    {
        Lniv[i] = initplateforme(Lniv[i]);
    }
    SDL_Rect position_ennemi;

    SDL_Color couleur = {255, 255, 255, 255};
    bool jeu = true;
    int statut = background(&window, &renderer, &image, &position);
    position.x = 0;
    position.y = 0;
    SDL_Rect fond_position_initiale = position;

    // Remplir les champs et charger les textures de l'astronaute
    if (choix_skin == 1)
    {
        astronaute = setAstronaute("sprites/aventurier1.png", "sprites/aventurier2.png", "sprites/aventurier_mort1.png", "sprites/aventurier_mort2.png", "sprites/aventurier_mort3.png", 1, renderer, 6, 12);
    }
    else if (choix_skin == 2)
    {

        astronaute = setAstronaute("sprites/astronaute1.png", "sprites/astronaute2.png", "sprites/astronaute_mort1.png", "sprites/astronaute_mort2.png", "sprites/astronaute_mort3.png", 1, renderer, 6, 12);
    }
    // Remplir les champs et charger les textures de l'ennemi
    ennemi = setEnnemi("sprites/ennemi1.png", "sprites/ennemi2.png", renderer);
    for (int i = 0; i < 2; i++)
    {
        Lniv[i].texture = loadTexturePNG("background/sol.png", renderer, &Lniv[i].position);
    }
    Lniv[2].texture = loadTexturePNG("background/blocs.png", renderer, &Lniv[2].position);

    Lniv[0].position.x=0;
    Lniv[0].position.y=position.h - Lniv[0].position.h;
    Lniv[0].position.w=position.w;
    Lniv[1].position.x=position.w + Lniv[2].position.w*2;
    Lniv[1].position.y=position.h - Lniv[1].position.h;
    Lniv[1].position.w=position.w/2;
    Lniv[2].position.x=position.w + Lniv[2].position.w/2;
    Lniv[2].position.y=position.h - Lniv[1].position.h-astronaute.position.h;
    vaisseau.position.x=position.w + Lniv[2].position.w*2+position.w/4;
    vaisseau.position.y=position.h - Lniv[1].position.h- vaisseau.position.h;
    astronaute.position.x = astronaute.position.w;
    astronaute.position.y = Lniv[0].position.y - astronaute.position.h;
    ennemi.position.x = 1200;
    ennemi.position.w = 108;
    ennemi.position.h = 100;
    ennemi.position.y = Lniv[0].position.y - ennemi.position.h;

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
    Mix_PlayMusic(musique, -1);
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
                        if (Lniv[0].collision== 1 || Lniv[1].collision == 1 || Lniv[2].collision == 1)                        
                        {
                            saut_duree = 20;
                        }
                    }
                    else if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_LEFT] && SDL_GetKeyboardState(NULL)[SDL_SCANCODE_UP])
                    {
                        dir = -1;
                        if (Lniv[0].collision== 1 || Lniv[1].collision == 1 || Lniv[2].collision == 1 )
                        {
                            saut_duree = 20;
                        }
                    }
                    else
                    {
                        if (Lniv[0].collision== 1 || Lniv[1].collision == 1 || Lniv[2].collision == 1 )
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
        sprintf(morts_str, "%03d", *morts);
        affichage_text_niveau(&tMorts, TAILLE_POLICE, &position_morts, position.w - position_morts.w, 0, &renderer, morts_str, couleur);
        positionMort_logo.x = position.w - positionMort_logo.w - position_morts.w - 10;
        positionMort_logo.y = 10;
        positionMort_logo.w = 40;
        positionMort_logo.h = 40;

        astronaute.position.x += vx;
        // Déplacement de l'arrière plan quand le personnage atteint les 3/4 de l'écran
        if (astronaute.position.x >= (position.w / 3) * 2)
        {
            position.x -= 3;
            astronaute.position.x -= vx;
            for (int i = 0; i < 3; i++)
            {
                Lniv[i].position.x -= 6;
            }
            vaisseau.position.x-=6;
            astronaute.position.x = (position.w / 3) * 2 - 1;
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
        for (int i = 0; i <3; i++)
        {
            Lniv[i].collision = collision(&astronaute.position, &Lniv[i].position);
        }
        // Enregistrement du temps si c'est le meilleur
        if (collision(&astronaute.position, &vaisseau.position) != 0)
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
            if (*niveau == 1)
            {
                *niveau = 2;
            }
            animation_victoire(renderer,vaisseau,image,position);
            statut = menu_victoire(window, renderer, TAILLE_POLICE, 20, x, image, fond_position_initiale, MAX_RECOMPENSES - temps_secondes);
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
        // Affichage du fond
        affichage_background(&renderer, &image, &position);
        // Affichage de l'ennemi en fonction de la position du perso
        position_perso_ennemi(astronaute.position, &ennemi.position, &ennemi.sprite_finale, &renderer, 2, 600);
        for (int i = 0; i < 3; i++)
        {
            if (Lniv[i].position.x + Lniv[i].position.w > 0 && Lniv[i].position.x < position.w)
            {
                SDL_RenderCopy(renderer, Lniv[i].texture, NULL, &Lniv[i].position);
            }
            if (Lniv[i].position.x + Lniv[i].position.w < 0 && Lniv[i].texture != NULL)
            {
                SDL_DestroyTexture(Lniv[i].texture);
            }
        }
        SDL_RenderCopy(renderer, vaisseau.immobile, NULL, &vaisseau.position);
        
        SDL_RenderCopy(renderer, tMorts, NULL, &position_morts);
        SDL_RenderCopy(renderer, tChrono, NULL, &position_chrono);
        SDL_RenderCopy(renderer, tMort_logo, NULL, &positionMort_logo);

        // Affichage du personnage
        affiche_perso(&renderer, astronaute.sprite_finale, astronaute.sprite1, astronaute.position, vx, dir);

        SDL_RenderPresent(renderer);
    }

Quit:
    destroyAstronaute(&astronaute);
    destroyEnnemi(&ennemi);
    destroyVaisseau(&vaisseau);
    if (image != NULL)
        SDL_DestroyTexture(image);
    if (tMorts != NULL)
        SDL_DestroyTexture(tMorts);
    if (tChrono != NULL)
        SDL_DestroyTexture(tChrono);
    for (int i = 0; i < 3; i++)
    {
        if (Lniv[i].texture != NULL)
            SDL_DestroyTexture(Lniv[i].texture);
    }
    if (musique != NULL)
        Mix_FreeMusic(musique);
    return statut;
}
