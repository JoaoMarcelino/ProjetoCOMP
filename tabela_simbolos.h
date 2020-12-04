#ifndef TABELA_SIMBOLOS_H
#define TABELA_SIMBOLOS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "functions.h"

typedef struct nodeTable * tableNode;
typedef struct nodeTable{

    char *name;
    char *type;
    char *params[4];

    tableNode next;
    tableNode child;
}nodet;



void globalTable(nodeptr);
void analiseTree(nodeptr , tableNode );
tableNode insert(tableNode , char *, char *, char *arr[]);
void printTable(tableNode);
void printParam(char *arr[], int );


#endif