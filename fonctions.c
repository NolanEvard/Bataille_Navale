void menu()
{
    // Déclaration et initialisation des variables
    int choixPrincipal = 0;
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
   int ligne = ' ';
   int colonne = 0, counter = 0;
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

    printf("\n\n========== Jouer à la bataille navale ==========\n\n");

    for (int i = 0; i <10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            switch (Planjeu [i] [j])
            {
                case 0:
                    printf("\033[0;31m");
                    counter++;
                    break;
                case 1:
                    printf("\033[0;31m");
                    counter++;
                    break;
                case 2:
                    break;
                case 3:
                    break;
                case 4:
                    break;
                default:
                    break;
            }
            printf("\u2588");
            if (counter % 10 == 0) printf("\n");
        }
    }

    do
    {
        printf("Veuillez entrer la coordonnées de colonne : ");
        scanf("%d", &colonne);
        if (colonne < 1 || colonne > 10) printf("La coordonnée entrée n'existe pas");
    }
    while (colonne < 1 || colonne > 10);

    do
    {
        printf("Veuillez entrer la coordonnées de ligne : ");
        scanf("%d", &ligne);
        if ((ligne - 65) < 0 || (ligne - 65) > 9) printf("La coordonnée entrée n'existe pas");
    }
    while ((ligne - 65) < 0 || (ligne - 65) > 9);

}