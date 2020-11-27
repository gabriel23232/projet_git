//
// Created by Gabriel on 25/11/2020.
//
#include "readXml.h"

void fermetureFichier(FILE* f){
    fclose(f);
    printf(" \n Fermeture du fichier!\n");
}

void baliseOuvrante(FILE *f, struct Tag *tab){ // detection de la balise ouvrante et stockage du nom de la balise
    char a = (char)fgetc(f);
    char nomBalise[50]; // variable temporaire de stockage d'information
    int compteur = 0;
    int posedeAtt=0; // 0 si faux, 1 si vrai
    while ( a != '<'){ // recherche balise d'ouverture
        a = (char)fgetc(f);
    }
    char c = (char)fgetc(f);
    while ( c != '>'){
        nomBalise[compteur]=c;
        compteur++;
        c = (char)fgetc(f);

        if(c==' ' && posedeAtt == 0)
        {
            posedeAtt=1;
            nomBalise[compteur]='\0';
        }
        if(posedeAtt==1)
        {
            tab->start = malloc(sizeof(char )* strlen(nomBalise));
            strcpy(tab->start ,nomBalise);
            compteur = 0;
            posedeAtt = 2;
        }
    }
    nomBalise[compteur] = '\0';
    if( posedeAtt==0){
        tab->start = malloc(sizeof(char )* strlen(nomBalise));
        strcpy(tab->start ,nomBalise);
    }else{
        char * tempo = nomBalise;
        decoupeAttribut(f,tempo, tab, compteur);
    }
}

void lecturecontent(FILE *f, struct Tag *tab){ // lecture des donnée jusque detection de la balise de fermeture ( </ )
    char a = (char)fgetc(f);
    char content[30]; // variable temporaire de stockage d'information
    int i =0;
    while ( a != '<'){
        /* if(i==0 && content[i]== ' ')
         {
             a = (char)fgetc(f);

         }*/
        a = (char)fgetc(f);
        content[i] = a;

        i++;
    }
    content[i-2]='\0';
    tab->content = malloc(sizeof(char )* strlen(content));
    strcpy(tab->content ,content);

}

void decoupeAttribut(FILE *f, char *nomBalise ,struct Tag *tab, int longeur) {
    char nomAtt[30];
    char valeurAtt[30];
    int compteur = 0;
    int nombreAtt = 0;
    struct Attr tempo[10];

    int i = 0;
    int fin = 0;
    while (fin == 0|| i<longeur){
        while (nomBalise[i] != '=') {
            if (nomBalise[i] == '\0') {
                fin = 1;
            } else {
                i++;
                nomAtt[compteur] = nomBalise[i];
                compteur++;
            }
        }
        nomAtt[compteur-1]='\0';
        compteur = 0;
        while (nomBalise[i] != ' ') {
            if (nomBalise[i] == '\0' || nomBalise[i]=='>') {
                fin = 1;
                break;
            } else {
                i++;
                valeurAtt[compteur] = nomBalise[i];
                compteur++;
            }
        }
        valeurAtt[compteur]='\0';
        compteur = 0;
        struct Attr monAttr;
        // monAttr.name = nomAtt;
        //monAttr.value = valeurAtt;

        char *test = nomAtt;
        char  *teeest = valeurAtt;
        tempo[nombreAtt].name= (char *) test;
        tempo[nombreAtt].value= (char *) teeest;
        nombreAtt++;

    }
//
    tab->attributs = malloc(sizeof( Attr )* nombreAtt);
    for (int y=0; y<nombreAtt;y++)
    {
        struct Attr *attribut = malloc(sizeof(Attr));
        attribut->name = malloc(sizeof(char) * strlen(tempo[y].name));
        strcpy(attribut->name, tempo[y].name);
        attribut->value = malloc(sizeof(char) * strlen(tempo[y].value));
        strcpy(attribut->value, tempo[y].value);
        tab->attributs[y] = attribut;
    }
    tab->attributsAmount= nombreAtt;
}


void baliseFermante(FILE * f,struct Tag* tab){;
    char nomBalise[30];
    int compteur = 0;
    char c = (char)fgetc(f);
    while ( c != '>'){
        nomBalise[compteur]= c;
        compteur ++;
        c = (char)fgetc(f);
    }
    nomBalise[compteur]='\0';
    tab->end = malloc(sizeof(char *)* strlen(nomBalise));
    strcpy(tab->end,nomBalise);
}


void lectureFichier(FILE* f, struct Tag *tab){
    tab->childsAmount=0;
    tab->childTags=NULL;

    baliseOuvrante(f,tab);
    lecturecontent(f,tab);
    baliseFermante(f,tab);
}

void AfficherFichier(struct Tag *tab)
{
    printf(" \n %s", tab->start);
    printf(" \n %s", tab->content);
    printf(" \n %s", tab->end);
}
