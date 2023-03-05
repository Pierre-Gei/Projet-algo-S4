typedef struct Astronaute{
    SDL_Rect position;
    SDL_Texture *sprite_finale;
    SDL_Texture *sprite1;
    SDL_Texture *sprite2;
    SDL_Texture *sprite_mort1;
    SDL_Texture *sprite_mort2;
    SDL_Texture *sprite_mort3;
    SDL_Rect dimension_mort;
    int vie;
    int vitesse_max;
    int vitesse_saut;
}Astronaute;

typedef struct Ennemi{
    SDL_Rect position;
    SDL_Texture *sprite_finale;
    SDL_Texture *sprite1;
    SDL_Texture *sprite2;
}Ennemi;

typedef struct plateforme{
    SDL_Rect position;
    SDL_Texture *texture;
    int collision;
}plateforme;

typedef struct vaisseau{
    SDL_Rect position;
    SDL_Texture * immobile;
    SDL_Texture * mouvement1;
    SDL_Texture * mouvement2;
}vaisseau;