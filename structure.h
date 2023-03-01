typedef struct Astronaute{
    SDL_Rect position;
    SDL_Texture *sprite_finale;
    SDL_Texture *sprite1;
    SDL_Texture *sprite2;
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