#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct node * tableNode;
typedef struct node{

    char *name;
    char *type;
    char *params[4];

    tableNode next;
    tableNode child;
}node;



void globalTable(nodeptr);
tableNode insertNode();
void analiseTree(nodeptr , tableNode );
tableNode insertNode(tableNode , char *, char *, char *);
tableNode printTable(table);
void printParam(char *, int );