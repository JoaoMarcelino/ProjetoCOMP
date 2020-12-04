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



nodeptr insertNode(nodeptr node, char *id, char *type){
    nodeptr aux = (nodeptr)malloc(sizeof(Node));
    aux->id = id;
    aux->type= type;
    /* Adicionar no inicio */
    aux->nodeBrother= NULL;
    aux->nodeNext= node;

    return aux;
};

void joinNodes(nodeptr node1, nodeptr node2){
    nodeptr aux = node1;
    if(aux){

        while(aux->nodeBrother){
            aux=aux->nodeBrother;
        }
        aux->nodeBrother = node2;
    }else if(node2){
        node1 = node2;
    }

};


 nodeptr checkFuncHelper(nodeptr node){

    nodeptr aux = node;
    int i =0;
    while(i!=3){
        aux=aux->nodeBrother;
        i+=1;
    }
    if(aux){
        return insertNode(node,NULL, "FuncDefinition");
    }else{
        return insertNode(node,NULL, "FuncDeclaration");
    }
};

nodeptr DeclarationFunc(nodeptr main,nodeptr typespec, nodeptr declarations){
    nodeptr aux= declarations;
    nodeptr node;
    nodeptr typeaux;
    char * type = typespec->type;
    while(aux){
        //printf("%p, %p, %p\n",main, declarations,node);
        typeaux = insertNode(NULL,NULL,type);
        joinNodes(typeaux, aux->nodeNext);
        node = insertNode(typeaux, NULL, "Declaration");
        if (main)
            joinNodes(main, node);
        else main = node;
        
        aux=aux->nodeBrother;
    }
    return main;
};
