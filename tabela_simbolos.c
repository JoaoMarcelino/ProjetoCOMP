#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "functions.h"
#include "tabela_simbolos.h"



tableNode insert(tableNode node, char *name, char *type, char *array[]){
    tableNode aux = (tableNode)malloc(sizeof(node));
    int i;
    aux->name = name;
    aux->type = type;

    aux->params = array;
    aux->child = NULL;
    aux->next = node;

    return aux;
};


void printParam(char *params[], int num){
    int i;
    if(num){
       printf("(");
        for(i=0;i<num;i++){
            if(i==num)
                printf("%s",params[i]);
            else
                printf("%s,",params[i]);
        }
        printf(")"); 
    }
    
}


void printTable(tableNode table){
    tableNode aux = table;

    while(aux){
        printf("===== %% Symbol Table =====\n");
        printf("%s\t%s",aux->name, aux->type);
        printParam(aux->params,1);
        printf("\n");
        aux=aux->next;
    }
}



void globalTable(nodeptr tree){
    char * var[] = {"int"};
    char * var2[] = {"void"};
    tableNode table = insert(NULL,"putchar","int",var);
    table = insert(table,"getchar","int",var2);
    //analiseTree(tree, table);
    printTable(table);
};


void analiseTree(nodeptr tree, tableNode table){

    nodeptr aux = tree;

    while(aux){
        
        //todo things

        if (aux->nodeNext){
            analiseTree(aux->nodeNext, table);
        }

        aux = aux->nodeBrother;
     
    }

};

