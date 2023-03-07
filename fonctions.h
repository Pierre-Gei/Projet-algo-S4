/*Collision avec un objet de type SDL_Rect*/
int collision(SDL_Rect * position_perso, SDL_Rect * rectangle);
/*Collision avec un enemi*/
int collision_enemis(SDL_Rect * position_perso, SDL_Rect * enemi, SDL_Texture ** texture_enemi, int *vies);
/*Impossible de sortir à gauche de l'écran et perte de vie si le perso tombe sur le bord inférieur*/
void collision_ecran(SDL_Rect *position_perso, SDL_Rect position, int *vie_restante);
/*Faire avancer l'ennemi vers le personnage*/
void position_perso_ennemi(SDL_Rect position_perso, SDL_Rect * position_ennemi, SDL_Texture **ennemi_texture,SDL_Renderer ** renderer, int vitesse_ennemi, int range);