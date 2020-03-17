#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <conio.h>
//#include "headers.h"
//#include "fonctions.c"
//#pragma execution_character_set( "utf-8" )
void menu();
void aide ();
void enregistrement ();
int find(char *fileName,char *strSearch);
void jeu ();
void afficherPlanJeu ( int tableau [10] [10]);

int main() {
    //SetConsoleOutputCP(65001);
    menu();
    return 0;
}
void menu()
{
    // Déclaration et initialisation des variables
    int choixPrincipal = 0;

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
            jeu();
            break;
        case 2:
            enregistrement();
            break;
        case 3:

            break;
        case 4:
            aide();
            getchar();
            break;
        default:
            printf("Il y a eu une erreur, veuillez redémarrer le programme !");
            break;
    }
}
void aide ()
{
    int choixAide = 0;
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
    getchar();
}
void enregistrement ()
{
    FILE* verifUtilisateur = NULL;
    FILE* rechercheUtilisateur = NULL;
    char nomUtilisateur [41] = "";
    unsigned int longueurNom = 0, utilisateurValide = 0;
    printf("\n\n========== S'enregistrer ============\n\n");
    do
    {
        printf("\nVeuillez entrer votre nom d'utilisateur : ");
        scanf("%s", nomUtilisateur);
        longueurNom = strlen(nomUtilisateur);
        if (longueurNom < 1) printf("\nVotre nom est trop court !");
        if (longueurNom > 40) printf ("\nVotre nom est trop long !");
    }
    while (longueurNom < 1 || longueurNom > 40);

    rechercheUtilisateur = fopen("utilisateurs.usr", "r");
    if (rechercheUtilisateur != NULL)
    {
        do{
            utilisateurValide = find("utilisateurs.usr", nomUtilisateur);
            if (utilisateurValide)
            {
                printf("\nCe nom est déja enregistré !\n");
                do
                {
                    printf("\nVeuillez entrer votre nom d'utilisateur : ");
                    scanf("%s", nomUtilisateur);
                    longueurNom = strlen(nomUtilisateur);
                    printf("%d", longueurNom);
                    if (longueurNom == 0) printf("\nVotre nom est trop court !");
                    if (longueurNom > 40) printf ("\nVotre nom est trop long !");
                }
                while (longueurNom == 0 || longueurNom > 40);
            }
            else
            {
                verifUtilisateur = fopen("utilisateurs.usr", "a");
                if (verifUtilisateur != NULL){
                    fprintf(verifUtilisateur, "%s\n", nomUtilisateur);
                    fclose(verifUtilisateur);
                    printf("\nVous avez été enregistré avec succès !!!");
                    system("Pause");
                }
                else{
                    printf("\nIl y a eu une erreur, veuillez redémarrer le programme !\n");
                }
            }
        }
        while (utilisateurValide);

    }
}
/**
 * Cette fonction recherche une chaine de caractère dans un fichier
 * ---> source : https://forums.futura-sciences.com/programmation-langages-algorithmique/141329-chercher-une-chaine-de-caractere-un-texte-langage-c.html
 * @param fileName
 * @param strSearch
 * @return found
 */
int find(char *fileName,char *strSearch)
{

    FILE *f;
    char c;
    int found=0;
    int pos=0;
    int length;

    f = fopen(fileName,"r");
    if( f == NULL )
        return 0;

    length=strlen(strSearch);

    while( fread(&c,1,1,f)>0 && !found ) {

        if( c==strSearch[pos] ) {
            pos++;
        } else {
            if(pos!=0) {
                fseek(f,-pos,SEEK_CUR);
                pos=0;
            }
        }

        found = (pos==length);

    }
    fclose(f);

    return found;

}
void jeu ()
{
    /*char nomUtilisateur [41] = "";
    int usercheck;
    FILE* verif = NULL;
    printf("\nVeuillez entrer votre nom d'utilisateur : ");
    scanf("%c", nomUtilisateur);
    verif = fopen("utilisateurs.usr", "r");
    if (verif != NULL)
    {
        usercheck = find("utilisateurs.usr", nomUtilisateur);
        if (usercheck)
        {

        }
    }
    else printf("Il y a eu un problème, veuillez redémarrer le programme");*/
    int Planjeu [10] [10] = {0};
    char colonne = 0;
    int ligne = 0, counter = 0, colonneInt = 0, croiseurCoule = 0, porteAvionCoule = 0, sousMarin1Coule = 0, sousMarin2Coule = 0, torpilleurCoule = 0;
    //position croiseur
    Planjeu [2][4] = 1;
    Planjeu [3][4] = 1;
    Planjeu [4][4] = 1;
    Planjeu [5][4] = 1;
    //position porte-avion
    Planjeu [0][9] = 1;
    Planjeu [1][9] = 1;
    Planjeu [2][9] = 1;
    Planjeu [3][9] = 1;
    Planjeu [4][9] = 1;
    //position sous-marin 1
    Planjeu [9][3] = 1;
    Planjeu [9][4] = 1;
    Planjeu [9][5] = 1;
    //position sous-marin 2
    Planjeu [3][5] = 1;
    Planjeu [4][5] = 1;
    Planjeu [5][5] = 1;
    //position torpilleur
    Planjeu [0][0] = 1;
    Planjeu [1][0] = 1;

    printf("\n\n====================   Jouer à la bataille navale   ====================\n\n");

    afficherPlanJeu(Planjeu);
    do{
        //demande et enregistre les coordonnées entrées par l'utilisateur
        do
        {
            printf("Veuillez entrer la coordonnee de colonne : ");
            scanf("%c", &colonne);
            //if (!(colonne >= 65 && colonne <= (65 + 10))) printf("\nLa coordonnée entree n'existe pas");
        }
            //controle la validité de la valeur entrée
        while (!(colonne >= 65 && colonne <= (65 + 10)));
        //demande et enregistre les coordonnées entrées par l'utilisateur
        do
        {
        printf("\nVeuillez entrer la coordonnee de ligne : ");
        scanf("%d", &ligne);
        if (ligne < 1 || ligne > 10) printf("\nLa coordonnee entree n'existe pas");
        }
        //controle la validité de la valeur entrée
        while (ligne < 1 || ligne > 10);
        /* Convertit la lettre entrée pour la colonne visée en un chiffre cohérent pour le tableau
         * en se servant du code ascii des lettres A à J */
        colonneInt = colonne - 65;
        //controle si la coodrdonnées entrée correspond à un bateau et définit la case sur "touché si c'est le cas"
        if (Planjeu [colonneInt][ligne]) Planjeu [colonneInt][ligne] = 3;
            //si la coordonnées ne correspond à aucun bateau alors la case est définie sur "a l'eau"
        else if (Planjeu [colonneInt][ligne] == 0) Planjeu [colonneInt][ligne] = 2;
        //si toutes les cases du croiseur sont touchées alors on passe l'etat des cases à 4, ce qui correspond à "coulé"
        if (Planjeu [2][4] == 3 && Planjeu [3][4] == 3 && Planjeu [4][4] == 3 && Planjeu [5][4] == 3)
        {
            //cases du croiseur
            Planjeu [2][4] = 4;
            Planjeu [3][4] = 4;
            Planjeu [4][4] = 4;
            Planjeu [5][4] = 4;
            croiseurCoule = 1;
        }
        //si toutes les cases du porte-avion sont touchées alors on passe l'etat des cases à 4, ce qui correspond à "coulé"
        if(Planjeu [0][9] == 3 && Planjeu [1][9] == 3 && Planjeu [2][9] == 3 && Planjeu [3][9] == 3 && Planjeu [4][9] == 3)
        {
            //cases du porte-avion
            Planjeu [0][9] = 4;
            Planjeu [1][9] = 4;
            Planjeu [2][9] = 4;
            Planjeu [3][9] = 4;
            Planjeu [4][9] = 4;
            porteAvionCoule = 1;
        }
        //si toutes les cases du sous-marin 1 sont touchées alors on passe l'etat des cases à 4, ce qui correspond à "coulé"
        if (Planjeu [9][3] == 3 && Planjeu [9][4] == 3 && Planjeu [9][5] == 3)
        {
            //cases du sous-marin 1
            Planjeu [9][3] = 4;
            Planjeu [9][4] = 4;
            Planjeu [9][5] = 4;
            sousMarin1Coule = 1;
        }
        //si toutes les cases du sous-marin 2 sont touchées alors on passe l'etat des cases à 4, ce qui correspond à "coulé"
        if (Planjeu [3][5] == 3 && Planjeu [4][5] == 3 && Planjeu [5][5] == 3)
        {
            //cases du sous-marin 2
            Planjeu [3][5] = 4;
            Planjeu [4][5] = 4;
            Planjeu [5][5] = 4;
            sousMarin2Coule = 1;
        }
        //si toutes les cases du torpilleur sont touchées alors on passe l'etat des cases à 4, ce qui correspond à "coulé"
        if (Planjeu [0][0] == 3 && Planjeu [1][0] == 3)
        {
            //cases du torpilleur
            Planjeu [0][0] = 4;
            Planjeu [1][0] = 4;
            torpilleurCoule = 1;
        }
        printf("      A       B      C      D      E      F      G      H     I\n");
//bordure du haut
        printf("   ");
        printf("%c", 201);
        for (int f = 0; f <= 7; f++)
        {
            for (int a = 0; a <=5; a++) printf ("%c", 205);
            printf("%c", 203);
        }
        for (int a = 0; a <=5; a++) printf ("%c", 205);
        printf("%c", 187);
        printf ("\n");
        for (int e = 0; e <=8 ; e++)
        {
            printf ("%3d", e + 1);
            for (int c = 0; c <= 8; c++)
            {

                printf("%c", 186);
                switch (Planjeu [e] [c])
                {
                    case 0:
                        printf("      ");
                        break;
                    case 1:
                        printf("      ");
                        break;
                    case 2:
                        printf("%c%c%c%c%c%c", 177, 177, 177, 177, 177, 177);
                        break;
                    case 3:
                        printf("%c%c%c%c%c%c", 178, 178, 178, 178, 178, 178);
                        break;
                    case 4:
                        printf("%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219);
                        break;
                }
            }
            printf("%c", 186);
            printf("\n");
            printf("   ");
            printf("%c", 204);
            for (int d = 0; d <= 7; d++)
            {
                printf("%c%c%c%c%c%c", 205, 205, 205, 205, 205, 205);
                printf("%c", 206);
            }
            printf("%c%c%c%c%c%c", 205, 205, 205, 205, 205, 205);
            printf("%c", 185);
            printf("\n");
        }
        printf ("%3d", 10);
        for (int c = 0; c <= 8; c++)
        {
            printf("%c", 186);
            switch (Planjeu [9] [c])
            {
                case 0:
                    printf("      ");
                    break;
                case 1:
                    printf("      ");
                    break;
                case 2:
                    printf("%c%c%c%c%c%c", 177, 177, 177, 177, 177, 177);
                    break;
                case 3:
                    printf("%c%c%c%c%c%c", 178, 178, 178, 178, 178, 178);
                    break;
                case 4:
                    printf("%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219);
                    break;
            }
        }
        printf("%c", 186);
        printf("\n");
        printf("   ");
//bordure bas
        printf("%c", 200);
        for (int f = 0; f <= 7; f++)
        {
            for (int a = 0; a <=5; a++) printf ("%c", 205);
            printf("%c", 202);
        }
        for (int a = 0; a <=5; a++) printf ("%c", 205);
        printf("%c", 188);
        printf("\n\n");
        printf("%c%c%c%c%c%c : A l'eau\n\n", 177, 177, 177, 177, 177, 177);
        printf("%c%c%c%c%c%c : Touche\n\n", 178, 178, 178, 178, 178, 178);
        printf("%c%c%c%c%c%c : Coule\n\n\n", 219, 219, 219, 219, 219, 219);

        system("Pause");
    }
    while (!(croiseurCoule == 1 && porteAvionCoule == 1 && sousMarin1Coule == 1 && sousMarin2Coule == 1 && torpilleurCoule == 1));
    printf("\nVICTOIRE !!!");
}
void afficherPlanJeu (int tableau [10] [10])
{
    printf("      A       B      C      D      E      F      G      H     I\n");
//bordure du haut
    printf("   ");
    printf("%c", 201);
    for (int f = 0; f <= 7; f++)
    {
        for (int a = 0; a <=5; a++) printf ("%c", 205);
        printf("%c", 203);
    }
    for (int a = 0; a <=5; a++) printf ("%c", 205);
    printf("%c", 187);
    printf ("\n");
    for (int e = 0; e <=8 ; e++)
    {
        printf ("%3d", e + 1);
        for (int c = 0; c <= 8; c++)
        {

            printf("%c", 186);
            switch (tableau [e] [c])
            {
                case 0:
                    printf("      ");
                    break;
                case 1:
                    printf("      ");
                    break;
                case 2:
                    printf("%c%c%c%c%c%c", 177, 177, 177, 177, 177, 177);
                    break;
                case 3:
                    printf("%c%c%c%c%c%c", 178, 178, 178, 178, 178, 178);
                    break;
                case 4:
                    printf("%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219);
                    break;
            }
        }
        printf("%c", 186);
        printf("\n");
        printf("   ");
        printf("%c", 204);
        for (int d = 0; d <= 7; d++)
        {
            printf("%c%c%c%c%c%c", 205, 205, 205, 205, 205, 205);
            printf("%c", 206);
        }
        printf("%c%c%c%c%c%c", 205, 205, 205, 205, 205, 205);
        printf("%c", 185);
        printf("\n");
    }
    printf ("%3d", 10);
    for (int c = 0; c <= 8; c++)
    {
        printf("%c", 186);
        switch (tableau [9] [c])
        {
            case 0:
                printf("      ");
                break;
            case 1:
                printf("      ");
                break;
            case 2:
                printf("%c%c%c%c%c%c", 177, 177, 177, 177, 177, 177);
                break;
            case 3:
                printf("%c%c%c%c%c%c", 178, 178, 178, 178, 178, 178);
                break;
            case 4:
                printf("%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219);
                break;
        }
    }
    printf("%c", 186);
    printf("\n");
    printf("   ");
//bordure bas
    printf("%c", 200);
    for (int f = 0; f <= 7; f++)
    {
        for (int a = 0; a <=5; a++) printf ("%c", 205);
        printf("%c", 202);
    }
    for (int a = 0; a <=5; a++) printf ("%c", 205);
    printf("%c", 188);
    printf("\n\n");
    printf("%c%c%c%c%c%c : A l'eau\n\n", 177, 177, 177, 177, 177, 177);
    printf("%c%c%c%c%c%c : Touche\n\n", 178, 178, 178, 178, 178, 178);
    printf("%c%c%c%c%c%c : Coule\n\n\n", 219, 219, 219, 219, 219, 219);

}