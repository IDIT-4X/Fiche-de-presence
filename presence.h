/* Constante */
#define DATE_LENGTH 11
#define MAX_LENGTH_CHAINE 200
#define NB_MAX_ETU 200

/* Structure */
typedef enum  {
    OUI,
    NON,
    PERSO,
    ABSENT
} Use;

typedef struct  {
    int numero;
    char nom[MAX_LENGTH_CHAINE];
    char prenom[MAX_LENGTH_CHAINE];
    Use utilisation;
    char date[DATE_LENGTH];
} Etudiant;

/* Entete de fonctions */
int premier_pas(int choix);
Use utilisation_machine(char* use);
void filtre_machine(Etudiant* etudiants, int nb_eleve, Use utilisation, char* date);
FILE* init_fic(char* fichier, char* mode);
void rond_point(char* args[]);