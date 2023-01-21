#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>


int background ( SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *image, SDL_Rect * position);

int init(SDL_Window **window, SDL_Renderer **renderer);
SDL_Texture *loadTexture(const char *filename, SDL_Renderer *renderer);
