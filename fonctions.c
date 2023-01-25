#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>

SDL_Texture * deplacement_droit(SDL_Rect *position_perso, SDL_Rect *position, SDL_Texture *texture, SDL_Texture *texture2, SDL_Texture *texture3)
{
    if (position_perso->x < position->w - position_perso->w)
        position_perso->x += 7;

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