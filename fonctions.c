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