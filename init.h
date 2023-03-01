/*Initialiser le texte correctement*/
void initText(SDL_Color couleur, SDL_Surface **texte_Surface,SDL_Texture **texte_texture, SDL_Renderer **renderer, int taillePolice, char *texte);
Astronaute initAstronaute(Astronaute a);
void destroyAstronaute(Astronaute *a);
Ennemi initEnnemi(Ennemi e);
void destroyEnnemi(Ennemi *e);