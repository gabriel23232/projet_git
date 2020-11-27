//
// Created by louis on 08/11/2020.
//
#include "generate.h"

struct DtdAttr *createDtdAttr(char *name, char ** values, int valuesSize, char * type) {
    struct DtdAttr *newDtdAttr = malloc(sizeof(DtdAttr));

    newDtdAttr->name = malloc(sizeof(char) * strlen(name));
    strcpy(newDtdAttr->name, name);

    if (valuesSize > 0) {
        newDtdAttr->type = NULL;
        newDtdAttr->valuesSize = valuesSize;
        newDtdAttr->values = malloc(sizeof(char *) * valuesSize);
        for (int i = 0; i < valuesSize; ++i) {
            newDtdAttr->values[i] = malloc(sizeof(char) * strlen(values[i]));
            strcpy(newDtdAttr->values[i], values[i]);
        }
    }
    else {
        newDtdAttr->type = malloc(sizeof(char) * 50);
        strcpy(newDtdAttr->type, type);
        newDtdAttr->values = NULL;
        newDtdAttr->valuesSize = 0;
    }

    newDtdAttr->obligation = 1;

    return newDtdAttr;
}

struct DtdAttr ** createDtdAttrList(char * tagName) {

    if (strstr(tagName, "bonjour")) {
        struct DtdAttr **attrList = malloc(sizeof(DtdAttr) * 2);

        attrList[0] = createDtdAttr("prenom", NULL, 0, "CDATA");
        attrList[1] = createDtdAttr("question", NULL, 0, "CDATA");

        return attrList;
    }
    if (strstr(tagName, "foot")) {
        struct DtdAttr **attrList = malloc(sizeof(DtdAttr));

        attrList[0] = createDtdAttr("equipe", NULL, 0, "CDATA");

        return attrList;
    }
    if (strstr(tagName, "etrange")) {
        struct DtdAttr **attrList = malloc(sizeof(DtdAttr));

        attrList[0] = createDtdAttr("vrai", NULL, 0, "CDATA");

        return attrList;
    }
}

struct Tag * createTag(char * start, struct Attr ** attrList, int attrAmount, struct Tag **childList, int childAmount, char * content, char * end) {
    struct Tag * newTag = malloc(sizeof(Tag));

    newTag->start = malloc(sizeof(char) * strlen(start));
    strcpy(newTag->start, start);

    newTag->attributsAmount = attrAmount;
    newTag->attributs = attrList;

    newTag->childTags = childList;
    newTag->childsAmount = childAmount;

    newTag->content = malloc(sizeof(char) * strlen(content));
    strcpy(newTag->content, content);

    newTag->end = malloc(sizeof(char) * strlen(end));
    strcpy(newTag->end, end);

    return newTag;
}

struct Attr ** createAttrList(int nbAttr) {

    struct Attr **attrList = malloc(sizeof(Attr) * nbAttr);

    attrList[0] = createAttr("name", "Charles");
    attrList[1] = createAttr("name", "Jack");

    return attrList;
}

struct Attr *createAttr(char* name, char* value) {
    struct Attr * newAttr = malloc(sizeof(Attr));

    newAttr->name = malloc(sizeof(char) * strlen(name));
    strcpy(newAttr->name, name);
    newAttr->value = malloc(sizeof(char) * strlen(value));
    strcpy(newAttr->value, value);

    return newAttr;
}

struct DtdTag *createDtdTag(char *tagName, struct DtdAttr ** dtdAttrList, int dtdAttrAmount, struct DtdTag **childs, int childsAmount, char *contentType, int obligation) {
    struct DtdTag *dtdTag = malloc(sizeof(DtdTag));

    dtdTag->tagName = malloc(sizeof(char*) * strlen(tagName));
    strcpy(dtdTag->tagName, tagName);

    dtdTag->attributsAmount = dtdAttrAmount;
    //dtdTag->attributs = malloc(sizeof(DtdAttr) * dtdAttrAmount);
    dtdTag->attributs = dtdAttrList;

    dtdTag->childsAmount = childsAmount;
    dtdTag->childTags = childs;

    dtdTag->contentType = malloc(sizeof(char) * strlen(contentType));
    strcpy(dtdTag->contentType, contentType);

    dtdTag->obligation = obligation;

    return dtdTag;
}


