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

void saut (SDL_Rect *position_perso, SDL_Rect *position, SDL_Texture *texture, SDL_Texture *texture2, SDL_Texture *texture3, SDL_Renderer *renderer, SDL_Texture *image)
{
    int i = 0;
    while (i < 10)
    {
        position_perso->y -= 50;
        i++;
        SDL_Delay(15);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, image, NULL, position);
        SDL_RenderCopy(renderer, texture2, NULL, position_perso);
        SDL_RenderPresent(renderer);
    }
    while (i < 20)
    {
        position_perso->y += 50;
        i++;
        SDL_Delay(15);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, image, NULL, position);
        SDL_RenderCopy(renderer, texture2, NULL, position_perso);
        SDL_RenderPresent(renderer);
    }

}
