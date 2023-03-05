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
#include "affichage.h"

int init(SDL_Window **window, SDL_Renderer **renderer)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("Erreur lors de l'initialisation de la SDL: %s", SDL_GetError());
        return -1;
    }
    if (TTF_Init() == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    if (SDL_CreateWindowAndRenderer(800, 600, SDL_WINDOW_FULLSCREEN_DESKTOP, window, renderer) != 0)
    {
        printf("Erreur lors de la creation de la fenetre et du renderer: %s", SDL_GetError());
        return -1;
    }
    return 0;
}

SDL_Texture *loadTexturePNG(const char *filename, SDL_Renderer *renderer, SDL_Rect *dimension)
{
    SDL_Texture *texture = NULL;
    SDL_Surface *tmp = NULL;
    tmp = IMG_Load(filename);
    if (tmp == NULL)
    {
        printf("Erreur lors du chargement de l'image: %s", SDL_GetError());
        return NULL;
    }
    texture = SDL_CreateTextureFromSurface(renderer, tmp);
    dimension->w = tmp->w;
    dimension->h = tmp->h;
    SDL_FreeSurface(tmp);
    if (texture == NULL)
    {
        printf("Erreur lors de la creation de la texture: %s", SDL_GetError());
        return NULL;
    }
    return texture;
}

SDL_Texture *loadTexture(const char *filename, SDL_Renderer *renderer)
{
    SDL_Texture *texture = NULL;
    SDL_Surface *tmp = NULL;
    tmp = SDL_LoadBMP(filename);
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

int background(SDL_Window **window, SDL_Renderer **renderer, SDL_Texture **image, SDL_Rect *position)
{
    int statut = EXIT_FAILURE;
    *image = loadTexture("background/background.bmp", *renderer);
    if (*image == NULL)
    {
        return -1;
    }
    statut = EXIT_SUCCESS;
    SDL_GetWindowSize(*window, &position->w, &position->h);
    SDL_QueryTexture(*image, NULL, NULL, &position->w, &position->h);
    position->x = 0;
    position->y = 0;
    return statut;
}

void initText(SDL_Color couleur, SDL_Surface **texte_Surface, SDL_Texture **texte_texture, SDL_Renderer **renderer, int taillePolice, char *texte)
{
    TTF_Font *police = TTF_OpenFont("Polices/Arcade.ttf", taillePolice);
    if (!police)
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_OpenFont : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    *texte_Surface = TTF_RenderText_Blended(police, texte, couleur);
    if (!texte_Surface)
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_RenderText_Blended : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    *texte_texture = SDL_CreateTextureFromSurface(*renderer, *texte_Surface);
    if (!(*texte_texture))
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
    a.dimension_mort.x = 0;
    a.dimension_mort.y = 0;
    a.dimension_mort.w = 0;
    a.dimension_mort.h = 0;
    a.vie = 1;
    a.sprite1 = NULL;
    a.sprite2 = NULL;
    a.sprite_finale = NULL;
    a.sprite_mort1 = NULL;
    a.sprite_mort2 = NULL;
    a.sprite_mort3 = NULL;
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

Astronaute setAstronaute(char *chemin1, char *chemin2, char *chemin_mort1, char *chemin_mort2, char *chemin_mort3, int vie, SDL_Renderer *renderer, int vitesse_max, int vitesse_saut)
{
    Astronaute a;
    a.vie = vie;
    a.sprite_mort1 = loadTexturePNG(chemin_mort1, renderer, &a.dimension_mort);
    a.sprite_mort2 = loadTexturePNG(chemin_mort2, renderer, &a.dimension_mort);
    a.sprite_mort3 = loadTexturePNG(chemin_mort3, renderer, &a.dimension_mort);
    a.sprite1 = loadTexturePNG(chemin1, renderer, &a.position);
    a.sprite2 = loadTexturePNG(chemin2, renderer, &a.position);
    a.sprite_finale = a.sprite1;
    a.vitesse_max = vitesse_max;
    a.vitesse_saut = vitesse_saut;
    return a;
}

Ennemi setEnnemi(char *chemin1, char *chemin2, SDL_Renderer *renderer)
{
    Ennemi e;
    e.sprite1 = loadTexturePNG(chemin1, renderer, &e.position);
    e.sprite2 = loadTexturePNG(chemin2, renderer, &e.position);
    e.sprite_finale = e.sprite1;
    return e;
}

void destroyAstronaute(Astronaute *a)
{
    if (a->sprite1 != NULL)
        SDL_DestroyTexture(a->sprite1);
    if (a->sprite2 != NULL)
        SDL_DestroyTexture(a->sprite2);
    if (a->sprite_finale != NULL)
        SDL_DestroyTexture(a->sprite_finale);
    if (a->sprite_mort1 != NULL)
        SDL_DestroyTexture(a->sprite_mort1);
    if (a->sprite_mort2 != NULL)
        SDL_DestroyTexture(a->sprite_mort2);
    if (a->sprite_mort3 != NULL)
        SDL_DestroyTexture(a->sprite_mort3);
}

void destroyEnnemi(Ennemi *e)
{
    if (e->sprite1 != NULL)
        SDL_DestroyTexture(e->sprite1);
    if (e->sprite2 != NULL)
        SDL_DestroyTexture(e->sprite2);
    if (e->sprite_finale != NULL)
        SDL_DestroyTexture(e->sprite_finale);
}

plateforme initplateforme(plateforme p)
{
    p.position.x = 0;
    p.position.y = 0;
    p.position.w = 0;
    p.position.h = 0;
    p.texture=NULL;
    p.collision=0;
}

vaisseau initvaisseau(vaisseau v)
{
    v.position.x = 0;
    v.position.y = 0;
    v.position.w = 0;
    v.position.h = 0;
    v.immobile = NULL;
    v.mouvement1 = NULL;
    v.mouvement2 = NULL;
}

vaisseau setVaisseau(vaisseau v, char *chemin_immobile, char *chemin_mouvement1, char *chemin_mouvement2, SDL_Renderer *renderer)
{
    v.immobile = loadTexturePNG(chemin_immobile, renderer, &v.position);
    v.mouvement1 = loadTexturePNG(chemin_mouvement1, renderer, &v.position);
    v.mouvement2 = loadTexturePNG(chemin_mouvement2, renderer, &v.position);
    return v;
}
