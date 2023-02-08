#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "niveau1.h"
int main()
{
    int statut = 0;
    statut = niveau1();
    return statut;
}