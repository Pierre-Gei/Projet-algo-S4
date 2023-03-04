#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>

void sauvegarde(int recompenses, int nbr_morts, int temps, int niveau, int tab_morts[], int tab_temps[], int taille_tab_morts, int choix_skin, int skin_achete)
{
    FILE *fichier = NULL;
    fichier = fopen("sauvegarde.txt", "w");
    if (fichier != NULL)
    {
        fprintf(fichier, "recompenses: %d \n", recompenses);
        for (int i = 0; i < taille_tab_morts; i++)
        {
            fprintf(fichier, "%d ", tab_morts[i]);
            fprintf(fichier, "%d ", tab_temps[i]);
        }
        fprintf(fichier, "nbr_morts: %d \n", nbr_morts);
        fprintf(fichier, "temps: %d \n", temps);
        fprintf(fichier, "niveau: %d \n", niveau);
        fprintf(fichier, "choix_skin: %d \n", choix_skin);
        fprintf(fichier, "skin_achete: %d \n", skin_achete);
        fclose(fichier);
    }
    else
    {
        printf("Impossible d'ouvrir le fichier sauvegarde.txt");
    }
}

void chargement(int *recompenses, int *nbr_morts, int *temps, int *niveau, int tab_morts[], int tab_temps[], int taille_tab_morts, int * choix_skin, int * skin_achete)
{
    FILE *fichier = NULL;
    *recompenses = 0;
    *nbr_morts = 0;
    *temps = 0;
    *niveau = 0;
    *choix_skin = 0;
    *skin_achete = 0;
    for (int i = 0; i < taille_tab_morts; i++)
    {
        tab_morts[i] = 0;
        tab_temps[i] = 0;
    }
    fichier = fopen("sauvegarde.txt", "r");
    if (fichier != NULL)
    {
        fscanf(fichier, "recompenses: %d \n", recompenses);
        for (int i = 0; i < taille_tab_morts; i++)
        {
            fscanf(fichier, "%d ", &tab_morts[i]);
            fscanf(fichier, "%d ", &tab_temps[i]);
        }
        fscanf(fichier, "nbr_morts: %d \n", nbr_morts);
        fscanf(fichier, "temps: %d \n", temps);
        fscanf(fichier, "niveau: %d \n", niveau);
        fscanf(fichier, "choix_skin: %d \n", choix_skin);
        fscanf(fichier, "skin_achete: %d \n", skin_achete);
        fclose(fichier);
    }
    else
    {
        printf("Impossible d'ouvrir le fichier sauvegarde.txt");
    }
}