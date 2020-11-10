/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 6 "uccompiler.y" /* yacc.c:339  */

    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include "y.tab.h"
    #define SIZE 100

    int yylex(void);
    int main(void);
    void yyerror (char *s);
    

    extern int treePrint;
	extern int SintaxErrors;
    extern int nline,ncol;
    extern char* yytext;

    typedef struct  node *nodeptr;

    typedef struct node{
        char *id;
        char *type;
        nodeptr nodeNext;
        nodeptr nodeBrother;
        int value;
    }Node;


    nodeptr createNode(){
        nodeptr aux = (nodeptr )malloc(sizeof(Node));

        if (aux!=NULL){
            aux->id=malloc(SIZE*sizeof(char));
            aux->type=malloc(SIZE*sizeof(char));
            aux->nodeNext=NULL;
            aux->nodeBrother= NULL;
        }
        return aux;
    }

    nodeptr insertNode(nodeptr node, char *id, char *type){
        nodeptr aux = (nodeptr)malloc(sizeof(Node));
        aux->id = id;
        aux->type= type;
        /* Adicionar no inicio */
        aux->nodeBrother= node;
        aux->nodeNext= NULL;

        return aux;
    }

    void freeTree(nodeptr first){
        nodeptr aux=first;
        nodeptr aux2;
        while (aux->nodeNext!=NULL){
            free(aux->id);
            free(aux->type);
            freeTree(aux->nodeBrother);
            aux2=aux->nodeNext;
            free(aux);
            aux=aux2;
        }
        free(aux2);
    }


    void printTree(nodeptr node){
        nodeptr aux = node;
        int i=0;
        while (aux){
            printf("%d %s %s\n",i++,aux->type, aux->id);
            aux=aux->nodeBrother;
        }
    }

    void joinNodes(nodeptr node1, nodeptr node2){
        if(node1){
            node1->nodeBrother = node2;
        }else if(node2){
            node1 = node2;
        }

    }


    /*
    () normal
    [] opcional
    {} zero ou mais repetições
    FunctionsAndDeclarations −→ (FunctionDefinition | FunctionDeclaration | Declaration) {FunctionDefinition | FunctionDeclaration | Declaration}


FunctionDefinition −→ TypeSpec FunctionDeclarator FunctionBody
    
    FunctionBody −→ LBRACE [DeclarationsAndStatements] RBRACE
    DeclarationsAndStatements −→ Statement DeclarationsAndStatements | Declaration DeclarationsAndStatements | Statement | Declaration
FunctionDeclaration −→ TypeSpec FunctionDeclarator SEMI
    
    FunctionDeclarator −→ ID LPAR ParameterList RPAR
    ParameterList −→ ParameterDeclaration {COMMA ParameterDeclaration}
    ParameterDeclaration −→ TypeSpec [ID]

Declaration −→ TypeSpec Declarator {COMMA Declarator} SEMI
    TypeSpec −→ CHAR | INT | VOID | SHORT | DOUBLE
    Declarator −→ ID [ASSIGN Expr]
    
    Statement −→ [Expr] SEMI
    Statement −→ LBRACE {Statement} RBRACE
    Statement −→ IF LPAR Expr RPAR Statement [ELSE Statement]
    Statement −→ WHILE LPAR Expr RPAR Statement
    Statement −→ RETURN [Expr] SEMI
    
    Expr −→ Expr (ASSIGN | COMMA) Expr
    Expr −→ Expr (PLUS | MINUS | MUL | DIV | MOD) Expr
    Expr −→ Expr (OR | AND | BITWISEAND | BITWISEOR | BITWISEXOR) Expr
    Expr −→ Expr (EQ | NE | LE | GE | LT | GT) Expr
    Expr −→ (PLUS | MINUS | NOT) Expr
    Expr −→ ID LPAR [Expr {COMMA Expr}] RPAR
    Expr −→ ID | INTLIT | CHRLIT | REALLIT | LPAR Expr RPAR



        
    %right ASSIGN
    %left COMMA
    %right EQ NE LE GE LT GT
    %left PLUS MINUS NOT
    %left MUL DIV MOD
    %left OR AND BITWISEAND BITWISEOR BITWISEXOR
    %right LPAR LBRACE

    */

#line 200 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    CHRLIT = 258,
    REALLIT = 259,
    INTLIT = 260,
    ID = 261,
    CHAR = 262,
    ELSE = 263,
    WHILE = 264,
    IF = 265,
    INT = 266,
    SHORT = 267,
    DOUBLE = 268,
    RETURN = 269,
    VOID = 270,
    BITWISEAND = 271,
    BITWISEOR = 272,
    BITWISEXOR = 273,
    AND = 274,
    ASSIGN = 275,
    MUL = 276,
    COMMA = 277,
    DIV = 278,
    EQ = 279,
    GE = 280,
    GT = 281,
    LBRACE = 282,
    LE = 283,
    LPAR = 284,
    LT = 285,
    MINUS = 286,
    MOD = 287,
    NE = 288,
    NOT = 289,
    OR = 290,
    PLUS = 291,
    RBRACE = 292,
    RPAR = 293,
    SEMI = 294,
    RESERVED = 295
  };
#endif
/* Tokens.  */
#define CHRLIT 258
#define REALLIT 259
#define INTLIT 260
#define ID 261
#define CHAR 262
#define ELSE 263
#define WHILE 264
#define IF 265
#define INT 266
#define SHORT 267
#define DOUBLE 268
#define RETURN 269
#define VOID 270
#define BITWISEAND 271
#define BITWISEOR 272
#define BITWISEXOR 273
#define AND 274
#define ASSIGN 275
#define MUL 276
#define COMMA 277
#define DIV 278
#define EQ 279
#define GE 280
#define GT 281
#define LBRACE 282
#define LE 283
#define LPAR 284
#define LT 285
#define MINUS 286
#define MOD 287
#define NE 288
#define NOT 289
#define OR 290
#define PLUS 291
#define RBRACE 292
#define RPAR 293
#define SEMI 294
#define RESERVED 295

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 140 "uccompiler.y" /* yacc.c:355  */

    struct node *node;
    char* id;

#line 325 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 342 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  8
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   489

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  42
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  21
/* YYNRULES -- Number of rules.  */
#define YYNRULES  72
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  135

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   296

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   231,   231,   234,   235,   238,   239,   242,   243,   244,
     245,   246,   249,   252,   255,   256,   259,   260,   263,   264,
     267,   268,   271,   272,   275,   276,   279,   280,   283,   284,
     287,   288,   292,   293,   295,   297,   299,   301,   304,   305,
     308,   309,   312,   313,   316,   317,   319,   320,   321,   322,
     323,   325,   326,   327,   328,   329,   331,   332,   333,   334,
     335,   336,   338,   339,   340,   342,   343,   344,   345,   346,
     347,   348,   349
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CHRLIT", "REALLIT", "INTLIT", "ID",
  "CHAR", "ELSE", "WHILE", "IF", "INT", "SHORT", "DOUBLE", "RETURN",
  "VOID", "BITWISEAND", "BITWISEOR", "BITWISEXOR", "AND", "ASSIGN", "MUL",
  "COMMA", "DIV", "EQ", "GE", "GT", "LBRACE", "LE", "LPAR", "LT", "MINUS",
  "MOD", "NE", "NOT", "OR", "PLUS", "RBRACE", "RPAR", "SEMI", "RESERVED",
  "\"then\"", "$accept", "FunctionsAndDec", "FunctionsAndDeclarations",
  "FuctionsAndDecExtra", "TypeSpec", "FunctionDeclarator", "ParameterList",
  "ParameterExtra", "ParameterDeclaration", "FunctionHelper",
  "FunctionBody", "DeclarationsAndStatements",
  "DeclarationsAndStatementsRep", "Declaration", "DeclarationExtra",
  "Declarator", "Statement", "StatementBrace", "StatementElse",
  "StatementReturn", "Expr", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296
};
# endif

#define YYPACT_NINF -34

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-34)))

#define YYTABLE_NINF -26

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      52,   -34,   -34,   -34,   -34,   -34,     8,    67,   -34,   -25,
     -11,   -34,    60,    60,   -34,   199,    52,   -20,   -34,   -34,
     -34,   -34,   -34,   -34,    -8,   189,   199,   199,   199,   360,
      16,   -13,    17,   -34,   -34,   195,     7,   268,   -16,   -34,
     -16,   199,   199,   199,   199,   199,   199,   199,   199,   199,
     199,   199,   199,   199,   199,   199,   199,   199,   199,   -34,
       2,   -24,    31,    24,   291,   -34,   -34,   453,   421,   439,
     402,   360,   -34,   360,   -34,   185,   100,   100,   100,   100,
     -16,   -34,   185,   381,   -16,    52,   -34,    43,   -34,   -34,
     -20,   -34,   -34,    16,    30,    46,    49,   106,   143,    70,
      44,   -34,    93,   220,   -34,     2,   -34,   199,   199,   -34,
     -34,   244,   -33,    48,   -34,    31,    93,   -34,   -34,   -34,
     -34,   -34,   314,   337,   -34,   -34,   -34,   -34,   155,   155,
     -34,    75,   155,   -34,   -34
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     7,     8,    10,    11,     9,     0,     0,     1,     0,
      31,     2,     0,     0,    27,     0,     0,     0,     5,     3,
       4,    67,    68,    66,    65,     0,     0,     0,     0,    30,
      17,     0,     0,    29,    26,     0,     0,     0,    63,    64,
      62,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    16,
      15,     0,    31,     0,     0,    72,    71,    53,    54,    55,
      52,    44,    48,    45,    49,    56,    59,    61,    58,    60,
      47,    50,    57,    51,    46,     0,    13,     0,    19,    12,
       0,    70,    69,    17,     0,     0,     0,     0,     0,     0,
       0,    20,     0,     0,    28,    15,    33,     0,     0,    42,
      37,     0,     0,     0,    34,    31,     0,    18,    24,    22,
      32,    14,     0,     0,    43,    39,    38,    23,     0,     0,
      36,    41,     0,    35,    40
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -34,   -34,    80,    76,     1,   -34,   -34,   -17,    -3,   -34,
     -34,     4,   -21,    14,    11,    54,   -14,   -34,   -34,   -34,
     -15
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     6,    18,    19,    99,    12,    31,    86,    60,    89,
     100,   118,   119,    13,    34,    17,   102,   114,   133,   110,
     103
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      29,     7,    32,    87,   125,    46,   106,    48,     8,    15,
      37,    38,    39,    40,    14,    88,    55,    30,    16,    33,
      64,    35,    59,    62,    85,    61,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    94,    65,    21,    22,    23,    24,
       1,    15,    95,    96,     2,     3,     4,    97,     5,     1,
      -6,     9,    91,     2,     3,     4,    10,     5,     9,   106,
      98,     9,    25,    10,    26,   107,   115,    27,   108,    28,
     -21,   117,   111,   132,   113,   126,    93,    11,   121,    20,
     105,   101,   122,   123,    94,   127,    21,    22,    23,    24,
       1,   104,    95,    96,     2,     3,     4,    97,     5,    21,
      22,    23,    24,   116,   130,   131,    90,     0,   134,     0,
      98,    46,    25,    48,    26,     0,     0,    27,     0,    28,
     -25,    54,    55,     0,     0,    25,    58,    26,     0,     0,
      27,     0,    28,     0,   112,   109,    21,    22,    23,    24,
       0,     0,    95,    96,     0,     0,    94,    97,    21,    22,
      23,    24,     0,     0,    95,    96,     0,     0,     0,    97,
      98,     0,    25,     0,    26,     0,     0,    27,     0,    28,
       0,     0,    98,     0,    25,     0,    26,     0,     0,    27,
      36,    28,    21,    22,    23,    24,    63,     0,    21,    22,
      23,    24,    21,    22,    23,    24,    46,     0,    48,     0,
      50,    51,     0,    52,     0,    53,    54,    55,    25,     0,
      26,    58,     0,    27,    25,    28,    26,     0,    25,    27,
      26,    28,     0,    27,     0,    28,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,     0,    52,     0,
      53,    54,    55,    56,     0,    57,    58,     0,     0,   120,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,     0,    52,     0,    53,    54,    55,    56,     0,    57,
      58,     0,     0,   124,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,     0,    52,     0,    53,    54,
      55,    56,     0,    57,    58,     0,    66,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,     0,    52,
       0,    53,    54,    55,    56,     0,    57,    58,     0,    92,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,     0,    52,     0,    53,    54,    55,    56,     0,    57,
      58,     0,   128,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,     0,    52,     0,    53,    54,    55,
      56,     0,    57,    58,     0,   129,    41,    42,    43,    44,
      45,    46,     0,    48,    49,    50,    51,     0,    52,     0,
      53,    54,    55,    56,     0,    57,    58,    41,    42,    43,
      44,     0,    46,     0,    48,    49,    50,    51,     0,    52,
       0,    53,    54,    55,    56,     0,     0,    58,    41,    42,
      43,     0,     0,    46,     0,    48,    49,    50,    51,     0,
      52,     0,    53,    54,    55,    56,     0,    41,    58,    43,
       0,     0,    46,     0,    48,    49,    50,    51,     0,    52,
       0,    53,    54,    55,    56,    41,     0,    58,     0,     0,
      46,     0,    48,    49,    50,    51,     0,    52,     0,    53,
      54,    55,    56,     0,    46,    58,    48,    49,    50,    51,
       0,    52,     0,    53,    54,    55,    56,     0,     0,    58
};

static const yytype_int16 yycheck[] =
{
      15,     0,    22,    27,    37,    21,    39,    23,     0,    20,
      25,    26,    27,    28,    39,    39,    32,    16,    29,    39,
      35,    29,     6,     6,    22,    38,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,     1,    38,     3,     4,     5,     6,
       7,    20,     9,    10,    11,    12,    13,    14,    15,     7,
       0,     1,    38,    11,    12,    13,     6,    15,     1,    39,
      27,     1,    29,     6,    31,    29,     6,    34,    29,    36,
      37,    37,    97,     8,    98,    37,    85,     7,   105,    13,
      93,    87,   107,   108,     1,   116,     3,     4,     5,     6,
       7,    90,     9,    10,    11,    12,    13,    14,    15,     3,
       4,     5,     6,    99,   128,   129,    62,    -1,   132,    -1,
      27,    21,    29,    23,    31,    -1,    -1,    34,    -1,    36,
      37,    31,    32,    -1,    -1,    29,    36,    31,    -1,    -1,
      34,    -1,    36,    -1,     1,    39,     3,     4,     5,     6,
      -1,    -1,     9,    10,    -1,    -1,     1,    14,     3,     4,
       5,     6,    -1,    -1,     9,    10,    -1,    -1,    -1,    14,
      27,    -1,    29,    -1,    31,    -1,    -1,    34,    -1,    36,
      -1,    -1,    27,    -1,    29,    -1,    31,    -1,    -1,    34,
       1,    36,     3,     4,     5,     6,     1,    -1,     3,     4,
       5,     6,     3,     4,     5,     6,    21,    -1,    23,    -1,
      25,    26,    -1,    28,    -1,    30,    31,    32,    29,    -1,
      31,    36,    -1,    34,    29,    36,    31,    -1,    29,    34,
      31,    36,    -1,    34,    -1,    36,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    -1,    28,    -1,
      30,    31,    32,    33,    -1,    35,    36,    -1,    -1,    39,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    -1,    28,    -1,    30,    31,    32,    33,    -1,    35,
      36,    -1,    -1,    39,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    -1,    28,    -1,    30,    31,
      32,    33,    -1,    35,    36,    -1,    38,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    -1,    28,
      -1,    30,    31,    32,    33,    -1,    35,    36,    -1,    38,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    -1,    28,    -1,    30,    31,    32,    33,    -1,    35,
      36,    -1,    38,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    -1,    28,    -1,    30,    31,    32,
      33,    -1,    35,    36,    -1,    38,    16,    17,    18,    19,
      20,    21,    -1,    23,    24,    25,    26,    -1,    28,    -1,
      30,    31,    32,    33,    -1,    35,    36,    16,    17,    18,
      19,    -1,    21,    -1,    23,    24,    25,    26,    -1,    28,
      -1,    30,    31,    32,    33,    -1,    -1,    36,    16,    17,
      18,    -1,    -1,    21,    -1,    23,    24,    25,    26,    -1,
      28,    -1,    30,    31,    32,    33,    -1,    16,    36,    18,
      -1,    -1,    21,    -1,    23,    24,    25,    26,    -1,    28,
      -1,    30,    31,    32,    33,    16,    -1,    36,    -1,    -1,
      21,    -1,    23,    24,    25,    26,    -1,    28,    -1,    30,
      31,    32,    33,    -1,    21,    36,    23,    24,    25,    26,
      -1,    28,    -1,    30,    31,    32,    33,    -1,    -1,    36
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     7,    11,    12,    13,    15,    43,    46,     0,     1,
       6,    44,    47,    55,    39,    20,    29,    57,    44,    45,
      45,     3,     4,     5,     6,    29,    31,    34,    36,    62,
      46,    48,    22,    39,    56,    29,     1,    62,    62,    62,
      62,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    28,    30,    31,    32,    33,    35,    36,     6,
      50,    38,     6,     1,    62,    38,    38,    62,    62,    62,
      62,    62,    62,    62,    62,    62,    62,    62,    62,    62,
      62,    62,    62,    62,    62,    22,    49,    27,    39,    51,
      57,    38,    38,    46,     1,     9,    10,    14,    27,    46,
      52,    53,    58,    62,    56,    50,    39,    29,    29,    39,
      61,    62,     1,    58,    59,     6,    55,    37,    53,    54,
      39,    49,    62,    62,    39,    37,    37,    54,    38,    38,
      58,    58,     8,    60,    58
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    42,    43,    44,    44,    45,    45,    46,    46,    46,
      46,    46,    47,    48,    49,    49,    50,    50,    51,    51,
      52,    52,    53,    53,    54,    54,    55,    55,    56,    56,
      57,    57,    58,    58,    58,    58,    58,    58,    59,    59,
      60,    60,    61,    61,    62,    62,    62,    62,    62,    62,
      62,    62,    62,    62,    62,    62,    62,    62,    62,    62,
      62,    62,    62,    62,    62,    62,    62,    62,    62,    62,
      62,    62,    62
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     2,     2,     1,     0,     1,     1,     1,
       1,     1,     5,     3,     4,     0,     1,     0,     3,     1,
       1,     0,     2,     3,     1,     0,     3,     2,     4,     1,
       2,     0,     2,     2,     2,     6,     5,     2,     2,     2,
       2,     0,     1,     2,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     2,     2,     1,     1,     1,     1,     4,
       4,     3,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 231 "uccompiler.y" /* yacc.c:1646  */
    {printf("Programa\n"); joinNodes((yyvsp[-1].node),(yyvsp[0].node)); (yyval.node) = insertNode((yyvsp[-1].node),NULL,"PROGRAM");printTree((yyval.node));}
#line 1585 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 234 "uccompiler.y" /* yacc.c:1646  */
    {joinNodes((yyvsp[-1].node),(yyvsp[0].node)); (yyval.node) = (yyvsp[-1].node);}
#line 1591 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 235 "uccompiler.y" /* yacc.c:1646  */
    {printf("FunctionsAndDeclarations\n"); joinNodes((yyvsp[-1].node),(yyvsp[0].node)); (yyval.node) = (yyvsp[-1].node);}
#line 1597 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 238 "uccompiler.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node);}
#line 1603 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 239 "uccompiler.y" /* yacc.c:1646  */
    {(yyval.node) = NULL;}
#line 1609 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 242 "uccompiler.y" /* yacc.c:1646  */
    {(yyval.node) = insertNode(NULL,NULL,"CHAR");}
#line 1615 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 243 "uccompiler.y" /* yacc.c:1646  */
    {printf("int\n");(yyval.node) = insertNode(NULL,NULL,"INT");}
#line 1621 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 244 "uccompiler.y" /* yacc.c:1646  */
    {printf("void\n");(yyval.node) = insertNode(NULL,NULL,"VOID");}
#line 1627 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 245 "uccompiler.y" /* yacc.c:1646  */
    {(yyval.node) = insertNode(NULL,NULL,"SHORT");}
#line 1633 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 246 "uccompiler.y" /* yacc.c:1646  */
    {(yyval.node) = insertNode(NULL,NULL,"DOUBLE");}
#line 1639 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 249 "uccompiler.y" /* yacc.c:1646  */
    {printf("id---%s\n",(yyvsp[-4].id));printTree((yyvsp[0].node));joinNodes((yyvsp[-2].node),(yyvsp[0].node)); (yyval.node) = insertNode((yyvsp[-2].node), (yyvsp[-4].id),"ID");printTree((yyvsp[-2].node));}
#line 1645 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 252 "uccompiler.y" /* yacc.c:1646  */
    {printf("parameterlist\n");joinNodes((yyvsp[-1].node),(yyvsp[0].node)); joinNodes((yyvsp[-2].node),(yyvsp[-1].node)); (yyval.node) = (yyvsp[-2].node);printTree((yyval.node));}
#line 1651 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 255 "uccompiler.y" /* yacc.c:1646  */
    {printf("parameterextra\n");joinNodes((yyvsp[-1].node),(yyvsp[0].node)); joinNodes((yyvsp[-2].node),(yyvsp[-1].node)); (yyval.node) = insertNode((yyvsp[-2].node), NULL,"COMMA");}
#line 1657 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 256 "uccompiler.y" /* yacc.c:1646  */
    {(yyval.node) = NULL;}
#line 1663 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 259 "uccompiler.y" /* yacc.c:1646  */
    {printf("id %s\n",(yyvsp[0].id));(yyval.node) = insertNode(NULL, (yyvsp[0].id),"ID");}
#line 1669 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 260 "uccompiler.y" /* yacc.c:1646  */
    {(yyval.node) = NULL;}
#line 1675 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 263 "uccompiler.y" /* yacc.c:1646  */
    {printf("functionbody\n");(yyval.node) = (yyvsp[-1].node);}
#line 1681 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 264 "uccompiler.y" /* yacc.c:1646  */
    {(yyval.node) = NULL;}
#line 1687 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 267 "uccompiler.y" /* yacc.c:1646  */
    {printf("decandstat\n");(yyval.node) = (yyvsp[0].node);}
#line 1693 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 268 "uccompiler.y" /* yacc.c:1646  */
    {(yyval.node) = NULL;}
#line 1699 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 271 "uccompiler.y" /* yacc.c:1646  */
    {printf("statement\n");joinNodes((yyvsp[-1].node),(yyvsp[0].node)); (yyval.node) = (yyvsp[-1].node);}
#line 1705 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 272 "uccompiler.y" /* yacc.c:1646  */
    {printf("declaration\n");joinNodes((yyvsp[-1].node),(yyvsp[0].node)); joinNodes((yyvsp[-2].node),(yyvsp[-1].node)); (yyval.node) = (yyvsp[-2].node);}
#line 1711 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 275 "uccompiler.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node);}
#line 1717 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 276 "uccompiler.y" /* yacc.c:1646  */
    {(yyval.node) = NULL;}
#line 1723 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 279 "uccompiler.y" /* yacc.c:1646  */
    {printf("Declaration\n");joinNodes((yyvsp[-1].node),(yyvsp[0].node)); (yyval.node) = insertNode((yyvsp[-1].node), (yyvsp[-2].id),"ID");}
#line 1729 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 280 "uccompiler.y" /* yacc.c:1646  */
    {printf("erro");(yyval.node) = insertNode(NULL,NULL,NULL);}
#line 1735 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 283 "uccompiler.y" /* yacc.c:1646  */
    {nodeptr aux; joinNodes((yyvsp[-1].node),(yyvsp[0].node)); aux = insertNode((yyvsp[-1].node),(yyvsp[-2].id),"ID"); (yyval.node)  = insertNode(aux,NULL,"COMMA"); }
#line 1741 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 284 "uccompiler.y" /* yacc.c:1646  */
    {printf("semi\n");(yyval.node) = NULL;}
#line 1747 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 287 "uccompiler.y" /* yacc.c:1646  */
    {printf("declarator1\n");(yyval.node) = insertNode((yyvsp[0].node),NULL,"ASSIGN");}
#line 1753 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 288 "uccompiler.y" /* yacc.c:1646  */
    {printf("declarator2\n");(yyval.node) = NULL;}
#line 1759 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 292 "uccompiler.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[-1].node);}
#line 1765 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 293 "uccompiler.y" /* yacc.c:1646  */
    {(yyval.node) = insertNode(NULL,NULL,NULL);}
#line 1771 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 295 "uccompiler.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node);}
#line 1777 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 297 "uccompiler.y" /* yacc.c:1646  */
    {joinNodes((yyvsp[-1].node),(yyvsp[0].node)); joinNodes((yyvsp[-3].node),(yyvsp[-1].node)); (yyval.node) = insertNode((yyvsp[-3].node),NULL,"IF");}
#line 1783 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 299 "uccompiler.y" /* yacc.c:1646  */
    {joinNodes((yyvsp[-2].node),(yyvsp[0].node)); (yyval.node) = insertNode((yyvsp[-2].node),NULL,"WHILE");}
#line 1789 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 301 "uccompiler.y" /* yacc.c:1646  */
    {(yyval.node) = insertNode((yyvsp[0].node),NULL,"RETURN");}
#line 1795 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 304 "uccompiler.y" /* yacc.c:1646  */
    {(yyval.node) = insertNode((yyvsp[-1].node),NULL,"STATEMENT");}
#line 1801 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 305 "uccompiler.y" /* yacc.c:1646  */
    {(yyval.node) = insertNode(NULL,NULL,NULL);}
#line 1807 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 308 "uccompiler.y" /* yacc.c:1646  */
    {(yyval.node) = insertNode((yyvsp[0].node),NULL,"STATEMENT");}
#line 1813 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 309 "uccompiler.y" /* yacc.c:1646  */
    {(yyval.node) = NULL;}
#line 1819 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 312 "uccompiler.y" /* yacc.c:1646  */
    {(yyval.node) = NULL;}
#line 1825 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 313 "uccompiler.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[-1].node);}
#line 1831 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 316 "uccompiler.y" /* yacc.c:1646  */
    {joinNodes((yyvsp[-2].node),(yyvsp[0].node)); (yyval.node) = insertNode((yyvsp[-2].node),NULL,"ASSIGN");}
#line 1837 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 317 "uccompiler.y" /* yacc.c:1646  */
    {joinNodes((yyvsp[-2].node),(yyvsp[0].node)); (yyval.node) = insertNode((yyvsp[-2].node),NULL,"COMMA");}
#line 1843 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 319 "uccompiler.y" /* yacc.c:1646  */
    {joinNodes((yyvsp[-2].node),(yyvsp[0].node)); (yyval.node) = insertNode((yyvsp[-2].node),NULL,"PLUS");}
#line 1849 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 320 "uccompiler.y" /* yacc.c:1646  */
    {joinNodes((yyvsp[-2].node),(yyvsp[0].node)); (yyval.node) = insertNode((yyvsp[-2].node),NULL,"MINUS");}
#line 1855 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 321 "uccompiler.y" /* yacc.c:1646  */
    {joinNodes((yyvsp[-2].node),(yyvsp[0].node)); (yyval.node) = insertNode((yyvsp[-2].node),NULL,"MUL");}
#line 1861 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 322 "uccompiler.y" /* yacc.c:1646  */
    {joinNodes((yyvsp[-2].node),(yyvsp[0].node)); (yyval.node) = insertNode((yyvsp[-2].node),NULL,"DIV");}
#line 1867 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 323 "uccompiler.y" /* yacc.c:1646  */
    {joinNodes((yyvsp[-2].node),(yyvsp[0].node)); (yyval.node) = insertNode((yyvsp[-2].node),NULL,"MOD");}
#line 1873 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 325 "uccompiler.y" /* yacc.c:1646  */
    {joinNodes((yyvsp[-2].node),(yyvsp[0].node)); (yyval.node) = insertNode((yyvsp[-2].node),NULL,"OR");}
#line 1879 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 326 "uccompiler.y" /* yacc.c:1646  */
    {joinNodes((yyvsp[-2].node),(yyvsp[0].node)); (yyval.node) = insertNode((yyvsp[-2].node),NULL,"AND");}
#line 1885 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 327 "uccompiler.y" /* yacc.c:1646  */
    {joinNodes((yyvsp[-2].node),(yyvsp[0].node)); (yyval.node) = insertNode((yyvsp[-2].node),NULL,"BITWISEAND");}
#line 1891 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 328 "uccompiler.y" /* yacc.c:1646  */
    {joinNodes((yyvsp[-2].node),(yyvsp[0].node)); (yyval.node) = insertNode((yyvsp[-2].node),NULL,"BITWISEOR");}
#line 1897 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 329 "uccompiler.y" /* yacc.c:1646  */
    {joinNodes((yyvsp[-2].node),(yyvsp[0].node)); (yyval.node) = insertNode((yyvsp[-2].node),NULL,"BITWISEXOR");}
#line 1903 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 331 "uccompiler.y" /* yacc.c:1646  */
    {joinNodes((yyvsp[-2].node),(yyvsp[0].node)); (yyval.node) = insertNode((yyvsp[-2].node),NULL,"EQ");}
#line 1909 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 332 "uccompiler.y" /* yacc.c:1646  */
    {joinNodes((yyvsp[-2].node),(yyvsp[0].node)); (yyval.node) = insertNode((yyvsp[-2].node),NULL,"NE");}
#line 1915 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 333 "uccompiler.y" /* yacc.c:1646  */
    {joinNodes((yyvsp[-2].node),(yyvsp[0].node)); (yyval.node) = insertNode((yyvsp[-2].node),NULL,"LE");}
#line 1921 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 334 "uccompiler.y" /* yacc.c:1646  */
    {joinNodes((yyvsp[-2].node),(yyvsp[0].node)); (yyval.node) = insertNode((yyvsp[-2].node),NULL,"GE");}
#line 1927 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 335 "uccompiler.y" /* yacc.c:1646  */
    {joinNodes((yyvsp[-2].node),(yyvsp[0].node)); (yyval.node) = insertNode((yyvsp[-2].node),NULL,"LT");}
#line 1933 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 336 "uccompiler.y" /* yacc.c:1646  */
    {joinNodes((yyvsp[-2].node),(yyvsp[0].node)); (yyval.node) = insertNode((yyvsp[-2].node),NULL,"GT");}
#line 1939 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 338 "uccompiler.y" /* yacc.c:1646  */
    {(yyval.node) = insertNode((yyvsp[0].node),NULL,"PLUS");}
#line 1945 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 339 "uccompiler.y" /* yacc.c:1646  */
    {(yyval.node) = insertNode((yyvsp[0].node),NULL,"MINUS");}
#line 1951 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 340 "uccompiler.y" /* yacc.c:1646  */
    {(yyval.node) = insertNode((yyvsp[0].node),NULL,"NOT");}
#line 1957 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 342 "uccompiler.y" /* yacc.c:1646  */
    {printf("id %s\n",(yyvsp[0].id));(yyval.node) = insertNode(NULL,(yyvsp[0].id),"ID");}
#line 1963 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 343 "uccompiler.y" /* yacc.c:1646  */
    {(yyval.node) = insertNode(NULL,(yyvsp[0].id),"INTLIT");}
#line 1969 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 344 "uccompiler.y" /* yacc.c:1646  */
    {(yyval.node) = insertNode(NULL,(yyvsp[0].id),"CHRLIT");}
#line 1975 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 345 "uccompiler.y" /* yacc.c:1646  */
    {(yyval.node) = insertNode(NULL,(yyvsp[0].id),"REALLIT");}
#line 1981 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 346 "uccompiler.y" /* yacc.c:1646  */
    {(yyval.node) = insertNode((yyvsp[-1].node),(yyvsp[-3].id),"ID");}
#line 1987 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 347 "uccompiler.y" /* yacc.c:1646  */
    {(yyval.node) = insertNode(NULL,NULL,NULL);}
#line 1993 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 348 "uccompiler.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[-1].node);}
#line 1999 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 349 "uccompiler.y" /* yacc.c:1646  */
    {(yyval.node) = insertNode(NULL,NULL,NULL);}
#line 2005 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2009 "y.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 353 "uccompiler.y" /* yacc.c:1906  */



void yyerror (char *s) {
    printf ( "Line %d, col %d: %s: %s\n" , nline , ncol ,s , yytext );
}

