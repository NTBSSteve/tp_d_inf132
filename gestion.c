#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "gestion.h"

// Fonctions pour générer les jours de la semaine servant a attribuer les heures aux quelles un membre est disponible
char* getNomJour(int i) {
    static char* nomsJours[] = {"Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi", "Dimanche"};

    if (i >= 0 && i < 7) {
        return nomsJours[i];
    } else {
        printf("Index du jour invalide.\n");
        return NULL;
    }
}
// Fonction qui verifie le format de l'horaire HH:MM
int FormatHeure(char entree[]){
    char *heure;
    char *min;
    if (strlen(entree) != 5) return 1;
    if (entree[2] != ':') return 1;
    heure = strtok(entree, ":"); 
    min = strtok(NULL, ":"); 
    int heure_con = atoi(heure);
    int min_con = atoi(min);
    if(heure_con < 0 || heure_con > 23 || min_con < 0 || min_con > 59){
        return 1;
    }

    return 0;
}
// Fonctions de gestion des membres
Membre ajouterMembre(Membre listeMembres[], int* nombreMembres, Membre nouveauMembre) {
    printf("Entrez le nom du membre : ");
    scanf("%s", nouveauMembre.nom);
  /*  fgets(nouveauMembre.nom, sizeof(nouveauMembre.nom), stdin);
    nouveauMembre.nom[strcspn(nouveauMembre.nom, "\n")] = 0;*/

    printf("Entrez le prénom du membre : ");
    scanf("%s", nouveauMembre.prenom);
   /* fgets(nouveauMembre.prenom, sizeof(nouveauMembre.prenom), stdin);
    nouveauMembre.prenom[strcspn(nouveauMembre.prenom, "\n")] = 0;*/

    printf("Entrez le rôle du membre (membre/secretaire/tresorier) : ");
    scanf("%s", nouveauMembre.role);
   /* fgets(nouveauMembre.role, sizeof(nouveauMembre.role), stdin);
    nouveauMembre.role[strcspn(nouveauMembre.role, "\n")] = 0;*/

    //printf("Entrez les coordonnées du membre : ");
    printf("Entrez le lieu de residence : ");
    scanf("%s", nouveauMembre.coordonnees.residence);
    /*fgets(nouveauMembre.coordonnees.residence, sizeof(nouveauMembre.coordonnees.residence), stdin);
    nouveauMembre.coordonnees.residence[strcspn(nouveauMembre.coordonnees.residence, "\n")] = 0;*/

    printf("Entrez votre adresse email : ");
    scanf("%s", nouveauMembre.coordonnees.adresse_email);
    /*fgets(nouveauMembre.coordonnees.adresse_email, sizeof(nouveauMembre.coordonnees.adresse_email), stdin);
    nouveauMembre.coordonnees.adresse_email[strcspn(nouveauMembre.coordonnees.adresse_email, "\n")] = 0;*/
    int u = 0;
    // Demander les horaires de disponibilité pour chaque jour de la semaine
    for (int i = 0; i < 7; i++) {
    char choice[3];
    	printf("Etes-vous disponible %s repondez par oui/non : ", getNomJour(i));
    	scanf("%s", choice);
    	int j = 0;
    	while(choice[j]){
    		choice[j] = tolower(choice[j]);
    		j++;
    	}	
    	if(strcmp(choice, "oui") == 0){
        	printf("Entrez les horaires de disponibilité pour %s  (HH:MM): ", getNomJour(i));
        	scanf("%s", nouveauMembre.horaires[i]);
            char *a = nouveauMembre.horaires[i];
            if(FormatHeure(a) == 1) {
                printf("Erreur! Veuillez redefinir votre horaire\n");
                i--;
            }
    	}else if(strcmp(choice, "non") != 0){
                printf("Erreur! Veuillez redefinir votre horaire\n");
                i--;
    	}else if(strcmp(choice, "non") == 0){
           strcat(nouveauMembre.horaires[i], "NULL "); 
            u++;
    	}
        if( u >= 4 ){
            printf("Vous devez etre disponible au moins quatre fois par semaine\n");
            i = 0;
            u = 0;
        }
        nouveauMembre.id = 7 - u;
    }
    int k = 1;
    while( k != 0){
    int tranche;
    printf(" En combien de tranche voulez-vous payer votre frais d'adhesion qui s'eleve a 150000 Fcfa (Entre 1 pour une tranche, 2 pour deux tranche et 3 pour trois tranche): ");
    scanf("%d", &tranche);
    switch (tranche)
    {
    case 1:
        printf("Entrez le montant : ");
        scanf("%f", &nouveauMembre.montant_adhesion.tranche);
            // Initialisation du nombre de paiements effectués à 0
              nouveauMembre.paiements_effectues = 0;
        if(nouveauMembre.montant_adhesion.tranche < 150000) 
        {
            k++;
            printf("Vous avez fait une erreur d'entree. Veuillez recommencer\n");
        }
        k = 0;
        break;
    case 2 :
        printf("Entrez le montant de la premiere partie   ");
        scanf("%f", &nouveauMembre.montant_adhesion.tranche);
            // Initialisation du nombre de paiements effectués à 0
                nouveauMembre.paiements_effectues = 1;
        if(nouveauMembre.montant_adhesion.tranche < 75000)
        {
            k++;
            printf("Vous avez fait une erreur d'entree. Veuillez recommencer\n");
        }
        k = 0;
        break;   
    case 3 :
        printf("Entrez le montant de la premiere partie : ");
        scanf("%f", &nouveauMembre.montant_adhesion.tranche);
            // Initialisation du nombre de paiements effectués à 0
              nouveauMembre.paiements_effectues = 2;
        if(nouveauMembre.montant_adhesion.tranche < 50000){
            k++;
            printf("Vous avez fait une erreur d'entree. Veuillez recommencer\n");
        }
        k = 0;
        break;
    default:
        printf("Erreur veuillez recommencer");
        break;
    }
    };



    // Incrémentation du nombre total de membres
    (*nombreMembres)++;

    // Ajout du nouveau membre à la fin de la liste des membres
    return nouveauMembre;

}
Membre modifierMembre(Membre listeMembres[], int* nombreMembres, Membre nouveauMembre) {
  /*  fgets(nouveauMembre.nom, sizeof(nouveauMembre.nom), stdin);
    nouveauMembre.nom[strcspn(nouveauMembre.nom, "\n")] = 0;*/
    Membre modif = nouveauMembre;
    Membre *Modifier = &nouveauMembre;
    FILE* fichie = fopen("id.txt", "r");
    if (fichie == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        exit(1);
    }
    int id;
        fscanf(fichie, "%d", &id);
        fclose(fichie);

   int g = 0; 
Membre *o = chargerMembres(Modifier, &id);
    printf("Que voulez vous modifier ??\n");
  do{
    printf("Entrez l'identifiant du membre a modifier : ");
    scanf("%d", &modif.id);
  if(o[id].id == modif.id){
    char choise[3];
    printf("Voulez-vous modifier le nom ?? (oui/non) ");
    	scanf("%s", choise);
    	int j = 0;
    	while(choise[j]){
    		choise[j] = tolower(choise[j]);
    		j++;
    	}	
    	if(strcmp(choise, "oui") == 0){
        	printf("Entrez le nouveau nom du membre : ");
        	scanf("%s", modif.nom);
             o[id].nom = modif.nom;
        }
        printf("Voulez-vous modifier le prenom ?? (oui/non) ");
    	scanf("%s", choise);
    	 j = 0;
    	while(choise[j]){
    		choise[j] = tolower(choise[j]);
    		j++;
    	}	
    	if(strcmp(choise, "oui") == 0){
        	printf("Entrez le nouveau prenom du membre : ");
        	scanf("%s", modif.prenom);
    	}else{
            modif.prenom
        }
   /* fgets(nouveauMembre.prenom, sizeof(nouveauMembre.prenom), stdin);
    nouveauMembre.prenom[strcspn(nouveauMembre.prenom, "\n")] = 0;*/
    printf("Voulez-vous modifier le role du membre ?? (oui/non) ");
    	scanf("%s", choise);
    	 j = 0;
    	while(choise[j]){
    		choise[j] = tolower(choise[j]);
    		j++;
    	}	
    	if(strcmp(choise, "oui") == 0){
        	printf("Entrez le nouveau role du membre : ");
        	scanf("%s", modif.role);
    	}
   /* fgets(nouveauMembre.role, sizeof(nouveauMembre.role), stdin);
    nouveauMembre.role[strcspn(nouveauMembre.role, "\n")] = 0;*/

    //printf("Entrez les coordonnées du membre : ");
    printf("Voulez-vous modifier le lieu de residence du membre ?? (oui/non) ");
    	scanf("%s", choise);
    	j = 0;
    	while(choise[j]){
    		choise[j] = tolower(choise[j]);
    		j++;
    	}	
    	if(strcmp(choise, "oui") == 0){
        	printf("Entrez le nouveau lieu de residence du membre : ");
        	scanf("%s", modif.coordonnees.residence);
    	}
    /*fgets(nouveauMembre.coordonnees.residence, sizeof(nouveauMembre.coordonnees.residence), stdin);
    nouveauMembre.coordonnees.residence[strcspn(nouveauMembre.coordonnees.residence, "\n")] = 0;*/
printf("Voulez-vous modifier l'adresse email du membre ?? (oui/non) ");
    	scanf("%s", choise);
    	 j = 0;
    	while(choise[j]){
    		choise[j] = tolower(choise[j]);
    		j++;
    	}	
    	if(strcmp(choise, "oui") == 0){
        	printf("Entrez la nouvelle adresse email du membre : ");
        	scanf("%s", modif.coordonnees.residence);
    	}
    /*fgets(nouveauMembre.coordonnees.adresse_email, sizeof(nouveauMembre.coordonnees.adresse_email), stdin);
    nouveauMembre.coordonnees.adresse_email[strcspn(nouveauMembre.coordonnees.adresse_email, "\n")] = 0;*/
    int u = 0;
    // Demander les horaires de disponibilité pour chaque jour de la semaine
    printf("Voulez-vous changer vos horaires de disponibilite ?? (oui/non) : ");
    scanf("%s", choise);
    	 j = 0;
    	while(choise[j]){
    		choise[j] = tolower(choise[j]);
    		j++;
    	}	
    	if(strcmp(choise, "oui") == 0){
    for (int i = 0; i < 7; i++) {
    char choice[3];
    	printf("Etes-vous disponible %s repondez par oui/non : ", getNomJour(i));
    	scanf("%s", choice);
    	 j = 0;
    	while(choice[j]){
    		choice[j] = tolower(choice[j]);
    		j++;
    	}	
    	if(strcmp(choice, "oui") == 0){
        	printf("Entrez les horaires de disponibilité pour %s  (HH:MM): ", getNomJour(i));
        	scanf("%s", modif.horaires[i]);
            char *a = modif.horaires[i];
            if(FormatHeure(a) == 1) {
                printf("Erreur! Veuillez redefinir votre horaire\n");
                i--;
            }
    	}else if(strcmp(choice, "non") != 0){
                printf("Erreur! Veuillez redefinir votre horaire\n");
                i--;
    	}else if(strcmp(choice, "non") == 0){
           strcat(modif.horaires[i], "NULL "); 
            u++;
    	}
        if( u >= 4 ){
            printf("Vous devez etre disponible au moins quatre fois par semaine\n");
            i = 0;
            u = 0;
        }
  }
   }
   printf("Voulez-vous modifier les tranches ?? (oui/non) : ");
   scanf("%s", choise);
    	 j = 0;
    	while(choise[j]){
    		choise[j] = tolower(choise[j]);
    		j++;
    	}	
    	if(strcmp(choise, "oui") == 0){
    if(o->paiements_effectues == 0) printf("Vous avez deja tous paye ");
    int tranche;
    printf(" Entrez la nouvelle tranche ");
    scanf("%d", &tranche);
    if(o->paiements_effectues == 1){
        if(tranche == 75000){
            printf("Vous venez de tous paye! ");
            modif.paiements_effectues = 0;
        }
    }
    if(o->paiements_effectues == 2){
        if(tranche == 50000){
            printf("Il va vous rester une dernier partie a payer  ");
            modif.paiements_effectues = 1;
        }
    }
   }
   printf("Avez-vous fini de modifier les informations ? (oui/non):");
      scanf("%s", choise);
    	 j = 0;
    	while(choise[j]){
    		choise[j] = tolower(choise[j]);
    		j++;
    	}	
    	if(strcmp(choise, "oui") == 0){
            g++;
        }
  }else {
    printf("L'id %d ne correspond pas a un id trouve ", modif.id);
    g = 0;
  }
}while( g == 0);
    // Ajout du nouveau membre à la fin de la liste des membres
   nouveauMembre = modif; 
    return nouveauMembre;

}
void supprimerMembreNonPayant(Membre listeMembres[], int* nombreMembres) {
    FILE* fichie = fopen("id.txt", "r");
    if (fichie == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }
    int id;
        fscanf(fichie, "%d", &id);
        fclose(fichie);

       Membre *MembreListe;
       
       if( chargerMembres(MembreListe, &id) == NULL) return;
       MembreListe = chargerMembres(MembreListe, &id);
    for (int i = 0; i < id; i++) {
        if (MembreListe[i].paiements_effectues != 0) {
                printf(" L'id %d n'a pas paye \n ", i + 1);
        }
    }
}
int VerifierFormatDate(char date[]){
    if(strlen(date) != 10) return 1;
    if(date[4] != '-' || date[7] != '-') return 1;
    for(int i = 0; i < 10; i++){
        if(i != 4 && i != 7 && (date[i] < '0' || date[i] > '9')) return 1;
    }
    int annee = atoi(date);
    int mois = atoi(date + 5);
    int jour = atoi(date + 8);
    if(annee < 2024 || mois < 1 || mois > 12 || jour < 1 || jour > 31) return 1;
    return 0;
}
// Fonctions de gestion des tâches
Tache ajouterTache( int* nombreTaches, Tache nouvelleTache) {
        FILE* fichie = fopen("id.txt", "r");
    if (fichie == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return nouvelleTache;
    }
    int id;
        fscanf(fichie, "%d", &id);
        fclose(fichie);

       Membre *MembreListe;
       
       if( chargerMembres(MembreListe, &id) == NULL) return nouvelleTache;
       MembreListe = chargerMembres(MembreListe, &id);
    printf("Entrez l'identifiant de la tâche : ");
    scanf("%d", &nouvelleTache.id);
    printf("Entrez le libellé de la tâche : ");
    scanf("%s", nouvelleTache.libelle);
    printf("Entrez le budget de la tâche : ");
    scanf("%f", &nouvelleTache.budget);
    int a = 0;
    do{
     printf("Entrez le responsable de la tâche : ");
    scanf("%s", nouvelleTache.responsable);
    for(int i = 0; i < id; i++){
    if(strcmp(MembreListe[i].nom, nouvelleTache.responsable) == 0){
      a++;
    }
    }
    }while(a == 0);
    printf("Entrez le statut de la tâche : ");
    scanf("%s", nouvelleTache.statut);
  do{
    printf("Entrez la date de fin de la tâche (YYYY-MM-DD) : ");
    scanf("%s", nouvelleTache.date_fin);
  }while(VerifierFormatDate(nouvelleTache.date_fin) != 0);
   /* listeTaches[*nombreTaches] = nouvelleTache;
    (*nombreTaches)++;*/
    return nouvelleTache;
}

void supprimerTache(Tache listeTaches[], int* nombreTaches, int idTache) {
    Tache *tachelis = chargerTaches(listeTaches, &idTache);
    for (int i = 0; i < sizeof(tachelis); i++) {
        if (tachelis[i].id == idTache) {
            printf(" Tache trouve!");
            break;
        }
    }
}

// Fonctions de gestion des ressources
void ajouterRessource(Ressource listeRessources[], int* nombreRessources, Ressource nouvelleRessource) {
    
    listeRessources[*nombreRessources] = nouvelleRessource;
    (*nombreRessources)++;
}

void supprimerRessource(Ressource listeRessources[], int* nombreRessources, int indexRessource) {
    for (int i = indexRessource; i < *nombreRessources - 1; i++) {
        listeRessources[i] = listeRessources[i + 1];
    }
    (*nombreRessources)--;
}

void modifierRessource(Ressource* ressourceAModifier, Ressource nouvelleRessource) {
    *ressourceAModifier = nouvelleRessource;
}

void gererDisponibiliteRessource(Ressource* ressource, int disponibilite) {
    ressource->disponibilite = disponibilite;
}

// Suivi des cotisations
void suivreCotisations(Membre listeMembres[], int nombreMembres) {
    for (int i = 0; i < nombreMembres; i++) {
       // printf("Membre ID: %d, Nom: %s %s, Montant adhesion: %f, Paiements effectués: %d\n", 
         //      listeMembres[i].id, listeMembres[i].nom, listeMembres[i].prenom, 
           //    listeMembres[i].montant_adhesion, listeMembres[i].paiements_effectues);
    }
}

// Génération de rapports
void genererRapportsTaches(Tache listeTaches[], int nombreTaches) {
    for (int i = 0; i < nombreTaches; i++) {
        printf("Tâche ID: %d, Libellé: %s, Budget: %.2f, Responsable: %s, Statut: %s, Date de fin: %s\n", 
               listeTaches[i].id, listeTaches[i].libelle, listeTaches[i].budget, 
               listeTaches[i].responsable, listeTaches[i].statut, listeTaches[i].date_fin);
    }
}

void genererRapportsRessources(Ressource listeRessources[], int nombreRessources) {
    for (int i = 0; i < nombreRessources; i++) {
        printf("Ressource Type: %s, Disponibilité: %d, Planification: %s\n", 
               listeRessources[i].type, listeRessources[i].disponibilite, 
               listeRessources[i].planification);
    }
}

// Fonctions de sauvegarde et de chargement des membres
void sauvegarderMembres(Membre listeMembres, int nombreMembres) {
    FILE* fichier = fopen("membres.txt", "a");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }
    int id;
    FILE* fichie = fopen("id.txt", "r");
    if (fichie == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }
        fscanf(fichie, "%d", &listeMembres.id);
        fclose(fichie);
    FILE* fichi = fopen("id.txt", "w");
    if (fichi == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }
        fprintf(fichi, "%d", listeMembres.id + 1);
        fclose(fichi);

        fprintf(fichier, "%d %s %s %s %s %s", 
                listeMembres.id + 1, listeMembres.nom, listeMembres.prenom, 
                listeMembres.role, listeMembres.coordonnees.residence, listeMembres.coordonnees.adresse_email );
        for (int j = 0; j < 7; j++) {
            //if(strcmp(listeMembres.horaires[j], "NULL") != 0) 
            fprintf(fichier, " %s %d ", listeMembres.horaires[j], j);
        }
       fprintf(fichier, "%.2f %d\n", listeMembres.montant_adhesion.tranche, listeMembres.paiements_effectues);
    

    fclose(fichier);
}

Membre *chargerMembres(Membre listeMembre[], int* nombreMembres) {
    Membre *listeMembres = listeMembre;
    int k[100];
    FILE* fichier = fopen("membres.txt", "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return NULL;
    }
    //printf("reusssi3");
    for(int i = 0; i < *nombreMembres; i++){
        fscanf(fichier, "%d%s%s%s%s%s", 
               &listeMembres[i].id, listeMembres[i].nom, listeMembres[i].prenom, 
               listeMembres[i].role, listeMembres[i].coordonnees.residence, listeMembres[i].coordonnees.adresse_email );
        for (int j = 0; j < 7; j++) {
            fscanf(fichier, "%s%d", listeMembres[i].horaires[j], &k[i]);
            //printf(" l'Heure : %s  Le jour: %d ", listeMembres[i].horaires[j], k[i]);
        }
        //printf("\n");
        fscanf(fichier, "%f%d", &listeMembres[i].montant_adhesion.tranche, &listeMembres[i].paiements_effectues);
     //   printf(" L'id :%d  Le nom:%s Le penom:%s Le role:%s Resisdence:%s Adresse:%s Montant:%f paiement:%d\n", listeMembres[i].id, listeMembres[i].nom, listeMembres[i].prenom, listeMembres[i].role, listeMembres[i].coordonnees.residence, listeMembres[i].coordonnees.adresse_email, listeMembres[i].montant_adhesion.tranche, listeMembres[i].paiements_effectues);
    }
    //printf("reusssi1");
    fclose(fichier);
    listeMembre = listeMembres;
    //printf("reusssi");
    return listeMembre;
}

// Fonctions de sauvegarde et de chargement des tâches
void sauvegarderTaches(Tache listeTaches, int nombreTaches) {
    FILE* fichier = fopen("taches.txt", "a");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }
    //for (int i = 0; i < nombreTaches; i++) {
        fprintf(fichier, "%d %s %.2f %s %s %s\n", 
                listeTaches.id, listeTaches.libelle, listeTaches.budget, 
                listeTaches.responsable, listeTaches.statut, listeTaches.date_fin);
    //}

    fclose(fichier);
}

Tache *chargerTaches(Tache listeTaches[], int* nombreTaches) {
    Tache *listeTache = listeTaches;
    FILE* fichier = fopen("taches.txt", "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return NULL;
    }
    int i = 0;
   // for (int i = 0; i < *nombreTaches; i++) 
    do{
        fscanf(fichier, "%d %s %f %s %s %s\n", 
               &listeTache[i].id, listeTache[i].libelle, &listeTache[i].budget, 
               listeTache[i].responsable, listeTache[i].statut, listeTache[i].date_fin);
        i++;
    }while(!feof(fichier));

    fclose(fichier);
  listeTaches = listeTache;
  return listeTaches;
}

// Fonctions de sauvegarde et de chargement des ressources
void sauvegarderRessources(Ressource listeRessources[], int nombreRessources) {
    FILE* fichier = fopen("ressources.txt", "w");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    fprintf(fichier, "%d\n", nombreRessources);
    for (int i = 0; i < nombreRessources; i++) {
        fprintf(fichier, "%s\n %d\n %s\n", 
                listeRessources[i].type, listeRessources[i].disponibilite, 
                listeRessources[i].planification);
    }

    fclose(fichier);
}

void chargerRessources(Ressource listeRessources[], int* nombreRessources) {
    FILE* fichier = fopen("ressources.txt", "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    fscanf(fichier, "%d", nombreRessources);
    for (int i = 0; i < *nombreRessources; i++) {
        fscanf(fichier, "%s\n %d\n %s\n", 
               listeRessources[i].type, &listeRessources[i].disponibilite, 
               listeRessources[i].planification);
    }

    fclose(fichier);
}
