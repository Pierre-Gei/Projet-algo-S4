#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include "affichage.h"
#include "fonctions.h"
#include <SDL2/SDL.h>

int main()
{
    SDL_Window *window = NULL;
    SDL_Texture *image = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Rect * position;
    position = malloc(sizeof(SDL_Rect));
    position->x = 0;
    position->y = 0;
    bool jeu = true;
    int statut = background(&window, &renderer, &image, &position);
    SDL_Surface *perso = NULL;
    perso = SDL_LoadBMP("sprites/aventurier1.bmp");
    SDL_Rect *position_perso;
    position_perso = malloc(sizeof(SDL_Rect));
    position_perso->x = position->w/2 - perso->w/2;
    position_perso->y =  position->h/2 - perso->h/2;
    SDL_Texture *texture = NULL;
    texture = SDL_CreateTextureFromSurface(renderer, perso);
    SDL_FreeSurface(perso);
    SDL_QueryTexture(texture, NULL, NULL, &position_perso->w, &position_perso->h);
   




    if(statut == -1)
        goto Quit;
  
    while(jeu)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    jeu = false;
                    break;
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                            jeu = false;
                            break;
                    }
                    break;
            }
        }
        SDL_RenderCopy(renderer, image, NULL, position);
        SDL_RenderCopy(renderer, texture, NULL, position_perso);
        
        SDL_RenderPresent(renderer);
    }

    Quit:
    if(image!=NULL)
        SDL_DestroyTexture(image);
    if(renderer!=NULL)
        SDL_DestroyRenderer(renderer);
    if(window!=NULL)
        SDL_DestroyWindow(window);
    SDL_Quit();
    free(position);
    return statut;
}