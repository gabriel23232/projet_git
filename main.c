#include "generate.h"
#include "compare.h"
#include "readXml.h"


int main() {
    int fin = 0;
    int* finFichier = &fin;

    /*Tag rien;
    Tag *test = &rien; // tableau de struct*/

    FILE* f = fopen("../test.txt","r");
    struct Tag tab[10];
    int index = 0; // represente les index du tableau de struct
    struct Tag *pointeur = &tab[0];
    if (f!= NULL){
        printf("Le fichier est ouvert !\n");
    }else{
        printf("Probleme de l'ouverture du fichier!\n");
        return 0;
    }

    lectureFichier(f,pointeur);
    //AfficherFichier(pointeur);
    char c = ' ';
    //char c = (char)fgetc(f);
    int ligne = 0;
    while (c != EOF)
    {

        c = (char)fgetc(f);
       /* while ( c != EOF)
        {
            c = (char)fgetc(f);
        }*/
    if ( c == '\n')
    {
        ligne ++;
        pointeur = &tab[ligne];
        lectureFichier(f,pointeur);
        //AfficherFichier(pointeur);
    }

    }
    fermetureFichier(f);
  
  
    //init ids
    ids = malloc(sizeof(Ids));
    ids->size = 0;

    ligne+=1;
    //realloc because no malloc during read xml :'(
    struct Tag **childs = malloc(sizeof(Tag) * ligne);
    for (int i = 0; i < ligne; ++i) {
        childs[i] = malloc(sizeof(Tag));
        childs[i]->start = malloc(sizeof(char) * strlen(tab[i].start));
        strcpy(childs[i]->start, tab[i].start);

        childs[i]->end = malloc(sizeof(char) * strlen(tab[i].end));
        strcpy(childs[i]->end, tab[i].end);

        childs[i]->content = malloc(sizeof(char) * strlen(tab[i].content));
        strcpy(childs[i]->content, tab[i].content);

        childs[i]->attributs = malloc(sizeof(Attr) * tab[i].attributsAmount);
        for (int j = 0; j < tab[i].attributsAmount; ++j) {
            childs[i]->attributs[j] = malloc(sizeof(Attr));
            childs[i]->attributs[j]->name = malloc(sizeof(char) * strlen(tab[i].attributs[j]->name));
            strcpy(childs[i]->attributs[j]->name, tab[i].attributs[j]->name);

            childs[i]->attributs[j]->value = malloc(sizeof(char) * strlen(tab[i].attributs[j]->value));
            strcpy(childs[i]->attributs[j]->value, tab[i].attributs[j]->value);
        }
        childs[i]->childTags = NULL;
        childs[i]->childsAmount = 0;
    }

    //init parent because only one level read :'(
    struct Tag *parent = createTag("parent", NULL, 0, childs, ligne, "", "parent");

    //init dtd because no dtd reader :'(
    struct DtdTag **childList = malloc(sizeof(DtdTag) * 3);
    childList[0] = createDtdTag("bonjour", createDtdAttrList("bonjour"), 2, NULL, 0, "#PCDATA", 1);
    childList[1] = createDtdTag("foot", createDtdAttrList("foot"), 1, NULL, 0, "#PCDATA", 1);
    childList[2] = createDtdTag("etrange", createDtdAttrList("etrange"), 1, NULL, 0, "#PCDATA", 1);
    struct DtdTag *dtdParent = createDtdTag("parent", NULL, 0, childList, 3, "#PCDATA", 1);

    if (compare(parent, dtdParent)) {
        printf("\n========================\nVotre xml respect la dtd !\n========================\n");
    }
    else {
        printf("\n========================\nvotre xml ne respect pas la dtd !\n========================\n");
    }

    return 0;
}
