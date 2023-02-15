#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include "affichage.h"

void collision(SDL_Rect * position_perso, SDL_Rect * rectangle)
{
    if ( (position_perso->x + position_perso->w) > rectangle->x && position_perso->x < (rectangle->x + rectangle->w) && (position_perso->y + position_perso->h) > rectangle->y && position_perso->y < (rectangle->y + rectangle->h) )
    {
        if (position_perso->x < rectangle->x)
        {
            position_perso->x = rectangle->x - position_perso->w;
        }
        else if (position_perso->x > rectangle->x)
        {
            position_perso->x = rectangle->x + rectangle->w;
        }
       
      
        
    }
}

SDL_Texture * deplacement_droit(SDL_Rect *position_perso, SDL_Rect *position, SDL_Texture *texture, SDL_Texture *texture2, SDL_Texture *texture3)
{
    // if (position_perso->x>=(position->w/4)*3)
    // {
    //     position->x-=10;
    // }
    // else
    // {
    //     position_perso->x += 7;
    // }
    // if(position->x==-(position->w))
    // {
    //     position->x=0;
    // }

    if (texture3 == texture)
    {
        return texture2;
    }
    else
    {
        return texture;
    }
}

SDL_Texture * deplacement_gauche(SDL_Rect *position_perso, SDL_Rect *position, SDL_Texture *texture, SDL_Texture *texture2, SDL_Texture *texture3)
{
    if (position_perso->x > 0)
        position_perso->x -= 7;

    if (texture3 == texture)
    {
        return texture2;
    }
    else
    {
        return texture;
    }
}

void saut_parabolique(SDL_Rect *position_perso, SDL_Rect *position, SDL_Texture *texture, SDL_Texture *texture2, SDL_Texture *texture3, SDL_Renderer *renderer, SDL_Texture *image, int direction)
{
    //deplacer le perso le long d'une trajectoire parabolique
    int i = 0;
    int a = 1;
    int b = 0;
    int c = -50;
    int position_initiale = position_perso->y;
    //deplacement en x
    do
    {
        if(direction == 1){
            if (position_perso->x>=(position->w/4)*3)
            {
                position->x -= 25;
            }
            else
            {
            position_perso->x += 25; 
            }
        }
        else if(direction == -1){
            if (position_perso->x -25 < 0)
            {
                position_perso->x = 0;
            }
            else
            {
                position_perso->x -= 25;
            }
        }
        position_perso->y += a * (i) * (i) + b * (i) + c;
        i++;
        if(position_perso->y > position_initiale)
        {
            position_perso->y = position_initiale;
        }
        SDL_Delay(39);
        affichage_background(&renderer,&image,position);
        SDL_RenderCopy(renderer, texture2, NULL, position_perso);
        SDL_RenderPresent(renderer);
    }while (position_perso->y < position_initiale && i>0);
}

