#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>

void initVariable(SDL_Rect *position, SDL_Rect *rectangle, SDL_Rect *position_perso, SDL_Surface *perso)
{
    position->x = 0;
    position->y = 0;

    position_perso->x = position->w / 2 - perso->w / 2;
    position_perso->y = 850;
    rectangle-> x= 0;
    rectangle->y = 960 ;
    rectangle->h = 100;
    rectangle->w = position->w;
}