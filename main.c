#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "fonction.c"
#pragma execution_character_set( "utf-8" )

int main() {
    // Déclaration et initialisation des variables
    int choixPrincipal = 0, choixAide = 0;
    SetConsoleOutputCP(65001);
    //Affichage du menu principal
    printf("\n\n========== BATAILLE NAVALE ==========\n\n");
    printf("1. Jouer \n");
    printf("2. S'enregistrer \n");
    printf("3. Mes meilleurs scores \n");
    printf("4. Aide \n");

    /* Demande et enregistre le choix de l'utilisateur et
     * si celui-ci n'est pas compris entre 1 et 4 il affiche
     * un message d'erreur et redemande un nombre à l'utilisateur*/
    do{
        printf("\nVotre choix : ");
        scanf("%d", &choixPrincipal);
        if (choixPrincipal < 1) printf("\nVeuillez saisir un nombre plus grand");
        if (choixPrincipal > 4) printf("\nVeuillez saisir un nombre plus petit");
    }
    while (choixPrincipal < 1 || choixPrincipal > 4);


    switch (choixPrincipal)
    {
        case 1:
            break;
        case 2:

            break;
        case 3:
            break;
        case 4:
            printf("\n1. Règles du jeu");
            printf("\n2. Aide pour s'enregistrer\n");
            do
            {
                printf("\nVotre choix : ");
                scanf("%d", &choixAide);
                if (choixAide < 1) printf("\nVeuillez saisir un nombre plus grand");
                if (choixAide > 2) printf("\nVeuillez saisir un nombre plus petit");
            }
            while (choixAide < 1 || choixAide > 2);

            switch (choixAide)
            {
                case 1:
                    printf("\n\n========= Règles du jeu ==========\n\n");
                    printf("Work in progress...\n");
                    break;
                case 2:
                    printf("\n\n========= Aide pour s'enregistrer ==========\n\n");
                    printf("Work in progress...\n");
                    break;
                default:
                    printf("Il y a eu une erreur, veuillez redémarrer le programme !");
                    break;
            }
            break;
        default:
            printf("Il y a eu une erreur, veuillez redémarrer le programme !");
            break;
    }

    return 0;
}