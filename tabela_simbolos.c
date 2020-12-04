#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "functions.h"
#include "tabela_simbolos.h"


void globalTable(nodeptr tree){
    tableNode table = insert(NULL,"putchar","int",["int"]);
    table = insert(table,"getchar","int",["void"]);

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


tableNode insert(tableNode node, char *name, char *type, char *array[]){
    tableNode aux = (tableNode)malloc(sizeof(node));
    int i;
    aux->name = name;
    aux->type = type;

    //perhaps mal feito
    for (i=0;i<4;i++){
        aux->params[i] = array[i];
    }
    aux->child = NULL;
    aux->next = node;

    return aux;
};


tableNode printTable(tableNode table){
    tableNode aux = table;

    while(aux){
        printf("===== %% Symbol Table =====\n");
        printf("%s\t%s",aux->name, aux->type);
        printParam(aux->params);
        printf("\n");
        aux=aux->next;
    }
}

void printParam(char *params[], int num){
    int i;
    if(num){
       printf("(");
        for(i=0;i<num;i++){
            if(i==num)
                printf("%s",params[i]);
            else
                printf("%s,"params[i]);
        }
        printf(")"); 
    }
    
}