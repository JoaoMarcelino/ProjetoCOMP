#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "functions.h"
#include "tabela_simbolos.h"
#include "ctype.h"


/*

    TODO:
        alterar tableNode insert de modo a que insira no final da LinkedList        (CHECK)
           
        Alterar insertParam de modo a que insira no final da LinkedList             (CHECK)

        PrintTable receber o nome da table quando estiver a ser criada              (CHECK)
        
        Analisar ParamList e inserir na LinkedList   

*/

tableNode insert(tableNode node, char *name, char *type, paramNode paramlist){
    tableNode new = (tableNode)malloc(sizeof(nodet));
    tableNode aux = node;
    int i;

    new->name = name;
    new->type = type;

    new->paramList = paramlist;

    new->child = NULL;
    new->next = NULL;

    if(aux){
        while(aux->next){
            aux=aux->next;
        }
        aux->next = new;
    }
    else{
        node = new;
    }
   

    return node;
}


paramNode insertParam(paramNode list, char *str){
    paramNode new = (paramNode)malloc(sizeof(nodep));
    paramNode aux = list;

    new->name = str;
    new->next = NULL;   

    
    if(aux){
        while(aux->next){
            aux=aux->next;
        }
        aux->next = new;
    }
    else{
        list = new;
    }

    return new;
}



void printParam(paramNode list, int num){
    paramNode aux = list;
    int i = 0;
    if(num){
       printf("(");
        while(aux){
            if(i== 0){
                printf("%s",aux->name);
                i =1;
            }
            else
                printf(",%s",aux->name);
            aux= aux->next;
        }
        printf(")"); 
    }
    
}


void printTable(tableNode table, char * name){
    tableNode aux = table;

    printf("===== %s Symbol Table =====\n", name);
    while(aux){
        printf("%s\t%s",aux->name, aux->type);
        printParam(aux->paramList,1);
        printf("\n");
        aux=aux->next;
    }
}



void globalTable(nodeptr tree){

    paramNode pchar = insertParam(NULL,"int");
    paramNode gchar = insertParam(NULL,"void");
    
    tableNode table = insert(NULL,"putchar","int", pchar);
    table = insert(table,"getchar","int", gchar);
    table = analiseTree(tree, table);
    printTable(table, "Global");
};


char *fuckC(char *str){

    if (!strcmp(str,"Char"))
        return "char";
    if (!strcmp(str,"Int"))
        return "int";
    if (!strcmp(str,"Void"))
        return "void";
    if (!strcmp(str,"Double"))
        return "double";
    if (!strcmp(str,"Short"))
        return "short";

}



 tableNode analiseDefinition(nodeptr tree, tableNode table){
    nodeptr aux = tree;
    tableNode placeholder = (tableNode)malloc(sizeof(nodet));
    char str[50];
    int i = 0, j = 0;
    printf("F_DEFINITION\n");
   
    /*  TODO LIST 
    F_DEFINITION
        Int
        Id
        ParamList
        FuncBody 
    */
    while(aux){
        i++;
        if (i==1){
            placeholder->type = fuckC(aux->type);

        }else if (i == 2){
            placeholder->name = aux->id;
        }else if (i == 3){
            //Anlise ParamList Falta Fazer Ainda
            placeholder->paramList = insertParam(NULL,"void");

        }
        
        printf("\t%s\n",aux->type);
        aux = aux->nodeBrother;
    }
   
    table = insert(table, placeholder->name, placeholder->type, placeholder->paramList);
    return table;
}

tableNode analiseDeclaration(nodeptr tree, tableNode table){
    nodeptr aux = tree;
    nodeptr helper = tree;
    tableNode placeholder = (tableNode)malloc(sizeof(nodet));
    int i = 0;
    printf("F_DECLARATION\n");

     /* TODO LIST 
    F_DECLARATION
        Char
        Id
        ParamList
    */

     while(aux){
        i++;
        if (i==1){
            placeholder->type = fuckC(aux->type);
        }else if (i == 2){
            placeholder->name = aux->id;
        }else if (i == 3){

            //Analise ParamList Falta Fazer Ainda
            //placeholder->paramList = insertParam(NULL,"void");

            helper = aux->nodeNext;

            while(helper){
                printf("\t %s\n",helper->nodeNext->type);
                helper = helper->nodeBrother;
            }

        }
        
        printf("\t%s\n",aux->type);
        aux = aux->nodeBrother;
    }
    table = insert(table, placeholder->name, placeholder->type, placeholder->paramList);
    return table;
}

tableNode analiseTree(nodeptr tree, tableNode table){

    nodeptr aux = tree;



    while(aux){
                
        if (!strcmp(aux->type, "FuncDefinition")){
            table = analiseDefinition(aux->nodeNext, table);
        }
        else if (!strcmp(aux->type, "FuncDeclaration")){
            table = analiseDeclaration(aux->nodeNext, table);
        }

        if (aux->nodeNext){
            table = analiseTree(aux->nodeNext, table);
        }

        aux = aux->nodeBrother;
     
    }
    return table;
};