/*Afficher le fond d'écran*/
int background(SDL_Window **window, SDL_Renderer **renderer, SDL_Texture **image, SDL_Rect *position);
/*Initialisation de la fenêtre*/
int init(SDL_Window **window, SDL_Renderer **renderer);
/*Charger une texture*/
SDL_Texture *loadTexture(const char *filename, SDL_Renderer *renderer);
/*Charger une texture a partir d'un PNG ou autre*/
SDL_Texture *loadTexturePNG(const char *filename, SDL_Renderer *renderer, SDL_Rect *dimension);
/*Initialiser le texte correctement*/
void initText(SDL_Color couleur, SDL_Surface **texte_Surface,SDL_Texture **texte_texture, SDL_Renderer **renderer, int taillePolice, char *texte);
/*Initialiser à 0 les champs de la structure Astronaute*/
Astronaute initAstronaute(Astronaute a);
/*Initialiser à 0 les champs de la structure Ennemi*/
Ennemi initEnnemi(Ennemi e);
/*Remplir les champs de la structure Astronaute*/
Astronaute setAstronaute(char *chemin1, char *chemin2, char *chemin_mort1, char *chemin_mort2, char *chemin_mort3, int vie, SDL_Renderer *renderer, int vitesse_max, int vitesse_saut);
/*Remplir les champs de la structure Ennemi*/
Ennemi setEnnemi(char *chemin1, char *chemin2, SDL_Renderer *renderer);
/*Detruire les textures d'une structure Astronaute*/
void destroyAstronaute(Astronaute *a);
/*Detruire les textures d'une structure Ennemi*/
void destroyEnnemi(Ennemi *e);
/*Initialiser à 0 les champs de la structure plateforme*/
plateforme initplateforme(plateforme p);
/*Initialiser à 0 les champs de la structure vaisseau*/
vaisseau initvaisseau(vaisseau v);
/*Remplir les champ de la structure vaisseau*/
vaisseau setVaisseau(vaisseau v, char *chemin_immobile, char *chemin_mouvement1, char *chemin_mouvement2, SDL_Renderer *renderer);
/*Detruire les textures d'une structure vaisseau*/
void destroyVaisseau(vaisseau *v);

