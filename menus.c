#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "structure.h"
#include "affichage.h"
#include "fonctions.h"
#include "init.h"
#include "niveau1.h"

void parametre(SDL_Window *window, SDL_Renderer *renderer, int TAILLE_POLICE, int INTERLIGNE, SDL_Texture *fond, SDL_Rect position_fond)
{
    SDL_Surface *texte_Surface = NULL;
    SDL_Texture *tSaut = NULL;
    SDL_Texture *tAvant = NULL;
    SDL_Texture *tGauche = NULL;
    SDL_Texture *tCommandes = NULL;
    SDL_Texture *tQuitter = NULL;
    SDL_Texture *tEchap = NULL;
    int window_width = 0;
    int window_height = 0;
    bool jeu = true;

    SDL_Point souris;

    SDL_Color couleurJaune = {255, 255, 0, 255};
    SDL_Color couleurBlanche = {255, 255, 255, 255};

    SDL_GetWindowSize(window, &window_width, &window_height);

    initText(couleurJaune, &texte_Surface, &tCommandes, &renderer, TAILLE_POLICE, "Commandes :");
    SDL_Rect rectRecommencer = {window_width / 2 - texte_Surface->w / 2, 300, texte_Surface->w, texte_Surface->h};
    int x = (window_width / 2 - texte_Surface->w / 2);
    SDL_FreeSurface(texte_Surface);

    initText(couleurJaune, &texte_Surface, &tSaut, &renderer, TAILLE_POLICE, "Saut :      ^");
    SDL_Rect rectSaut = {x, 355 + texte_Surface->h + INTERLIGNE, texte_Surface->w, texte_Surface->h};
    SDL_FreeSurface(texte_Surface);

    initText(couleurJaune, &texte_Surface, &tAvant, &renderer, TAILLE_POLICE, "Avant :    >");
    SDL_Rect rectAvant = {x, 355 + 2 * texte_Surface->h + 2 * INTERLIGNE, texte_Surface->w, texte_Surface->h};
    SDL_FreeSurface(texte_Surface);

    initText(couleurJaune, &texte_Surface, &tGauche, &renderer, TAILLE_POLICE, "Gauche :  <");
    SDL_Rect rectGauche = {x, 355 + 3 * texte_Surface->h + 3 * INTERLIGNE, texte_Surface->w, texte_Surface->h};
    SDL_FreeSurface(texte_Surface);

    initText(couleurJaune, &texte_Surface, &tEchap, &renderer, TAILLE_POLICE, "Menu : Echap");
    SDL_Rect rectEchap = {x, 355 + 4 * texte_Surface->h + 4 * INTERLIGNE, texte_Surface->w, texte_Surface->h};
    SDL_FreeSurface(texte_Surface);

    initText(couleurJaune, &texte_Surface, &tQuitter, &renderer, TAILLE_POLICE, "Retour");
    SDL_Rect rectQuitter = {x, 355 + 6 * texte_Surface->h + 4 * INTERLIGNE, texte_Surface->w, texte_Surface->h};
    SDL_FreeSurface(texte_Surface);

    while (jeu)
    {
        SDL_Delay(39);
        SDL_Event event;
        SDL_GetMouseState(&souris.x, &souris.y);
        changement_couleur_inRect(TAILLE_POLICE, couleurBlanche, couleurJaune, &renderer, &tQuitter, "Retour", souris, rectQuitter);

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
                    if (SDL_PointInRect(&souris, &rectQuitter))
                    {
                        printf("Retour ! \n");

                        goto Quit;
                    }
                }
                break;
            }
        }
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, fond, NULL, &position_fond);
        SDL_RenderCopy(renderer, tCommandes, NULL, &rectRecommencer);
        SDL_RenderCopy(renderer, tSaut, NULL, &rectSaut);
        SDL_RenderCopy(renderer, tAvant, NULL, &rectAvant);
        SDL_RenderCopy(renderer, tGauche, NULL, &rectGauche);
        SDL_RenderCopy(renderer, tEchap, NULL, &rectEchap);
        SDL_RenderCopy(renderer, tQuitter, NULL, &rectQuitter);
        SDL_RenderPresent(renderer);
    }
Quit:
    if (tCommandes != NULL)
        SDL_DestroyTexture(tCommandes);
    if (tQuitter != NULL)
        SDL_DestroyTexture(tQuitter);
    if (tSaut != NULL)
        SDL_DestroyTexture(tSaut);
    if (tAvant != NULL)
        SDL_DestroyTexture(tAvant);
    if (tGauche != NULL)
        SDL_DestroyTexture(tGauche);
    if (tEchap != NULL)
        SDL_DestroyTexture(tEchap);

    return;
}

int menu_jeu(SDL_Window *window, SDL_Renderer *renderer, int TAILLE_POLICE, int INTERLIGNE, int x, SDL_Texture *fond, SDL_Rect position_fond)
{
    SDL_RenderClear(renderer);
    SDL_Surface *texte_Surface = NULL;
    SDL_Texture *tContinue = NULL;
    SDL_Texture *tRecommencer = NULL;
    SDL_Texture *tCommandes = NULL;
    SDL_Texture *tQuitter = NULL;
    int window_width = 0;
    int window_height = 0;
    bool jeu = true;
    int statut = 0;

    SDL_Point souris;

    SDL_Color couleurBlanche = {255, 255, 255, 255};
    SDL_Color couleurJaune = {255, 255, 0, 255};
    SDL_GetWindowSize(window, &window_width, &window_height);

    initText(couleurBlanche, &texte_Surface, &tContinue, &renderer, TAILLE_POLICE, "Continuer");
    SDL_Rect rectContinue = {x, (window_height - 4 * texte_Surface->h - 3 * INTERLIGNE) / 2, texte_Surface->w, texte_Surface->h};
    SDL_FreeSurface(texte_Surface);

    initText(couleurBlanche, &texte_Surface, &tCommandes, &renderer, TAILLE_POLICE, "Commandes");
    SDL_Rect rectCommandes = {x, (window_height - 4 * texte_Surface->h - 3 * INTERLIGNE) / 2 + texte_Surface->h + INTERLIGNE, texte_Surface->w, texte_Surface->h};
    SDL_FreeSurface(texte_Surface);

    initText(couleurBlanche, &texte_Surface, &tRecommencer, &renderer, TAILLE_POLICE, "Recommencer");
    SDL_Rect rectRecommencer = {x, (window_height - 4 * texte_Surface->h - 3 * INTERLIGNE) / 2 + 2 * texte_Surface->h + 2 * INTERLIGNE, texte_Surface->w, texte_Surface->h};
    SDL_FreeSurface(texte_Surface);

    initText(couleurBlanche, &texte_Surface, &tQuitter, &renderer, TAILLE_POLICE, "Quitter");
    SDL_Rect rectQuitter = {x, (window_height - 4 * texte_Surface->h - 3 * INTERLIGNE) / 2 + 3 * texte_Surface->h + 3 * INTERLIGNE, texte_Surface->w, texte_Surface->h};
    SDL_FreeSurface(texte_Surface);

    while (jeu)
    {
        SDL_Delay(39);
        SDL_Event event;
        SDL_GetMouseState(&souris.x, &souris.y);
        changement_couleur_inRect(TAILLE_POLICE, couleurJaune, couleurBlanche, &renderer, &tContinue, "Continuer", souris, rectContinue);
        changement_couleur_inRect(TAILLE_POLICE, couleurJaune, couleurBlanche, &renderer, &tCommandes, "Commandes", souris, rectCommandes);
        changement_couleur_inRect(TAILLE_POLICE, couleurJaune, couleurBlanche, &renderer, &tRecommencer, "Recommencer", souris, rectRecommencer);
        changement_couleur_inRect(TAILLE_POLICE, couleurJaune, couleurBlanche, &renderer, &tQuitter, "Quitter", souris, rectQuitter);

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
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    if (SDL_PointInRect(&souris, &rectContinue))
                    {
                        statut = 0;
                        jeu = false;
                    }
                    else if (SDL_PointInRect(&souris, &rectCommandes))
                    {
                        parametre(window, renderer, TAILLE_POLICE, INTERLIGNE, fond, position_fond);
                    }
                    else if (SDL_PointInRect(&souris, &rectRecommencer))
                    {
                        statut = 1;
                        jeu = false;
                    }
                    else if (SDL_PointInRect(&souris, &rectQuitter))
                    {
                        statut = -1;
                        jeu = false;
                    }

                    break;
                }
            }
        }
        SDL_RenderCopy(renderer, fond, NULL, &position_fond);
        SDL_RenderCopy(renderer, tContinue, NULL, &rectContinue);
        SDL_RenderCopy(renderer, tCommandes, NULL, &rectCommandes);
        SDL_RenderCopy(renderer, tRecommencer, NULL, &rectRecommencer);
        SDL_RenderCopy(renderer, tQuitter, NULL, &rectQuitter);
        SDL_RenderPresent(renderer);
    }

Quit:
    if (tContinue != NULL)
        SDL_DestroyTexture(tContinue);
    if (tRecommencer != NULL)
        SDL_DestroyTexture(tRecommencer);
    if (tQuitter != NULL)
        SDL_DestroyTexture(tQuitter);
    if (tCommandes != NULL)
        SDL_DestroyTexture(tCommandes);

    return statut;
}

int menu_game_over(SDL_Window *window, SDL_Renderer *renderer, int TAILLE_POLICE, int INTERLIGNE, int x, SDL_Texture *fond, SDL_Rect position_fond)
{
    SDL_RenderClear(renderer);
    SDL_Surface *texte_Surface = NULL;
    SDL_Texture *tPerdu = NULL;
    SDL_Texture *tRecommencer = NULL;
    SDL_Texture *tQuitter = NULL;
    int window_width = 0;
    int window_height = 0;
    bool jeu = true;
    int statut = 0;

    SDL_Point souris;

    SDL_Color couleurBlanche = {255, 255, 255, 255};
    SDL_Color couleurJaune = {255, 255, 0, 255};

    SDL_GetWindowSize(window, &window_width, &window_height);

    initText(couleurBlanche, &texte_Surface, &tPerdu, &renderer, 200, "Game Over");
    SDL_Rect rectPerdu = {window_width / 2 - texte_Surface->w / 2, (window_height - 4 * texte_Surface->h - 3 * INTERLIGNE) / 2, texte_Surface->w, texte_Surface->h};
    SDL_FreeSurface(texte_Surface);

    initText(couleurBlanche, &texte_Surface, &tRecommencer, &renderer, TAILLE_POLICE, "Recommencer");
    SDL_Rect rectRecommencer = {x, (window_height - 4 * texte_Surface->h - 3 * INTERLIGNE) / 2 + texte_Surface->h + INTERLIGNE, texte_Surface->w, texte_Surface->h};
    SDL_FreeSurface(texte_Surface);

    initText(couleurBlanche, &texte_Surface, &tQuitter, &renderer, TAILLE_POLICE, "Quitter");
    SDL_Rect rectQuitter = {x, (window_height - 4 * texte_Surface->h - 3 * INTERLIGNE) / 2 + 2 * texte_Surface->h + 2 * INTERLIGNE, texte_Surface->w, texte_Surface->h};
    SDL_FreeSurface(texte_Surface);

    while (jeu)
    {
        SDL_Delay(39);
        SDL_Event event;
        SDL_GetMouseState(&souris.x, &souris.y);
        changement_couleur_inRect(TAILLE_POLICE, couleurJaune, couleurBlanche, &renderer, &tRecommencer, "Recommencer", souris, rectRecommencer);
        changement_couleur_inRect(TAILLE_POLICE, couleurJaune, couleurBlanche, &renderer, &tQuitter, "Quitter", souris, rectQuitter);

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
                    if (SDL_PointInRect(&souris, &rectRecommencer))
                    {
                        printf("Recommencer ! \n");
                        statut = 1;
                        goto Quit;
                    }
                    if (SDL_PointInRect(&souris, &rectQuitter))
                    {
                        printf("Quitter ! \n");
                        statut = -1;
                        goto Quit;
                    }
                    break;
                }
            }
        }
        SDL_RenderCopy(renderer, fond, NULL, &position_fond);
        SDL_RenderCopy(renderer, tPerdu, NULL, &rectPerdu);
        SDL_RenderCopy(renderer, tRecommencer, NULL, &rectRecommencer);
        SDL_RenderCopy(renderer, tQuitter, NULL, &rectQuitter);
        SDL_RenderPresent(renderer);
    }

Quit:
    if (tRecommencer != NULL)
        SDL_DestroyTexture(tRecommencer);
    if (tQuitter != NULL)
        SDL_DestroyTexture(tQuitter);
    if (tPerdu != NULL)
        SDL_DestroyTexture(tPerdu);

    return statut;
}

int menu_victoire(SDL_Window *window, SDL_Renderer *renderer, int TAILLE_POLICE, int INTERLIGNE, int x, SDL_Texture *fond, SDL_Rect position_fond, int gains)
{
    SDL_RenderClear(renderer);
    SDL_Surface *texte_Surface = NULL;
    SDL_Texture *tGagne = NULL;
    SDL_Texture *tRecommencer = NULL;
    SDL_Texture *tQuitter = NULL;
    SDL_Texture *tReccompenses = NULL;
    SDL_Texture *tPiece = NULL;
    SDL_Rect rectPiece;
    int window_width = 0;
    int window_height = 0;
    bool jeu = true;
    int statut = 0;
    char recompenses_texte [20];
    sprintf(recompenses_texte, "+ %d", gains);

    SDL_Point souris;

    SDL_Color couleurBlanche = {255, 255, 255, 255};
    SDL_Color couleurJaune = {255, 255, 0, 255};

    SDL_GetWindowSize(window, &window_width, &window_height);

    initText(couleurBlanche, &texte_Surface, &tGagne, &renderer, 200, "VICTOIRE ");
    SDL_Rect rectGagne = {window_width / 2 - texte_Surface->w / 2, (window_height - 4 * texte_Surface->h - 3 * INTERLIGNE) / 2, texte_Surface->w, texte_Surface->h};
    SDL_FreeSurface(texte_Surface);

    initText(couleurBlanche, &texte_Surface, &tRecommencer, &renderer, TAILLE_POLICE, "Suivant");
    SDL_Rect rectRecommencer = {x, (window_height - 4 * texte_Surface->h - 3 * INTERLIGNE) / 2 + texte_Surface->h + INTERLIGNE, texte_Surface->w, texte_Surface->h};
    SDL_FreeSurface(texte_Surface);

    initText(couleurBlanche, &texte_Surface, &tQuitter, &renderer, TAILLE_POLICE, "Quitter");
    SDL_Rect rectQuitter = {x, (window_height - 4 * texte_Surface->h - 3 * INTERLIGNE) / 2 + 2 * texte_Surface->h + 2 * INTERLIGNE, texte_Surface->w, texte_Surface->h};
    SDL_FreeSurface(texte_Surface);

    initText(couleurBlanche, &texte_Surface, &tReccompenses, &renderer, TAILLE_POLICE, recompenses_texte);
    SDL_Rect rectRecompenses = {window_width / 2 - texte_Surface->w / 2,rectGagne. y + rectGagne.h +20, texte_Surface->w, texte_Surface->h};
    SDL_FreeSurface(texte_Surface);

    tPiece = loadTexturePNG("sprites/piece.png", renderer, &rectPiece);
    rectPiece.w = 40;
    rectPiece.h = 40;
    rectPiece.y = rectRecompenses.y + rectRecompenses.h / 2 - rectPiece.h / 2;
    rectPiece.x = rectRecompenses.x +rectRecompenses.w + 10;


    while (jeu)
    {
        SDL_Delay(39);
        SDL_Event event;
        SDL_GetMouseState(&souris.x, &souris.y);
        changement_couleur_inRect(TAILLE_POLICE, couleurJaune, couleurBlanche, &renderer, &tRecommencer, "Suivant", souris, rectRecommencer);
        changement_couleur_inRect(TAILLE_POLICE, couleurJaune, couleurBlanche, &renderer, &tQuitter, "Quitter", souris, rectQuitter);

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
                    if (SDL_PointInRect(&souris, &rectRecommencer))
                    {
                        printf("Suivant ! \n");
                        statut = 0;
                        goto Quit;
                    }
                    if (SDL_PointInRect(&souris, &rectQuitter))
                    {
                        printf("Quitter ! \n");
                        statut = -1;
                        goto Quit;
                    }
                    break;
                }
            }
        }
        SDL_RenderCopy(renderer, fond, NULL, &position_fond);
        SDL_RenderCopy(renderer, tGagne, NULL, &rectGagne);
        SDL_RenderCopy(renderer, tRecommencer, NULL, &rectRecommencer);
        SDL_RenderCopy(renderer, tQuitter, NULL, &rectQuitter);
        SDL_RenderCopy(renderer, tReccompenses, NULL, &rectRecompenses);
        SDL_RenderCopy(renderer, tPiece, NULL, &rectPiece);
        SDL_RenderPresent(renderer);
    }

Quit:
    if (tRecommencer != NULL)
        SDL_DestroyTexture(tRecommencer);
    if (tQuitter != NULL)
        SDL_DestroyTexture(tQuitter);
    if (tGagne != NULL)
        SDL_DestroyTexture(tGagne);
    if (tReccompenses != NULL)
        SDL_DestroyTexture(tReccompenses);
    if (tPiece != NULL)
        SDL_DestroyTexture(tPiece);

    return statut;
}

int choix_niveau(SDL_Window *window, SDL_Renderer *renderer, int TAILLE_POLICE, int INTERLIGNE, int x, SDL_Texture *fond, SDL_Rect position_fond, int *niveau, int tab_mort[], int tab_temps[], int *recompenses, int choix_skin)
{
    SDL_RenderClear(renderer);

    SDL_Surface *texte_Surface = NULL;
    SDL_Texture *tMort_logo = NULL;
    SDL_Texture *tMort_logo2 = NULL;
    SDL_Rect rectMort_logo ;
    SDL_Rect rectMort_logo2 ;
    tMort_logo = loadTexturePNG("sprites/mort.png", renderer, &rectMort_logo);
    tMort_logo2 = loadTexturePNG("sprites/mort.png", renderer, &rectMort_logo2);

    SDL_Texture *tNiveau1 = NULL;
    SDL_Texture *tNiveau2 = NULL;
    SDL_Texture *tNiveau1_temps = NULL;
    SDL_Texture *tNiveau2_temps = NULL;
    SDL_Texture *tJouer1 = NULL;
    SDL_Texture *tJouer2 = NULL;
    int minutes = 0;
    int secondes = 0;
    char temps_niveau1[30];
    char temps_niveau2[30];
    char mort_niveau1[20];
    char mort_niveau2[20];

    // Mise en forme du temps et des morts en chaîne de caractères
    minutes = tab_temps[0] / 60;
    secondes = tab_temps[0] % 60;
    sprintf(temps_niveau1, "Temps : %02d:%02d", minutes, secondes);
    sprintf(mort_niveau1, "%03d", tab_mort[0]);
    minutes = tab_temps[1] / 60;
    secondes = tab_temps[1] % 60;
    sprintf(temps_niveau2, "Temps : %02d:%02d", minutes, secondes);
    sprintf(mort_niveau2, "%03d", tab_mort[1]);

    SDL_Texture *tNiveau1_mort = NULL;
    SDL_Texture *tNiveau2_mort = NULL;
    SDL_Texture *tRetour = NULL;
    int window_width = 0;
    int window_height = 0;
    bool jeu = true;
    int statut = 0;

    SDL_Point souris;
    SDL_GetWindowSize(window, &window_width, &window_height);
    SDL_Rect rectContour_niveau1 = {0, 0, 500, 500};
    SDL_Rect rectContour_niveau2 = {0, 0, 500, 500};

    SDL_Color couleurBlanche = {255, 255, 255, 255};
    SDL_Color couleurJaune = {255, 255, 0, 255};
    SDL_Color couleurGrise = {100, 100, 100, 255};

    // Calcul des coordonnées des rectangles informatifs des niveaux
    initText(couleurBlanche, &texte_Surface, &tNiveau1, &renderer, 60, "Niveau 1 - Presentation");
    rectContour_niveau1.x = window_width / 4 - texte_Surface->w / 2 - 10;
    rectContour_niveau1.y = rectContour_niveau1.h / 2;
    rectContour_niveau1.w = texte_Surface->w + 20;
    SDL_Rect rectNiveau1 = {rectContour_niveau1.x + ((rectContour_niveau1.w - texte_Surface->w) / 2), rectContour_niveau1.y, texte_Surface->w, texte_Surface->h};
    SDL_FreeSurface(texte_Surface);

    initText(couleurBlanche, &texte_Surface, &tNiveau1_temps, &renderer, 60, temps_niveau1);
    SDL_Rect rectNiveau1_temps = {rectContour_niveau1.x + ((rectContour_niveau1.w - texte_Surface->w) / 2), rectContour_niveau1.h / 4 + rectContour_niveau1.y, texte_Surface->w, texte_Surface->h};
    SDL_FreeSurface(texte_Surface);

    rectMort_logo.x = rectNiveau1_temps.x;
    rectMort_logo.y = (rectContour_niveau1.h / 4) * 2 + rectContour_niveau1.y;
    rectMort_logo.w = 40;
    rectMort_logo.h = 40;

    initText(couleurBlanche, &texte_Surface, &tNiveau1_mort, &renderer, 60, mort_niveau1);
    SDL_Rect rectNiveau1_mort = {rectNiveau1_temps.x + rectMort_logo.w + 10, rectMort_logo.y - 7  , texte_Surface->w, texte_Surface->h};
    SDL_FreeSurface(texte_Surface);

    initText(couleurBlanche, &texte_Surface, &tJouer1, &renderer, 60, "Jouer");
    SDL_Rect rectJouer1 = {rectContour_niveau1.x + ((rectContour_niveau1.w - texte_Surface->w) / 2), (rectContour_niveau1.h / 4) * 3 + rectContour_niveau1.y, texte_Surface->w, texte_Surface->h};
    SDL_FreeSurface(texte_Surface);

    initText(couleurBlanche, &texte_Surface, &tNiveau2, &renderer, 60, "Niveau 2 - Planete 0");
    rectContour_niveau2.x = window_width - rectContour_niveau1.x - rectContour_niveau1.w;
    rectContour_niveau2.y = rectContour_niveau2.h / 2;
    rectContour_niveau2.w = rectContour_niveau1.w;
    SDL_Rect rectNiveau2 = {rectContour_niveau2.x + ((rectContour_niveau2.w - texte_Surface->w) / 2), rectContour_niveau2.y, texte_Surface->w, texte_Surface->h};
    SDL_FreeSurface(texte_Surface);

    initText(couleurBlanche, &texte_Surface, &tNiveau2_temps, &renderer, 60, temps_niveau2);
    SDL_Rect rectNiveau2_temps = {rectContour_niveau2.x + ((rectContour_niveau2.w - texte_Surface->w) / 2), rectContour_niveau2.h / 4 + rectContour_niveau2.y, texte_Surface->w, texte_Surface->h};
    SDL_FreeSurface(texte_Surface);

    rectMort_logo2.x = rectNiveau2_temps.x;
    rectMort_logo2.y = (rectContour_niveau2.h / 4) * 2 + rectContour_niveau2.y;
    rectMort_logo2.w = 40;
    rectMort_logo2.h = 40;

    initText(couleurBlanche, &texte_Surface, &tNiveau2_mort, &renderer, 60, mort_niveau2);
    SDL_Rect rectNiveau2_mort = {rectNiveau2_temps.x + rectMort_logo2.w + 10, rectMort_logo2.y - 7, texte_Surface->w, texte_Surface->h};
    SDL_FreeSurface(texte_Surface);

    initText(couleurBlanche, &texte_Surface, &tJouer2, &renderer, 60, "Jouer");
    SDL_Rect rectJouer2 = {rectContour_niveau2.x + ((rectContour_niveau2.w - texte_Surface->w) / 2), (rectContour_niveau2.h / 4) * 3 + rectContour_niveau2.y, texte_Surface->w, texte_Surface->h};
    SDL_FreeSurface(texte_Surface);

    initText(couleurBlanche, &texte_Surface, &tRetour, &renderer, 60, "Retour");
    SDL_Rect rectRetour = {rectContour_niveau1.x, window_height - texte_Surface->h - 60, texte_Surface->w, texte_Surface->h};
    SDL_FreeSurface(texte_Surface);

    while (jeu)
    {
        SDL_RenderClear(renderer);
        changement_couleur_inRect(60, couleurJaune, couleurBlanche, &renderer, &tJouer1, "Jouer", souris, rectJouer1);
        if (*niveau == 2)
        {
            changement_couleur_inRect(60, couleurJaune, couleurBlanche, &renderer, &tJouer2, "Jouer", souris, rectJouer2);
        }

        changement_couleur_inRect(60, couleurJaune, couleurBlanche, &renderer, &tRetour, "Retour", souris, rectRetour);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        SDL_Delay(39);
        SDL_Event event;
        SDL_GetMouseState(&souris.x, &souris.y);

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
                    if (SDL_PointInRect(&souris, &rectJouer1))
                    {
                        while ((statut = niveau1(window, renderer, &tab_mort[0], &tab_temps[0], recompenses, niveau, x, TAILLE_POLICE, choix_skin)) == 1)
                        {
                        }
                        // if (statut == 0)
                        // {
                        //     while (niveau2(window, renderer, &tab_mort[1], &tab_temps[1], x, TAILLE_POLICE) == 1)
                        //     {
                        //     }
                        // }

                        goto Quit;
                    }
                    if (SDL_PointInRect(&souris, &rectJouer2))
                    {
                        if (*niveau == 2)
                        {
                            // while (niveau2(window, renderer, &tab_mort[1], &tab_temps[1], x, TAILLE_POLICE) == 1)
                            // {
                            // }
                        }

                        goto Quit;
                    }
                    if (SDL_PointInRect(&souris, &rectRetour))
                    {
                        goto Quit;
                    }
                    break;
                }
            }
        }
        SDL_RenderCopy(renderer, fond, NULL, &position_fond);
        SDL_RenderCopy(renderer, tNiveau1, NULL, &rectNiveau1);
        SDL_RenderCopy(renderer, tNiveau1_temps, NULL, &rectNiveau1_temps);
        SDL_RenderCopy(renderer, tNiveau1_mort, NULL, &rectNiveau1_mort);
        SDL_RenderCopy(renderer, tJouer1, NULL, &rectJouer1);
        SDL_RenderCopy(renderer, tMort_logo, NULL, &rectMort_logo);
        SDL_RenderDrawRect(renderer, &rectContour_niveau1);

        if (*niveau != 2)
        {
            SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
            changement_couleur(60, couleurGrise, &renderer, &tNiveau2, "Niveau 2 - Planete 0");
            changement_couleur(60, couleurGrise, &renderer, &tNiveau2_temps, temps_niveau2);
            changement_couleur(60, couleurGrise, &renderer, &tNiveau2_mort, mort_niveau2);
            changement_couleur(60, couleurGrise, &renderer, &tJouer2, "Jouer");
            SDL_SetTextureColorMod(tMort_logo2, 128, 128, 128);
        }
        SDL_RenderDrawRect(renderer, &rectContour_niveau2);
        SDL_RenderCopy(renderer, tNiveau2, NULL, &rectNiveau2);
        SDL_RenderCopy(renderer, tNiveau2_temps, NULL, &rectNiveau2_temps);
        SDL_RenderCopy(renderer, tNiveau2_mort, NULL, &rectNiveau2_mort);
        SDL_RenderCopy(renderer, tJouer2, NULL, &rectJouer2);
        SDL_RenderCopy(renderer, tRetour, NULL, &rectRetour);
        SDL_RenderCopy(renderer, tMort_logo2, NULL, &rectMort_logo2);
        SDL_RenderPresent(renderer);
    }

Quit:
    if (tNiveau1 != NULL)
        SDL_DestroyTexture(tNiveau1);
    if (tNiveau1_mort != NULL)
        SDL_DestroyTexture(tNiveau1_mort);
    if (tNiveau1_temps != NULL)
        SDL_DestroyTexture(tNiveau1_temps);
    if (tJouer1 != NULL)
        SDL_DestroyTexture(tJouer1);
    if (tNiveau2 != NULL)
        SDL_DestroyTexture(tNiveau2);
    if (tNiveau2_mort != NULL)
        SDL_DestroyTexture(tNiveau2_mort);
    if (tNiveau2_temps != NULL)
        SDL_DestroyTexture(tNiveau2_temps);
    if (tJouer2 != NULL)
        SDL_DestroyTexture(tJouer2);
    if (tRetour != NULL)
        SDL_DestroyTexture(tRetour);

    return statut;
}

int inventaire(SDL_Window *window, SDL_Renderer *renderer, int TAILLE_POLICE, int INTERLIGNE, int x, SDL_Texture *fond, SDL_Rect position_fond, int *choix_skin, int *recompenses, int *skin_achete)
{
    SDL_RenderClear(renderer);
    int window_width = 0;
    int window_height = 0;
    bool jeu = true;
    int statut = 0;
    SDL_GetWindowSize(window, &window_width, &window_height);
    SDL_Point souris;

    SDL_Color couleurBlanche = {255, 255, 255, 255};
    SDL_Color couleurJaune = {255, 255, 0, 255};
    SDL_Color couleurGrise = {128, 128, 128, 255};
    SDL_Surface *texte_surface = NULL;
    SDL_Texture *tInventaire = NULL;
    SDL_Rect contourAventurier;
    SDL_Rect contourAstronaute;
    SDL_Rect rectAventurier;
    SDL_Texture *aventurier = loadTexturePNG("sprites/aventurier1.png", renderer, &rectAventurier);
    SDL_Rect rectAstronaute;
    SDL_Texture *astronaute = loadTexturePNG("sprites/astronaute1.png", renderer, &rectAstronaute);
    float ratio = rectAventurier.h / rectAventurier.w;

    contourAventurier.w = 300;
    contourAventurier.h = contourAventurier.w * ratio + 200;
    contourAventurier.x = window_width / 2 - contourAventurier.w - 125;
    contourAventurier.y = window_height / 2 - contourAventurier.h / 2;

    rectAventurier.x = contourAventurier.x + contourAventurier.w / 2 - rectAventurier.w / 2;
    rectAventurier.y = contourAventurier.y + 50;

    contourAstronaute.w = contourAventurier.w;
    contourAstronaute.h = contourAventurier.h;
    contourAstronaute.x = window_width / 2 + 125;
    contourAstronaute.y = contourAventurier.y;

    rectAstronaute.x = contourAstronaute.x + contourAstronaute.w / 2 - rectAstronaute.w / 2;
    rectAstronaute.y = contourAstronaute.y + 50;

    SDL_Texture *tNomAventurier = NULL;
    SDL_Texture *tAge = NULL;
    SDL_Texture *tTailleAventurier = NULL;
    SDL_Texture *tPoids = NULL;
    SDL_Texture *tChoisirAventurier = NULL;

    SDL_Texture *tNomAstronaute = NULL;
    SDL_Texture *tAgeAstronaute = NULL;
    SDL_Texture *tTailleAstronaute = NULL;
    SDL_Texture *tPoidsAstronaute = NULL;
    SDL_Texture *tChoisirAstronaute = NULL;
    SDL_Texture *tPrix = NULL;
    SDL_Texture *tPiece = NULL;
    SDL_Rect piece;

    SDL_Texture *tRetour = NULL;

    initText(couleurBlanche, &texte_surface, &tInventaire, &renderer, TAILLE_POLICE, "Inventaire");
    SDL_Rect rectInventaire = {window_width / 2 - texte_surface->w / 2, 0, texte_surface->w, texte_surface->h};
    SDL_FreeSurface(texte_surface);

    // Aventurier
    initText(couleurBlanche, &texte_surface, &tNomAventurier, &renderer, 50, "Nom : Astro");
    SDL_Rect rectNomAventurier = {contourAventurier.x + 10, contourAventurier.y + (contourAventurier.h - rectAventurier.y) + 50, texte_surface->w, texte_surface->h};
    SDL_FreeSurface(texte_surface);

    initText(couleurBlanche, &texte_surface, &tAge, &renderer, 50, "Age : 30 ans");
    SDL_Rect rectAge = {contourAventurier.x + 10, contourAventurier.y + (contourAventurier.h - rectAventurier.y) + 100, texte_surface->w, texte_surface->h};
    SDL_FreeSurface(texte_surface);

    initText(couleurBlanche, &texte_surface, &tTailleAventurier, &renderer, 50, "Taille : 170 cm");
    SDL_Rect rectTailleAventurier = {contourAventurier.x + 10, contourAventurier.y + (contourAventurier.h - rectAventurier.y) + 150, texte_surface->w, texte_surface->h};
    SDL_FreeSurface(texte_surface);

    initText(couleurBlanche, &texte_surface, &tPoids, &renderer, 50, "Poids : 80 Kg");
    SDL_Rect rectPoids = {contourAventurier.x + 10, contourAventurier.y + (contourAventurier.h - rectAventurier.y) + 200, texte_surface->w, texte_surface->h};
    SDL_FreeSurface(texte_surface);

    initText(couleurBlanche, &texte_surface, &tChoisirAventurier, &renderer, 50, "Choisir");
    SDL_Rect rectChoisirAventurier = {contourAventurier.x + (contourAventurier.w - texte_surface->w) / 2, rectPoids.y - (contourAventurier.h - (rectPoids.y + rectPoids.h)) / 2 - texte_surface->h / 2, texte_surface->w, texte_surface->h};
    SDL_FreeSurface(texte_surface);

    // Astronaute
    initText(couleurBlanche, &texte_surface, &tNomAstronaute, &renderer, 50, "Nom : Rocket");
    SDL_Rect rectNomAstronaute = {contourAstronaute.x + 10, contourAstronaute.y + (contourAstronaute.h - rectAstronaute.y) + 50, texte_surface->w, texte_surface->h};
    SDL_FreeSurface(texte_surface);

    initText(couleurBlanche, &texte_surface, &tAgeAstronaute, &renderer, 50, "Age : 20 ans");
    SDL_Rect rectAgeAstronaute = {contourAstronaute.x + 10, contourAstronaute.y + (contourAstronaute.h - rectAstronaute.y) + 100, texte_surface->w, texte_surface->h};
    SDL_FreeSurface(texte_surface);

    initText(couleurBlanche, &texte_surface, &tTailleAstronaute, &renderer, 50, "Taille : 150 cm");
    SDL_Rect rectTailleAstronaute = {contourAstronaute.x + 10, contourAstronaute.y + (contourAstronaute.h - rectAstronaute.y) + 150, texte_surface->w, texte_surface->h};
    SDL_FreeSurface(texte_surface);

    initText(couleurBlanche, &texte_surface, &tPoidsAstronaute, &renderer, 50, "Poids : 60 Kg");
    SDL_Rect rectPoidsAstronaute = {contourAstronaute.x + 10, contourAstronaute.y + (contourAstronaute.h - rectAstronaute.y) + 200, texte_surface->w, texte_surface->h};
    SDL_FreeSurface(texte_surface);

    initText(couleurBlanche, &texte_surface, &tChoisirAstronaute, &renderer, 50, "Choisir");
    SDL_Rect rectChoisirAstronaute = {contourAstronaute.x + (contourAstronaute.w - texte_surface->w) / 2, rectPoidsAstronaute.y - (contourAstronaute.h - (rectPoidsAstronaute.y + rectPoidsAstronaute.h)) / 2 - texte_surface->h / 2, texte_surface->w, texte_surface->h};
    SDL_FreeSurface(texte_surface);

    tPiece = loadTexturePNG("sprites/piece.png", renderer, &piece);
    piece.x = contourAstronaute.x + 5;
    piece.y = contourAstronaute.y + 5;
    piece.w = 30;
    piece.h = 30;

    initText(couleurBlanche, &texte_surface, &tPrix, &renderer, 40, "250");
    SDL_Rect rectPrix = {piece.x + piece.w + 5, piece.y + (piece.h - texte_surface->h) / 2, texte_surface->w, texte_surface->h};
    SDL_FreeSurface(texte_surface);

    //retour 
    initText(couleurBlanche, &texte_surface, &tRetour, &renderer, TAILLE_POLICE, "Retour");
    SDL_Rect rectRetour = { 200, window_height - 100, texte_surface->w, texte_surface->h};
    SDL_FreeSurface(texte_surface);

    while (jeu)
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_Delay(39);
        SDL_Event event;
        SDL_GetMouseState(&souris.x, &souris.y);

        changement_couleur_inRect(50, couleurJaune, couleurBlanche, &renderer, &tChoisirAventurier, "Choisir", souris, rectChoisirAventurier);
        changement_couleur_inRect(50, couleurJaune, couleurBlanche, &renderer, &tRetour, "Retour", souris, rectRetour);
        if (*recompenses >= 250 || *skin_achete == 2)
        {
            changement_couleur_inRect(50, couleurJaune, couleurBlanche, &renderer, &tChoisirAstronaute, "Choisir", souris, rectChoisirAstronaute);
        }
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
                    if (SDL_PointInRect(&souris, &rectChoisirAventurier))
                    {
                        *choix_skin = 1;
                    }
                    if (SDL_PointInRect(&souris, &rectChoisirAstronaute) && *recompenses >= 250)
                    {
                        if (*skin_achete == 1)
                        {
                            *recompenses -= 250;
                        }
                        *skin_achete = 2;
                        *choix_skin = 2;
                    }
                    if (SDL_PointInRect(&souris, &rectRetour))
                    {
                        goto Quit;
                    }
                    break;
                }
            }
        }
        SDL_RenderCopy(renderer, fond, NULL, &position_fond);
        SDL_RenderCopy(renderer, tInventaire, NULL, &rectInventaire);
        SDL_RenderCopy(renderer, aventurier, NULL, &rectAventurier);
        SDL_RenderCopy(renderer, astronaute, NULL, &rectAstronaute);
        SDL_RenderCopy(renderer, tNomAventurier, NULL, &rectNomAventurier);
        SDL_RenderCopy(renderer, tAge, NULL, &rectAge);
        SDL_RenderCopy(renderer, tTailleAventurier, NULL, &rectTailleAventurier);
        SDL_RenderCopy(renderer, tPoids, NULL, &rectPoids);
        SDL_RenderDrawRect(renderer, &contourAventurier);
        SDL_RenderCopy(renderer, tChoisirAventurier, NULL, &rectChoisirAventurier);

        if (*skin_achete == 1 && *recompenses <= 250)
        {
            SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
            changement_couleur(50, couleurGrise, &renderer, &tNomAstronaute, "Astronaute");
            changement_couleur(50, couleurGrise, &renderer, &tAgeAstronaute, "Age : 20 ans");
            changement_couleur(50, couleurGrise, &renderer, &tTailleAstronaute, "Taille : 150 cm");
            changement_couleur(50, couleurGrise, &renderer, &tPoidsAstronaute, "Poids : 60 Kg");
            changement_couleur(50, couleurGrise, &renderer, &tChoisirAstronaute, "Choisir");
            SDL_SetTextureColorMod(astronaute, 128, 128, 128);
        }
        SDL_RenderDrawRect(renderer, &contourAstronaute);
        SDL_RenderCopy(renderer, tNomAstronaute, NULL, &rectNomAstronaute);
        SDL_RenderCopy(renderer, tAgeAstronaute, NULL, &rectAgeAstronaute);
        SDL_RenderCopy(renderer, tTailleAstronaute, NULL, &rectTailleAstronaute);
        SDL_RenderCopy(renderer, tPoidsAstronaute, NULL, &rectPoidsAstronaute);
        SDL_RenderCopy(renderer, tChoisirAstronaute, NULL, &rectChoisirAstronaute);
        SDL_RenderCopy(renderer, tRetour, NULL, &rectRetour);
        if (*skin_achete < 2)
        {
            SDL_RenderCopy(renderer, tPiece, NULL, &piece);
            SDL_RenderCopy(renderer, tPrix, NULL, &rectPrix);
        }

        SDL_RenderPresent(renderer);
    }

Quit:
    if (tNomAstronaute != NULL)
        SDL_DestroyTexture(tNomAstronaute);
    if (tAgeAstronaute != NULL)
        SDL_DestroyTexture(tAgeAstronaute);
    if (tTailleAstronaute != NULL)
        SDL_DestroyTexture(tTailleAstronaute);
    if (tPoidsAstronaute != NULL)
        SDL_DestroyTexture(tPoidsAstronaute);
    if (tChoisirAstronaute != NULL)
        SDL_DestroyTexture(tChoisirAstronaute);
    if (tNomAventurier != NULL)
        SDL_DestroyTexture(tNomAventurier);
    if (tAge != NULL)
        SDL_DestroyTexture(tAge);
    if (tTailleAventurier != NULL)
        SDL_DestroyTexture(tTailleAventurier);
    if (tPoids != NULL)
        SDL_DestroyTexture(tPoids);
    if (tChoisirAventurier != NULL)
        SDL_DestroyTexture(tChoisirAventurier);
    if (tInventaire != NULL)
        SDL_DestroyTexture(tInventaire);
    if (aventurier != NULL)
        SDL_DestroyTexture(aventurier);
    if (astronaute != NULL)
        SDL_DestroyTexture(astronaute);
    if (tPiece != NULL)
        SDL_DestroyTexture(tPiece);
    if (tPrix != NULL)
        SDL_DestroyTexture(tPrix);
    return statut;
}