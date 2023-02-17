#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include "affichage.h"

void collision(SDL_Rect *position_perso, SDL_Rect *rectangle)
{
    SDL_Rect intersection;
    if (SDL_IntersectRect(position_perso, rectangle, &intersection))
    {
       printf("x = %d, y = %d, w = %d, h = %d\n", intersection.x, intersection.y, intersection.w, intersection.h);
       if(intersection.w > intersection.h)
       {
           if(position_perso->y < intersection.y)
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
           if(position_perso->x < intersection.x)
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
