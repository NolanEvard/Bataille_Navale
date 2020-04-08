/*
 * Projet: Bataille navale
 * Auteur: Nolan Evard
 * Decription: Ce programme est un jeu, il vous permet de jouer
 * à la bataille navale contre un ordinateur en devant trouver
 * l'emplacement de bateaux dont la position est codée dans le
 * programme.
 * Version: 1.0 du 08.04.2020
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>

void menu(char *username);
void aide (char *username);
void jeu (char *username);
void afficherPlanJeu (int tableau [10] [10]);
void regleJeu (char *username);
void aideEnregistrement (char *username);
void cleanerScanf ();
void login (char *username);
int saveScore (char *username, int score);
void printScores ();
void logQuit (char *username);
void logDejaAttaque (char *username, int col, int line);
void logTouche (char *username, int col, int line);
void logALeau (char *username, int col, int line);
void logCoule (char *username, int col, int line);
void logVictoire (char *username);

//Variable et tableau globaux utilisé pour le système de log et date & heure
FILE* writelog = NULL;
char buffer[256] = {""};

int main() {
    //tableaux enregistrant le nom d'utilisateur
    char user [21] = {""};
    //Demande un login à l'utilisateur au lancement du programme
    login(user);

    //une fois authentifié l'utilisateur est redirigé vers le menu principal
    menu(user);
    return 0;
}

/**
 * @name menu
 * Cette fonction affiche le menu principal et prend en compte
 * le choix de l'utilisateur afin d'exécuter la fonction correspndant
 * à son choix:
 * @param username
 */

void menu(char *username)
{
    // Déclaration et initialisation des variables
    int choixPrincipal = 0;
    time_t timestamp = time(NULL);

    //Ecrit un log lorsqu'un utilisateur se rend dans le menu principal

    //Ecrit la date dans le tableau "buffer" --> source : https://c.developpez.com/faq/?page=Gestion-des-dates-et-heures
    strftime(buffer, sizeof(buffer), "%A %d %B %Y - %X.", localtime(&timestamp));

    //ouverture du fichier de logs
    writelog = fopen("../gamefiles/Logs/logsBatailleNavale", "a");
    //écriture du log dans le fichier de logs
    fprintf(writelog, "[ %s ] : L'utilisateur %s s'est rendu dans le menu\n", buffer, username);
    //fermeture du fichier de logs
    fclose(writelog);

    //Affichage du menu principal
    printf("\n\n====================   BATAILLE NAVALE   ====================\n\n\n");
    printf("1. Jouer \n");
    printf("2. Changer d'utilisateur \n");
    printf("3. Scores \n");
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
            jeu(username);
            system("cls");
            menu(username);
            break;
            //s'il rentre 2, le sywstème d'enregistrement s'affiche
        case 2:
            login(username);
            system("cls");
            menu(username);
            break;
            //s'il rentre 3, les scores s'affichent
        case 3:
            printScores();
            system("pause");
            system("cls");
            menu(username);
            break;
            //s'il rentre 4, l'aide s'affiche
        case 4:
            system("cls");
            //affcihage de l'aide
            aide(username);
            system("cls");
            menu(username);
            break;
            //s'il rentre 5, le programme s'arrete
        case 5:
            logQuit(username);
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
 * @param username
 */
void aide (char *username)
{
    //déclarations et intialisation de la variable de choix
    int choixAide = 0;

    time_t timestamp = time(NULL);
    strftime(buffer, sizeof(buffer), "%A %d %B %Y - %X.", localtime(&timestamp));
    writelog = fopen("../gamefiles/Logs/logsBatailleNavale", "a");
    fprintf(writelog, "[ %s ] : L'utilisateur %s s'est rendu dans la section aide\n", buffer, username);
    fclose(writelog);

    printf("\n\n=====================    Aide    ====================\n\n");
    //Affichage du menu principal
    printf("\n1. Regles du jeu");
    printf("\n2. Aide pour s'authentifier\n");
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
            regleJeu(username);
            break;
            //s'il rentre 2, l'aide pour s'enregistrer s'affiche
        case 2:
            system("cls");
            aideEnregistrement(username);
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
 * @param username
 */
void jeu (char *username)
{
    //déclarations et initialisation de variables / tableaux
    int Planjeu [10] [10] = {0};
    int GrilleJeu [10] [10] = {0};
    char colonne = 0;
    int ligne = 0, counter = 0, colonneInt = 0, croiseurCoule = 0, porteAvionCoule = 0, sousMarin1Coule = 0, sousMarin2Coule = 0, torpilleurCoule = 0, random = 0, score = 0, valide = 0, invalid = 0;
    int torpilleur = 0, sousMarin1 = 0, sousMarin2 = 0, croiseur = 0, porteAvion = 0;
    //pointeur sur fichier
    FILE* RecupPlanJeu = NULL;

    //génération d'un nombre aléatoire entre 0 et 4 pour le choix aléatoire d'un plan de jeu
    srand(time(NULL));
    random = (rand() % (4 - 0 + 1)) + 0;

    //ouverture du fichier de plans de jeu
    RecupPlanJeu = fopen("../gamefiles/Maps/PlansJeu.txt", "r");

    //déplacement du curseur virtuel au bon plan de jeu selon le nombre aléatoire généré précédemment
    fseek(RecupPlanJeu, (random * 100), SEEK_SET);

    //si l'ouverture a réussi alors le programme exécute les instructions suivantes
    if (RecupPlanJeu != NULL)
    {
        for (int y = 0; y < 10; y++)
        {
            for (int z = 0; z < 10; z++)
            {
                //Récupération du nombre dans le fichier sous la forme d'un caractère ascii
                GrilleJeu [y] [z] = fgetc(RecupPlanJeu);
                //conversion du nombre en un entier
                GrilleJeu [y] [z] = GrilleJeu [y] [z] - 48;
            }
        }
    }
    //Message d'erreur au cas où l'ouverture du fichier échoue
    else printf("\nIl y a eu une erreur, relancez le progremme !\n");

    //fermeture du fichier
    fclose(RecupPlanJeu);

    //déclaration d'un constante de temps
    time_t timestamp = time(NULL);

    //log du début de jeu
    strftime(buffer, sizeof(buffer), "%A %d %B %Y - %X.", localtime(&timestamp));
    writelog = fopen("../gamefiles/Logs/logsBatailleNavale", "a");
    fprintf(writelog, "[ %s ] : L'utilisateur %s a lancé une partie\n", buffer, username);
    fclose(writelog);

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
                invalid = 0;
                printf("\nVeuillez entrer la coordonnee de colonne (en majuscule): ");
                scanf("%s", &colonne);
                //vidage du scanf
                cleanerScanf();
                //message d'erreur en cas de non respect des conventions
                if (colonne < 65 || colonne  > (65 + 10)) printf("\nVeuillez entrer une lettre entre A et J svp\n");

                //contrôle la longueur de la chaine entrée
                if (strlen(&colonne) > 1)
                {
                    printf ("\nUne seule lettre s'il vous plait\n");
                    invalid = 1;
                }
            }
                //controle la validité de la valeur entrée
            while (colonne < 65 || colonne  > (65 + 10) || invalid >=1);


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
            if (Planjeu [ligne] [colonneInt] == 3 || Planjeu [ligne] [colonneInt] == 4 || Planjeu [ligne] [colonneInt] == 2)
            {
                printf (" \nVous avez deja attaque cette case !\n");
                logDejaAttaque(username, colonne, ligne);
            }
        }
            //redemande des coordonnées si la case entrée a déja été attaquée
        while (Planjeu [ligne] [colonneInt] == 3 || Planjeu [ligne] [colonneInt] == 4 || Planjeu [ligne] [colonneInt] == 2);

        score++;

        //controle si la coordonnées entrée correspond à un bateau et définit la case sur "touché si c'est le cas"
        if (GrilleJeu [ligne] [colonneInt] == 1 || GrilleJeu [ligne] [colonneInt] == 2 || GrilleJeu [ligne] [colonneInt] == 3 || GrilleJeu [ligne] [colonneInt] == 4 || GrilleJeu [ligne] [colonneInt] == 5)
        {
            switch (GrilleJeu [ligne] [colonneInt])
            {
                case 1:
                    Planjeu [ligne] [colonneInt] = 3;
                    GrilleJeu [ligne] [colonneInt] = 6;
                    torpilleur++;
                    break;
                case 2:
                    Planjeu [ligne] [colonneInt] = 3;
                    GrilleJeu [ligne] [colonneInt] = 7;
                    sousMarin1 ++;
                    break;
                case 3:
                    Planjeu [ligne] [colonneInt] = 3;
                    GrilleJeu [ligne] [colonneInt] = 8;
                    sousMarin2 ++;
                    break;
                case 4:
                    Planjeu [ligne] [colonneInt] = 3;
                    GrilleJeu [ligne] [colonneInt] = 9;
                    croiseur ++;
                    break;
                case 5:
                    Planjeu [ligne] [colonneInt] = 3;
                    GrilleJeu [ligne] [colonneInt] = 10;
                    porteAvion ++;
                    break;
            }
            logTouche(username, colonne, ligne);
        }

            //si la coordonnées ne correspond à aucun bateau alors la case est définie sur "a l'eau"
        else if (GrilleJeu [ligne] [colonneInt] == 0)
        {
            Planjeu [ligne] [colonneInt] = 2;
            logALeau(username,colonne, ligne);
        }
        //si les variables incrémentales des différents bateaux atteignent leur maximum alors le bateau est définit sur coulé
         if (torpilleur >= 2 || sousMarin1 >= 3 || sousMarin2 >= 3 || croiseur >= 4 || porteAvion >= 5)
         {
             for (int i = 0; i < 10; i++)
             {
                 for (int j = 0; j < 10; j++)
                 {
                     switch (GrilleJeu [j] [i])
                     {
                         case 6:
                             Planjeu [j] [i] = 4;
                             torpilleur = 0;
                             torpilleurCoule = 1;
                             break;
                         case 7:
                             Planjeu [j] [i] = 4;
                             sousMarin1 = 0;
                             sousMarin1Coule = 1;
                             break;
                         case 8:
                             Planjeu [j] [i] = 4;
                             sousMarin2 = 0;
                             sousMarin2Coule = 1;
                             break;
                         case 9:
                             Planjeu [j] [i] = 4;
                             croiseur = 0;
                             croiseurCoule = 1;
                             break;
                         case 10:
                             Planjeu [j] [i] = 4;
                             porteAvion = 0;
                             porteAvionCoule = 1;
                             break;
                     }
                 }
             }

             logCoule(username, colonne, ligne);
         }

        //réaffiche le plan de jeu en fonction des changements d'etats des cases causés par la coordonée entrée
        afficherPlanJeu(Planjeu);
    }
        //vérifie la conditon pour la victoire, si tout les bateaux sont coullés alors c'est victoire, sinon on redemande une coordonnées jusqu'à que ce soit le cas
    while (!(croiseurCoule == 1 && porteAvionCoule == 1 && sousMarin1Coule == 1 && sousMarin2Coule == 1 && torpilleurCoule == 1));
    logVictoire(username);

    valide = saveScore(username, score);

    printf(" _   _ _      _        _            _ _ _ \n"
           "| | | (_)    | |      (_)          | | | |\n"
           "| | | |_  ___| |_ ___  _ _ __ ___  | | | |\n"
           "| | | | |/ __| __/ _ \\| | '__/ _ \\ | | | |\n"
           "\\ \\_/ / | (__| || (_) | | | |  __/ |_|_|_|\n"
           " \\___/|_|\\___|\\__\\___/|_|_|  \\___| (_|_|_)\n"
           "                                          \n"
           "                                          \n\n\n");
    printf("\n\nVous avez coule tous les bateaux enemis en %d coups !\n\n", score);

    system("pause");

    //contrôle que l'écriture du score à réussi avant de les imprimer
    if (valide) printScores();
    //si l'écriture du fichier n'as pas réussi le progranmme affiche un message d'erreur
    else printf("il y a eu une erreur avec l'enregistrement de votre score, pour consulter les socres précédents \nrendez vous dans la section \"scores\" du menu principal");

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
    printf("      A       B      C      D      E      F      G      H     I      J\n");

    //affiche la bordure du haut
    printf("   ");
    printf("%c", 201);
    for (int f = 0; f <= 8; f++)
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
        for (int c = 0; c <= 9; c++)
        {
            printf("%c", 186);

            //imprime différent caractère selon l'etat de la case, cette partie du code est essentielle pour l'affichage de la battaile
            switch (tableau [e] [c])
            {
                case 0:
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
        for (int d = 0; d <= 8; d++)
        {
            printf("%c%c%c%c%c%c", 205, 205, 205, 205, 205, 205);
            printf("%c", 206);
        }
        printf("%c%c%c%c%c%c", 205, 205, 205, 205, 205, 205);
        printf("%c", 185);
        printf("\n");
    }
    printf ("%3d", 10);
    for (int c = 0; c <= 9; c++)
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
    for (int f = 0; f <= 8; f++)
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
 * @param username
 */
void regleJeu (char *username)
{
    time_t timestamp = time(NULL);
    strftime(buffer, sizeof(buffer), "%A %d %B %Y - %X.", localtime(&timestamp));
    writelog = fopen("../gamefiles/Logs/logsBatailleNavale", "a");
    fprintf(writelog, "[ %s ] : L'utilisateur %s a lu les règles du jeu\n", buffer, username);
    fclose(writelog);

    //entête
    printf("\n=====================    Regles du jeu    =====================\n\n");

    //règles du jeu
    printf("La bataille navale est un jeu qui oppose deux joueurs, chacuns possedant 5 bateaux :\n"
           "- Un porte avion : 5 cases\n"
           "- Un croiseur : 4 cases\n"
           "- Deux sous-marins : 3 cases\n"
           "- Un torpilleur : 2 cases \n");
    printf("Dans le cas de cette bataille navale, il n'y a pas deux joueurs, vous affrontez l'ordinateur.\n"
           "Des cartes predefinies sont enregistree dans le programme  et votre but est de trouver l'emplacement\n"
           "des bateaux en un minimum de coups. Vous allez devoir entrer une coordonee verticale et horizontale \n"
           "afin de renseigner le programme sur quelle case vous souhaitez frapper. Vous gagnez donc une fois \n"
           "tout les bateaux coules\n\n\n");
}
/**
 * @name aideEnregistrement
 * Cette fonction affiche l'aide pour s'enregistrer
 * @param username
 */
void aideEnregistrement (char *username)
{
    time_t timestamp = time(NULL);
    strftime(buffer, sizeof(buffer), "%A %d %B %Y - %X.", localtime(&timestamp));
    writelog = fopen("../gamefiles/Logs/logsBatailleNavale", "a");
    fprintf(writelog, "[ %s ] : L'utilisateur %s a eu besoin d'aide pour s'authentifier\n", buffer, username);
    fclose(writelog);
    //entête
    printf("\n\n===================    Comment s'authentifier ?    ====================\n\n");
    //Aide pour l'enregistrement
    printf("Ce programme contient un systeme de nom d'utilisateur, normalement, si tout s'est passe correctement \n"
           "le programme vous a demande un nom d'utilisateur au demarrage du programme. Cependant si vous souhaitez\n"
           "changer d'utilisateur, c'est possible. Il vous suffit de vous rendre dans la section \"changer d'utilisateur\"\n"
           "du menu principal. Vous n'aurez alors qu'a saisir un nouveau nom d'utilisateur et le tour est joue.\n\n\n");
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
/**
 * @name login
 * Cette fonction demande un nom d'utilisateur et l'enregistre
 * @param username
 */
void login (char *username)
{
    //initialisation du tableau "username"
    for (int i = 0; i < 21; i++) username[i] = 0;
    //nettoie la console
    system("cls");
    //entête
    printf("\n=====================    LOGIN    ===================\n\n");
    printf("\n\nVeuillez entrer votre nom d'utilisateur (longueur max : 20 caracteres, espaces compris)\n\n");
    do
    {
        printf("\n\n\n\nVotre nom : ");
        //enregistre le nom d'utilisateur dans le tableau "username"
        gets(username);
        //message d'erreur si le nom ne respecte pas les conventions
        if (strlen(username) > 20) printf("\nVeuillez entrez un nom plus petit");

    }
    //contrôle que le nom repsecte les conventions, et le redemande si ce n'est pas le cas
    while (strlen(username) <= 0 || strlen (username) >20);
    //nettoie le scanf pour éviter les problèmes au prochain scanf
    cleanerScanf();

    //Ecriture du log d'enregistrement
    time_t timestamp = time(NULL);
    strftime(buffer, sizeof(buffer), "%A %d %B %Y - %X.", localtime(&timestamp));
    writelog = fopen("../gamefiles/Logs/logsBatailleNavale", "a");
    fprintf(writelog, "[ %s ] : Un nouvel utilisateur s'est enregistré sous le nom de : %s\n", buffer, username);
    fclose(writelog);
    system("cls");
    printf("\n===================    ENREGISTRE AVEC SUCCES    ===================\n\n\n");
    printf("\n\nVous etes bien connecte avec le nom : %s\n\n\n\n\n", username);

    //marque une pause
    system("pause");

    //nettoie la console
    system("cls");
}
/**
 * @name saveScore
 * Cette fonction souvegarde un score dans un fichier de score
 * @param username
 * @param score
 * @return success
 */
int saveScore (char *username, int score)
{
    //Déclaration des variables et pointeurs

    //pointeur sur fichier
    FILE* save = NULL;
    time_t timestamp = time(NULL);
    int success = 0;

    //ouverture du fichier de scores
    save = fopen ("../gamefiles/Scores/scoresBatailleNavale", "a");

    //si l'ouverture à réussi alors le programme exécute les instructions suivantes
    if (save != NULL)
    {
        //formatage de la date et de l'heure dans le buffer (voir source plus haut)
        strftime(buffer, sizeof(buffer), "%A %d %B %Y - %X.", localtime(&timestamp));
        //Ecriture du score dans le fichier
        fprintf(save, "%s | %s | %d coups\n\n", buffer, username, score);
        //variable de retour de la fonction qui confirme que le score a été écrit ou non
        success = 1;
    }
    //fermeture du fichier
    fclose(save);
    return success;
}
/**
 * @name printScores
 * Cette fonction Imprime le contenu du fichier de scores
 */
void printScores ()
{
    //Déclaration des variables et pointeurs

    //pointeur sur fichier
    FILE* printScores = NULL;
    int carac = 0, counter = 0;

    //ouverture du fichier de scores
    printScores = fopen("../gamefiles/Scores/scoresBatailleNavale", "r");

    //si l'ouverture à réussi alors le programme exécute les instructions suivantes
     if (printScores != NULL)
     {
         //nettoyage de la console
         system("cls");

         //entête
         printf("\n===================    SCORES    ===================\n\n");

         //Titres de colonnes du tableau de scores
         printf("\n\t\tDate\t\t     utilisateur  score\n");
         printf("-----------------------------------------------------------\n");

         //positionne le curseur virtuel au début du fichier
         fseek(printScores,0, SEEK_SET);

         //Imprime le contenu du fichier de scores
         do{
             carac = fgetc(printScores);
             printf("%c", carac);
             counter = 1;
         }
         //imprime tant que l'on a pas atteint la fin du fichier
         while (carac != EOF);
        printf("\n\n\n\n\n");
     }
    //si il n'y a pas encore de scores alors le message ci-dessous s'affiche
    if (counter == 0) printf("\n\nIl n'y a pas encore de scores, jouez une partie !\n\n\n\n");
     //fermeture du fichier
     fclose(printScores);
}
/**
 * @name logQuit
 * Cette fonction écrit un log lorsqu'un uitilisateur quitte le programme
 * @param username
 */
void logQuit (char *username)
{
    //Déclaration d'un constante de temps
    time_t timestamp = time(NULL);

    //Formattage de la date et de l'heure dans le buffer
    strftime(buffer, sizeof(buffer), "%A %d %B %Y - %X.", localtime(&timestamp));
    //ouverture du fichier de logs
    writelog = fopen("../gamefiles/Logs/logsBatailleNavale", "a");
    //écriture du log
    fprintf(writelog, "[ %s ] : L'utilisateur %s a quitté le programme\n", buffer, username);
    //fermeture du fichier
    fclose(writelog);
}
/**
 * @name logDejaAttaque
 * Cette fonction écrit un log lorsqu'un utilisateur touche une case déja attaquée
 * @param username
 * @param col
 * @param line
 */
void logDejaAttaque (char *username, int col, int line)
{
    //Déclaration d'un constante de temps
    time_t timestamp = time(NULL);

    //Formattage de la date et de l'heure dans le buffer
    strftime(buffer, sizeof(buffer), "%A %d %B %Y - %X.", localtime(&timestamp));
    //ouverture du fichier de logs
    writelog = fopen("../gamefiles/Logs/logsBatailleNavale", "a");
    //écriture du log
    fprintf(writelog, "[ %s ] : L'utilisateur %s a attaqué la case %c:%d --> case déja attaquée ! !\n", buffer, username, col, line + 1);
    //fermeture du fichier
    fclose(writelog);
}
/**
 * @name logTouche
 * Cette fonction écrit un log lorsqu'un utilisateur touche un bateau
 * @param username
 * @param col
 * @param line
 */
void logTouche (char *username, int col, int line)
{
    //Déclaration d'un constante de temps
    time_t timestamp = time(NULL);

    //Formattage de la date et de l'heure dans le buffer
    strftime(buffer, sizeof(buffer), "%A %d %B %Y - %X.", localtime(&timestamp));
    //ouverture du fichier de logs
    writelog = fopen("../gamefiles/Logs/logsBatailleNavale", "a");
    //écriture du log
    fprintf(writelog, "[ %s ] : L'utilisateur %s a attaque la case %c:%d --> touché !\n", buffer, username, col, line + 1);
    //fermeture du fichier
    fclose(writelog);
}
/**
 * @name logALeau
 * Cette fonction écrit un log lorsqu'aucun bateau n'est touché
 * @param username
 * @param col
 * @param line
 */
void logALeau (char *username, int col, int line)
{
    //Déclaration d'un constante de temps
    time_t timestamp = time(NULL);

    //Formattage de la date et de l'heure dans le buffer
    strftime(buffer, sizeof(buffer), "%A %d %B %Y - %X.", localtime(&timestamp));
    //ouverture du fichier de logs
    writelog = fopen("../gamefiles/Logs/logsBatailleNavale", "a");
    //écriture du log
    fprintf(writelog, "[ %s ] : L'utilisateur %s a attaque la case %c:%d --> à l'eau !\n", buffer, username, col, line + 1);
    //fermeture du fichier
    fclose(writelog);
}
/**
 * @name logCoule
 * Cette fonction écrit un log lorsqu'un utilisateur coule un bateau
 * @param username
 * @param col
 * @param line
 */
void logCoule (char *username, int col, int line)
{
    //Déclaration d'un constante de temps
    time_t timestamp = time(NULL);

    //Formattage de la date et de l'heure dans le buffer
    strftime(buffer, sizeof(buffer), "%A %d %B %Y - %X.", localtime(&timestamp));
    //ouverture du fichier de logs
    writelog = fopen("../gamefiles/Logs/logsBatailleNavale", "a");
    //écriture du log
    fprintf(writelog, "[ %s ] : L'utilisateur %s a attaque la case %c:%d --> un bateau est coulé !\n", buffer, username, col, line + 1);
    //fermeture du fichier
    fclose(writelog);
}
/**
 * @name logVictoire
 * Cette fonction écrit le log de la victoire en y comprenant
 * le nom de l'utilisateur et la date & l'heure de la victoire
 * @param username
 */
void logVictoire (char *username)
{
    //Déclaration d'un constante de temps
    time_t timestamp = time(NULL);

    //Formattage de la date et de l'heure dans le buffer
    strftime(buffer, sizeof(buffer), "%A %d %B %Y - %X.", localtime(&timestamp));
    //ouverture du fichier de logs
    writelog = fopen("../gamefiles/Logs/logsBatailleNavale", "a");
    //écriture du log
    fprintf(writelog, "[ %s ] : L'utilisateur %s a gagné la partie !\n", buffer, username);
    //fermeture du fichier
    fclose(writelog);
}
