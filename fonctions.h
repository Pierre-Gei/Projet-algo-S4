SDL_Texture *deplacement_droit(SDL_Rect *position_perso, SDL_Rect *position, SDL_Texture *texture, SDL_Texture *texture2, SDL_Texture *texture3);
SDL_Texture * deplacement_gauche(SDL_Rect *position_perso, SDL_Rect *position, SDL_Texture *texture, SDL_Texture *texture2, SDL_Texture *texture3);

//Fait sauter le personnage en fonction de la direction donnée en paramètre (1 pour droite, -1 pour gauche et 0 pour le saut vertical)
void saut_parabolique(SDL_Rect *position_perso, SDL_Rect *position, SDL_Texture *texture, SDL_Texture *texture2, SDL_Texture *texture3, SDL_Renderer *renderer, SDL_Texture *image, int direction);