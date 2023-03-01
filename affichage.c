#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <unistd.h>
#include "fonctions.h"
#include "init.h"

int init(SDL_Window **window, SDL_Renderer **renderer)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("Erreur lors de l'initialisation de la SDL: %s", SDL_GetError());
        return -1;
    }
    if (TTF_Init() == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    if (SDL_CreateWindowAndRenderer(800, 600, SDL_WINDOW_FULLSCREEN_DESKTOP, window, renderer) != 0)
    {
        printf("Erreur lors de la creation de la fenetre et du renderer: %s", SDL_GetError());
        return -1;
    }
    return 0;
}

SDL_Texture *loadTexturePNG(const char *filename, SDL_Renderer *renderer, SDL_Rect *dimension)
{
    SDL_Texture *texture = NULL;
    SDL_Surface *tmp = NULL;
    tmp = IMG_Load(filename);
    if (tmp == NULL)
    {
        printf("Erreur lors du chargement de l'image: %s", SDL_GetError());
        return NULL;
    }
    texture = SDL_CreateTextureFromSurface(renderer, tmp);
    dimension->w = tmp->w;
    dimension->h = tmp->h;
    SDL_FreeSurface(tmp);
    if (texture == NULL)
    {
        printf("Erreur lors de la creation de la texture: %s", SDL_GetError());
        return NULL;
    }
    return texture;
}

SDL_Texture *loadTexture(const char *filename, SDL_Renderer *renderer)
{
    SDL_Texture *texture = NULL;
    SDL_Surface *tmp = NULL;
    tmp = SDL_LoadBMP(filename);
    if (tmp == NULL)
    {
        printf("Erreur lors du chargement de l'image: %s", SDL_GetError());
        return NULL;
    }
    texture = SDL_CreateTextureFromSurface(renderer, tmp);
    SDL_FreeSurface(tmp);
    if (texture == NULL)
    {
        printf("Erreur lors de la creation de la texture: %s", SDL_GetError());
        return NULL;
    }
    return texture;
}

int background(SDL_Window **window, SDL_Renderer **renderer, SDL_Texture **image, SDL_Rect *position)
{
    int statut = EXIT_FAILURE;
    *image = loadTexture("background/background.bmp", *renderer);
    if (*image == NULL)
    {
        return -1;
    }
    statut = EXIT_SUCCESS;
    SDL_GetWindowSize(*window, &position->w, &position->h);
    SDL_QueryTexture(*image, NULL, NULL, &position->w, &position->h);
    position->x = 0;
    position->y = 0;
    return statut;
}

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
    int fondtest = 0;
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

    // SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

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
    int fondtest = 0;
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

    // SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

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

