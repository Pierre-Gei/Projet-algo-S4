#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include "structure.h"

int collision(SDL_Rect *position_perso, SDL_Rect *objet)
{
    SDL_Rect intersection;
    if (SDL_IntersectRect(position_perso, objet, &intersection))
    {
        if (intersection.w > intersection.h)
        {
            if (position_perso->y < intersection.y)
            {
                position_perso->y = intersection.y - position_perso->h;
                return 1;
            }
            else
            {
                position_perso->y = intersection.y + intersection.h;
                return -1;
            }
        }
        else
        {
            if (position_perso->x < intersection.x)
            {
                position_perso->x = intersection.x - position_perso->w;
            }
            else
            {
                position_perso->x = intersection.x + intersection.w;
            }
            return -1;
        }
    }
}

int collision_enemis(SDL_Rect *position_perso, SDL_Rect *enemi, SDL_Texture **texture_enemi, int *vies)
{
    SDL_Rect intersection;
    if (SDL_IntersectRect(position_perso, enemi, &intersection))
    {
        if (intersection.w > intersection.h)
        {
            // Si le personnage tue l'enemi en touchant la tete
            if (position_perso->y < intersection.y)
            {
                // position_perso->y = intersection.y - position_perso->h;
                enemi->x = 0;
                enemi->y = 0;
                enemi->w = 0;
                enemi->h = 0;
                SDL_DestroyTexture(*texture_enemi);
            }
            else
            {
                *vies = *vies - 1;
                return -1;
            }
        }
        else
        {
            if (position_perso->x < intersection.x)
            {
                *vies = *vies - 1;
                return -1;
            }
            else
            {
                *vies = *vies - 1;
                return -1;
            }
        }
    }
}

void collision_ecran(SDL_Rect *position_perso, SDL_Rect position, int *vie_restante)
{
    if (position_perso->x <= 0)
    {
        position_perso->x = 0;
    }
    if (position_perso->y >= position.h)
    {
        *vie_restante = *vie_restante - 1;
    }
}

void position_perso_ennemi(SDL_Rect position_perso, SDL_Rect *position_ennemi, SDL_Texture **ennemi_texture, SDL_Renderer **renderer, int vitesse_ennemi, int range)
{
    if (position_ennemi->x - position_perso.x > 0 && position_ennemi->x - position_perso.x < range)
    {
        position_ennemi->x = position_ennemi->x - vitesse_ennemi;
        SDL_RenderCopy(*renderer, *ennemi_texture, NULL, position_ennemi);
    }
    else if (position_ennemi->x - position_perso.x < 0 && position_ennemi->x - position_perso.x > -range)
    {
        position_ennemi->x = position_ennemi->x + vitesse_ennemi;
        SDL_RenderCopyEx(*renderer, *ennemi_texture, NULL, position_ennemi, 0, NULL, SDL_FLIP_HORIZONTAL);
    }
    else
    {
        SDL_RenderCopy(*renderer, *ennemi_texture, NULL, position_ennemi);
    }
}
