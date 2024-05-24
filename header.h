#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
//#######################################################################################
//Joueur
//#######################################################################################
typedef struct pion{
    char nom[50];
    int argent;
    int pos;
    int x;
    int y;
    int r;
    int g;
    int b;
}t_joueur;

t_joueur* creationJoueur(int nbJ, int x, int y){

    int r=(-1),g=(-1),b=(-1);
    t_joueur* joueur;
    joueur=(t_joueur*)malloc(nbJ*sizeof(t_joueur));
    if(joueur==NULL){
        printf("\nProbleme de l'allocation des joueurs");
    }

    //Attribution des positions des joueurs
    for(int i=0; i<nbJ; i++){
        joueur[i].x=x;
        joueur[i].y=y;
        joueur[i].pos=0;
        joueur[i].argent=1500;
        x=x+20;
    }

    //Rentrer pseudo
    for(int i=0; i<nbJ; i++){
        printf("\n| Veuillez rentrer un pseudo(sans espace) pour le joueur numero %d: ",i+1);
        scanf("%s",joueur[i].nom);
    }

    //Attribution couleurs des pion joueur
    /* Pour chaque joueur, on lui demande la coloration de son pion pour la partie rgb */
    printf("\n| Choisissez votre couleur de pion (coloration de (0-255) de rouge, vert, bleu):\n");
    for(int i=0; i<nbJ; i++){
        printf("\n\n\t%s a vous de choisir!",joueur[i].nom);
        while(r<0 || r>255){
            printf("\n\tChoix rouge: ");
            scanf("%d",&r);
        }joueur[i].r=r;
        while(g<0 || g>255){
            printf("\tChoix vert: ");
            scanf("%d",&g);
        }joueur[i].g=g;
        while(b<0 || b>255){
            printf("\tChoix bleu: ");
            scanf("%d",&b);
        }joueur[i].b=b;
        r=(-1);
        g=(-1);
        b=(-1);
    }
    return joueur;
}

/*
t_joueur* chargement(){//ajouter le chargement des cartes
    int argent=0,x=0,y=0,r=0,g=0,b=0;
    char nom;
    t_joueur* joueur;
    FILE * ifs = fopen("sauvegarde.txt","r");
    if (!ifs){
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }

    fscanf(ifs,"%d",&j);
    for(int i=0; i<nbJ; i++){
        fgets(nom,50,ifs);
        strcpy(joueur[i].nom,nom);
        fscanf(ifs,"%d%d%d%d%d%d",&argent,&x,&y,&r,&g,&b);
        joueur[i].argent=argent;
        joueur[i].x=x;
        joueur[i].y=y;
        joueur[i].r=r;
        joueur[i].g=g;
        joueur[i].b=b;
    }
    return joueur;
}
*/
//#######################################################################################
//Cartes proprietes
//#######################################################################################
typedef struct carte_PrixImmobilier{
    char nomPlage[50];
    int prix;
    int prop;
    int loyer;
    int m1;
    int m2;
    int m3;
    int m4;
    int h;
    int hypo;
    int num;
    int pos;
    int m_SurProp;
    int h_SurProp;
    int hypo_Prop;
    int prixMaison;
    int prixHotel;
}t_cartes;

t_cartes* cartesImmobilier()
{
    //initialisation des variables
    char nom[50]={0};//meilleure allocation de place
    int prix=0, prop=0,loyer=0,m1=0,m2=0,m3=0,m4=0,h=0,hypo=0,num=0,pos=0,m_SurProp=0,h_SurProp=0,hypo_Prop=0,prixM=0,prixH=0;
    FILE* recu=fopen("cartes.txt","r");
        if (!recu)
    {
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }
    t_cartes* cartes;
    cartes=(t_cartes*)malloc(22*sizeof(t_cartes));
    if(cartes==NULL){
        printf("\nProbleme de l'allocation des cartes");
        exit(-1);
    }

    //attribution variables cartes
    for (int i=0; i<22; i++){
        fscanf(recu,"%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d",&prix,&prop,&loyer,&m1,&m2,&m3,&m4,&h,&hypo,&num,&pos,&m_SurProp,&h_SurProp,&hypo_Prop,&prixM,&prixH);
        cartes[i].prix=prix;
        cartes[i].prop=prop;
        cartes[i].loyer=loyer;
        cartes[i].m1=m1;
        cartes[i].m2=m2;
        cartes[i].m3=m3;
        cartes[i].m4=m4;
        cartes[i].h=h;
        cartes[i].hypo=hypo;
        cartes[i].num=num;
        cartes[i].pos=pos;
        cartes[i].m_SurProp=m_SurProp;
        cartes[i].h_SurProp=h_SurProp;
        cartes[i].hypo_Prop=hypo_Prop;
        cartes[i].prixMaison=prixM;
        cartes[i].prixHotel=prixH;
    }
    for(int i=0; i<22; i++){
        fgets(nom,50,recu);
        strcpy(cartes[i].nomPlage,nom);
    }
    fclose(recu);
    return cartes;
}

int trouverPropriete(int position,t_cartes* cartes){
    for(int i=0; i<22; i++){
        if(cartes[i].pos==position) return i;
    }
}

int trouverPropriete2(int n,t_cartes* cartes){
    //nom propriete a rechercher
    int num=0,trouver=0;
    do{
        do{
            printf("\n| Quel propriete t'interesse(en numero)?\n (-1 pour retour au menu)\n Choix:  ");
            fflush(stdin);
            scanf("%d",&num);
        }while(num<(-1) || num>29);

        if(num==(-1)){
            trouver=1;
            return num;
        }
        for(int i=0; i<22; i++){
            if(cartes[i].prop==n && cartes[i].pos==num){
                trouver=1;
                return i;
            }
        }
    }while(trouver==0);
}

void affichageCarteImmobilier(int i,t_cartes* cartes){
    printf("\n\t\t\t\t\t ______________________________\n\t\t\t\t\t  %s\n\t\t\t\t\t  (%d)\n\t\t\t\t\t ------------------------------\n\n\t\t\t\t\t  Prix\t%d\n\t\t\t\t\t  Loyer\t%d\n\t\t\t\t\t  Avec 1 Maison\t%d\n\t\t\t\t\t  Avec 2 Maison\t%d\n\t\t\t\t\t  Avec 3 Maison\t%d\n\t\t\t\t\t  Avec 4 Maison\t%d\n\t\t\t\t\t  Avec Hotel\t%d\n\t\t\t\t\t ------------------------------\n\t\t\t\t\t  Prix maison: %d\n\t\t\t\t\t  Prix hotel: %d\n\t\t\t\t\t  Valeur hypotheque: %d\n\t\t\t\t\t ______________________________\n",cartes[i].nomPlage,cartes[i].pos,cartes[i].prix,cartes[i].loyer,cartes[i].m1,cartes[i].m2,cartes[i].m3,cartes[i].m4,cartes[i].h,cartes[i].prixMaison,cartes[i].prixHotel,cartes[i].hypo);

}

void affichageCarteMH(int i,t_cartes* cartes){
    printf("\n\t\t\t\t\t ______________________________\n\t\t\t\t\t  %s\n\t\t\t\t\t  Nombre de maison: %d\n\t\t\t\t\t  Nombre d'hotel: %d\n\t\t\t\t\t ______________________________\n",cartes[i].nomPlage,cartes[i].m_SurProp,cartes[i].h_SurProp);

}
//#######################################################################################
//Cartes chances et communautees
//#######################################################################################
typedef struct carte_Chance{//structure cartes chance
    char enonce[100];
    int argent;
    int cases;
    int pos;
    int pri;
}t_chance;

typedef struct carte_Commu{//structure carte commmunaute
    char enonce[80];
    int argent;
    int cases;
    int pos;
}t_commu;

t_chance* cartesChance()
{
    //initialisation des variables
    char enonce[100]={0};//meilleure allocation de place
    int argent=0, cases=0,pos=0,pri=0;
    FILE* recu=fopen("chance.txt","r");
    if (!recu)
    {
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }
    t_chance* chance;
    chance=(t_chance*)malloc(16*sizeof(t_chance));
    if(chance==NULL){
        printf("\nProbleme de l'allocation des cartes");
        exit(-1);
    }

    //attribution variables cartes
    for (int i=0; i<16; i++){
        fscanf(recu,"%d%d%d%d",&argent,&cases,&pos,&pri);
        chance[i].argent=argent;
        chance[i].cases=cases;
        chance[i].pos=pos;
        chance[i].pri=pri;
    }
    for (int i=0; i<16; i++){
        fgets(enonce,100,recu);
        strcpy(chance[i].enonce,enonce);
    }

    fclose(recu);
    return chance;
}

t_commu* cartesCommunautes()
{
    //initialisation des variables
    char enonce[80]={0};//meilleure allocation de place
    int argent=0, cases=0,pos=0;
    FILE* recu=fopen("commu.txt","r");
        if (!recu)
    {
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }
    t_commu* commu;
    commu=(t_commu*)malloc(16*sizeof(t_commu));
    if(commu==NULL){
        printf("\nProbleme de l'allocation des cartes");
        exit(-1);
    }

    //attribution variables cartes
    for (int i=0; i<16; i++){
        fscanf(recu,"%d%d%d",&argent,&cases,&pos);
        commu[i].argent=argent;
        commu[i].cases=cases;
        commu[i].pos=pos;
    }
    for (int i=0; i<16; i++){
        fgets(enonce,80,recu);
        strcpy(commu[i].enonce,enonce);
    }

    fclose(recu);
    return commu;
}

int tirerAuSort(){//permet le tirage random des cartes chances et communautes
    int min=0, max=15;
    srand(time(NULL));
    return min + rand() % (max+1 - min);
}

void affichageCarteChance(int i,t_chance* chance){
        printf("\n\t\t\t\t\t ##############################\n\t\t\t\t\t Carte chance\n\n\t\t\t\t\t  %s\n\t\t\t\t\t ##############################\n",chance[i].enonce);
}

void affichageCarteCommu(int i,t_commu* commu){
        printf("\n\t\t\t\t\t ##############################\n\t\t\t\t\t Carte communaute\n\n\t\t\t\t\t  %s\n\t\t\t\t\t ##############################\n",commu[i].enonce);
}

//#######################################################################################
//Avancement
//#######################################################################################
int des(){
    int min=1, max=6;
    srand(time(NULL));
    return min + rand() % (max+1 - min);
}

int avancer(int n, t_joueur* joueur){
    if(joueur[n].y>22 && joueur[n].y<138 && joueur[n].x>202 && joueur[n].x<320){
        joueur[n].y=joueur[n].y-(60-(n*20));
        joueur[n].x=joueur[n].x+(125-(n*20));
    }
    else if(joueur[n].y>22 && joueur[n].y<138 && joueur[n].x>320 && joueur[n].x<692)joueur[n].x=joueur[n].x+60;
    else if(joueur[n].x>692 && joueur[n].x<809 && joueur[n].y>22 && joueur[n].y<138){
        joueur[n].x=joueur[n].x+(60-(n*20));
        joueur[n].y=joueur[n].y+(125-(n*20));
    }
    else if(joueur[n].x>692 && joueur[n].x<809 && joueur[n].y>138 && joueur[n].y<569) joueur[n].y=joueur[n].y+60;
    else if(joueur[n].y>569 && joueur[n].y<688 && joueur[n].x>692 && joueur[n].x<809){
            joueur[n].y=joueur[n].y+(60-(n*20));
            joueur[n].x=joueur[n].x-(125-(n*20));
    }
    else if(joueur[n].y>569 && joueur[n].y<688 && joueur[n].x>320 && joueur[n].x<692) joueur[n].x=joueur[n].x-60;


    else if(joueur[n].x>202 && joueur[n].x<320 && joueur[n].y>569 && joueur[n].y<688){
        joueur[n].x=joueur[n].x-(60-(n*20));
        joueur[n].y=joueur[n].y-(125-(n*20));
    }
    else if(joueur[n].x>202 && joueur[n].x<318 && joueur[n].y>138 && joueur[n].y<569) joueur[n].y=joueur[n].y-60;
}

void ajoutPosition(t_joueur* joueur, int n, int valeurD){
    while(valeurD>0){
        if(joueur[n].pos==30){
            joueur[n].pos=1;
            printf("\n 1ere case veut dire le debut d'un nouveau depart: tu as recu 200$ \n");
            joueur[n].argent=joueur[n].argent+200;//a changer
        }
        else joueur[n].pos++;
        valeurD--;
    }
}

void lancement(int valeur, int n, t_joueur* joueur){
    for(int i=0; i<valeur; i++){
        avancer(n,joueur);
    }
}
//#######################################################################################
//Paiement
//#######################################################################################
int loyer(int indice, t_cartes* cartes){
    if(cartes[indice].h_SurProp==0){
        if(cartes[indice].m_SurProp==0)return cartes[indice].loyer;
        else if(cartes[indice].m_SurProp==1)return cartes[indice].m1;
        else if(cartes[indice].m_SurProp==2)return cartes[indice].m2;
        else if(cartes[indice].m_SurProp==3)return cartes[indice].m3;
        else if(cartes[indice].m_SurProp==4)return cartes[indice].m4;
    }
    else cartes[indice].h;
}

#endif // HEADER_H_INCLUDED
