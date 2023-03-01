#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <math.h>
#include "structure.h"


void initText(SDL_Color couleur, SDL_Surface **texte_Surface, SDL_Texture **texte_texture, SDL_Renderer **renderer, int taillePolice, char *texte)
{
    TTF_Font * police = TTF_OpenFont("Polices/Arcade.ttf", taillePolice);
    if(!police)
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_OpenFont : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    *texte_Surface = TTF_RenderText_Blended(police, texte, couleur);
      if(!texte_Surface)
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_RenderText_Blended : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    *texte_texture = SDL_CreateTextureFromSurface(*renderer, *texte_Surface);
    if(!(*texte_texture))
    {
        fprintf(stderr, "Erreur d'initialisation de SDL_CreateTextureFromSurface : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    TTF_CloseFont(police);
}

Astronaute initAstronaute(Astronaute a)
{
    a.position.x = 0;
    a.position.y = 0;
    a.position.w = 0;
    a.position.h = 0;
    a.vie = 1;
    a.sprite1 = NULL;
    a.sprite2 = NULL;
    a.sprite_finale = NULL;
    a.vitesse_max = 0;
    a.vitesse_saut = 0;
    return a;
}

Ennemi initEnnemi(Ennemi e)
{
    e.position.x = 0;
    e.position.y = 0;
    e.position.w = 0;
    e.position.h = 0;
    e.sprite1 = NULL;
    e.sprite2 = NULL;
    e.sprite_finale = NULL;
}

void destroyAstronaute(Astronaute *a)
{
    if(a->sprite1 != NULL)
        SDL_DestroyTexture(a->sprite1);
    if(a->sprite2 != NULL)
        SDL_DestroyTexture(a->sprite2);
    if(a->sprite_finale != NULL)
        SDL_DestroyTexture(a->sprite_finale);
}

void destroyEnnemi(Ennemi *e)
{
    if(e->sprite1 != NULL)
        SDL_DestroyTexture(e->sprite1);
    if(e->sprite2 != NULL)
        SDL_DestroyTexture(e->sprite2);
    if(e->sprite_finale != NULL)
        SDL_DestroyTexture(e->sprite_finale);
}