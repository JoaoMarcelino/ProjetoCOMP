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




tableNode globalTable(nodeptr tree){
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

    return table;

}


void findFirstParam(nodeptr tree, tableNode main, tableNode local){
    nodeptr aux = tree;
    tableNode auxTable = main;
    //Percorre a funçao local, como nao encontra procura na Main, se o PRIMEIRO filho for um store, etc chamar outra vez a mesma funçao
    if (strcmp(aux->type,"Store")){
        while(auxTable){
            if (!strcmp(auxTable-> name, aux->id)){
                printf("%s", auxTable -> type);
                break;
            }
            auxTable = auxTable -> next;
        }
    }
}

void findSecondParam(nodeptr tree,tableNode main,tableNode local){
    nodeptr aux = tree;
    tableNode auxTable = main;

    
    //Percorre a funçao local, como nao encontra procura na Main, se o SEGUNDO filho for um store, etc chamar outra vez a mesma funçao
    if (strcmp(aux->nodeBrother->type,"Store")){
        while(auxTable){
            if (!strcmp(auxTable-> name, aux->nodeBrother->id)){
                printf("%s", auxTable -> type);
                break;
            }
            auxTable = auxTable -> next;
        }
    }
}



void printAST(nodeptr node, nodeptr helper, int nPontos, tableNode main, tableNode local){
    nodeptr aux =node;
    tableNode auxTable = main;
    int check =0;

        while (aux){
        
        auxTable = main;

        //printf("%.2d",nPontos);
        

        if(!strcmp(aux->type,"Store") || !strcmp(aux->type,"Add")){
            printPontos(nPontos);
            printf("%s - ",aux->type);

            findFirstParam(aux ->nodeNext, auxTable, local);

            printf("\n");

        }else if( !strcmp(aux->type,"Comma")){
            printPontos(nPontos);
            printf("%s - ",aux->type);

            findSecondParam(aux ->nodeNext, auxTable, local);

            printf("\n");

        }else if(aux->id){
            
            if (!strcmp(aux->type, "IntLit")){
                printPontos(nPontos);
                printf("%s(%s) - int\n",aux->type, aux->id);

            }else if (!strcmp(aux->type, "ChrLit")){
                printPontos(nPontos);
                printf("%s(%s) - int\n",aux->type, aux->id);

            }else if (!strcmp(aux->type, "RealLit")){
                printPontos(nPontos);
                printf("%s(%s) - double\n",aux->type, aux->id);
            } 

            else if (!helper){
                printPontos(nPontos);
                printf("%s(%s)",aux->type, aux->id); 
                
                /* TODO: buscar valores a tabela */
                
                while(auxTable){
                    if (!strcmp(auxTable -> name, aux->id)){
                        printf(" - %s", auxTable -> type);
                        break;
                    }
                    auxTable = auxTable -> next;
                }
                printf("\n");
            }
            else {
                printPontos(nPontos);
                printf("%s(%s)\n",aux->type, aux->id); 
            }
            

        }else if(!strcmp(aux->type,"Else") ){
            
        }
        else if(!strcmp(aux->type,"StatList")){
            
            if (needsStatList(aux)){
                if (check==1){
                    check=0;
                    printPontos(nPontos+=2);
                    printf("%s\n",aux->type);
                }else{
                    printPontos(nPontos);
                    printf("%s\n",aux->type);
                }
            }
            else{
                if(!check){
                    nPontos -=2;
                    check=1;
                }
            }
        }
        else{
            printPontos(nPontos);
            printf("%s\n",aux->type);
        }


        /*
        CASO AUX->TYPE SEJA FUNCTION DECLARATION IDK 
        CASO SEJA FUNCTION DEFINITION DAR A TABELA DESSA FUNCAO
            A TABELA GLOBAL PODERA VIR A SER IMPORTANTE PARA A FUNCTION DEFINITION NAS CALLS
        CASO SEJA DECLARATION DAR A TABELA GLOBAL

         */

        if (aux->nodeNext){
            if (!strcmp(aux->type,"FuncDeclaration") | !strcmp(aux->type,"Declaration") | !strcmp(aux->type,"ParamDeclaration") ){
                printAST(aux->nodeNext, aux, nPontos + 2, main, local);
                
            }else if (!strcmp(aux->type,"FuncDefinition")) {
                auxTable = main;
               
                while(auxTable){
                    if (!strcmp(aux->nodeNext->nodeBrother->id, auxTable->name)){
                        local = auxTable;
                        break;
                    }
                    auxTable = auxTable ->next;
                }
                printAST(aux->nodeNext, aux, nPontos + 2, main, local->child);
            }else{
                printAST(aux->nodeNext, NULL, nPontos + 2, main, local);
            }
            
        }
        
        if (check==1){
            check=0;
            nPontos+=2;
        }
        aux=aux->nodeBrother;
    }
}