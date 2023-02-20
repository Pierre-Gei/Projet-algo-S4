#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

/*Afficher le fond d'écran*/
int background(SDL_Window **window, SDL_Renderer **renderer, SDL_Texture **image, SDL_Rect *position);
/*Initialisation de la fenêtre*/
int init(SDL_Window **window, SDL_Renderer **renderer);
/*Charger une texture*/
SDL_Texture *loadTexture(const char *filename, SDL_Renderer *renderer);
/*Afficher le fond d'écran en jeu*/
void affichage_background(SDL_Renderer **renderer, SDL_Texture **image, SDL_Rect *position);
/*Petit menu en jeu*/
int menu_jeu(SDL_Window * window, SDL_Renderer * renderer, int TAILLE_POLICE, int INTERLIGNE);
/*Afficher le texte dans une boucle*/
void affichage_text_niveau(SDL_Texture **texture, TTF_Font * police, SDL_Rect * position,int x, int y, SDL_Renderer **renderer, char * texte, SDL_Color couleur);
/*Alterner entre les deux sprites du personnage*/
void changement_sprites(SDL_Texture **rendu, SDL_Texture *texture1, SDL_Texture *texture2);

void changement_couleur(TTF_Font *police, SDL_Color couleur, SDL_Renderer **renderer, SDL_Texture **texte_texture,char *texte);
void changement_couleur_inRect(TTF_Font *police, SDL_Color couleur,SDL_Color couleur_initiale, SDL_Renderer **renderer, SDL_Texture **texte_texture, char *texte, SDL_Point souris, SDL_Rect rectangle);

int menu_game_over(SDL_Window *window, SDL_Renderer *renderer, int TAILLE_POLICE, int INTERLIGNE);