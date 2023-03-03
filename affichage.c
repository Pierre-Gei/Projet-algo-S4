
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "structure.h"
#include "fonctions.h"
#include "init.h"
#include "niveau1.h"

void affichage_background(SDL_Renderer **renderer, SDL_Texture **image, SDL_Rect *position)
{
    SDL_RenderClear(*renderer);
    if (position->x <= -position->w)
    {
        position->x = 0;
    }
    SDL_RenderCopy(*renderer, *image, NULL, position);
    position->x = position->x + 1920;
    SDL_RenderCopy(*renderer, *image, NULL, position);
    position->x = position->x - 1920;
}

void affichage_text_niveau(SDL_Texture **texture, int Taille_Police, SDL_Rect *position, int x, int y, SDL_Renderer **renderer, char *texte, SDL_Color couleur)
{
    TTF_Font *police = TTF_OpenFont("Polices/Arcade.ttf", Taille_Police);
    if (!police)
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_OpenFont : %s \n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_Surface *surface = TTF_RenderText_Blended(police, texte, couleur);
    if (!surface)
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_RenderText_Blended : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    *texture = SDL_CreateTextureFromSurface(*renderer, surface);
    if (!(*texture))
    {
        fprintf(stderr, "Erreur d'initialisation de SDL_CreateTextureFromSurface : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    position->x = x;
    position->y = y;
    position->w = surface->w;
    position->h = surface->h;
    SDL_FreeSurface(surface);
    TTF_CloseFont(police);
}

void changement_sprites(SDL_Texture **rendu, SDL_Texture *texture1, SDL_Texture *texture2)
{
    if (*rendu == texture1)
    {
        *rendu = texture2;
    }
    else
    {
        *rendu = texture1;
    }
}

void changement_couleur(int Taille_Police, SDL_Color couleur, SDL_Renderer **renderer, SDL_Texture **texte_texture, char *texte)
{
    TTF_Font *police = TTF_OpenFont("Polices/Arcade.ttf", Taille_Police);
    SDL_Surface *texte_Surface = TTF_RenderText_Blended(police, texte, couleur);
    if (!texte_Surface)
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_RenderText_Blended : %s \n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    *texte_texture = SDL_CreateTextureFromSurface(*renderer, texte_Surface);
    if (!texte_texture)
    {
        fprintf(stderr, "Erreur d'initialisation de SDL_CreateTextureFromSurface : %s \n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_FreeSurface(texte_Surface);
    TTF_CloseFont(police);
}

void changement_couleur_inRect(int Taille_Police, SDL_Color couleur, SDL_Color couleur_initiale, SDL_Renderer **renderer, SDL_Texture **texte_texture, char *texte, SDL_Point souris, SDL_Rect rectangle)
{
    TTF_Font *police = TTF_OpenFont("Polices/Arcade.ttf", Taille_Police);
    if (SDL_PointInRect(&souris, &rectangle))
    {
        changement_couleur(Taille_Police, couleur, renderer, texte_texture, texte);
    }
    else
    {
        changement_couleur(Taille_Police, couleur_initiale, renderer, texte_texture, texte);
    }
    TTF_CloseFont(police);
}

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

    return statut;
}

void affiche_perso(SDL_Renderer **renderer, SDL_Texture *perso_rendu, SDL_Texture *perso_static, SDL_Rect position_perso, int vx, int direction)
{
    if (vx > 0)
    {
        SDL_RenderCopy(*renderer, perso_rendu, NULL, &position_perso);
    }
    else if (vx < 0)
    {
        SDL_RenderCopyEx(*renderer, perso_rendu, NULL, &position_perso, 0, NULL, SDL_FLIP_HORIZONTAL);
    }
    else if (vx == 0 && direction == 1)
    {
        SDL_RenderCopy(*renderer, perso_static, NULL, &position_perso);
    }
    else if (vx == 0 && direction == -1)
    {
        SDL_RenderCopyEx(*renderer, perso_static, NULL, &position_perso, 0, NULL, SDL_FLIP_HORIZONTAL);
    }
}

void animation_mort(SDL_Renderer *renderer, Astronaute a, SDL_Texture *fond, SDL_Rect position_fond)
{
    a.dimension_mort.x = a.position.x;
    a.dimension_mort.y = a.position.y;
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, fond, NULL, &position_fond);
    SDL_RenderCopy(renderer, a.sprite_mort1, NULL, &a.dimension_mort);
    SDL_RenderPresent(renderer);
    SDL_Delay(400);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, fond, NULL, &position_fond);
    SDL_RenderCopy(renderer, a.sprite_mort2, NULL, &a.dimension_mort);
    SDL_RenderPresent(renderer);
    SDL_Delay(400);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, fond, NULL, &position_fond);
    SDL_RenderCopy(renderer, a.sprite_mort3, NULL, &a.dimension_mort);
    SDL_RenderPresent(renderer);
    SDL_Delay(1000);
}
int choix_niveau(SDL_Window *window, SDL_Renderer *renderer, int TAILLE_POLICE, int INTERLIGNE, int x, SDL_Texture *fond, SDL_Rect position_fond, int niveau, int tab_mort[], int tab_temps[])
{
    SDL_RenderClear(renderer);

    SDL_Surface *texte_Surface = NULL;
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

    //Mise en forme du temps et des morts en chaîne de caractères
    minutes = tab_temps[0] / 60;
    secondes = tab_temps[0] % 60;
    sprintf(temps_niveau1, "Temps : %02d:%02d", minutes, secondes);
    sprintf(mort_niveau1, "Morts : %03d", tab_mort[0]);
    minutes = tab_temps[1] / 60;
    secondes = tab_temps[1] % 60;
    sprintf(temps_niveau2, "Temps : %02d:%02d", minutes, secondes);
    sprintf(mort_niveau2, "Morts : %03d", tab_mort[1]);

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

    //Calcul des coordonnées des rectangles informatifs des niveaux
    initText(couleurBlanche, &texte_Surface, &tNiveau1, &renderer, 60, "Niveau 1 - Presentation");
    rectContour_niveau1.x = window_width / 4 - texte_Surface->w / 2 - 10;
    rectContour_niveau1.y = rectContour_niveau1.h / 2;
    rectContour_niveau1.w = texte_Surface->w + 20;
    SDL_Rect rectNiveau1 = {rectContour_niveau1.x + ((rectContour_niveau1.w - texte_Surface->w) / 2), rectContour_niveau1.y, texte_Surface->w, texte_Surface->h};
    SDL_FreeSurface(texte_Surface);

    initText(couleurBlanche, &texte_Surface, &tNiveau1_temps, &renderer, 60, temps_niveau1);
    SDL_Rect rectNiveau1_temps = {rectContour_niveau1.x + ((rectContour_niveau1.w - texte_Surface->w) / 2), rectContour_niveau1.h / 4 + rectContour_niveau1.y, texte_Surface->w, texte_Surface->h};
    SDL_FreeSurface(texte_Surface);

    initText(couleurBlanche, &texte_Surface, &tNiveau1_mort, &renderer, 60, mort_niveau1);
    SDL_Rect rectNiveau1_mort = {rectNiveau1_temps.x, (rectContour_niveau1.h / 4) * 2 + rectContour_niveau1.y, texte_Surface->w, texte_Surface->h};
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

    initText(couleurBlanche, &texte_Surface, &tNiveau2_mort, &renderer, 60, mort_niveau2);
    SDL_Rect rectNiveau2_mort = {rectNiveau2_temps.x, (rectContour_niveau2.h / 4) * 2 + rectContour_niveau2.y, texte_Surface->w, texte_Surface->h};
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
        changement_couleur_inRect(60, couleurJaune, couleurBlanche, &renderer, &tJouer2, "Jouer", souris, rectJouer2);
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
                        while (niveau1(window, renderer, &tab_mort[0], &tab_temps[0], x, TAILLE_POLICE) == 1)
                        {
                        }
                        goto Quit;
                    }
                    if (SDL_PointInRect(&souris, &rectJouer2))
                    {
                        // while (niveau2(window, renderer, &tab_mort[1], &tab_temps[1], x, TAILLE_POLICE) == 1)
                        // {
                        // }
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
        SDL_RenderDrawRect(renderer, &rectContour_niveau1);
        SDL_RenderDrawRect(renderer, &rectContour_niveau2);
        SDL_RenderCopy(renderer, tNiveau2, NULL, &rectNiveau2);
        SDL_RenderCopy(renderer, tNiveau2_temps, NULL, &rectNiveau2_temps);
        SDL_RenderCopy(renderer, tNiveau2_mort, NULL, &rectNiveau2_mort);
        SDL_RenderCopy(renderer, tJouer2, NULL, &rectJouer2);
        SDL_RenderCopy(renderer, tRetour, NULL, &rectRetour);
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