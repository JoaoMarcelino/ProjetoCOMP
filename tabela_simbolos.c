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






char *changeChars(char *str){

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
            paramlist = insertParam(paramlist, changeChars(helper->type), helper->nodeBrother->id);
        }
        else
            paramlist = insertParam(paramlist, changeChars(helper->type), NULL);

        
        aux = aux->nodeBrother;
    }

    return paramlist;
}


 tableNode analiseDeclaration(nodeptr tree, tableNode table){
    nodeptr aux = tree;

    table = insert(table, aux->nodeBrother->id, changeChars(aux->type), NULL, NULL);
    
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
    placeholder->child = NULL;

    paramNode auxParam;
    paramNode param = insertParam(NULL, "param", NULL);
    
    placeholder->child = NULL;

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
            placeholder->type = changeChars(aux->type);
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
            placeholder->type = changeChars(aux->type);

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

char * findParam(nodeptr tree, tableNode main, tableNode local){

    char *str1 = findFirstParam(tree, main, local);
    char *str2 = findSecondParam(tree, main, local);
    
    if (!strcmp(str1,"void") || !strcmp(str2,"void")){
        return "undef";
    }
    else if (!strcmp(str1,"undef") || !strcmp(str2,"undef")){
        return "undef";
    }
    else if (!strcmp(str1,"double") || !strcmp(str2,"double")){
        return "double";
    }
    else if (!strcmp(str1,"int") || !strcmp(str2,"int")){
        return "int";
    }
    else if (!strcmp(str1,"short") || !strcmp(str2,"short")){
        return "short";
    }
    else if (!strcmp(str1,"char") || !strcmp(str2,"char")){
        return "char";
    }
    
    return "TODO";
}


char * findFirstParam(nodeptr tree, tableNode main, tableNode local){
    nodeptr aux = tree;
    tableNode auxMain = main;
    tableNode auxLocal = local;
    //Percorre a funçao local, como nao encontra procura na Main, se o PRIMEIRO filho for um store, etc chamar outra vez a mesma funçao

    //printf("%s\n", aux->type);
    if(!strcmp(aux->type,"Store")|| !strcmp(aux->type,"Plus")|| !strcmp(aux->type,"Minus")|| !strcmp(aux->type,"Call")){

        return findFirstParam(aux->nodeNext, auxMain, auxLocal);
        //printf("int1");
        

    }else if ( !strcmp(aux->type,"Add") || !strcmp(aux->type,"Mul")|| !strcmp(aux->type,"Sub")|| !strcmp(aux->type,"Div")){
           
        return findParam(aux->nodeNext,auxMain, auxLocal);
        
        
    }else if( !strcmp(aux->type,"Comma")){

        return findSecondParam(aux->nodeNext, auxMain, auxLocal);
        //printf("int4 %s",auxTree->nodeNext->type);
        

    }else if (!strcmp(aux->type, "Mod")|| !strcmp(aux->type,"Or")|| !strcmp(aux->type,"And")|| !strcmp(aux->type,"Le")|| !strcmp(aux->type,"Lt")|| !strcmp(aux->type,"Ge")|| !strcmp(aux->type,"Gt")|| !strcmp(aux->type,"Eq")|| !strcmp(aux->type,"Ne")|| !strcmp(aux->type,"BitWiseAnd")|| !strcmp(aux->type,"BitWiseOr")|| !strcmp(aux->type,"BitWiseXor")|| !strcmp(aux->type,"Not")){
         return "int";
         
    }else if(aux->id){
        
        if (!strcmp(aux->type, "IntLit")){
            return "int";
            

        }else if (!strcmp(aux->type, "ChrLit")){
            return "int";
            

        }else if (!strcmp(aux->type, "RealLit")){
            return "double";
            
        }
    } 


    while(auxLocal){
        if (!strcmp(auxLocal-> name, aux->id)){
            return  auxLocal -> type;
            
            break;
        }
        auxLocal = auxLocal -> next;
    }
    while(auxMain){
        if (!strcmp(auxMain-> name, aux->id)){
            return  auxMain -> type;
            
            break;
        }
        auxMain = auxMain -> next;
    }
    return "undef";
}

char *findSecondParam(nodeptr tree,tableNode main,tableNode local){
    nodeptr aux = tree;
    nodeptr auxTree = aux->nodeBrother;
    tableNode auxMain = main;
    tableNode auxLocal = local;
    //Percorre a funçao local, como nao encontra procura na Main, se o SEGUNDO filho for um store, etc chamar outra vez a mesma funçao
     
     
    if (auxTree){
        //printf("%s\n", auxTree->type);
        if(!strcmp(auxTree->type,"Store")|| !strcmp(auxTree->type,"Plus")|| !strcmp(auxTree->type,"Minus")|| !strcmp(auxTree->type,"Call")){

            return findFirstParam(auxTree->nodeNext, auxMain, auxLocal);
            //printf("int3");
            

        }else if ( !strcmp(auxTree->type,"Add") || !strcmp(auxTree->type,"Mul")|| !strcmp(auxTree->type,"Sub")|| !strcmp(auxTree->type,"Div")){
           
            return findParam(auxTree->nodeNext,auxMain, auxLocal);
            
        
        }else if( !strcmp(auxTree->type,"Comma")){

            return findSecondParam(aux ->nodeNext, auxMain, auxLocal);
            //printf("int4 %s",auxTree->nodeNext->type);
            

        }else if (!strcmp(auxTree->type, "Mod")|| !strcmp(auxTree->type,"Or")|| !strcmp(auxTree->type,"And")|| !strcmp(auxTree->type,"Le")|| !strcmp(auxTree->type,"Lt")|| !strcmp(auxTree->type,"Ge")|| !strcmp(auxTree->type,"Gt")|| !strcmp(auxTree->type,"Eq")|| !strcmp(auxTree->type,"Ne")|| !strcmp(auxTree->type,"BitWiseAnd")|| !strcmp(auxTree->type,"BitWiseOr")|| !strcmp(auxTree->type,"BitWiseXor")|| !strcmp(auxTree->type,"Not")){
            return "int";
            
        }else if(auxTree->id){
            
            if (!strcmp(auxTree->type, "IntLit")){
                return "int";
                

            }else if (!strcmp(auxTree->type, "ChrLit")){
                return "int";
                

            }else if (!strcmp(auxTree->type, "RealLit")){
                return "double";
                
            }
        } 
    }
     
    while(auxLocal){
        if (!strcmp(auxLocal-> name, aux->nodeBrother->id)){
            return auxLocal -> type;
            
            break;
        }
        auxLocal = auxLocal -> next;
    }

    while(auxMain){
        if (!strcmp(auxMain-> name, aux->nodeBrother->id)){
            return auxMain -> type;
            
            break;
        }
        auxMain = auxMain -> next;
    }

    return "undef";

}



void printAST(nodeptr node, nodeptr helper, int nPontos, tableNode main, tableNode local){
    nodeptr aux =node;
    tableNode auxTable = main;
    int check =0;
    int flag = 0;

        while (aux){
        
        auxTable = main;

        //printf("%.2d",nPontos);
        

        if(!strcmp(aux->type,"Store")|| !strcmp(aux->type,"Plus")|| !strcmp(aux->type,"Minus")|| !strcmp(aux->type,"Call")){
            printPontos(nPontos);
            printf("%s - ",aux->type);

            printf("%s", findFirstParam(aux ->nodeNext, auxTable, local));

            printf("\n");

        }else if ( !strcmp(aux->type,"Add") || !strcmp(aux->type,"Mul")|| !strcmp(aux->type,"Sub")|| !strcmp(aux->type,"Div")){
            
            printPontos(nPontos);
            printf("%s - ",aux->type);
            
            printf("%s", findParam(aux->nodeNext,auxTable, local));
            
            printf("\n");
        
        }else if( !strcmp(aux->type,"Comma")){
            printPontos(nPontos);
            printf("%s - ",aux->type);
            //printf("int7 %s",aux ->type);
            printf("%s", findSecondParam(aux ->nodeNext, auxTable, local));

            printf("\n");

        }else if (!strcmp(aux->type, "Mod")|| !strcmp(aux->type,"Or")|| !strcmp(aux->type,"And")|| !strcmp(aux->type,"Le")|| !strcmp(aux->type,"Lt")|| !strcmp(aux->type,"Ge")|| !strcmp(aux->type,"Gt")|| !strcmp(aux->type,"Eq")|| !strcmp(aux->type,"Ne")|| !strcmp(aux->type,"BitWiseAnd")|| !strcmp(aux->type,"BitWiseOr")|| !strcmp(aux->type,"BitWiseXor")|| !strcmp(aux->type,"Not")){
                printPontos(nPontos);
                printf("%s - int\n", aux->type);
            } 
        else if(aux->id){
            
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
                printf("%s(%s) - ",aux->type, aux->id); 
                while(auxTable){
                    if(strcmp(aux->id,auxTable->name)==0){
                        
                        if (auxTable->paramList){
                            printf("%s", auxTable->type);
                            printParam(auxTable->paramList);
                            printf("\n");
                            flag =1 ;
                        }
                    }
                    auxTable = auxTable->next;
                    
                }
                               
                /* TODO: buscar valores a tabela */
                if(flag == 0){
                    printf("%s",findFirstParam(aux , main, local));
                    printf("\n");
                }
                flag = 0;
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