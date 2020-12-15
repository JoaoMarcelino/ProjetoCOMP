#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "functions.h"
#include "tabela_simbolos.h"
#include "ctype.h"


/*

    TODO:
        ANALISE DE DECLARACOES
*/

tableNode insert(tableNode node, char *name, char *type, paramNode paramlist, tableNode child){
    tableNode new = (tableNode)malloc(sizeof(nodet));
    tableNode aux = node;
    
    new->name = name;
    new->type = type;

    new->paramList = paramlist;

    new->child = child;
    new->next = NULL;
    
    if (!aux){
        return new;
    }
    
    while(aux){
        if (!strcmp(aux->name,new->name)){

            if(!aux->child){
                new->next = aux->next;
                aux->type = new->type;
                aux->paramList = new->paramList;
                aux->child = new->child;
            }
            break;
        }
        else if (!aux->next){
            aux->next = new;
            break;
        }
            
        
        aux = aux->next;
    }
    
    return node;
}


paramNode insertParam(paramNode list, char *str, char *str2){
    paramNode new = (paramNode)malloc(sizeof(nodep));
    paramNode aux = list;
    
    new->name = str;
    new->var = str2;
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

    return list;
}



void printParam(paramNode list){
    paramNode aux = list;
    int i = 0;
    int var = strcmp(list->name,"param");
    if(var){
        printf("(");
    }
    else
        printf("\t");
        
    while(aux){
        if(i== 0){
            printf("%s",aux->name);
            i =1;
        }
        else
            printf(",%s",aux->name);
        aux= aux->next;
    }
    if(var){
        printf(")");
    }
    
}


void printTable(tableNode table, char * name){
    tableNode aux = table;
    if (strcmp(name, "Global"))
        printf("===== Function %s Symbol Table =====\n", name);
    else
        printf("===== %s Symbol Table =====\n", name);
    while(aux){
        printf("%s\t%s",aux->name, aux->type);
        if (aux->paramList)
            printParam(aux->paramList);
        printf("\n");
        aux=aux->next;
    }

    printf("\n");
}






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

    return "NULL";
}

paramNode analiseParam(nodeptr tree){
    nodeptr aux = tree;
    nodeptr helper;
    paramNode paramlist = NULL;
    

    while(aux){

        helper = aux ->nodeNext;
        if (helper->nodeBrother){
            paramlist = insertParam(paramlist, fuckC(helper->type), helper->nodeBrother->id);
        }
        else
            paramlist = insertParam(paramlist, fuckC(helper->type), NULL);

        
        aux = aux->nodeBrother;
    }

    return paramlist;
}


 tableNode analiseDeclaration(nodeptr tree, tableNode table){
    nodeptr aux = tree;

    table = insert(table, aux->nodeBrother->id, fuckC(aux->type), NULL, NULL);
    
    return table;
 }

tableNode analiseFunctionBody(nodeptr tree, tableNode table){
    nodeptr aux = tree;
    tableNode tableAux = table;
    while(aux){

        if(strcmp(aux->type, "Declaration") == 0)
                tableAux = analiseDeclaration(aux->nodeNext,tableAux);

        aux = aux->nodeBrother;
    }
    return table;
}


 tableNode analiseFunctionDefinition(nodeptr tree, tableNode table){
    nodeptr aux = tree;
    tableNode placeholder = (tableNode)malloc(sizeof(nodet));

    paramNode auxParam;
    paramNode param = insertParam(NULL, "param", NULL);
    
    int i = 0;
   
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
            placeholder->child = insert(placeholder->child, "return", placeholder->type, NULL, NULL);
        }else if (i == 2){
            placeholder->name = aux->id;
            
        }else if (i == 3){
            placeholder->paramList = analiseParam(aux->nodeNext);
            auxParam = placeholder->paramList;
            while(auxParam){

                if(auxParam->var)
                    placeholder->child = insert(placeholder->child, auxParam->var, auxParam->name, param, NULL);
                auxParam = auxParam->next;
            }


        }else if (i == 4){
            placeholder->child = analiseFunctionBody(aux->nodeNext, placeholder->child);
        }

        aux = aux->nodeBrother;
    }
    table = insert(table, placeholder->name, placeholder->type, placeholder->paramList, placeholder->child);
    
    return table;
}



tableNode analiseFunctionDeclaration(nodeptr tree, tableNode table){
    nodeptr aux = tree;
    tableNode placeholder = (tableNode)malloc(sizeof(nodet));
    int i = 0;

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
            placeholder->paramList = analiseParam(aux->nodeNext);

        }

        aux = aux->nodeBrother;
    }
    table = insert(table, placeholder->name, placeholder->type, placeholder->paramList, NULL);
    return table;
}


tableNode analiseTree(nodeptr tree, tableNode table){

    nodeptr aux = tree->nodeNext;



    while(aux){
                
        if (!strcmp(aux->type, "FuncDefinition")){
            table = analiseFunctionDefinition(aux->nodeNext, table);
        }
        else if (!strcmp(aux->type, "FuncDeclaration")){
            table = analiseFunctionDeclaration(aux->nodeNext, table);
        }
        else if (!strcmp(aux->type, "Declaration")){
            table = analiseDeclaration(aux->nodeNext, table);
        }

        aux = aux->nodeBrother;
     
    }
    return table;
};




void globalTable(nodeptr tree){
    paramNode pchar = insertParam(NULL,"int", NULL);
    paramNode gchar = insertParam(NULL,"void", NULL);
    
    tableNode table = insert(NULL,"putchar","int", pchar, NULL);
    table = insert(table,"getchar","int", gchar, NULL);
    table = analiseTree(tree, table);

    tableNode aux = table;
    tableNode helper = table;


    printTable(table, "Global");

    while(aux){
        if (aux ->child){
            helper = aux->child;
            while(helper){
                
                printTable(helper, aux->name);
                helper = helper->child;
            }

        }
        aux = aux->next;
    }

}