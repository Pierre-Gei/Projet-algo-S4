#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "affichage.h"
#include "fonctions.h"
#include <SDL2/SDL.h>

int init(SDL_Window **window, SDL_Renderer **renderer)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("Erreur lors de l'initialisation de la SDL: %s", SDL_GetError());
        return -1;
    }
    if (SDL_CreateWindowAndRenderer(800, 600, SDL_WINDOW_FULLSCREEN_DESKTOP, window, renderer) != 0)
    {
        printf("Erreur lors de la creation de la fenetre et du renderer: %s", SDL_GetError());
        return -1;
    }
    return 0;
}

SDL_Texture *loadTexture(const char *filename, SDL_Renderer *renderer)
{
    SDL_Texture *texture = NULL;
    SDL_Surface *tmp = NULL;
    tmp = SDL_LoadBMP("background1.bmp");
    if (tmp == NULL)
    {
        printf("Erreur lors du chargement de l'image: %s", SDL_GetError());
        return NULL;
    }
    texture = SDL_CreateTextureFromSurface(renderer, tmp);
    SDL_FreeSurface(tmp);
    if (texture == NULL)
    {
        printf("Erreur lors de la creation de la texture: %s", SDL_GetError());
        return NULL;
    }
    return texture;
}

int setWindowColor(SDL_Renderer *renderer, SDL_Color color)
{
    if (SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a) < 0)
        return -1;
    if (SDL_RenderClear(renderer) < 0)
        return -1;
    return 0;
}

int main()
{

    SDL_Window *window = NULL;
    SDL_Texture *image = NULL;
    SDL_Renderer *renderer = NULL;
    int statut = EXIT_FAILURE;
    SDL_Rect position;
    position.x=0;
    position.y=0;
    
    if (init(&window, &renderer) != 0)
    {
        goto Quit;
    }
    image = loadTexture("background/background1.bmp", renderer);
    if (image == NULL)
    {
        goto Quit;
    }
    statut = EXIT_SUCCESS;
    SDL_GetWindowSize(window, &position.x, &position.y);
    printf("x : %d, Y : %d", position.x, position.y);
    position.x = position.x / 2 - 330;
    position.y = position.y / 2 -( 441/2);
    SDL_QueryTexture(image, NULL, NULL, &position.w, &position.h);
    SDL_RenderCopy(renderer, image, NULL, &position);
    SDL_RenderPresent(renderer);

    SDL_Delay(5000);
Quit:
    if (image != NULL)
        SDL_DestroyTexture(image);
    if (renderer != NULL)
        SDL_DestroyRenderer(renderer);
    if (window != NULL)
        SDL_DestroyWindow(window);
    SDL_Quit();
    return statut;
}