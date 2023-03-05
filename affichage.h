/*Afficher le fond d'écran en jeu*/
void affichage_background(SDL_Renderer **renderer, SDL_Texture **image, SDL_Rect *position);
/*Afficher le texte dans une boucle*/
void affichage_text_niveau(SDL_Texture **texture, int Taille_Police, SDL_Rect *position, int x, int y, SDL_Renderer **renderer, char *texte, SDL_Color couleur);
/*Alterner entre les deux sprites du personnage*/
void changement_sprites(SDL_Texture **rendu, SDL_Texture *texture1, SDL_Texture *texture2);
/*Changer la couleur d'un texte*/
void changement_couleur(int Taille_Police, SDL_Color couleur, SDL_Renderer **renderer, SDL_Texture **texte_texture, char *texte);
/*Changer la couleur d'un texte lorsque la souris survol*/
void changement_couleur_inRect(int Taille_Police, SDL_Color couleur, SDL_Color couleur_initiale, SDL_Renderer **renderer, SDL_Texture **texte_texture, char *texte, SDL_Point souris, SDL_Rect rectangle);
/*Textures du personnage en fonction de la direction*/
void affiche_perso(SDL_Renderer **renderer, SDL_Texture *perso_rendu, SDL_Texture *perso_static, SDL_Rect position_perso, int vx, int direction);
/*Animation de mort du personnage*/
void animation_mort(SDL_Renderer *renderer, Astronaute a, SDL_Texture *fond, SDL_Rect position_fond);
/*Animation de victoire*/
void animation_victoire(SDL_Renderer * renderer, vaisseau v, SDL_Texture*fond, SDL_Rect position_fond);