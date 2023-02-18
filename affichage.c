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
    if (SDL_CreateWindowAndRenderer(800, 600, SDL_WINDOW_FULLSCREEN_DESKTOP, window, renderer) != 0)
    {
        printf("Erreur lors de la creation de la fenetre et du renderer: %s", SDL_GetError());
        return -1;
    }
    return 0;
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

int menu_jeu(SDL_Window *window, SDL_Renderer *renderer, int TAILLE_POLICE, int INTERLIGNE, SDL_Rect *position_perso)
{
    SDL_Texture *image = NULL;
    TTF_Font *police = NULL;
    SDL_Surface *texte_Surface = NULL;
    SDL_Texture *tContinue = NULL;
    SDL_Texture *tRecommencer = NULL;
    SDL_Texture *tQuitter = NULL;
    SDL_Texture *fond = NULL;
    SDL_Rect position_fond;
    int fondtest = 0;
    int window_width = 0;
    int window_height = 0;
    bool jeu = true;
    int statut = 0;

    SDL_Color couleurBlanche = {255, 255, 255, 255};
    SDL_GetWindowSize(window, &window_width, &window_height);

    initText(&police, couleurBlanche, &texte_Surface, &tContinue, &renderer, TAILLE_POLICE, "Continuer");
    int x = (window_width - texte_Surface->w) / 2;
    SDL_Rect rect1 = {x, (window_height - 4 * texte_Surface->h - 3 * INTERLIGNE) / 2, texte_Surface->w, texte_Surface->h};
    SDL_FreeSurface(texte_Surface);

    initText(&police, couleurBlanche, &texte_Surface, &tRecommencer, &renderer, TAILLE_POLICE, "Recommencer");
    SDL_Rect rect2 = {x, (window_height - 4 * texte_Surface->h - 3 * INTERLIGNE) / 2 + texte_Surface->h + INTERLIGNE, texte_Surface->w, texte_Surface->h};
    SDL_FreeSurface(texte_Surface);

    initText(&police, couleurBlanche, &texte_Surface, &tQuitter, &renderer, TAILLE_POLICE, "Quitter");
    SDL_Rect rect3 = {x, (window_height - 4 * texte_Surface->h - 3 * INTERLIGNE) / 2 + 2 * texte_Surface->h + 2 * INTERLIGNE, texte_Surface->w, texte_Surface->h};
    SDL_FreeSurface(texte_Surface);

    fondtest = background(&window, &renderer, &fond, &position_fond);

    // TTF_CloseFont(police); je sais pas ou le mettre

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    while (jeu)
    {
        SDL_Delay(39);
        SDL_Event event;
        SDL_RenderCopy(renderer, fond, NULL, &position_fond);
        SDL_RenderCopy(renderer, tContinue, NULL, &rect1);
        SDL_RenderCopy(renderer, tRecommencer, NULL, &rect2);
        SDL_RenderCopy(renderer, tQuitter, NULL, &rect3);

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
                    if (event.button.x >= rect1.x && event.button.x <= rect1.x + rect1.w && event.button.y >= rect1.y && event.button.y <= rect1.y + rect1.h)
                    {
                        printf("Continuer ! \n");
                        statut = 0;
                        goto Quit;
                    }
                    if (event.button.x >= rect2.x && event.button.x <= rect2.x + rect2.w && event.button.y >= rect2.y && event.button.y <= rect2.y + rect2.h)
                    {
                        printf("Recommencer ! \n");
                        statut = 1;
                        position_perso->x = 560;
                        position_perso->y = 850;
                        goto Quit;
                    }
                    if (event.button.x >= rect3.x && event.button.x <= rect3.x + rect3.w && event.button.y >= rect3.y && event.button.y <= rect3.y + rect3.h)
                    {
                        printf("Quitter ! \n");
                        statut = -1;
                        goto Quit;
                    }
                    break;
                }
            }
            SDL_RenderPresent(renderer);
        }
    }

Quit:
    if (image != NULL)
        SDL_DestroyTexture(image);
    if (police != NULL)
        TTF_CloseFont(police);
    if (tContinue != NULL)
        SDL_DestroyTexture(tContinue);
    if (tRecommencer != NULL)
        SDL_DestroyTexture(tRecommencer);
    if (tQuitter != NULL)
        SDL_DestroyTexture(tQuitter);
    if (fond != NULL)
        SDL_DestroyTexture(fond);

    return statut;
}

void affichage_text_niveau(SDL_Texture **texture, TTF_Font *police, SDL_Rect *position, int x, int y, SDL_Renderer **renderer, char *texte, SDL_Color couleur)
{
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
