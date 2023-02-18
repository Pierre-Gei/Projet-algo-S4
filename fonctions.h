/*Collision avec un objet de type SDL_Rect*/
void collision(SDL_Rect * position_perso, SDL_Rect * rectangle);
/*Collision avec un enemi*/
void collision_enemis(SDL_Rect * position_perso, SDL_Rect * enemi, SDL_Texture ** texture_enemi, int *vies);