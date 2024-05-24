#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include "header.h"
#define SCREEN_W 1024
#define SCREEN_H 700

void init_ALLEG(){
    allegro_init();
    set_color_depth(desktop_color_depth());
    install_keyboard();
    install_mouse();
    install_sound(DIGI_AUTODETECT,MIDI_AUTODETECT,NULL);

    if((set_gfx_mode(GFX_AUTODETECT_WINDOWED,SCREEN_W,SCREEN_H,0,0))!=0){
        allegro_message("Probleme de mode graphique !");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
}

//Sous-programme menu
t_joueur* menuPrincipal()
{
    int choix =0, nbJ=0;
    t_joueur* joueur;
    do
    {
        printf("\n__________ Menu principal ________________________________:\n\t1.Lancer une nouvelle partie\n\t2.Charger une partie\n\t3.Sauvegarder partie en cours\n\t4.Afficher regles\n\t5.Quitter\n");
        fflush(stdin);
        scanf("%d",&choix);
    }
    while ((choix<1) || (choix>4));
    if(choix==1){
        //creation du joueur

    }
    else if(choix==2){
        //sous programme chargement
    }
    else if(choix==3){
        //sous programme sauvegarde
        menuPrincipal();
    }
    else if(choix==4){
        //sous programme regles
        menuPrincipal();
    }
    else exit(-1);
}


int petitMenu(int n,t_joueur* joueur,t_cartes* cartes,t_chance* chance, t_commu* commu){
    int choix=0, acheter=0, valeurD=0, valeurT=0, indice=0, indiceB=0, somme=0, a=0, b=0;
    do
    {
        printf("\n\n ___________________________________________\n|\n| C'est ton tour %s, que veux tu faire:\n\tARGENT: %d $\n\n\t1.Vos proprietes\n\t2.Localisation maisons et hotels\n\t3.Lancer de De\n\t4.Acheter un(e) maison/hotel\n\t5.Ne rien faire\n\t6.Retour au menu principal\n\tChoix: ",joueur[n].nom,joueur[n].argent);
        fflush(stdin);
        scanf("%d", &choix);
    }while((choix<1)||(choix>6));
    if(choix==1){//voir les proprietes
        for(int i=0; i<22; i++){
            if(cartes[i].prop==n)affichageCarteImmobilier(i,cartes);
        }
        petitMenu(n,joueur,cartes,chance,commu);
    }
    else if(choix==2){//localisation des maisons et hotels
        for(int i=0; i<22; i++){
            if(cartes[i].prop==n)affichageCarteMH(i,cartes);
        }
        petitMenu(n,joueur,cartes,chance,commu);
    }
    else if(choix==3){//lancement de De
        valeurD=des();
        ajoutPosition(joueur,n,valeurD);//reajuste le numero de la position
        printf("\n On roule le des! ... On a %d   (position joueur a la case %d)\n",valeurD, joueur[n].pos);
        lancement(valeurD,n,joueur);

        //VERIF SI C'EST UNE PROPRIETE(blindage)----------------------------
        if((joueur[n].pos>=1&&joueur[n].pos<=5)||(joueur[n].pos>=8&&joueur[n].pos<=11)||(joueur[n].pos>=13&&joueur[n].pos<=14)||(joueur[n].pos>=16&&joueur[n].pos<=18)||(joueur[n].pos>=20&&joueur[n].pos<=21)||(joueur[n].pos>=23&&joueur[n].pos<=26)||(joueur[n].pos>=28&&joueur[n].pos<=29)){
            indice=trouverPropriete(joueur[n].pos,cartes);
            //-------------------------------------------------
            if(cartes[indice].prop!=(-1)){//si la carte appartient a quelqu'un
                if(cartes[indice].prop!=n){//que ce n'est pas au joueur
                    somme=loyer(indice,cartes);
                    printf("\n\t Tu as atteri sur %s\n\t %s a cette plage! Tu dois payer! -%d $\n",cartes[indice].nomPlage,joueur[(cartes[indice].prop)].nom,somme);//verif si propriete appartient a quelqu'un
                    joueur[n].argent=joueur[n].argent-somme;
                    joueur[(cartes[indice].prop)].argent=joueur[(cartes[indice].prop)].argent+somme;
                    printf("\n\t=== New balance: %d $ ===\n",joueur[n].argent);
                }
                else{//on le propose d'acheter des maisons ou un hotel
                    //trouver la propriete
                    indiceB=trouverPropriete2(n,cartes);
                    //conditions
                    if(indiceB!=(-1)){
                        //menu choix
                        do{
                            printf("\n| Que veux tu acheter ? (soit 4 maisons ou 1 hotel)\n\t 1.Une maison\n\t 2.Un hotel\n\t 3.Retour\n\tChoix:");
                            fflush(stdin);
                            scanf("%d",&b);
                        }while(b<1 || b>3);
                        if(b==1 && (joueur[n].argent-cartes[indiceB].prixMaison)>=0 && cartes[indiceB].m_SurProp<4){
                            joueur[n].argent=joueur[n].argent-cartes[indiceB].prixMaison;
                            printf("\n\t=== New balance: %d $ ===\n",joueur[n].argent);
                            cartes[indiceB].m_SurProp++;
                            printf("\n\t Une maison a ete achete! Tu as %d maison(s) sur cette propriete\n",cartes[indiceB].m_SurProp);
                        }
                        else if(b==2 && (joueur[n].argent-cartes[indiceB].prixHotel)>=0 && cartes[indiceB].h_SurProp==0){
                            joueur[n].argent=joueur[n].argent-cartes[indiceB].prixHotel;
                            printf("\n\t=== New balance: %d $ ===\n",joueur[n].argent);
                            cartes[indiceB].h_SurProp++;
                            printf("\n\t Un hotel a ete achete! Tu as %d hotel sur cette propriete\n",cartes[indiceB].h_SurProp);
                        }
                        else if(b==3);
                        else printf("\n\tTu as soit atteint le maximum pour ce type(maison ou hotel) de batiment ou...tu n'es pas aussi riche que tu le pense!\n");
                    }
                }
            }
            else{
                affichageCarteImmobilier(indice,cartes);//affiche la propriete
                do{
                    printf("\n| %s est libre, tu voudrais pas...l'acheter peut-etre?\n\t1. Acheter\n\t2. Ne pas acheter\n\n\t=>  ",cartes[indice].nomPlage);
                    fflush(stdin);
                    scanf("%d",&acheter);
                }while(acheter<1 && acheter>2);
                if(acheter==1 && (joueur[n].argent-cartes[indice].prix)>=0){
                    cartes[indice].prop=n;
                    joueur[n].argent=joueur[n].argent-cartes[indice].prix;//si le man a assez d'argent
                    printf("\n\t=== New balance: %d $ ===\n",joueur[n].argent);
                }
                else if(acheter==1 && (joueur[n].argent-cartes[indice].prix)<0) printf("\n\tHmmm...on dirait pas que tu assez d'argent!\n");
                else printf("\n\tTant pis!\n");
            }
            //-------------------------------------------------
        }//VERIF SI CASE CHANCE --------------------------------
        else if(joueur[n].pos==6 || joueur[n].pos==27){//cases carte chance
            valeurT=tirerAuSort();//tirage au sort d'un carte chance
            affichageCarteChance(valeurT,chance);
            //-------------------------------------------------
            if(chance[valeurT].argent!=0){//si consequence argent
                joueur[n].argent=joueur[n].argent+chance[valeurT].argent;
                printf("\n\t=== New balance: %d $ ===\n",joueur[n].argent);
            }
            else if(chance[valeurT].cases!=0){//si consequence cases
                //si changement de cage alors on l'ajoute a sa position actuelle comme avec le lancement de de
                if(chance[valeurT].pri==1){//ajout case sortir de prison
                    if(joueur[n].pos==7){//seuelment si joueur en prison
                        ajoutPosition(joueur,n,chance[valeurT].cases);
                        printf("\n Joueur maintenant a la case %d\n",joueur[n].pos);
                        lancement(chance[valeurT].cases,n,joueur);
                    }
                }
                else{
                    ajoutPosition(joueur,n,chance[valeurT].cases);
                    printf("\n Joueur maintenant a la case %d\n",joueur[n].pos);
                    lancement(chance[valeurT].cases,n,joueur);
                }
            }
            else if(chance[valeurT].pos!=0){//si consequence position
            }
            //-------------------------------------------------
        }//VERIF SI CASE COMMUNAUTE --------------------------
        else if(joueur[n].pos==12 || joueur[n].pos==19){//cases carte communautes
            valeurT=tirerAuSort();
            affichageCarteCommu(valeurT,commu);
            //-------------------------------------------------
            if(commu[valeurT].argent!=0){
                joueur[n].argent=joueur[n].argent+commu[valeurT].argent;
                printf("\n\t=== New balance: %d $ ===\n",joueur[n].argent);
            }
            else if(commu[valeurT].cases!=0){//si changement de cage alors on l'ajoute a sa position actuelle comme avec le lancement de de
                ajoutPosition(joueur,n,commu[valeurT].cases);
                printf("\n Joueur maintenant a la case %d\n",joueur[n].pos);
                lancement(commu[valeurT].cases,n,joueur);
            }
            else if(commu[valeurT].pos!=0){//changement de position
            }
            //-------------------------------------------------
        }
    }
    else if(choix==4){//acheter des maisons/hotels
            //trouver la propriete
            indiceB=trouverPropriete2(n,cartes);
            //conditions
            if(indiceB==(-1)){
                petitMenu(n,joueur,cartes,chance,commu);
            }
            else{
                //menu choix
                do{
                    printf("\n| Que veux tu acheter ? (soit 4 maisons ou 1 hotel)\n\t 1.Une maison\n\t 2.Un hotel\n\t 3.Retour\n\tChoix:");
                    fflush(stdin);
                    scanf("%d",&b);
                }while(b<1 || b>3);
                if(b==1 && (joueur[n].argent-cartes[indiceB].prixMaison)>=0 && cartes[indiceB].m_SurProp<4){
                    joueur[n].argent=joueur[n].argent-cartes[indiceB].prixMaison;
                    printf("\n\t=== New balance: %d $ ===\n",joueur[n].argent);
                    cartes[indiceB].m_SurProp++;
                    printf("\n\t Une maison a ete achete! Tu as %d maison(s) sur cette propriete\n",cartes[indiceB].m_SurProp);
                }
                else if(b==2 && (joueur[n].argent-cartes[indiceB].prixHotel)>=0 && cartes[indiceB].h_SurProp==0){
                    joueur[n].argent=joueur[n].argent-cartes[indiceB].prixHotel;
                    printf("\n\t=== New balance: %d $ ===\n",joueur[n].argent);
                    cartes[indiceB].h_SurProp++;
                    printf("\n\t Un hotel a ete achete! Tu as %d hotel sur cette propriete\n",cartes[indiceB].h_SurProp);
                }
                else if(b==3)petitMenu(n,joueur,cartes,chance,commu);
                else printf("\n\tTu as soit atteint le maximum pour ce type(maison ou hotel) de batiment ou...tu n'es pas aussi riche que tu le pense!\n");
            }
    }
    else if(choix==6){//retour au menu principal
        menuPrincipal();//on repasse au menu prinncipal
    }
}

/*
void verifPosition(int n, t_joueur* joueur){
    if()//condition chance
    else if()//condition communaute
    else if()//condition aller en prison
    else if()//taxes
    else if()//en prison ?
    else if()//case depart
    else{

    }
}
*/

int main()
{
    //DEBUT INITIALISATION ------------------------------------------------
    //Initialisation des variables
    int nbJ=0,x=230,y=110,n=0, indice=0,choix=0;
    int valeurD=0;
    //cartes Immobiliere
    t_cartes* cartes=cartesImmobilier();
    t_chance* chance=cartesChance();
    t_commu* commu=cartesCommunautes();

    printf("------------------ Bienvenue a Monopoly Beach edition! ------------------\n\n");
    printf(" ________________________________________________________________________________\n| Petite aide de jeu:                                                            |\n| Pour etre sur du bon fonctionnement de la partie il faut                       |\n| toujours allez regarder le plateau pour avancer dans les commandes.            |\n| Il se peut aussi qu'il faut tout simplement faire entrer.                      |\n|________________________________________________________________________________|\n\n\n");
        //Choix nombres de joueurs
        while(nbJ<2 || nbJ>4){
            printf("\n| Combien de joueurs dans la partie?\n\tChoix: ");
            scanf("%d",&nbJ);
        }printf("\n Parfait, allez c'est parti!\n");
        t_joueur* joueur=creationJoueur(nbJ,x,y);
    //---------------------------------------------------------------------

    BITMAP* buffy;
    BITMAP* fond;
    BITMAP* board;

    init_ALLEG();

    buffy=create_bitmap(SCREEN_W,SCREEN_H);
    fond=load_bitmap("fond.bmp",NULL);
    board=load_bitmap("monopBoard.bmp",NULL);

    install_keyboard();
    install_mouse();
    show_mouse(screen);

    while(!key[KEY_ESC]){
        blit(fond,buffy,0,0,0,0,SCREEN_W,SCREEN_H);
        masked_blit(board,buffy,0,0,0,0,SCREEN_W,SCREEN_H);
        for(int i=0; i<nbJ; i++){
           circlefill(buffy,joueur[i].x,joueur[i].y,10,makecol(joueur[i].r,joueur[i].g,joueur[i].b));
           circle(buffy,joueur[i].x,joueur[i].y,10,makecol(0,0,0));
        }
        blit(buffy,screen,0,0,0,0,SCREEN_W,SCREEN_H);

        valeurD=petitMenu(n,joueur,cartes,chance,commu);
        //tour
        if(n<nbJ-1){
            n++;
        }
        else{n=0;}
    }
    allegro_exit();
    destroy_bitmap(buffy);

    return 0;
}END_OF_MAIN();
