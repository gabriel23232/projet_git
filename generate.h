//
// Created by louis on 08/11/2020.
//
#ifndef PISCINEC_GENERATE_H
#define PISCINEC_GENERATE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Tag {
    char * start;
    struct Attr ** attributs;
    int attributsAmount;
    char * content;
    char * end;
    struct Tag ** childTags; //array of child tag structs
    int childsAmount;
} Tag;

struct DtdTag {
    char * tagName;
    struct DtdAttr ** attributs;
    int attributsAmount;
    struct DtdTag ** childTags; //array of child dtdTag structs
    int childsAmount;
    char * contentType;
    int obligation; //0 or more, 1 and 1 only
} DtdTag;

struct DtdAttr {
    char * name;
    char ** values;
    int valuesSize;
    char * type; //keep empty if values et and define type if no determined values
    int obligation; //0 or more, 1 need a value cant be empty
    char * defaultValue;
} DtdAttr;

struct Attr {
    char * name;
    char * value;
} Attr;

struct Tag *createTag(char * start, struct Attr ** attrList, int AttrAmount, struct Tag **childList, int childAmount, char* content, char *end);
struct DtdTag *createDtdTag(char *tagName, struct DtdAttr ** dtdAttrList, int dtdAttrAmount, struct DtdTag **childs, int childsAmount, char *contentType, int obligation);
struct DtdAttr *createDtdAttr(char *name, char ** values, int valuesSize, char * type);
struct Attr *createAttr(char* name, char* value);
struct DtdAttr **createDtdAttrList(char *tagName);
struct Attr **createAttrList();

#endif //PISCINEC_GENERATE_H
