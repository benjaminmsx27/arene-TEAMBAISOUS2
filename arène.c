#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define size 40

int map[size][size];


void affichage(){
    int i, j;
    //Met plein de retour a la ligne pour ne pas voir la map d'avant
    for (i = 0; i < 30; i++)printf("\n");

    //Barre du haut du tableau (limite du tableau)
    printf("                    ");
    for (i = 0; i < (size*2) +3; i++)printf("X"); //barre latéral du coté droit
    printf("\n");

    //tableau
    for (i=0;i < size;i++){
        printf("                    X "); //barre latéral du coté gauche (centré tableau)
        for (j=0;j<size;j++){
            if(map[i][j] == 0){ // if map i j = variable
                printf(". ");

            }else if (map[i][j] > 1000){
                printf("# ");
            }
        }
        printf("X\n");
    }

    //Barre du bas du tableau
    printf("                    ");
    for (i = 0; i < size * 2 + 3; i++)printf("X");
    printf("\n");
}

void initialisation_map (){  //toute la map est initialisé a 0
    int i, j;
    for (i=0;i<size;i++){
        for(j=0;j<size;j++){
            map[i][j] = 0;
        }
    }
}

void limit_du_tableau (){   //ne fonctionne pas
    int i, j;
    for (i=0 ; i<size ; i++){
        for (j=0 ; j<size ; j++){
            if (i = 0 || i == size-1 || j == 0 || j == size-1);
        }
    }
}

int deplacement (int depx, int depy , int ID){
    if (ID > 1000){ // vérif ID du joueur supérieur à 1000
        if (depx <= 3 && depy <= 5){   //limite de déplacement du joueur

            //Cherche le joueur
            int i, j, x, y,isFind;
            for (i=0;i<size;i++){           // parcours de tableau pour chercher la case ou est l'ID du joueur
                for(j=0;j<size;j++){
                    if (map [i][j] == ID){  // si la case contient ID
                        x = i;              // on stock les coordonnées en x et y
                        y = j;
                        isFind = 1;         // arret de la boucle
                        break;
                    }
                }
                if(isFind == 1){            // arret de la boucle
                    break;
                }
            }

            if((x+depx < size) && (x+depx >= 0) && (y+depy < size) && (y+depy >= 0)){ // On verifie si les coordonnée sont dans le tableau
                //On le reinitialise
                map[x][y] = 0;
                //On le bouge de son deplacement
                x += depx;
                y += depy;
                //On le met dans la nouvelle case
                map[x][y] = 1;
            }
        }
    }
    //if (depx + x > size-1 || depy + y > size-1){
            //l'IA ne peux pas bouger ici : il doit modifier son déplacement
        //depx = depx - 2;         // valeur donnée au hasard  // ca ne fonctionne pas
    //}


}

int NombreDeJoueurs (){
    int NombreIA;

    printf("saisir le nombre de joueurs : ");
    scanf("%d", &NombreIA);
    condition_initiales_ia(NombreIA);
}

int condition_initiales_ia (int NombreIA){
    int ID_ia,i;

    for(i=1 ; i<=NombreIA ; i++){  //numéro des ia
        ID_ia = 1000 + i;
        //appel des fonctions des IA
        int reussi = 1;
        while(reussi == 1){ //si tant que = 1 ==> appel de la fonction
            reussi = placement_IA (NombreIA,ID_ia); // si la fonction rate (case déjà occupé) while = 1 donc la fonction recommence
        }
    }
}

int placement_IA (int NombreIA , int ID_ia){
    int i, j;
    int x = rand()%size;  //case aléatoire sur la map
    int y = rand()%size;  //case aléatoire sur la map

    for (i = 0 ; i < 3 ; i++){
        for (j=0 ; j < 3 ; j++){
            if (map[x+i][y+j] >= 1000 || x+1 >= size || y+1 >= size){  //test si la case est déja occupé et //si la position de la case correspond au limites du tableau
                return 1;
            }
        }
    }
    map[x][y] = ID_ia;
    map[x+1][y] = ID_ia;
    map[x][y+1] = ID_ia;
    map[x+1][y+1] = ID_ia;
    return 0;
}

int main()
{

    printf("E-CROC \n \n");

    //Initialisation
    initialisation_map ();
    NombreDeJoueurs();
    //appel des ia en mettant leur ID

    //Jeux
    time_t tpsDepart = time(NULL); //prend le tps actuel du debut de partie
    int isplayed = 1 ;
    int pos = 2;
    while (isplayed){

        time_t current = time(NULL); //prend le tps actuel
        while (time(NULL) - current <= 0.5); // attend 1 seconde avant de continuer le programme (0.5 = 1 seconde)

        // deplacement des ia
        // condition initiale du remplissage


        /*map[5][pos] = 0; //on remet la case ou était l'ia à 0
        pos++;
        map[5][pos] = 1;
        */


        //Affichage
        affichage();

        //A NE OAS OUBLIER
        if((time(NULL)-tpsDepart >= 2)/* || (win)*/){ //arret de la partie au bout de 4 minutes ou une victoire CHANGER LE TPS UNE FOIS FINI
            isplayed = 0; //arret du jeu
        }
    }
    return 0;

}
