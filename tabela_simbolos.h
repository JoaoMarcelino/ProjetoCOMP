#ifndef TABELA_SIMBOLOS_H
#define TABELA_SIMBOLOS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "functions.h"

typedef struct nodeParam * paramNode;
typedef struct nodeParam{

    char *name;
    char *var;
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

tableNode insert(tableNode , char *, char *, paramNode , tableNode);
void printTable(tableNode, char *);
void printParam(paramNode);

tableNode analiseTree(nodeptr , tableNode );
tableNode analiseFunctionDefinition(nodeptr, tableNode );
tableNode analiseFunctionDeclaration(nodeptr, tableNode );
tableNode analiseDefinition(nodeptr , tableNode );
#endif