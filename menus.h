/*Afficher les paramètres avec les commandes*/
void parametre(SDL_Window *window, SDL_Renderer *renderer, int TAILLE_POLICE, int INTERLIGNE, SDL_Texture *fond, SDL_Rect position_fond);
/*Petit menu en jeu*/
int menu_jeu(SDL_Window *window, SDL_Renderer *renderer, int TAILLE_POLICE, int INTERLIGNE, int x, SDL_Texture *fond, SDL_Rect position_fond);
/*Menu de mort du personnage*/
int menu_game_over(SDL_Window *window, SDL_Renderer *renderer, int TAILLE_POLICE, int INTERLIGNE, int x, SDL_Texture *fond, SDL_Rect position_fond);
/*Menu de victoire*/
int menu_victoire(SDL_Window *window, SDL_Renderer *renderer, int TAILLE_POLICE, int INTERLIGNE, int x, SDL_Texture *fond, SDL_Rect position_fond);
/*Menu choix de niveau*/
int choix_niveau(SDL_Window *window, SDL_Renderer *renderer, int TAILLE_POLICE, int INTERLIGNE, int x, SDL_Texture *fond, SDL_Rect position_fond, int *niveau, int tab_mort[], int tab_temps[], int *recompenses);