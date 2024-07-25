#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "presence.h"

void rond_point(char* args[]) {
    FILE* f = init_fic(args[1], "a+");
    char ligne[MAX_LENGTH_CHAINE];
    char* section;
    char date[DATE_LENGTH];
    int i = 0,choix;
    Etudiant etudiants[NB_MAX_ETU];

    while(fgets(ligne, MAX_LENGTH_CHAINE, f) != NULL) {
        section = strtok(ligne, "/");
        if (section != NULL) {
            etudiants[i].numero = atoi(section);
        }
        section = strtok(NULL, "/");
        if (section != NULL) {
            strncpy(etudiants[i].nom, section, MAX_LENGTH_CHAINE - 1);
        }
        section = strtok(NULL, "/");
        if (section != NULL) {
            strncpy(etudiants[i].prenom, section, MAX_LENGTH_CHAINE - 1);
        }
        section = strtok(NULL, "/");
        if (section != NULL) {
            etudiants[i].utilisation = utilisation_machine(section);
        }
        section = strtok(NULL, "/");
        if (section != NULL) {
            strncpy(etudiants[i].date, section, DATE_LENGTH - 1);
        }
        i++;
        if (i >= NB_MAX_ETU) {
            break;
        }
    }

    fclose(f);

    choix = premier_pas(choix);
    if(choix == 1){
         printf("__________________________________________________\n");
        printf("|\t\t Checker les pc : \t\t  |\n");
        printf("|_________________________________________________|\n");
        printf("|\t[1]: 1 à 1................................|\n");
        printf("|\t[2]: 1 à la fin succéssivement............|\n");
        printf("|_________________________________________________|\n");
        printf("Tapez (1 ou 2) : ");
        scanf("%d", &choix);
    }
    else{
        printf("\tEntrer la date: (format YYYY-MM-DD)\v");
        scanf("%10s", date);

        printf("\n");
        printf(" ________________________________________________________________________\n");
        printf("|\t\t\tQue voulez vous savoir?  \t\t\t |\n");
        printf("|________________________________________________________________________|\n");
        printf("|\t[1]: pour voir la liste de ceux qui utlisent l'ordi\t\t |\n");
        printf("|\t[2]: pour voir la liste de ceux qui n'utlisent pas l'ordi\t |\n");
        printf("|\t[3]: pour voir la liste de ceux qui utlisent ordi perso\t\t |\n");
        printf("|\t[4]: pour voir la liste de ceux qui sont absents\t\t |\n");
        printf("|________________________________________________________________________|\n");

        printf("\t\tTapez: "); 
        scanf("%d",&choix);
        switch(choix) {
            case 1:
                filtre_machine(etudiants,i,OUI,date);
                break;
            case 2:
                filtre_machine(etudiants,i,NON,date);
                break;
            case 3:
                filtre_machine(etudiants,i,PERSO,date);
                break;
            case 4:
                filtre_machine(etudiants,i,ABSENT,date);
                break;
        }
    }
}

Use utilisation_machine(char* use) {
    if(strcmp(use, "OUI") == 0) {
        return OUI;
    }
    else  if(strcmp(use, "NON") == 0) {
        return NON;
    }
    else  if(strcmp(use, "PERSO") == 0) {
        return PERSO;
    }
    return ABSENT;
}

void filtre_machine(Etudiant* etudiants, int nb_eleve, Use utilisation, char* date) {
    const char* use_str;
    int i;
    if(utilisation == OUI) {
        use_str = "utilisent ordi";
    } else if(utilisation == NON) {
        use_str = "n'utilisent pas ordi";
    } else if(utilisation == PERSO) {
        use_str = "utilisent ordi perso";
    } else {
        use_str = "sont absents";
    }

    printf("Liste des éléves qui %s \n", use_str);
    for(i = 0; i < nb_eleve; i++) {
        if(etudiants[i].utilisation == utilisation && strcmp(etudiants[i].date, date) == 0) {
            printf("Numero: %d %s %s \n", etudiants[i].numero, etudiants[i].nom, etudiants[i].prenom);
        }
    }
}

FILE* init_fic(char* fichier, char* mode) {
    FILE* f = fopen(fichier, mode);
    if(f == NULL) {
        printf("Erreur d'ouverture du fichier %s\n", fichier);
        exit(1);
    }
    return f;
}


/* premier pas */

int premier_pas(int choix){

    printf("__________________________________________________\n");
    printf("|\t\tQue voulez-vous\t\t\t  |\n");
    printf("|_________________________________________________|\n");
    printf("|\t[1]: Checker les pc\t\t\t  |\n");
    printf("|\t[2]: voir simplement la liste\t\t  |\n");
    printf("|_________________________________________________|\n");
    printf("Tapez (1 ou 2) : ");
    scanf("%d", &choix);

    return choix;
}