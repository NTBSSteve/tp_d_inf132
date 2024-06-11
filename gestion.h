#ifndef __GESTION__H__
#define __GESTION__H__

// structure à utiliser dans les fonctions
typedef struct{
	char residence[100];
	char adresse_email[100];
} Coordonne;
typedef struct {
    float tranche;
} Tranche;
typedef struct {
    int id;
    char nom[50];
    char prenom[50];
    char role[50];
    Coordonne coordonnees;
    char horaires[7][50]; // Disponibilité pour chaque jour de la semaine
    Tranche montant_adhesion;
    int paiements_effectues;
} Membre;

typedef struct {
    int id;
    char libelle[100];
    float budget;
    char responsable[50];
    char statut[20];
    char date_fin[11]; // Format YYYY-MM-DD
} Tache;

typedef struct {
    char type[50];
    int disponibilite; // 1 pour disponible, 0 pour non disponible
    char planification[100];
} Ressource;

typedef struct {
    float cotisations;
    float depenses;
    float solde;
} Finances;
 
// prototypes des fonctions

char* getNomJour(int i);

Membre ajouterMembre(Membre listeMembres[], int* nombreMembres, Membre nouveauMembre);
Membre modifierMembre(Membre listeMembres[], int* nombreMembres, Membre nouveauMembre);
void supprimerMembreNonPayant(Membre listeMembres[], int* nombreMembres);
Tache ajouterTache( int* nombreTaches, Tache nouvelleTache);
void supprimerTache(Tache listeTaches[], int* nombreTaches, int idTache);
void ajouterRessource(Ressource listeRessources[], int* nombreRessources, Ressource nouvelleRessource);
void supprimerRessource(Ressource listeRessources[], int* nombreRessources, int indexRessource);
void modifierRessource(Ressource* ressourceAModifier, Ressource nouvelleRessource);
void gererDisponibiliteRessource(Ressource* ressource, int disponibilite);
void suivreCotisations(Membre listeMembres[], int nombreMembres);
void genererRapportsTaches(Tache listeTaches[], int nombreTaches);
void genererRapportsRessources(Ressource listeRessources[], int nombreRessources);


void sauvegarderMembres(Membre listeMembres, int nombreMembres);
Membre *chargerMembres(Membre listeMembres[], int* nombreMembres);
void sauvegarderTaches(Tache listeTaches, int nombreTaches);
Tache *chargerTaches(Tache listeTaches[], int* nombreTaches);
void sauvegarderRessources(Ressource listeRessources[], int nombreRessources);
void chargerRessources(Ressource listeRessources[], int* nombreRessources);


#endif
