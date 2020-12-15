#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct  node *nodeptr;

typedef struct node{
    char *id;
    char *type;
    nodeptr nodeNext;
    nodeptr nodeBrother;
    int value;
}Node;


void printTree(nodeptr , int );
void printPontos(int );
int needsStatList(nodeptr );

#endif
