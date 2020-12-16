#ifndef TABELA_SIMBOLOS_H
#define TABELA_SIMBOLOS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct nodeTable * tableNode;
typedef struct nodeParam * paramNode;
typedef struct  node *nodeptr;

// FUNCTIONS.H

typedef struct node{
    char *id;
    char *type;
    
    tableNode table;

    nodeptr nodeNext;
    nodeptr nodeBrother;
    int value;
}Node;


void printTree(nodeptr , int );
void printPontos(int );
int needsStatList(nodeptr );


// TABELA_SIMBOLOS.H


typedef struct nodeParam{

    char *name;
    char *var;
    paramNode next;

}nodep;

typedef struct nodeTable{

    char *name;
    char *type;
    paramNode paramList;

    tableNode next;
    tableNode child;
}nodet;


char * fuckC(char *);

tableNode globalTable(nodeptr);
void printAST(nodeptr , nodeptr,  int , tableNode , tableNode );

tableNode insert(nodeptr ,tableNode , char *, char *, paramNode , tableNode);
void printTable(tableNode, char *);
void printParam(paramNode);

tableNode analiseTree(nodeptr , tableNode );
tableNode analiseFunctionDefinition(nodeptr, tableNode );
tableNode analiseFunctionDeclaration(nodeptr, tableNode );
tableNode analiseDefinition(nodeptr , tableNode );

#endif