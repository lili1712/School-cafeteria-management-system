#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//Memory allocation problems mdp et id
typedef struct Date{
    int jour;
    int mois;
    int annee;
} date;

typedef struct Repas{
    int menu1;
    int menu2;
    char meal[20];
} repas;

typedef struct Ticket{
    date date_expiration;
    repas repasT;
} ticket;

struct Utilisateur {
    int id;
    char mdp[30];
    char prenom[30];
    char nom[30];
    date D_naissance;
    char genie[30];
    int solde;
    //panier is an array of tickets
    ticket panier[21];
};



typedef struct MenuJour{
    repas petitDej;
    repas dej;
    repas diner;
    date dateDuJour;
} menuJour;

struct Menu {
    menuJour lundi;
    menuJour mardi;
    menuJour mercredi;
    menuJour jeudi;
    menuJour vendredi;
    menuJour samedi;
    menuJour dimanche;
};

void ajouter_eleve(char nomFichier[]) {
    int id,jour,mois,annee,solde;
    char mdp[20], nom[30], prenom[30], genie[30];
    struct Utilisateur user;
    FILE *f;

    printf("Entrez le prenom de l'eleve : ");
    scanf("%s", prenom);

    printf("\nEntrez le nom de l'eleve : ");
    scanf("%s", nom);

    printf("\nEntrez le genie de l'eleve : ");
    scanf("%s", genie);

    printf("\nEntrez la date de naissance de l'eleve : ");
    printf("\n\tjour :");
    scanf("%d", &jour);
    printf("\n\tmois :");
    scanf("%d", &mois);
    printf("\n\tannee :");
    scanf("%d", &annee);

    printf("Entrez le solde de l'eleve : ");
    scanf("%d", &solde);

    printf("Entrez l'id de l'eleve : ");
    scanf("%d", &id);

    printf("Entrez le mot de passe de l'eleve : ");
    scanf("%s", mdp);

    f = fopen(nomFichier, "a");
        fprintf(f, "%d %s %s %s %d/%d/%d %s %d;", id,mdp,prenom,nom,jour,mois,annee,genie,solde);
    fclose(f);
}

void supprimer_eleve(int id_eleve, char nomFichier[]){
    FILE *f,*newf;
    int id,jour,mois,annee,solde;
    char mdp[20], nom[30], prenom[30], genie[30];
    bool user_exist=false;
    char k;

    f = fopen(nomFichier, "r");
        while (!user_exist) {
            while (id!=id_eleve) {
            fscanf(f,"%d %*s %*s %*s %*d/%*d/%*d %*s %*d;",&id);
            k=fgetc(f);
            if (k==EOF) {
                break;
            }
        }
        if (id != id_eleve) {
            printf("Il n' ya aucun eleve avec cet identifiant, essayez un autre : ");
            scanf("%d", id);
        } else {
            user_exist = true;
        }
        }

        newf = fopen("tempFile.txt", "w");
            fseek(f,0,SEEK_SET);
            do {
                fscanf(f,"%d %s %s %s %d/%d/%d %s %d;",&id,mdp,prenom,nom,&jour,&mois,&annee,genie,&solde);
                k=fgetc(f);
                if (id != id_eleve) {
                    fprintf(newf,"%d %s %s %s %d/%d/%d %s %d;",&id,mdp,prenom,nom,&jour,&mois,&annee,genie,&solde);
                }
            } while (k!=EOF);
        fclose(newf);
    fclose(f);
}

int main() {
    //Page Authentification
    struct Utilisateur user;
    struct Menu day;
    ticket ticketJ;
    FILE *f;
    char modp[8],mdp[30],f_modp[30],prenom[30],nom[30],genie[30],k,No;
    No='N';
    int i,destinationRub,Id,f_id,f_jour,f_mois,f_annee,f_solde,jour,petitDej,dej,diner,index=0,line,res1,res2,answer,return_answ,admin_menu,admin_idEleve;
    bool user_exist=false,repeat=true,but_return=true;

    while (!user_exist) {
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
        printf("\tID : ");
        scanf("%d", &Id);

        printf("\n\tMot de passe : ");
        scanf("%s",modp);
        printf("\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");


            //Verification de l'existence de l'utilisateur
            f=fopen("database_PI.txt","r");
                while (modp != f_modp && Id != f_id) {
                    fscanf(f,"%d %s %s %s %d/%d/%d %s %d",&f_id,f_modp,prenom,nom,&f_jour,&f_mois,&f_annee,genie,&f_solde);
                    k=fgetc(f);
                    if (k==EOF) {
                        break;
                    }
                }
                res1=strcmp(modp,f_modp);

                if (res1==0 && Id==f_id && res2 !=1) {
                    user_exist=true;
                    //Verifier si c'est l'admin
                    //Remplissage des propriétés de user à partir des informations disponibles dans le fichier
                    user.id=f_id;
                    user.D_naissance.jour=f_jour;
                    user.D_naissance.mois=f_mois;
                    user.D_naissance.annee=f_annee;
                    user.solde=f_solde;
                    strcpy(user.mdp,f_modp);
                    strcpy(user.prenom,prenom);
                    strcpy(user.nom,nom);
                    strcpy(user.genie,genie);
                fclose(f);
                } else {
                    printf("\nMot de passe ou identifiant inexistant\n");
                }

    }

        //Remplissage du menu depuis fichier menu
        f=fopen("database_PI_menu.txt","r");
            fscanf(f,"%d/%d/%d %*s %*s %*s %*s %*s %*s",&day.lundi.dateDuJour.jour,&day.lundi.dateDuJour.mois,&day.lundi.dateDuJour.annee);
            fgetc(f);
            fscanf(f,"%d/%d/%d %*s %*s %*s %*s %*s %*s",&day.mardi.dateDuJour.jour,&day.mardi.dateDuJour.mois,&day.mardi.dateDuJour.annee);
            fgetc(f);
            fscanf(f,"%d/%d/%d %*s %*s %*s %*s %*s %*s",&day.mercredi.dateDuJour.jour,&day.mercredi.dateDuJour.mois,&day.mercredi.dateDuJour.annee);
            fgetc(f);
            fscanf(f,"%d/%d/%d %*s %*s %*s %*s %*s %*s",&day.jeudi.dateDuJour.jour,&day.jeudi.dateDuJour.mois,&day.jeudi.dateDuJour.annee);
            fgetc(f);
            fscanf(f,"%d/%d/%d %*s %*s %*s %*s %*s %*s",&day.vendredi.dateDuJour.jour,&day.vendredi.dateDuJour.mois,&day.vendredi.dateDuJour.annee);
            fgetc(f);
            fscanf(f,"%d/%d/%d %*s %*s %*s %*s %*s %*s",&day.samedi.dateDuJour.jour,&day.samedi.dateDuJour.mois,&day.samedi.dateDuJour.annee);
            fgetc(f);
            fscanf(f,"%d/%d/%d %*s %*s %*s %*s %*s %*s",&day.dimanche.dateDuJour.jour,&day.dimanche.dateDuJour.mois,&day.dimanche.dateDuJour.annee);
        fclose(f);

    //separation entre les pages
    system("cls");







    //Page Rubriques

    while (but_return) {
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
        printf("\t1 -> utilisateur\n\t2 -> Menu\n\n\t\tOu aller? => ");
        scanf("%d", &destinationRub);

        while (destinationRub != 1 && destinationRub != 2 ) {
            printf("\tEntrez 1 ou 2 pour acceder a la page desiree : ");
            scanf("%d", &destinationRub);
        }
        //separation entre les pages
        printf("\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
        system("cls");










        switch (destinationRub)
        {
        case 1 :
            //Page de l'utilisateur
            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
            printf("Prenom : %s\n", user.prenom);
            printf("Nom : %s\n", user.nom);
            printf("Date de naissance : %d/%d/%d\n", user.D_naissance.jour, user.D_naissance.mois, user.D_naissance.annee);
            printf("Genie : %s\n", user.genie);
            printf("Solde : %d\n", user.solde);
            printf("Panier : \n");
            if (index==0) {
                printf("\t Panier vide, aucun ticket!\n");
            } else {
                i=0;
                while (i<index) {
                    printf("Ticket %d -> date d'expiration : %d/%d/%d | Menu1 : %d | Menu2 : %d | repas : %s \n",i+1,
                            user.panier[i].date_expiration.jour, user.panier[i].date_expiration.mois, user.panier[i].date_expiration.annee,
                            user.panier[i].repasT.menu1,
                            user.panier[i].repasT.menu2,
                            user.panier[i].repasT.meal);
                    i++;
                }
            }
            printf("\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
            //bouton Retour vers la page rubrique
            printf("\n\tVoulez-vous retourner a la page rubrique ? 0oui/1non => ");
            scanf("%d", &return_answ);
            if (return_answ==1) {
                but_return=false;
            }


            printf("\n\n\n\n");//separation entre les pages

            system("cls");
            break;
        case 2 :
            //Page du Menu
            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
            printf("1 -> Lundi\n2 -> Mardi\n3 -> Mercredi\n4 -> Jeudi\n5 -> Vendredi\n6 -> Samedi\n7 -> Dimanche\n\n Ou aller => ");
            scanf("%d", &jour);
            system("cls");

            while (repeat){
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
                switch (jour)
                {
                case 1 :
                    printf("Choisir menu 1 ou 2 pour le petit dejeuner clickez n'importe quel chiffre si aucun : ");
                    scanf("%d",&petitDej);
                    if (petitDej==1){
                        //Create ticket
                        ticketJ.date_expiration.jour=day.lundi.dateDuJour.jour;
                        ticketJ.date_expiration.mois=day.lundi.dateDuJour.mois;
                        ticketJ.date_expiration.annee=day.lundi.dateDuJour.annee;
                        strcpy(ticketJ.repasT.meal,"petitDej");
                        ticketJ.repasT.menu1=1;
                        ticketJ.repasT.menu2=0;
                        //add ticket
                        user.panier[index]=ticketJ;
                        index++;
                        //payment phase
                        user.solde--;
                    } else if (petitDej==2){
                        ticketJ.date_expiration.jour=day.lundi.dateDuJour.jour;
                        ticketJ.date_expiration.mois=day.lundi.dateDuJour.mois;
                        ticketJ.date_expiration.annee=day.lundi.dateDuJour.annee;
                        strcpy(ticketJ.repasT.meal,"petitDej");
                        ticketJ.repasT.menu2=1;
                        ticketJ.repasT.menu1=0;
                        //add ticket
                        user.panier[index]=ticketJ;
                        index++;
                        //payment phase
                        user.solde--;
                    }

                    printf("Choisir menu 1 ou 2 pour le dejeuner clickez n'importe quel chiffre si aucun : ");
                    scanf("%d",&dej);
                    if (dej==1){
                        //Create ticket
                        ticketJ.date_expiration.jour=day.lundi.dateDuJour.jour;
                        ticketJ.date_expiration.mois=day.lundi.dateDuJour.mois;
                        ticketJ.date_expiration.annee=day.lundi.dateDuJour.annee;
                        strcpy(ticketJ.repasT.meal,"Dejeuner");
                        ticketJ.repasT.menu1=1;
                        ticketJ.repasT.menu2=0;
                        //add ticket
                        user.panier[index]=ticketJ;
                        index++;
                        //payment phase
                        user.solde--;
                    } else if (dej==2){
                        ticketJ.date_expiration.jour=day.lundi.dateDuJour.jour;
                        ticketJ.date_expiration.mois=day.lundi.dateDuJour.mois;
                        ticketJ.date_expiration.annee=day.lundi.dateDuJour.annee;
                        strcpy(ticketJ.repasT.meal,"Dejeuner");
                        ticketJ.repasT.menu2=1;
                        ticketJ.repasT.menu1=0;
                        //add ticket
                        user.panier[index]=ticketJ;
                        index++;
                        //payment phase
                        user.solde--;
                    }

                    printf("Choisir menu 1 ou 2 pour le diner clickez n'importe quel chiffre si aucun : ");
                    scanf("%d",&diner);
                    if (diner==1){
                        //Create ticket
                        ticketJ.date_expiration.jour=day.lundi.dateDuJour.jour;
                        ticketJ.date_expiration.mois=day.lundi.dateDuJour.mois;
                        ticketJ.date_expiration.annee=day.lundi.dateDuJour.annee;
                        strcpy(ticketJ.repasT.meal,"diner");
                        ticketJ.repasT.menu1=1;
                        ticketJ.repasT.menu2=0;
                        //add ticket
                        user.panier[index]=ticketJ;
                        index++;
                        //payment phase
                        user.solde--;
                    } else if (diner==2){
                        ticketJ.date_expiration.jour=day.lundi.dateDuJour.jour;
                        ticketJ.date_expiration.mois=day.lundi.dateDuJour.mois;
                        ticketJ.date_expiration.annee=day.lundi.dateDuJour.annee;
                        strcpy(ticketJ.repasT.meal,"diner");
                        ticketJ.repasT.menu2=1;
                        ticketJ.repasT.menu1=0;
                        //add ticket
                        user.panier[index]=ticketJ;
                        index++;
                        //payment phase
                        user.solde--;
                    }
                    break;
                case 2 :
                    printf("Choisir menu 1 ou 2 pour le petit dejeuner clickez n'importe quel chiffre si aucun : ");
                    scanf("%d",&petitDej);
                    if (petitDej==1){
                        //Create ticket
                        ticketJ.date_expiration.jour=day.mardi.dateDuJour.jour;
                        ticketJ.date_expiration.mois=day.mardi.dateDuJour.mois;
                        ticketJ.date_expiration.annee=day.mardi.dateDuJour.annee;
                        strcpy(ticketJ.repasT.meal,"petitDej");
                        ticketJ.repasT.menu1=1;
                        ticketJ.repasT.menu2=0;
                        //add ticket
                        user.panier[index]=ticketJ;
                        index++;
                        //payment phase
                        user.solde--;
                    } else if (petitDej==2){
                        ticketJ.date_expiration.jour=day.mardi.dateDuJour.jour;
                        ticketJ.date_expiration.mois=day.mardi.dateDuJour.mois;
                        ticketJ.date_expiration.annee=day.mardi.dateDuJour.annee;
                        strcpy(ticketJ.repasT.meal,"petitDej");
                        ticketJ.repasT.menu2=1;
                        ticketJ.repasT.menu1=0;
                        //add ticket
                        user.panier[index]=ticketJ;
                        index++;
                        //payment phase
                        user.solde--;
                    }

                    printf("Choisir menu 1 ou 2 pour le dejeuner clickez n'importe quel chiffre si aucun : ");
                    scanf("%d",&dej);
                    if (dej==1){
                        //Create ticket
                        ticketJ.date_expiration.jour=day.mardi.dateDuJour.jour;
                        ticketJ.date_expiration.mois=day.mardi.dateDuJour.mois;
                        ticketJ.date_expiration.annee=day.mardi.dateDuJour.annee;
                        strcpy(ticketJ.repasT.meal,"Dejeuner");
                        ticketJ.repasT.menu1=1;
                        ticketJ.repasT.menu2=0;
                        //add ticket
                        user.panier[index]=ticketJ;
                        index++;
                        //payment phase
                        user.solde--;
                    } else if (dej==2){
                        ticketJ.date_expiration.jour=day.mardi.dateDuJour.jour;
                        ticketJ.date_expiration.mois=day.mardi.dateDuJour.mois;
                        ticketJ.date_expiration.annee=day.mardi.dateDuJour.annee;
                        strcpy(ticketJ.repasT.meal,"Dejeuner");
                        ticketJ.repasT.menu2=1;
                        ticketJ.repasT.menu1=0;
                        //add ticket
                        user.panier[index]=ticketJ;
                        index++;
                        //payment phase
                        user.solde--;
                    }

                    printf("Choisir menu 1 ou 2 pour le diner clickez n'importe quel chiffre si aucun : ");
                    scanf("%d",&diner);
                    if (diner==1){
                        //Create ticket
                        ticketJ.date_expiration.jour=day.mardi.dateDuJour.jour;
                        ticketJ.date_expiration.mois=day.mardi.dateDuJour.mois;
                        ticketJ.date_expiration.annee=day.mardi.dateDuJour.annee;
                        strcpy(ticketJ.repasT.meal,"Diner");
                        ticketJ.repasT.menu1=1;
                        ticketJ.repasT.menu2=0;
                        //add ticket
                        user.panier[index]=ticketJ;
                        index++;
                        //payment phase
                        user.solde--;
                    } else if (diner==2){
                        ticketJ.date_expiration.jour=day.mardi.dateDuJour.jour;
                        ticketJ.date_expiration.mois=day.mardi.dateDuJour.mois;
                        ticketJ.date_expiration.annee=day.mardi.dateDuJour.annee;
                        strcpy(ticketJ.repasT.meal,"Diner");
                        ticketJ.repasT.menu2=1;
                        ticketJ.repasT.menu1=0;
                        //add ticket
                        user.panier[index]=ticketJ;
                        index++;
                        //payment phase
                        user.solde--;
                    }
                    break;
                case 3 :
                    printf("Choisir menu 1 ou 2 pour le petit dejeuner clickez n'importe quel chiffre si aucun : ");
                    scanf("%d",&petitDej);
                    if (petitDej==1){
                        //Create ticket
                        ticketJ.date_expiration.jour=day.mercredi.dateDuJour.jour;
                        ticketJ.date_expiration.mois=day.mercredi.dateDuJour.mois;
                        ticketJ.date_expiration.annee=day.mercredi.dateDuJour.annee;
                        strcpy(ticketJ.repasT.meal,"petitDej");
                        ticketJ.repasT.menu1=1;
                        ticketJ.repasT.menu2=0;
                        //add ticket
                        user.panier[index]=ticketJ;
                        index++;
                        //payment phase
                        user.solde--;
                    } else if (petitDej==2){
                        ticketJ.date_expiration.jour=day.mercredi.dateDuJour.jour;
                        ticketJ.date_expiration.mois=day.mercredi.dateDuJour.mois;
                        ticketJ.date_expiration.annee=day.mercredi.dateDuJour.annee;
                        strcpy(ticketJ.repasT.meal,"petitDej");
                        ticketJ.repasT.menu2=1;
                        ticketJ.repasT.menu1=0;
                        //add ticket
                        user.panier[index]=ticketJ;
                        index++;
                        //payment phase
                        user.solde--;
                    }

                    printf("Choisir menu 1 ou 2 pour le dejeuner clickez n'importe quel chiffre si aucun : ");
                    scanf("%d",&dej);
                    if (dej==1){
                        //Create ticket
                        ticketJ.date_expiration.jour=day.mercredi.dateDuJour.jour;
                        ticketJ.date_expiration.mois=day.mercredi.dateDuJour.mois;
                        ticketJ.date_expiration.annee=day.mercredi.dateDuJour.annee;
                        strcpy(ticketJ.repasT.meal,"Dejeuner");
                        ticketJ.repasT.menu1=1;
                        ticketJ.repasT.menu2=0;
                        //add ticket
                        user.panier[index]=ticketJ;
                        index++;
                        //payment phase
                        user.solde--;
                    } else if (dej==2){
                        ticketJ.date_expiration.jour=day.mercredi.dateDuJour.jour;
                        ticketJ.date_expiration.mois=day.mercredi.dateDuJour.mois;
                        ticketJ.date_expiration.annee=day.mercredi.dateDuJour.annee;
                        strcpy(ticketJ.repasT.meal,"Dejeuner");
                        ticketJ.repasT.menu2=1;
                        ticketJ.repasT.menu1=0;
                        //add ticket
                        user.panier[index]=ticketJ;
                        index++;
                        //payment phase
                        user.solde--;
                    }

                    printf("Choisir menu 1 ou 2 pour le diner clickez n'importe quel chiffre si aucun : ");
                    scanf("%d",&diner);
                    if (diner==1){
                        //Create ticket
                        ticketJ.date_expiration.jour=day.mercredi.dateDuJour.jour;
                        ticketJ.date_expiration.mois=day.mercredi.dateDuJour.mois;
                        ticketJ.date_expiration.annee=day.mercredi.dateDuJour.annee;
                        strcpy(ticketJ.repasT.meal,"Diner");
                        ticketJ.repasT.menu1=1;
                        ticketJ.repasT.menu2=0;
                        //add ticket
                        user.panier[index]=ticketJ;
                        index++;
                        //payment phase
                        user.solde--;
                    } else if (diner==2){
                        ticketJ.date_expiration.jour=day.mercredi.dateDuJour.jour;
                        ticketJ.date_expiration.mois=day.mercredi.dateDuJour.mois;
                        ticketJ.date_expiration.annee=day.mercredi.dateDuJour.annee;
                        strcpy(ticketJ.repasT.meal,"Diner");
                        ticketJ.repasT.menu2=1;
                        ticketJ.repasT.menu1=0;
                        //add ticket
                        user.panier[index]=ticketJ;
                        index++;
                        //payment phase
                        user.solde--;
                    }
                    break;
                case 4 :
                    printf("Choisir menu 1 ou 2 pour le petit dejeuner clickez n'importe quel chiffre si aucun : ");
                    scanf("%d",&petitDej);
                    if (petitDej==1){
                        //Create ticket
                        ticketJ.date_expiration.jour=day.jeudi.dateDuJour.jour;
                        ticketJ.date_expiration.mois=day.jeudi.dateDuJour.mois;
                        ticketJ.date_expiration.annee=day.jeudi.dateDuJour.annee;
                        strcpy(ticketJ.repasT.meal,"petitDej");
                        ticketJ.repasT.menu1=1;
                        ticketJ.repasT.menu2=0;
                        //add ticket
                        user.panier[index]=ticketJ;
                        index++;
                        //payment phase
                        user.solde--;
                    } else if (petitDej==2){
                        ticketJ.date_expiration.jour=day.jeudi.dateDuJour.jour;
                        ticketJ.date_expiration.mois=day.jeudi.dateDuJour.mois;
                        ticketJ.date_expiration.annee=day.jeudi.dateDuJour.annee;
                        strcpy(ticketJ.repasT.meal,"petitDej");
                        ticketJ.repasT.menu2=1;
                        ticketJ.repasT.menu1=0;
                        //add ticket
                        user.panier[index]=ticketJ;
                        index++;
                        //payment phase
                        user.solde--;
                    }

                    printf("Choisir menu 1 ou 2 pour le dejeuner clickez n'importe quel chiffre si aucun : ");
                    scanf("%d",&dej);
                    if (dej==1){
                        //Create ticket
                        ticketJ.date_expiration.jour=day.jeudi.dateDuJour.jour;
                        ticketJ.date_expiration.mois=day.jeudi.dateDuJour.mois;
                        ticketJ.date_expiration.annee=day.jeudi.dateDuJour.annee;
                        strcpy(ticketJ.repasT.meal,"Dejeuner");
                        ticketJ.repasT.menu1=1;
                        ticketJ.repasT.menu2=0;
                        //add ticket
                        user.panier[index]=ticketJ;
                        index++;
                        //payment phase
                        user.solde--;
                    } else if (dej==2){
                        ticketJ.date_expiration.jour=day.jeudi.dateDuJour.jour;
                        ticketJ.date_expiration.mois=day.jeudi.dateDuJour.mois;
                        ticketJ.date_expiration.annee=day.jeudi.dateDuJour.annee;
                        strcpy(ticketJ.repasT.meal,"Dejeuner");
                        ticketJ.repasT.menu2=1;
                        ticketJ.repasT.menu1=0;
                        //add ticket
                        user.panier[index]=ticketJ;
                        index++;
                        //payment phase
                        user.solde--;
                    }

                    printf("Choisir menu 1 ou 2 pour le diner clickez n'importe quel chiffre si aucun : ");
                    scanf("%d",&diner);
                    if (diner==1){
                        //Create ticket
                        ticketJ.date_expiration.jour=day.jeudi.dateDuJour.jour;
                        ticketJ.date_expiration.mois=day.jeudi.dateDuJour.mois;
                        ticketJ.date_expiration.annee=day.jeudi.dateDuJour.annee;
                        strcpy(ticketJ.repasT.meal,"Diner");
                        ticketJ.repasT.menu1=1;
                        ticketJ.repasT.menu2=0;
                        //add ticket
                        user.panier[index]=ticketJ;
                        index++;
                        //payment phase
                        user.solde--;
                    } else if (diner==2){
                        ticketJ.date_expiration.jour=day.jeudi.dateDuJour.jour;
                        ticketJ.date_expiration.mois=day.jeudi.dateDuJour.mois;
                        ticketJ.date_expiration.annee=day.jeudi.dateDuJour.annee;
                        strcpy(ticketJ.repasT.meal,"Diner");
                        ticketJ.repasT.menu2=1;
                        ticketJ.repasT.menu1=0;
                        //add ticket
                        user.panier[index]=ticketJ;
                        index++;
                        //payment phase
                        user.solde--;
                    }
                    break;
                case 5 :
                    printf("Choisir menu 1 ou 2 pour le petit dejeuner clickez n'importe quel chiffre si aucun : ");
                    scanf("%d",&petitDej);
                    if (petitDej==1){
                        //Create ticket
                        ticketJ.date_expiration.jour=day.vendredi.dateDuJour.jour;
                        ticketJ.date_expiration.mois=day.vendredi.dateDuJour.mois;
                        ticketJ.date_expiration.annee=day.vendredi.dateDuJour.annee;
                        strcpy(ticketJ.repasT.meal,"petitDej");
                        ticketJ.repasT.menu1=1;
                        ticketJ.repasT.menu2=0;
                        //add ticket
                        user.panier[index]=ticketJ;
                        index++;
                        //payment phase
                        user.solde--;
                    } else if (petitDej==2){
                        ticketJ.date_expiration.jour=day.vendredi.dateDuJour.jour;
                        ticketJ.date_expiration.mois=day.vendredi.dateDuJour.mois;
                        ticketJ.date_expiration.annee=day.vendredi.dateDuJour.annee;
                        strcpy(ticketJ.repasT.meal,"petitDej");
                        ticketJ.repasT.menu2=1;
                        ticketJ.repasT.menu1=0;
                        //add ticket
                        user.panier[index]=ticketJ;
                        index++;
                        //payment phase
                        user.solde--;
                    }

                    printf("Choisir menu 1 ou 2 pour le dejeuner clickez n'importe quel chiffre si aucun : ");
                    scanf("%d",&dej);
                    if (dej==1){
                        //Create ticket
                        ticketJ.date_expiration.jour=day.vendredi.dateDuJour.jour;
                        ticketJ.date_expiration.mois=day.vendredi.dateDuJour.mois;
                        ticketJ.date_expiration.annee=day.vendredi.dateDuJour.annee;
                        strcpy(ticketJ.repasT.meal,"Dejeuner");
                        ticketJ.repasT.menu1=1;
                        ticketJ.repasT.menu2=0;
                        //add ticket
                        user.panier[index]=ticketJ;
                        index++;
                        //payment phase
                        user.solde--;
                    } else if (dej==2){
                        ticketJ.date_expiration.jour=day.vendredi.dateDuJour.jour;
                        ticketJ.date_expiration.mois=day.vendredi.dateDuJour.mois;
                        ticketJ.date_expiration.annee=day.vendredi.dateDuJour.annee;
                        strcpy(ticketJ.repasT.meal,"Dejeuner");
                        ticketJ.repasT.menu2=1;
                        ticketJ.repasT.menu1=0;
                        //add ticket
                        user.panier[index]=ticketJ;
                        index++;
                        //payment phase
                        user.solde--;
                    }

                    printf("Choisir menu 1 ou 2 pour le diner clickez n'importe quel chiffre si aucun : ");
                    scanf("%d",&diner);
                    if (diner==1){
                        //Create ticket
                        ticketJ.date_expiration.jour=day.vendredi.dateDuJour.jour;
                        ticketJ.date_expiration.mois=day.vendredi.dateDuJour.mois;
                        ticketJ.date_expiration.annee=day.vendredi.dateDuJour.annee;
                        strcpy(ticketJ.repasT.meal,"Diner");
                        ticketJ.repasT.menu1=1;
                        ticketJ.repasT.menu2=0;
                        //add ticket
                        user.panier[index]=ticketJ;
                        index++;
                        //payment phase
                        user.solde--;
                    } else if (diner==2){
                        ticketJ.date_expiration.jour=day.vendredi.dateDuJour.jour;
                        ticketJ.date_expiration.mois=day.vendredi.dateDuJour.mois;
                        ticketJ.date_expiration.annee=day.vendredi.dateDuJour.annee;
                        strcpy(ticketJ.repasT.meal,"Diner");
                        ticketJ.repasT.menu2=1;
                        ticketJ.repasT.menu1=0;
                        //add ticket
                        user.panier[index]=ticketJ;
                        index++;
                        //payment phase
                        user.solde--;
                    }
                    break;
                case 6 :
                    printf("Choisir menu 1 ou 2 pour le petit dejeuner clickez n'importe quel chiffre si aucun : ");
                    scanf("%d",&petitDej);
                    if (petitDej==1){
                        //Create ticket
                        ticketJ.date_expiration.jour=day.samedi.dateDuJour.jour;
                        ticketJ.date_expiration.mois=day.samedi.dateDuJour.mois;
                        ticketJ.date_expiration.annee=day.samedi.dateDuJour.annee;
                        strcpy(ticketJ.repasT.meal,"petitDej");
                        ticketJ.repasT.menu1=1;
                        ticketJ.repasT.menu2=0;
                        //add ticket
                        user.panier[index]=ticketJ;
                        index++;
                        //payment phase
                        user.solde--;
                    } else if (petitDej==2){
                        ticketJ.date_expiration.jour=day.samedi.dateDuJour.jour;
                        ticketJ.date_expiration.mois=day.samedi.dateDuJour.mois;
                        ticketJ.date_expiration.annee=day.samedi.dateDuJour.annee;
                        strcpy(ticketJ.repasT.meal,"petitDej");
                        ticketJ.repasT.menu2=1;
                        ticketJ.repasT.menu1=0;
                        //add ticket
                        user.panier[index]=ticketJ;
                        index++;
                        //payment phase
                        user.solde--;
                    }

                    printf("Choisir menu 1 ou 2 pour le dejeuner clickez n'importe quel chiffre si aucun : ");
                    scanf("%d",&dej);
                    if (dej==1){
                        //Create ticket
                        ticketJ.date_expiration.jour=day.samedi.dateDuJour.jour;
                        ticketJ.date_expiration.mois=day.samedi.dateDuJour.mois;
                        ticketJ.date_expiration.annee=day.samedi.dateDuJour.annee;
                        strcpy(ticketJ.repasT.meal,"Dejeuner");
                        ticketJ.repasT.menu1=1;
                        ticketJ.repasT.menu2=0;
                        //add ticket
                        user.panier[index]=ticketJ;
                        index++;
                        //payment phase
                        user.solde--;
                    } else if (dej==2){
                        ticketJ.date_expiration.jour=day.samedi.dateDuJour.jour;
                        ticketJ.date_expiration.mois=day.samedi.dateDuJour.mois;
                        ticketJ.date_expiration.annee=day.samedi.dateDuJour.annee;
                        strcpy(ticketJ.repasT.meal,"Dejeuner");
                        ticketJ.repasT.menu2=1;
                        ticketJ.repasT.menu1=0;
                        //add ticket
                        user.panier[index]=ticketJ;
                        index++;
                        //payment phase
                        user.solde--;
                    }

                    printf("Choisir menu 1 ou 2 pour le diner clickez n'importe quel chiffre si aucun : ");
                    scanf("%d",&diner);
                    if (diner==1){
                        //Create ticket
                        ticketJ.date_expiration.jour=day.samedi.dateDuJour.jour;
                        ticketJ.date_expiration.mois=day.samedi.dateDuJour.mois;
                        ticketJ.date_expiration.annee=day.samedi.dateDuJour.annee;
                        strcpy(ticketJ.repasT.meal,"Diner");
                        ticketJ.repasT.menu1=1;
                        ticketJ.repasT.menu2=0;
                        //add ticket
                        user.panier[index]=ticketJ;
                        index++;
                        //payment phase
                        user.solde--;
                    } else if (diner==2){
                        ticketJ.date_expiration.jour=day.samedi.dateDuJour.jour;
                        ticketJ.date_expiration.mois=day.samedi.dateDuJour.mois;
                        ticketJ.date_expiration.annee=day.samedi.dateDuJour.annee;
                        strcpy(ticketJ.repasT.meal,"Diner");
                        ticketJ.repasT.menu2=1;
                        ticketJ.repasT.menu1=0;
                        //add ticket
                        user.panier[index]=ticketJ;
                        index++;
                        //payment phase
                        user.solde--;
                    }
                    break;
                case 7 :
                    printf("Choisir menu 1 ou 2 pour le petit dejeuner clickez n'importe quel chiffre si aucun : ");
                    scanf("%d",&petitDej);
                    if (petitDej==1){
                        //Create ticket
                        ticketJ.date_expiration.jour=day.dimanche.dateDuJour.jour;
                        ticketJ.date_expiration.mois=day.dimanche.dateDuJour.mois;
                        ticketJ.date_expiration.annee=day.dimanche.dateDuJour.annee;
                        strcpy(ticketJ.repasT.meal,"petitDej");
                        ticketJ.repasT.menu1=1;
                        ticketJ.repasT.menu2=0;
                        //add ticket
                        user.panier[index]=ticketJ;
                        index++;
                        //payment phase
                        user.solde--;
                    } else if (petitDej==2){
                        ticketJ.date_expiration.jour=day.dimanche.dateDuJour.jour;
                        ticketJ.date_expiration.mois=day.dimanche.dateDuJour.mois;
                        ticketJ.date_expiration.annee=day.dimanche.dateDuJour.annee;
                        strcpy(ticketJ.repasT.meal,"petitDej");
                        ticketJ.repasT.menu2=1;
                        ticketJ.repasT.menu1=0;
                        //add ticket
                        user.panier[index]=ticketJ;
                        index++;
                        //payment phase
                        user.solde--;
                    }

                    printf("Choisir menu 1 ou 2 pour le dejeuner clickez n'importe quel chiffre si aucun : ");
                    scanf("%d",&dej);
                    if (dej==1){
                        //Create ticket
                        ticketJ.date_expiration.jour=day.dimanche.dateDuJour.jour;
                        ticketJ.date_expiration.mois=day.dimanche.dateDuJour.mois;
                        ticketJ.date_expiration.annee=day.dimanche.dateDuJour.annee;
                        strcpy(ticketJ.repasT.meal,"Dejeuner");
                        ticketJ.repasT.menu1=1;
                        ticketJ.repasT.menu2=0;
                        //add ticket
                        user.panier[index]=ticketJ;
                        index++;
                        //payment phase
                        user.solde--;
                    } else if (dej==2){
                        ticketJ.date_expiration.jour=day.dimanche.dateDuJour.jour;
                        ticketJ.date_expiration.mois=day.dimanche.dateDuJour.mois;
                        ticketJ.date_expiration.annee=day.dimanche.dateDuJour.annee;
                        strcpy(ticketJ.repasT.meal,"Dejeuner");
                        ticketJ.repasT.menu2=1;
                        ticketJ.repasT.menu1=0;
                        //add ticket
                        user.panier[index]=ticketJ;
                        index++;
                        //payment phase
                        user.solde--;
                    }

                    printf("Choisir menu 1 ou 2 pour le diner clickez n'importe quel chiffre si aucun : ");
                    scanf("%d",&diner);
                    if (diner==1){
                        //Create ticket
                        ticketJ.date_expiration.jour=day.dimanche.dateDuJour.jour;
                        ticketJ.date_expiration.mois=day.dimanche.dateDuJour.mois;
                        ticketJ.date_expiration.annee=day.dimanche.dateDuJour.annee;
                        strcpy(ticketJ.repasT.meal,"Diner");
                        ticketJ.repasT.menu1=1;
                        ticketJ.repasT.menu2=0;
                        //add ticket
                        user.panier[index]=ticketJ;
                        index++;
                        //payment phase
                        user.solde--;
                    } else if (diner==2){
                        ticketJ.date_expiration.jour=day.dimanche.dateDuJour.jour;
                        ticketJ.date_expiration.mois=day.dimanche.dateDuJour.mois;
                        ticketJ.date_expiration.annee=day.dimanche.dateDuJour.annee;
                        strcpy(ticketJ.repasT.meal,"Diner");
                        ticketJ.repasT.menu2=1;
                        ticketJ.repasT.menu1=0;
                        //add ticket
                        user.panier[index]=ticketJ;
                        index++;
                        //payment phase
                        user.solde--;
                    }
                    break;
                }
                //Prendre plus de tickets
                printf("\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
                printf("Voulez vous prendre d'autre tickets pour le meme jour? 0oui/1non => ");
                scanf("%d", &answer);
                if (answer==0){
                    repeat=true;
                } else {
                    repeat=false;
                }
                system("cls");
            }
            //reset repeat button
            repeat=true;
            //bouton Retour vers la page rubrique
            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
            printf("\nVoulez-vous retourner a la page rubrique ? 0oui/1non => ");
            scanf("%d", &return_answ);
            if (return_answ==1) {
                but_return=false;
            }
            printf("\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
            break;
        }
    }
    system("cls");

}


