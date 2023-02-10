#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "niveau1.h"
#include "affichage.h"
#include "fonctions.h"
#include "init.h"

#define TAILLE_POLICE 75
#define INTERLIGNE 20

int main()
{
    SDL_Window *window = NULL;
    SDL_Texture *image = NULL;
    SDL_Renderer *renderer = NULL;
    TTF_Font * police = NULL;
    SDL_Surface *texte_Surface = NULL;
    SDL_Texture *tJouer = NULL;
    SDL_Texture *tCharger = NULL;
    SDL_Texture *tParametres = NULL;
    SDL_Texture *tSauvegarder = NULL;
    SDL_Texture *tQuitter = NULL;
    int window_width = 0;
    int window_height = 0;
    bool jeu = true;

    SDL_Color couleurBlanche = {255, 255, 255, 255};
    init(&window, &renderer);
    SDL_GetWindowSize(window, &window_width, &window_height);

    initText(&police,couleurBlanche, &texte_Surface, &tJouer, &renderer, TAILLE_POLICE, "Jouer");
    int x = (window_width - texte_Surface->w)/2;
    SDL_Rect rect1 = {x , ( window_height - 4*texte_Surface->h -3*INTERLIGNE) /2 , texte_Surface->w, texte_Surface->h};
    SDL_FreeSurface(texte_Surface);

    initText(&police,couleurBlanche, &texte_Surface, &tCharger, &renderer, TAILLE_POLICE, "Charger");
    SDL_Rect rect2 = {x, ( window_height - 4*texte_Surface->h -3*INTERLIGNE) /2 + texte_Surface->h + INTERLIGNE, texte_Surface->w, texte_Surface->h};
    SDL_FreeSurface(texte_Surface);

    initText(&police,couleurBlanche, &texte_Surface, &tParametres, &renderer, TAILLE_POLICE, "Parametres");
    SDL_Rect rect3 = {x, ( window_height - 4*texte_Surface->h -3*INTERLIGNE) /2 + 2*texte_Surface->h + 2*INTERLIGNE, texte_Surface->w, texte_Surface->h};
    SDL_FreeSurface(texte_Surface);

    initText(&police,couleurBlanche, &texte_Surface, &tSauvegarder, &renderer, TAILLE_POLICE, "Sauvegarder");
    SDL_Rect rect4 = {x, ( window_height - 4*texte_Surface->h -3*INTERLIGNE) /2 + 3*texte_Surface->h + 3*INTERLIGNE, texte_Surface->w, texte_Surface->h};
    SDL_FreeSurface(texte_Surface);

    initText(&police,couleurBlanche, &texte_Surface, &tQuitter, &renderer, TAILLE_POLICE, "Quitter");
    SDL_Rect rect5 = {x, ( window_height - 4*texte_Surface->h -3*INTERLIGNE) /2 + 4*texte_Surface->h + 4*INTERLIGNE, texte_Surface->w, texte_Surface->h};
    SDL_FreeSurface(texte_Surface);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);


    while (jeu)
    {
        SDL_Delay(39);
        SDL_Event event;
        // SDL_RenderDrawRect(renderer, &rect1);
        // SDL_RenderDrawRect(renderer, &rect2);
        // SDL_RenderDrawRect(renderer, &rect3);
        // SDL_RenderDrawRect(renderer, &rect4);
        // SDL_RenderDrawRect(renderer, &rect5);
        SDL_RenderCopy(renderer, tJouer, NULL, &rect1);
        SDL_RenderCopy(renderer, tCharger, NULL, &rect2);
        SDL_RenderCopy(renderer, tParametres, NULL, &rect3);
        SDL_RenderCopy(renderer, tSauvegarder, NULL, &rect4);
        SDL_RenderCopy(renderer, tQuitter, NULL, &rect5);
      
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                jeu = false;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    jeu = false;
                    break;
                }
                break;
            }
        }
        SDL_RenderPresent(renderer);
    }

Quit:
    if (image != NULL)
        SDL_DestroyTexture(image);
    if (renderer != NULL)
        SDL_DestroyRenderer(renderer);
    if (window != NULL)
        SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
    
    return 0;
}