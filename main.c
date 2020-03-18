/*
 * Projet: Bataille navale
 * Auteur: Nolan Evard
 * Decription: Ce programme est un jeu, il vous permet de jouer
 * à la bataille navale contre un ordinateur en devant trouver
 * l'emplacement de bateaux dont la position est codée dans le
 * programme.
 * Version: 0.1 du 18.03.2020
 */
#include <stdio.h>
#include <stdlib.h>
void menu();
void aide ();
void jeu ();
void afficherPlanJeu (int tableau [10] [10]);
void regleJeu ();
void aideEnregistrement ();
void cleanerScanf ();

int main() {
    menu();
    return 0;
}

/**
 * @name menu
 * Cette fonction affiche le menu principal et prend en compte
 * le choix de l'utilisateur afin d'exécuter la fonction correspndant
 * à son choix:
 * @param
 */

void menu()
{
    // Déclaration et initialisation des variables
    int choixPrincipal = 0;

    //Affichage du menu principal
    printf("\n\n====================   BATAILLE NAVALE   ====================\n\n\n");
    printf("1. Jouer \n");
    printf("2. S'enregistrer \n");
    printf("3. Mes meilleurs scores \n");
    printf("4. Aide \n");
    printf("5. Quitter\n");

    /* Demande et enregistre le choix de l'utilisateur et
     * si celui-ci n'est pas compris entre 1 et 4 il affiche
     * un message d'erreur et redemande un nombre à l'utilisateur*/
    do{
        printf("\nVotre choix : ");
        scanf("%d", &choixPrincipal);
        cleanerScanf();
        if (choixPrincipal < 1) printf("\nVeuillez saisir un nombre plus grand");
        if (choixPrincipal > 5) printf("\nVeuillez saisir un nombre plus petit");
    }
    while (choixPrincipal < 1 || choixPrincipal > 5);

    //redirige l'utilisateur vers la bonne partie du code selon son choix
    switch (choixPrincipal)
    {
        //s'il rentre 1, le jeu démarre
        case 1:
            system("cls");
            jeu();
            system("cls");
            menu();
            break;
            //s'il rentre 2, le sywstème d'enregistrement s'affiche
        case 2:
            system("cls");
            printf("\nWork in progress...\n");
            system("pause");
            system("cls");
            menu();
            break;
            //s'il rentre 3, ses meilleurs scores s'affichent
        case 3:
            system("cls");
            printf("\nWork in progress...\n");
            system("pause");
            system("cls");
            menu();
            break;
            //s'il rentre 4, l'aide s'affiche
        case 4:
            system("cls");
            //affcihage de l'aide
            aide();
            system("cls");
            menu();
            break;
            //s'il rentre 5, le programme s'arrete
        case 5:
            break;
            //cas extrême, si le programme venait à accéder à cette partie du code qui noramlement n'est pas acessible, alors le programme affiche quand même un message d'erreur
        default:
            printf("Il y a eu une erreur, veuillez redémarrer le programme !");
            break;
    }
}
/**
 * @name aide
 * Cette fonction affiche la section aide et redirige l'utilisateur
 * vers la bonne rubrique en exécutant la fonction coprrespondante
 * @param
 */
void aide ()
{
    //déclarations et intialisation de la variable de choix
    int choixAide = 0;

    printf("\n\n=====================    Aide    ====================\n\n");
    //Affichage du menu principal
    printf("\n1. Regles du jeu");
    printf("\n2. Aide pour s'enregistrer\n");
    //enregistre et s'assure que le choix entré par l'utilisateur respecte les conventions
    do
    {
        printf("\nVotre choix : ");
        scanf("%d", &choixAide);
        if (choixAide < 1) printf("\nVeuillez saisir un nombre plus grand");
        if (choixAide > 2) printf("\nVeuillez saisir un nombre plus petit");
    }
    while (choixAide < 1 || choixAide > 2);
    //redirige l'utilisateur vers le bon aide en fonction de son choix
    switch (choixAide)
    {
        //s'il rentre un, les règles du jeu s'affichent
        case 1:
            system("cls");
            regleJeu();
            break;
            //s'il rentre 2, l'aide pour s'enregistrer s'affiche
        case 2:
            system("cls");
            aideEnregistrement();
            break;
            //si une erreur se produit, le message d'erreur suivant s'affiche
        default:
            printf("Il y a eu une erreur, veuillez redémarrer le programme !");
            break;
    }
    //marque une pause pour la console
    system("\n\nPause");
}
/**
 * @name jeu
 * Cette fonction permet de pouvoir jouer à la bataille navale
 * @param
 */
void jeu ()
{
    //déclarations et initialisation de variables / tableaux
    int Planjeu [10] [10] = {0};
    char colonne = 0;
    int ligne = 0, counter = 0, colonneInt = 0, croiseurCoule = 0, porteAvionCoule = 0, sousMarin1Coule = 0, sousMarin2Coule = 0, torpilleurCoule = 0;
    //Posittionement des différents bateaux
    //position croiseur
    Planjeu [2][4] = 1;
    Planjeu [3][4] = 1;
    Planjeu [4][4] = 1;
    Planjeu [5][4] = 1;
    //position porte-avion
    Planjeu [0][8] = 1;
    Planjeu [1][8] = 1;
    Planjeu [2][8] = 1;
    Planjeu [3][8] = 1;
    Planjeu [4][8] = 1;
    //position sous-marin 1
    Planjeu [9][3] = 1;
    Planjeu [9][4] = 1;
    Planjeu [9][5] = 1;
    //position sous-marin 2
    Planjeu [3][1] = 1;
    Planjeu [4][1] = 1;
    Planjeu [5][1] = 1;
    //position torpilleur
    Planjeu [0][0] = 1;
    Planjeu [1][0] = 1;

    //début du jeu
    //En-tête
    printf("\n\n====================   Jouer a la bataille navale   ====================\n\n");
    //affichage du plan de jeu
    afficherPlanJeu(Planjeu);
    do{
        do
        {
            //demande et enregistre les coordonnées entrées par l'utilisateur en boucle tant que le choix ne repecte pas les conventions
            do
            {
                printf("\nVeuillez entrer la coordonnee de colonne (en majuscule): ");
                scanf("%c", &colonne);
                //vidage du scanf
                cleanerScanf();
                //message d'erreur en cas de non respect des conventions
                if (colonne < 65 || colonne  > (65 + 10)) printf("\nVeuillez entrer une lettre entre A et J svp\n");
            }
                //controle la validité de la valeur entrée
            while (colonne < 65 || colonne  > (65 + 10));


            //demande et enregistre les coordonnées entrées par l'utilisateur en boucle tant que le choix ne repecte pas les conventions
            do
            {
                printf("\nVeuillez entrer la coordonnee de ligne : ");
                scanf("%d", &ligne);
                //vidage du scanf
                cleanerScanf();
                //message d'erreur en cas de non respect des conventions
                if (ligne < 1 || ligne > 10) printf("\nLa coordonnee entree n'existe pas");
            }
                //controle la validité de la valeur entrée
            while (ligne < 1 || ligne > 10);

            /* Convertit la lettre entrée pour la colonne visée en un chiffre cohérent pour le tableau
            * en se servant du code ascii des lettres A à J */
            colonneInt = colonne - 65;

            //converti le numéro entré en un numéro correspondant aux cases d'un tableau en C (commençant à 0)
            ligne = ligne - 1;

            //message d'erreur si la case enrée a déja été attaquée
            if (Planjeu [ligne] [colonneInt] == 3 || Planjeu [ligne] [colonneInt] == 4 || Planjeu [ligne] [colonneInt] == 2) printf (" \nVous avez deja attaque cette case !\n");
        }
            //redemande des coordonnées si la case entrée a déja été attaquée
        while (Planjeu [ligne] [colonneInt] == 3 || Planjeu [ligne] [colonneInt] == 4 || Planjeu [ligne] [colonneInt] == 2);


        //controle si la coodrdonnées entrée correspond à un bateau et définit la case sur "touché si c'est le cas"
        if (Planjeu [ligne] [colonneInt]) Planjeu [ligne][colonneInt] = 3;

            //si la coordonnées ne correspond à aucun bateau alors la case est définie sur "a l'eau"
        else if (Planjeu [ligne] [colonneInt] == 0) Planjeu [ligne] [colonneInt] = 2;

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
        if(Planjeu [0][8] == 3 && Planjeu [1][8] == 3 && Planjeu [2][8] == 3 && Planjeu [3][8] == 3 && Planjeu [4][8] == 3)
        {
            //cases du porte-avion
            Planjeu [0][8] = 4;
            Planjeu [1][8] = 4;
            Planjeu [2][8] = 4;
            Planjeu [3][8] = 4;
            Planjeu [4][8] = 4;
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
        if (Planjeu [3][1] == 3 && Planjeu [4][1] == 3 && Planjeu [5][1] == 3)
        {
            //cases du sous-marin 2
            Planjeu [3][1] = 4;
            Planjeu [4][1] = 4;
            Planjeu [5][1] = 4;
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
        //réaffiche le plan de jeu en fonction des changements d'etats des cases causés par la coordonée entrée
        afficherPlanJeu(Planjeu);
    }
        //vérifie la conditon pour la victoire, si tout les bateaux sont coullés alors c'est victoire, sinon on redemande une coordonnées jusqu'à que ce soit le cas
    while (!(croiseurCoule == 1 && porteAvionCoule == 1 && sousMarin1Coule == 1 && sousMarin2Coule == 1 && torpilleurCoule == 1));
    printf(" _   _ _      _        _            _ _ _ \n"
           "| | | (_)    | |      (_)          | | | |\n"
           "| | | |_  ___| |_ ___  _ _ __ ___  | | | |\n"
           "| | | | |/ __| __/ _ \\| | '__/ _ \\ | | | |\n"
           "\\ \\_/ / | (__| || (_) | | | |  __/ |_|_|_|\n"
           " \\___/|_|\\___|\\__\\___/|_|_|  \\___| (_|_|_)\n"
           "                                          \n"
           "                                          \n\n\n");

    system("pause");

}
/**
 * @name afficherPlanJeu
 * Cette fonction affiche le plan de jeu en fonction de l'etat dans lequels se trouve les cases du tableau "planJeu"
 * @param tableau
 */
void afficherPlanJeu (int tableau [10] [10])
{
    //nettoie la console
    system("cls");

    printf("\n");
    //Affiche les entêtes de colones
    printf("      A       B      C      D      E      F      G      H     I\n");

    //affiche la bordure du haut
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

    //Affiche tout la partie intermédiaire du plan de jeu
    for (int e = 0; e <=8 ; e++)
    {
        printf ("%3d", e + 1);
        for (int c = 0; c <= 8; c++)
        {
            printf("%c", 186);

            //imprime différent caractère selon l'etat de la case, cette partie du code est essentielle pour l'affichage de la battaile
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

        //Affichage de la dernière ligne et de la bordure du bas
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

    //légende "touché", "coulé", "à l'eau"
    printf("%c%c%c%c%c%c : A l'eau   ", 177, 177, 177, 177, 177, 177);
    printf("%c%c%c%c%c%c : Touche   ", 178, 178, 178, 178, 178, 178);
    printf("%c%c%c%c%c%c : Coule   \n\n\n", 219, 219, 219, 219, 219, 219);

}
/**
 * @name regleJeu
 * Cette fonction affiche les règles du jeu
 * @param
 */
void regleJeu ()
{
    //entête
    printf("\n=====================    Regles du jeu    =====================\n\n");

    //règles du jeu
    printf("La bataille navale est un jeu qui oppose deux joueur, chacuns possedant 5 bateaux :\n"
           "- Un porte avion : 5 cases\n"
           "- Un croiseur : 4 cases\n"
           "- Deux sous-marins : 3 cases\n"
           "- Un torpilleur : 2 cases ");
    printf("Dans le cas de cette bataille navale, il n'y a pas deux joueurs, vous affrontez l'ordinateur.\n"
           "Des cartes predefinies sont enregistree dans le programme  et votre but est de trouver l'emplacement\n"
           "des bateaux en un minimum de coups. Vous allez devoir entrer une coordonee verticale et horizontale \n"
           "afin de renseigner le programme sur quelle case vous souhaitez frapper. Vous gagnez donc une fois \n"
           "tout les bateaux coules\n\n\n");
}
/**
 * @name aideEnregistrement
 * Cette fonction affiche l'aide pour s'enregistrer
 * @param
 */
void aideEnregistrement ()
{
    //entête
    printf("\n\n===================    Comment s'enregister ?    ====================\n\n");
    //Aide pour l'enregistrement
    printf("Pour vous enregistrer il vous suffit de vous rendre en premier dans la section du menu principal \"s'enregistrer\", \n"
           "puis de saisir votre nom d'utilisateur et si tout s'est deroule correctement un message de confirmation devrait \n"
           "s'afficher et vous devriez etre enregistre. A present vous pouvez retourner au menu principal et vous rendre dans\n"
           "la section jouer. Vous devriez pouvoir vous connecter sans probleme.\n"
           "Si vraiment ce n'est pas le cas, redemarrez le programme et recommencer la procedure d'enregistrement.\n\n\n");
}
/**
 * @name cleanerScanf
 * Cette fonction nettoie ce qui reste dans un scanf après utilisation
 * et permet ainsi d'éviter des bugs notamment lorsque l'on commence à
 * manipulaer des caractères ou chaines de caractères.
 * @param
 * Source: ---> Eliott Jacquier
 */
void cleanerScanf ()
{
    //variable uniquement temporaire, aucune autre utilité
    int voider;
    //stocke ce qui se trouve dans le scanf et remplace son contenu par "rien"
    while((voider=getchar()) != EOF && voider != '\n');
}