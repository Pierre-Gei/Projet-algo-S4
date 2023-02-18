#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>

void sauvegarde(int recompenses, int nbr_morts, int temps, int niveau)
{
    FILE *fichier = NULL;
    fichier = fopen("sauvegarde.txt", "w");
    if (fichier != NULL)
    {
        fprintf(fichier, "recompenses: %d \n", recompenses);
        fprintf(fichier, "nbr_morts: %d \n", nbr_morts);
        fprintf(fichier, "temps: %d \n", temps);
        fprintf(fichier, "niveau: %d \n", niveau);
        fclose(fichier);
    }
    else
    {
        printf("Impossible d'ouvrir le fichier sauvegarde.txt");
    }
}

void chargement(int *recompenses, int *nbr_morts, int *temps, int *niveau)
{
    FILE *fichier = NULL;
    fichier = fopen("sauvegarde.txt", "r");
    if (fichier != NULL)
    {
        fscanf(fichier, "recompenses: %d \n", recompenses);
        fscanf(fichier, "nbr_morts: %d \n", nbr_morts);
        fscanf(fichier, "temps: %d \n", temps);
        fscanf(fichier, "niveau: %d \n", niveau);
        fclose(fichier);
    }
    else
    {
        printf("Impossible d'ouvrir le fichier sauvegarde.txt");
    }
}