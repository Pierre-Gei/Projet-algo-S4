#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>

SDL_Texture * deplacement_droit(SDL_Rect *position_perso, SDL_Rect *position, SDL_Texture *texture, SDL_Texture *texture2, SDL_Texture *texture3)
{
    if (position_perso->x>=(position->w/4)*3)
    {
        position->x-=10;
    }
    else
    {
        position_perso->x += 7;
    }
    if(position->x==-(position->w))
    {
        position->x=0;
    }

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

void saut_diagonal_droit(SDL_Rect *position_perso, SDL_Rect *position, SDL_Texture *texture, SDL_Texture *texture2, SDL_Texture *texture3, SDL_Renderer *renderer, SDL_Texture *image)
{

    int i = 0;
    while (i < 10)
    {
        position_perso->y -= 25;
        position_perso->x += 25;
        i++;
        SDL_Delay(30);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, image, NULL, position);
        SDL_RenderCopy(renderer, texture2, NULL, position_perso);
        SDL_RenderPresent(renderer);
    }
    while (i < 20)
    {
        position_perso->x += 25;
        position_perso->y += 25;
        
        i++;
        SDL_Delay(30);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, image, NULL, position);
        SDL_RenderCopy(renderer, texture2, NULL, position_perso);
        SDL_RenderPresent(renderer);
    }
}

void saut_parabolique(SDL_Rect *position_perso, SDL_Rect *position, SDL_Texture *texture, SDL_Texture *texture2, SDL_Texture *texture3, SDL_Renderer *renderer, SDL_Texture *image)
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
        position_perso->x += 25;
        position_perso->y += a * (i) * (i) + b * (i) + c;
        i++;
        if(position_perso->y > position_initiale)
        {
            position_perso->y = position_initiale;
        }
        SDL_Delay(30);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, image, NULL, position);
        SDL_RenderCopy(renderer, texture2, NULL, position_perso);
        SDL_RenderPresent(renderer);
    }while (position_perso->y < position_initiale && i>0);
}