#include <stdio.h>
#include <string.h>
#include "gestion.h"

int main() {
    Membre listeMembres[100];
    int nombreMembres = 0;

    Tache listeTaches[100];
    int nombreTaches = 0;

    Ressource listeRessources[100];
    int nombreRessources = 0;

    int choixModule, choixGestion;
    Membre nouveauMembre;
    Tache nouvelleTache;
    Ressource nouvelleRessource;
    Membre p;
    while (1) {
        printf("\nMenu principal :\n");
        printf("1. Gestion des membres\n");
        printf("2. Gestion des tâches\n");
        printf("3. Gestion des ressources\n");
        printf("4. Suivi des budgets et statistiques\n");
        printf("5. Quitter\n");
        printf("Entrez votre choix : ");
        scanf("%d", &choixModule);

        switch (choixModule) {
            case 1:
                printf("\nGestion des membres :\n");
                printf("1. Ajouter un membre\n");
                printf("2. Supprimer les membres non payants\n");
                printf("3. Modifier un membre \n");
                printf("Entrez votre choix : ");
                scanf("%d", &choixGestion);

                switch (choixGestion) {
                    case 1:
                        p = ajouterMembre(listeMembres, &nombreMembres, nouveauMembre);
                        sauvegarderMembres(p, nombreMembres);
                        break;
                    case 2:
                        supprimerMembreNonPayant(listeMembres, &nombreMembres);
                       // sauvegarderMembres(p, nombreMembres);
                        break;
                    case 3:
                        p = modifierMembre(listeMembres, &nombreMembres, nouveauMembre);
                        sauvegarderMembres(p, nombreMembres);
                        break;
                }
                break;
            case 2:
                printf("\nGestion des tâches :\n");
                printf("1. Ajouter une tâche\n");
                printf("2. Supprimer une tâche\n");
                printf("Entrez votre choix : ");
                scanf("%d", &choixGestion);

                switch (choixGestion) {
                    case 1:
                        Tache nou = ajouterTache( &nombreTaches, nouvelleTache);
                        sauvegarderTaches(nou, nombreTaches);
                        break;
                    case 2:
                        printf("Entrez l'ID de la tâche à supprimer : ");
                        int idTache;
                        scanf("%d", &idTache);
                        supprimerTache(listeTaches, &nombreTaches, idTache);
                        //sauvegarderTaches(listeTaches, nombreTaches);
                        break;
                }
                break;
            case 3:
                printf("\nGestion des ressources :\n");
                printf("1. Ajouter une ressource\n");
                printf("2. Supprimer une ressource\n");
                printf("3. Modifier une ressource\n");
                printf("4. Gérer la disponibilité d'une ressource\n");
                printf("Entrez votre choix : ");
                scanf("%d", &choixGestion);

                switch (choixGestion) {
                    case 1:
                        printf("Entrez le type de ressource : ");
                        scanf("%s", nouvelleRessource.type);
                        printf("Entrez la disponibilité de la ressource (1 pour disponible, 0 pour non disponible) : ");
                        scanf("%d", &nouvelleRessource.disponibilite);
                        printf("Entrez la planification de la ressource : ");
                        scanf("%s", nouvelleRessource.planification);
                        ajouterRessource(listeRessources, &nombreRessources, nouvelleRessource);
                        sauvegarderRessources(listeRessources, nombreRessources);
                        break;
                    case 2:
                        printf("Entrez l'index de la ressource à supprimer : ");
                        int indexRessource;
                        scanf("%d", &indexRessource);
                        supprimerRessource(listeRessources, &nombreRessources, indexRessource);
                        sauvegarderRessources(listeRessources, nombreRessources);
                        break;
                    case 3:
                        printf("Entrez l'index de la ressource à modifier : ");
                        scanf("%d", &indexRessource);
                        printf("Entrez le nouveau type de ressource : ");
                        scanf("%s", nouvelleRessource.type);
                        printf("Entrez la nouvelle disponibilité de la ressource (1 pour disponible, 0 pour non disponible) : ");
                        scanf("%d", &nouvelleRessource.disponibilite);
                        printf("Entrez la nouvelle planification de la ressource : ");
                        scanf("%s", nouvelleRessource.planification);
                        modifierRessource(&listeRessources[indexRessource], nouvelleRessource);
                        sauvegarderRessources(listeRessources, nombreRessources);
                        break;
                    case 4:
                        printf("Entrez l'index de la ressource à gérer : ");
                        scanf("%d", &indexRessource);
                        printf("Entrez la nouvelle disponibilité de la ressource (1 pour disponible, 0 pour non disponible) : ");
                        int disponibilite;
                        scanf("%d", &disponibilite);
                        gererDisponibiliteRessource(&listeRessources[indexRessource], disponibilite);
                        sauvegarderRessources(listeRessources, nombreRessources);
                        break;
                }
                break;
            case 4:
                printf("\nSuivi des budgets et statistiques :\n");
                printf("1. Suivre les cotisations\n");
                printf("2. Générer un rapport des tâches\n");
                printf("3. Générer un rapport des ressources\n");
                printf("Entrez votre choix : ");
                scanf("%d", &choixModule);

                switch (choixModule) {
                    case 1:
                        suivreCotisations(listeMembres, nombreMembres);
                        break;
                    case 2:
                        genererRapportsTaches(listeTaches, nombreTaches);
                        break;
                    case 3:
                        genererRapportsRessources(listeRessources, nombreRessources);
                        break;
                }
                break;
            case 5:
                printf("Au revoir !\n");
                return 0;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
                break;
        }
    }

    return 0;
}
