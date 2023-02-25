/*Collision avec un objet de type SDL_Rect*/
void collision(SDL_Rect * position_perso, SDL_Rect * rectangle);
/*Collision avec un enemi*/
void collision_enemis(SDL_Rect * position_perso, SDL_Rect * enemi, SDL_Texture ** texture_enemi, int *vies);
/*Impossible de sortir à gauche de l'écran et perte de vie si le perso tombe sur le bord inférieur*/
void collision_ecran(SDL_Rect *position_perso, SDL_Rect position, int *vie_restante);