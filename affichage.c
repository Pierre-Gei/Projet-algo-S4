#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "structure.h"
#include "init.h"

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

void animation_victoire(SDL_Renderer *renderer, vaisseau v, SDL_Texture *fond, SDL_Rect position_fond)
{
    int cpt = 0;
    int temps = 0;
    int acceleration = 0;
    SDL_Texture *temp = NULL;
    while (v.position.y > 200)
    {
        v.position.y = v.position.y - 15;
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, fond, NULL, &position_fond);
        SDL_RenderCopy(renderer, v.immobile, NULL, &v.position);
        SDL_RenderPresent(renderer);
        SDL_Delay(20);
    }
    SDL_Delay(500);
    while (v.position.x < position_fond.w)
    {
        v.position.x = v.position.x + acceleration;
        acceleration = acceleration + 1;
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, fond, NULL, &position_fond);
        if (SDL_GetTicks() - temps > 100)
        {
            if (cpt % 2 == 0)
            {
                temp = v.mouvement1;
            }
            else
            {
                temp = v.mouvement2;
            }
            cpt++;
            temps = SDL_GetTicks();
        }
        SDL_RenderCopy(renderer, temp, NULL, &v.position);
        SDL_RenderPresent(renderer);
        SDL_Delay(20);
    }
}