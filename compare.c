//
// Created by louis on 08/11/2020.
//
#include "compare.h"

int compare(struct Tag *tag, struct DtdTag *dtdTag) {

    if (!checkTagName(tag->start, tag->end, dtdTag->tagName)) return 0;
    if (!checkAttributs(tag->attributs, tag->attributsAmount, dtdTag->attributs, dtdTag->attributsAmount)) return 0;

    if (dtdTag->childsAmount > 0) {
        return compareChilds(tag, dtdTag);
    }
    return 1;
}

int compareChilds(struct Tag *tag, struct DtdTag *dtdTag) {

    int find; //defini si on a trouvé un correspondance entre le tag et une dtd, permet de renvoyer 0 si on a pas trouver de cmparaison possible

    for (int i = 0; i < tag->childsAmount; ++i) {
        find = 0;
        for (int j = 0; j < dtdTag->childsAmount; ++j) {
            
            if (checkTagName(tag->childTags[i]->start, tag->childTags[i]->end,
                             dtdTag->childTags[j]->tagName)) { //find a corresponding dtd for each child
                find = 1;

                struct Tag *tagToCheck = tag->childTags[i];
                struct DtdTag *dtdToCheck = dtdTag->childTags[j];

                if (!checkAttributs(tagToCheck->attributs, tagToCheck->attributsAmount, dtdToCheck->attributs,
                                    dtdToCheck->attributsAmount))
                    return 0;

                if (tag->childsAmount > 0) { //si il a des enfants on les checks car c'est une balise parent
                    if (!compareChilds(tagToCheck, dtdToCheck)) return 0;
                } else { //pas d'enfants donc on check son content car c'est une balise enfant
                    if (!checkContent(tagToCheck->content, dtdToCheck->contentType)) return 0;
                }

            }
        }
        if (!find) {
            return 0;
        }
    }

    return 1;
}

int checkTagName(char *start, char *end, char *tagName) {
    if (strstr(start, tagName) == NULL) return 1; //check in both way
    if (strstr(tagName, start) == NULL) return 0; //check in both way
    if (strstr(end, tagName) == NULL) return 0; //check in both way
    if (strstr(tagName, end) == NULL) return 0; //check in both way

    return 1;
}

int checkAttributs(struct Attr **attrList, int sizeAttr, struct DtdAttr **dtdAttrList, int sizeDtdAttr) {

    int find;

    for (int i = 0; i < sizeAttr; ++i) {
        find = 0;
        for (int j = 0; j < sizeDtdAttr; ++j) {
            if (checkAttrName(attrList[i]->name, dtdAttrList[j]->name)) {
                find = 1;

                if (!checkAttrValue(attrList[i]->value, dtdAttrList[i])) return 0;

            }
        }
        if (!find) return 0; //pas trouvé d'occurrence
    }

    return 1;
}

int checkAttrName(char *attrName, char *dtdAttrName) {
    if (strstr(attrName, dtdAttrName) == NULL) return 0; //check in both way
    if (strstr(dtdAttrName, attrName) == NULL) return 0; //check in both way
    return 1;
}

int checkAttrValue(char *value, struct DtdAttr *dtdAttr) {
    if (strlen(value) == 0) {
        if (dtdAttr->obligation == 1) return 0;
    }
    else {
        if (dtdAttr->valuesSize > 0) {
            if (!checkAttrValues(value, dtdAttr->values, dtdAttr->valuesSize)) return 0;
        }
        else {
            if (!checkAttrType(value, dtdAttr->type)) return 0;
        }
    }
    return 1;
}


int checkAttrValues(char *value, char ** values, int valuesSize) {

    for (int i = 0; i < valuesSize; ++i) {
        if (strstr(value, values[i]) && strstr(values[i], value)) return 1;
    }

    return 0;
}

int checkAttrType(char *value, char *type){
    //if (strstr(type, "CDATA")) return 1;
    if (strstr(type, "NMTOKEN")) {
        if (strstr(value, " ")) return 0;
    }
    else if (strstr(type, "IDREF")) {
        if (!inId(value)) return 0;
    }
    else if (strstr(type, "ID")) {
        if (inId(value)) return 0;
        else addId(value);
    }

    return 1;
}

int inId(char *value) {
    if (ids->size == 0) return 0;

    for (int i = 0; i < ids->size; ++i) {
        if (strstr(ids->ids[i], value)) {
            return 1;
        }
    }

    return 0;
}

void addId(char *value) {

    char **newIds = malloc(sizeof(char *) * ids->size+1);

    //copy anciens éléments
    for (int i = 0; i < ids->size; ++i) {
        newIds[i] = malloc(sizeof(char) * strlen(ids->ids[i]));
        strcpy(newIds[i], ids->ids[i]);
    }

    //nouvel élément
    ids->size += 1;
    newIds[ids->size-1] = malloc(sizeof(char) * strlen(value));
    strcpy(newIds[ids->size-1], value);

    free(ids->ids);
    ids->ids = newIds;
}

int checkContent(char *content, char *contentType) {
    if (strstr(contentType, "EMPTY")) {
        if (strlen(content) > 0) return 0;
    }
    //#PCDATA et ANY pas pris en compte pour le moment

    return 1;
}


