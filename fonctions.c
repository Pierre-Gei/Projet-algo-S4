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
