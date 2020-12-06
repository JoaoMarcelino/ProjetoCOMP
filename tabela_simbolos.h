#ifndef TABELA_SIMBOLOS_H
#define TABELA_SIMBOLOS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "functions.h"

typedef struct nodeParam * paramNode;
typedef struct nodeParam{

    char *name;
    paramNode next;

}nodep;

typedef struct nodeTable * tableNode;
typedef struct nodeTable{

    char *name;
    char *type;
    paramNode paramList;

    tableNode next;
    tableNode child;
}nodet;





void globalTable(nodeptr);

tableNode insert(tableNode , char *, char *, paramNode);
void printTable(tableNode);
void printParam(paramNode, int );

void analiseTree(nodeptr , tableNode );
void analiseDeclaration(nodeptr, tableNode );
void analiseDefinition(nodeptr, tableNode );

#endif