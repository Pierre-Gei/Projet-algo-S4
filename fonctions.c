#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include "affichage.h"

void collision(SDL_Rect *position_perso, SDL_Rect *objet)
{
    SDL_Rect intersection;
    if (SDL_IntersectRect(position_perso, objet, &intersection))
    {
        if (intersection.w > intersection.h)
        {
            if (position_perso->y < intersection.y)
            {
                position_perso->y = intersection.y - position_perso->h;
            }
            else
            {
                position_perso->y = intersection.y + intersection.h;
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
        }
    }
}

void collision_enemis(SDL_Rect *position_perso, SDL_Rect *enemi, SDL_Texture **texture_enemi, int *vies)
{
    SDL_Rect intersection;
    if (SDL_IntersectRect(position_perso, enemi, &intersection))
    {
        if (intersection.w > intersection.h)
        {
            //Si le personnage tue l'enemi en touchant la tete
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
            }
        }
        else
        {
            if (position_perso->x < intersection.x)
            {
                *vies = *vies - 1;
            }
            else
            {
                *vies = *vies - 1;
            }
        }
    }
}
