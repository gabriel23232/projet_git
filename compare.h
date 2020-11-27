//
// Created by louis on 08/11/2020.
//

#ifndef PISCINEC_COMPARE_H
#define PISCINEC_COMPARE_H

#include "generate.h"

struct Ids {
    char ** ids;
    int size;
} Ids;

struct Ids * ids;

int compare(struct Tag *, struct DtdTag *);

int compareChilds(struct Tag *tag, struct DtdTag *dtdTag);

int checkTagName(char *, char *, char *);

int checkAttributs(struct Attr**, int size, struct DtdAttr **, int sizeDtdAttr);
int checkAttrName(char *attrName, char *dtdAttrName);
int checkAttrValue(char *value, struct DtdAttr *dtdAttr);
int checkAttrValues(char *value, char ** values, int valuesSize);
int checkAttrType(char *value, char *type);
int inId(char*value);
void addId(char *value);

int checkContent(char * content, char * contentType);

#endif //PISCINEC_COMPARE_H
