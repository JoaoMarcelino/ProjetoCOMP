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



char * fuckC(char *);

void globalTable(nodeptr);

tableNode insert(tableNode , char *, char *, paramNode);
void printTable(tableNode, char *);
void printParam(paramNode, int );

tableNode analiseTree(nodeptr , tableNode );
tableNode analiseDefinition(nodeptr, tableNode );
tableNode analiseDeclaration(nodeptr, tableNode );
#endif