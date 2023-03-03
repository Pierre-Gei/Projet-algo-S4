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
#include "fonctions.h"
#include "init.h"
#include "niveau1.h"
#include "save.h"

#define TAILLE_POLICE 75
#define INTERLIGNE 20

int main()
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Surface *texte_Surface = NULL;
    SDL_Texture *tTitre = NULL;
    SDL_Texture *tJouer = NULL;
    SDL_Texture *tCharger = NULL;
    SDL_Texture *tParametres = NULL;
    SDL_Texture *tSauvegarder = NULL;
    SDL_Texture *tQuitter = NULL;
    SDL_Texture *tValidation_save = NULL;
    SDL_Texture *tValidation_charger = NULL;
    SDL_Texture *fond = NULL;
    SDL_Rect position_fond;
    int fondtest = 0;
    int window_width = 0;
    int window_height = 0;
    bool jeu = true;
    int statut = 0;
    int tab_morts[] = {0, 0};
    int tab_temps[] = {0, 0};
    int recompenses = 0;
    int morts = 0;
    int niveau = 1;
    int meilleur_temps = 0;
    int save = 0;

    // compteur de morts
    SDL_Rect position_morts;
    SDL_Texture *tMorts = NULL;
    char morts_str[20];

    SDL_Point souris;

    SDL_Color couleurBlanche = {255, 255, 255, 255};
    SDL_Color couleurJaune = {255, 255, 0, 255};
    init(&window, &renderer);
    SDL_GetWindowSize(window, &window_width, &window_height);

    initText(couleurBlanche, &texte_Surface, &tJouer, &renderer, TAILLE_POLICE, "Jouer");
    int x = (window_width - texte_Surface->w) / 2;
    int y = (window_height - 4 * texte_Surface->h - 3 * INTERLIGNE) / 2;
    SDL_Rect rectJouer = {x, (window_height - 4 * texte_Surface->h - 3 * INTERLIGNE) / 2, texte_Surface->w, texte_Surface->h};
    SDL_FreeSurface(texte_Surface);

    initText(couleurBlanche, &texte_Surface, &tTitre, &renderer, 200, "Astroventure");
    SDL_Rect rectTitre = {window_width / 2 - texte_Surface->w / 2, y / 2 - texte_Surface->h / 2, texte_Surface->w, texte_Surface->h};
    SDL_FreeSurface(texte_Surface);

    initText(couleurBlanche, &texte_Surface, &tCharger, &renderer, TAILLE_POLICE, "Charger");
    SDL_Rect rectCharger = {x, (window_height - 4 * texte_Surface->h - 3 * INTERLIGNE) / 2 + texte_Surface->h + INTERLIGNE, texte_Surface->w, texte_Surface->h};
    SDL_FreeSurface(texte_Surface);

    initText(couleurBlanche, &texte_Surface, &tParametres, &renderer, TAILLE_POLICE, "Commandes");
    SDL_Rect rectParam = {x, (window_height - 4 * texte_Surface->h - 3 * INTERLIGNE) / 2 + 2 * texte_Surface->h + 2 * INTERLIGNE, texte_Surface->w, texte_Surface->h};
    SDL_FreeSurface(texte_Surface);

    initText(couleurBlanche, &texte_Surface, &tSauvegarder, &renderer, TAILLE_POLICE, "Sauvegarder");
    SDL_Rect rectSauv = {x, (window_height - 4 * texte_Surface->h - 3 * INTERLIGNE) / 2 + 3 * texte_Surface->h + 3 * INTERLIGNE, texte_Surface->w, texte_Surface->h};
    SDL_FreeSurface(texte_Surface);

    initText(couleurBlanche, &texte_Surface, &tQuitter, &renderer, TAILLE_POLICE, "Quitter");
    SDL_Rect rectQuit = {x, (window_height - 4 * texte_Surface->h - 3 * INTERLIGNE) / 2 + 4 * texte_Surface->h + 4 * INTERLIGNE, texte_Surface->w, texte_Surface->h};
    SDL_FreeSurface(texte_Surface);

    initText(couleurBlanche, &texte_Surface, &tValidation_save, &renderer, 50, "Sauvegarde effectuee");
    SDL_Rect rectValidation_save = {window_width - texte_Surface->w, window_height - texte_Surface->h, texte_Surface->w, texte_Surface->h};
    SDL_FreeSurface(texte_Surface);

    initText(couleurBlanche, &texte_Surface, &tValidation_charger, &renderer, 50, "Chargement effectue");
    SDL_Rect rectValidation_charger = {window_width - texte_Surface->w, window_height - texte_Surface->h, texte_Surface->w, texte_Surface->h};
    SDL_FreeSurface(texte_Surface);

    fondtest = background(&window, &renderer, &fond, &position_fond);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    while (jeu)
    {
        SDL_Delay(39);
        SDL_Event event;
        SDL_GetMouseState(&souris.x, &souris.y);
        changement_couleur_inRect(TAILLE_POLICE, couleurJaune, couleurBlanche, &renderer, &tJouer, "Jouer", souris, rectJouer);
        changement_couleur_inRect(TAILLE_POLICE, couleurJaune, couleurBlanche, &renderer, &tCharger, "Charger", souris, rectCharger);
        changement_couleur_inRect(TAILLE_POLICE, couleurJaune, couleurBlanche, &renderer, &tParametres, "Commandes", souris, rectParam);
        changement_couleur_inRect(TAILLE_POLICE, couleurJaune, couleurBlanche, &renderer, &tSauvegarder, "Sauvegarder", souris, rectSauv);
        changement_couleur_inRect(TAILLE_POLICE, couleurJaune, couleurBlanche, &renderer, &tQuitter, "Quitter", souris, rectQuit);

        while (SDL_PollEvent(&event))
        {

            switch (event.type)
            {
            case SDL_QUIT:
                jeu = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    // boutton Jouer
                    if (SDL_PointInRect(&souris, &rectJouer))
                    {
                        // printf("Jouer ! \n");
                        // while (niveau1(window, renderer, &tab_morts[0], &tab_temps[0], x, TAILLE_POLICE) == 1)
                        // {
                        // }
                        // SDL_RenderPresent(renderer);
                        choix_niveau(window, renderer, TAILLE_POLICE, INTERLIGNE, x, fond, position_fond, niveau, tab_morts, tab_temps, &recompenses);
                    }
                    // boutton Charger
                    if (SDL_PointInRect(&souris, &rectCharger))
                    {
                        printf("Charger ! \n");
                        chargement(&recompenses, &morts, &meilleur_temps, &niveau, tab_morts, tab_temps, 2);
                        save = -25;
                    }
                    // bouton Parametres
                    if (SDL_PointInRect(&souris, &rectParam))
                    {
                        printf("Parametres ! \n");
                        parametre(window, renderer, TAILLE_POLICE, INTERLIGNE, fond, position_fond);
                    }
                    // bouton Sauvegarder
                    if (SDL_PointInRect(&souris, &rectSauv))
                    {
                        printf("Sauvegarder ! \n");
                        sauvegarde(recompenses, morts, meilleur_temps, niveau, tab_morts, tab_temps, 2);
                        save = 25;
                    }
                    // bouton Quitter
                    if (SDL_PointInRect(&souris, &rectQuit))
                    {
                        printf("Quitter ! \n");
                        jeu = false;
                    }
                }
                break;
            }
        }
        // Affichage du nombre de morts
        morts = tab_morts[0] + tab_morts[1];
        sprintf(morts_str, "Morts: %03d", morts);
        affichage_text_niveau(&tMorts, TAILLE_POLICE, &position_morts, position_fond.w - position_morts.w, 0, &renderer, morts_str, couleurBlanche);

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, fond, NULL, &position_fond);
        SDL_RenderCopy(renderer, tTitre, NULL, &rectTitre);
        SDL_RenderCopy(renderer, tMorts, NULL, &position_morts);
        SDL_RenderCopy(renderer, tJouer, NULL, &rectJouer);
        SDL_RenderCopy(renderer, tCharger, NULL, &rectCharger);
        SDL_RenderCopy(renderer, tParametres, NULL, &rectParam);
        SDL_RenderCopy(renderer, tSauvegarder, NULL, &rectSauv);
        SDL_RenderCopy(renderer, tQuitter, NULL, &rectQuit);
        if (save > 0)
        {
            SDL_RenderCopy(renderer, tValidation_save, NULL, &rectValidation_save);
            save--;
        }
        if (save < 0)
        {
            SDL_RenderCopy(renderer, tValidation_charger, NULL, &rectValidation_charger);
            save++;
        }

        SDL_RenderPresent(renderer);
    }

Quit:
    if (tJouer != NULL)
        SDL_DestroyTexture(tJouer);
    if (tCharger != NULL)
        SDL_DestroyTexture(tCharger);
    if (tParametres != NULL)
        SDL_DestroyTexture(tParametres);
    if (tSauvegarder != NULL)
        SDL_DestroyTexture(tSauvegarder);
    if (tQuitter != NULL)
        SDL_DestroyTexture(tQuitter);
    if (renderer != NULL)
        SDL_DestroyRenderer(renderer);
    if (window != NULL)
        SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}