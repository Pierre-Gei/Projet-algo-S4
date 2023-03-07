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

#define MAX_RECOMPENSES 400

int niveau2(SDL_Window *window, SDL_Renderer *renderer, int *morts, int *meilleur_temps, int *recompenses, int *niveau, int x, int TAILLE_POLICE, int choix_skin)
{
    Astronaute astronaute;
    astronaute = initAstronaute(astronaute);
    Ennemi ennemi[5];
    for (int i = 0; i < 10; i++)
    {
        ennemi[i] = initEnnemi(ennemi[i]);
    }
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
    plateforme Lniv[10];
    for (int i = 0; i < 10; i++)
    {
        Lniv[i] = initplateforme(Lniv[i]);
    }

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
    for (int i = 0; i < 5; i++)
    {
        ennemi[i] = setEnnemi("sprites/ennemi1.png", "sprites/ennemi2.png", renderer);
    }
    for (int i = 0; i < 6; i++)
    {
        Lniv[i].texture = loadTexturePNG("background/sol.png", renderer, &Lniv[i].position);
    }
    for (int i = 6; i < 10; i++)
    {
        Lniv[i].texture = loadTexturePNG("background/blocs.png", renderer, &Lniv[i].position);
    }

    Lniv[0].position.x = 0;
    Lniv[0].position.y = position.h - Lniv[0].position.h;
    Lniv[0].position.w = position.w / 2;
    Lniv[1].position.x = position.w / 2;
    Lniv[1].position.y = position.h - Lniv[1].position.h;
    Lniv[1].position.w = position.w / 2;
    Lniv[2].position.x = position.w + 2 * astronaute.position.w;
    Lniv[2].position.y = position.h - Lniv[2].position.h;
    Lniv[2].position.w = position.w / 2;
    Lniv[3].position.x = position.w + 2 * astronaute.position.w + position.w / 2;
    Lniv[3].position.y = position.h - Lniv[3].position.h;
    Lniv[3].position.w = position.w / 2;
    Lniv[9].position.x = 2 * position.w + astronaute.position.w;
    Lniv[9].position.y = position.h - Lniv[4].position.h - astronaute.position.h - astronaute.position.h / 2;
    Lniv[7].position.x = 2 * position.w + astronaute.position.w * 4;
    Lniv[7].position.y = position.h - Lniv[5].position.h - astronaute.position.h * 3;
    Lniv[6].position.x = 2 * position.w + astronaute.position.w * 7;
    Lniv[6].position.y = position.h - Lniv[5].position.h - astronaute.position.h - astronaute.position.h / 2;
    Lniv[5].position.x = 2 * position.w + astronaute.position.w * 10;
    Lniv[5].position.y = position.h - Lniv[5].position.h;
    Lniv[5].position.w = position.w / 2;
    Lniv[8].position.x = 2 * position.w + astronaute.position.w * 9 + position.w / 2;
    Lniv[8].position.y = position.h - Lniv[4].position.h - astronaute.position.h - astronaute.position.h / 2;
    Lniv[4].position.x = 3 * position.w + astronaute.position.w * 8;
    Lniv[4].position.y = position.h - Lniv[4].position.h;
    Lniv[4].position.w = position.w / 2;
    vaisseau.position.x = 3 * position.w + astronaute.position.w * 8 + position.w / 4;
    vaisseau.position.y = position.h - Lniv[4].position.h - vaisseau.position.h;
    astronaute.position.x = astronaute.position.w;
    astronaute.position.y = Lniv[0].position.y - astronaute.position.h;
    ennemi[0].position.x = 1200;
    ennemi[0].position.w = 108;
    ennemi[0].position.h = 100;
    ennemi[0].position.y = Lniv[0].position.y - ennemi[0].position.h;
    ennemi[1].position.x = 2600;
    ennemi[1].position.w = 108;
    ennemi[1].position.h = 100;
    ennemi[1].position.y = Lniv[1].position.y - ennemi[1].position.h;
    ennemi[2].position.x = 1200;
    ennemi[2].position.w = 108;
    ennemi[2].position.h = 100;
    ennemi[2].position.y = Lniv[2].position.y - ennemi[2].position.h;
    ennemi[3].position.x = 1080;
    ennemi[3].position.w = 108;
    ennemi[3].position.h = 100;
    ennemi[3].position.y = Lniv[3].position.y - ennemi[3].position.h;
    ennemi[4].position.x = 1200;
    ennemi[4].position.w = 108;
    ennemi[4].position.h = 100;
    ennemi[4].position.y = Lniv[4].position.y - ennemi[4].position.h;

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
                        if (Lniv[0].collision == 1 || Lniv[2].collision == 1 || Lniv[3].collision == 1 || Lniv[4].collision == 1 || Lniv[5].collision == 1 || Lniv[6].collision == 1 || Lniv[7].collision == 1 || Lniv[1].collision == 1 || Lniv[8].collision == 1 || Lniv[9].collision == 1)
                        {
                            saut_duree = 20;
                        }
                    }
                    else if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_LEFT] && SDL_GetKeyboardState(NULL)[SDL_SCANCODE_UP])
                    {
                        dir = -1;
                        if (Lniv[0].collision == 1 || Lniv[2].collision == 1 || Lniv[3].collision == 1 || Lniv[4].collision == 1 || Lniv[5].collision == 1 || Lniv[6].collision == 1 || Lniv[7].collision == 1 || Lniv[1].collision == 1 || Lniv[8].collision == 1 || Lniv[9].collision == 1)
                        {
                            saut_duree = 20;
                        }
                    }
                    else
                    {
                        if (Lniv[0].collision == 1 || Lniv[2].collision == 1 || Lniv[3].collision == 1 || Lniv[4].collision == 1 || Lniv[5].collision == 1 || Lniv[6].collision == 1 || Lniv[7].collision == 1 || Lniv[1].collision == 1 || Lniv[8].collision == 1 || Lniv[9].collision == 1)
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
            for (int i = 0; i < 10; i++)
            {
                Lniv[i].position.x -= 6;
            }
            for (int i = 0; i < 5; i++)
            {
                ennemi[i].position.x -= 6;
            }
            vaisseau.position.x -= 6;
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
        for (int i = 0; i < 10; i++)
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
            animation_victoire(renderer, vaisseau, image, position);
            statut = menu_victoire(window, renderer, TAILLE_POLICE, 20, x, image, fond_position_initiale, MAX_RECOMPENSES - temps_secondes);

            // Animation victoire

            goto Quit;
        }

        // Collision enemis avec le perso
        for (int i = 0; i < 5; i++)
        {
            if (collision_enemis(&astronaute.position, &ennemi[i].position, &ennemi[i].sprite1, &astronaute.vie) == -1)
            {
                animation_mort(renderer, astronaute, image, position);
            }
            if (astronaute.vie != 1)
            {
                (*morts)++;
                statut = menu_game_over(window, renderer, TAILLE_POLICE, 20, x, image, fond_position_initiale);
                goto Quit;
            }
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
            for (int i = 0; i < 5; i++)
            {
                changement_sprites(&ennemi[i].sprite_finale, ennemi[i].sprite1, ennemi[i].sprite2);
                ennemi_temps = SDL_GetTicks();
            }
        }

        SDL_Delay(10);
        SDL_RenderClear(renderer);

        // SDL_SetTextureColorMod (aventurier_texture, 255, 0, 0); // Pour changer la couleur du perso
        affichage_background(&renderer, &image, &position);
        // Affichage de l'ennemi en fonction de la position du perso
        for (int i = 0; i < 5; i++)
        {
            position_perso_ennemi(astronaute.position, &ennemi[i].position, &ennemi[i].sprite_finale, &renderer, 2, 600);
        }
        for (int i = 0; i < 10; i++)
        {
            SDL_RenderCopy(renderer, Lniv[i].texture, NULL, &Lniv[i].position);
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
    for (int i = 0; i < 5; i++)
    {
        destroyEnnemi(&ennemi[i]);
    }
    destroyVaisseau(&vaisseau);
    if (image != NULL)
        SDL_DestroyTexture(image);
    if (tMorts != NULL)
        SDL_DestroyTexture(tMorts);
    if (tChrono != NULL)
        SDL_DestroyTexture(tChrono);
    for (int i = 0; i < 10; i++)
    {
        if (Lniv[i].texture != NULL)
            SDL_DestroyTexture(Lniv[i].texture);
    }
    return statut;
}
