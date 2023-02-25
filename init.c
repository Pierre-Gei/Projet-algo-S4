#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <math.h>


void initText(TTF_Font ** police, SDL_Color couleur, SDL_Surface **texte_Surface, SDL_Texture **texte_texture, SDL_Renderer **renderer, int taillePolice, char *texte)
{
    *police = TTF_OpenFont("Polices/Arcade.ttf", taillePolice);
    if(!(*police))
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_OpenFont : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    *texte_Surface = TTF_RenderText_Blended(*police, texte, couleur);
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
}