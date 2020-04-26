
/*  A Bison parser, made from bas.y
 by  GNU Bison version 1.25
  */

#define YYBISON 1  /* Identify Bison output.  */

#define	INTEGER	258
#define	DECIMAL	259
#define	CHARACTER	260
#define	VAR	261
#define	CONST	262
#define	INT	263
#define	FLOAT	264
#define	CHAR	265
#define	BOOL	266
#define	ENDOFFILE	267
#define	GE	268
#define	LE	269
#define	GT	270
#define	LT	271
#define	EQ	272
#define	NE	273
#define	NOT	274
#define	AND	275
#define	OR	276
#define	B_TRUE	277
#define	B_FALSE	278
#define	UMINUS	279

#line 1 "bas.y"

#include <bits/stdc++.h>
using namespace std;
ofstream qudFile, symFile, errFile;

set<string> unusedVar;
extern int yylineno;
int RegID = 0, scopeID = 0;
bool c_failed = false;  // failed compilation

enum dataType {
  UNDEFINED,
  T_BOOL,
  T_INT,
  T_FLOAT,
  T_CHAR
};

// Symbol Table node
struct symNode{
	bool isConst;
	dataType type;
	string strValue;
	bool isInit;
	bool isUsed;
	int line;

	symNode(bool isConst = 0, dataType type = UNDEFINED, string val = "", bool isInit = 0, bool isUsed = 0, int line = 0) 
		: isConst(isConst), type(type), strValue(val), isInit(isInit), isUsed(isUsed), line(line) {}


  void printSym(char* varName){
    string t_str;
    switch(type){
      case T_BOOL:
        t_str = "Boolean";
        break;
      case T_INT:
        t_str = "Integer";
        break;
      case T_FLOAT:
        t_str = "Float";
        break;
      case T_CHAR:
        t_str = "Character";
        break;
      default:
        break;
    }
     symFile<<varName<<"\t\t\t"<<isConst<<"\t\t"<<t_str<<"\t\t\t"<<strValue<<"\t\t\t"<<isInit<<"\t\t\t"<<isUsed<<"\t\t"<<line<<"\n";
  }
};

vector< map<string, symNode> > symbolTable(1);
map<string, dataType> varType;



/* prototypes */
int yylex(void);
void yyerror(char *);
string RegNoGen(void);
void declareVar(char*, bool, dataType, string, bool, bool, int);
void isDefined(char*);
int findVar(char*);
int checkType(int, int);
void assignVar(char*,char*);
void printErrors(void);
void constError(char*);
void notDefinedError(char*);
void uninitializedWarning(char*);
void conflictWarning(void);
void redefinitionError(char*);
void symboTableFileInit(void);
void printTripleOperandOperation(string, string, char*);
void printQuadOperandOperation(string, string, string, char*);


#line 80 "bas.y"
typedef union {
  char* val; 
      		
	char* name;

  struct info1{
    int type;
    char val[100];
  }info;
		

} YYSTYPE;
#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	YYFINAL		95
#define	YYFLAG		-32768
#define	YYNTBASE	35

#define YYTRANSLATE(x) ((unsigned)(x) <= 279 ? yytranslate[x] : 44)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,    31,
    32,    26,    24,     2,    25,     2,    27,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,    29,     2,
    30,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,    33,     2,    34,     2,     2,     2,     2,     2,
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
     2,     2,     2,     2,     2,     1,     2,     3,     4,     5,
     6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
    16,    17,    18,    19,    20,    21,    22,    23,    28
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     2,     5,     7,     9,    11,    14,    17,    20,    24,
    27,    33,    39,    45,    51,    56,    61,    66,    71,    74,
    77,    80,    83,    87,    89,    91,    93,    95,    97,    99,
   102,   106,   110,   114,   118,   122,   126,   130,   134,   138,
   142,   145,   149,   153,   157,   160,   162,   164
};

static const short yyrhs[] = {    36,
     0,    36,    37,     0,    37,     0,    12,     0,    29,     0,
    38,    29,     0,    39,    29,     0,    40,    29,     0,    42,
    41,    43,     0,    42,    43,     0,     7,     8,     6,    30,
    40,     0,     7,     9,     6,    30,    40,     0,     7,    10,
     6,    30,    40,     0,     7,    11,     6,    30,    40,     0,
     8,     6,    30,    40,     0,     9,     6,    30,    40,     0,
    10,     6,    30,    40,     0,    11,     6,    30,    40,     0,
     8,     6,     0,     9,     6,     0,    10,     6,     0,    11,
     6,     0,     6,    30,    40,     0,     3,     0,     4,     0,
     5,     0,     6,     0,    22,     0,    23,     0,    25,    40,
     0,    40,    24,    40,     0,    40,    25,    40,     0,    40,
    26,    40,     0,    40,    27,    40,     0,    40,    16,    40,
     0,    40,    15,    40,     0,    40,    13,    40,     0,    40,
    14,    40,     0,    40,    18,    40,     0,    40,    17,    40,
     0,    19,    40,     0,    40,    20,    40,     0,    40,    21,
    40,     0,    31,    40,    32,     0,    41,    37,     0,    37,
     0,    33,     0,    34,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
   118,   121,   123,   124,   127,   129,   130,   131,   132,   133,
   136,   142,   147,   152,   159,   164,   169,   174,   181,   185,
   189,   193,   199,   206,   213,   219,   225,   233,   239,   246,
   252,   258,   264,   270,   276,   282,   288,   294,   300,   306,
   312,   318,   324,   330,   338,   340,   343,   350
};
#endif


#if YYDEBUG != 0 || defined (YYERROR_VERBOSE)

static const char * const yytname[] = {   "$","error","$undefined.","INTEGER",
"DECIMAL","CHARACTER","VAR","CONST","INT","FLOAT","CHAR","BOOL","ENDOFFILE",
"GE","LE","GT","LT","EQ","NE","NOT","AND","OR","B_TRUE","B_FALSE","'+'","'-'",
"'*'","'/'","UMINUS","';'","'='","'('","')'","'{'","'}'","program","function",
"stmt","declaration","assignment","expr","nested_stmt","Obrace","Cbrace", NULL
};
#endif

static const short yyr1[] = {     0,
    35,    36,    36,    36,    37,    37,    37,    37,    37,    37,
    38,    38,    38,    38,    38,    38,    38,    38,    38,    38,
    38,    38,    39,    40,    40,    40,    40,    40,    40,    40,
    40,    40,    40,    40,    40,    40,    40,    40,    40,    40,
    40,    40,    40,    40,    41,    41,    42,    43
};

static const short yyr2[] = {     0,
     1,     2,     1,     1,     1,     2,     2,     2,     3,     2,
     5,     5,     5,     5,     4,     4,     4,     4,     2,     2,
     2,     2,     3,     1,     1,     1,     1,     1,     1,     2,
     3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
     2,     3,     3,     3,     2,     1,     1,     1
};

static const short yydefact[] = {     0,
    24,    25,    26,    27,     0,     0,     0,     0,     0,     4,
     0,    28,    29,     0,     5,     0,    47,     1,     3,     0,
     0,     0,     0,     0,     0,     0,     0,     0,    19,    20,
    21,    22,    27,    41,    30,     0,     2,     6,     7,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     8,    48,    46,     0,    10,    23,     0,     0,     0,
     0,     0,     0,     0,     0,    44,    37,    38,    36,    35,
    40,    39,    42,    43,    31,    32,    33,    34,    45,     9,
     0,     0,     0,     0,    15,    16,    17,    18,    11,    12,
    13,    14,     0,     0,     0
};

static const short yydefgoto[] = {    93,
    18,    19,    20,    21,    22,    55,    23,    56
};

static const short yypact[] = {    87,
-32768,-32768,-32768,   -24,    34,     2,     4,     5,     6,-32768,
   149,-32768,-32768,   149,-32768,   149,-32768,   118,-32768,   -22,
    -9,   188,    55,   149,    17,    18,    44,    49,    26,    27,
    37,    38,-32768,-32768,-32768,   168,-32768,-32768,-32768,   149,
   149,   149,   149,   149,   149,   149,   149,   149,   149,   149,
   149,-32768,-32768,-32768,    55,-32768,     1,    39,    45,    46,
    51,   149,   149,   149,   149,-32768,    22,    22,    22,    22,
    22,    22,   205,   205,   -25,   -25,-32768,-32768,-32768,-32768,
   149,   149,   149,   149,     1,     1,     1,     1,     1,     1,
     1,     1,    79,    82,-32768
};

static const short yypgoto[] = {-32768,
-32768,   -14,-32768,-32768,   -11,-32768,-32768,    28
};


#define	YYLAST		232


static const short yytable[] = {    34,
    50,    51,    35,    37,    36,    24,    38,    29,    54,    30,
    31,    32,    57,    40,    41,    42,    43,    44,    45,    39,
    46,    47,    58,    59,    48,    49,    50,    51,    67,    68,
    69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
    79,    25,    26,    27,    28,    48,    49,    50,    51,    60,
    85,    86,    87,    88,    61,    62,    63,     1,     2,     3,
     4,     5,     6,     7,     8,     9,    64,    65,    81,    89,
    90,    91,    92,    11,    82,    83,    12,    13,    94,    14,
    84,    95,    80,    15,     0,    16,     0,    17,    53,     1,
     2,     3,     4,     5,     6,     7,     8,     9,    10,     0,
     0,     0,     0,     0,     0,    11,     0,     0,    12,    13,
     0,    14,     0,     0,     0,    15,     0,    16,     0,    17,
     1,     2,     3,     4,     5,     6,     7,     8,     9,     0,
     0,     0,     0,     0,     0,     0,    11,     0,     0,    12,
    13,     0,    14,     0,     0,     0,    15,     0,    16,     0,
    17,     1,     2,     3,    33,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,    11,     0,     0,
    12,    13,     0,    14,     0,     0,     0,     0,     0,    16,
    40,    41,    42,    43,    44,    45,     0,    46,    47,     0,
     0,    48,    49,    50,    51,     0,     0,     0,     0,    66,
    40,    41,    42,    43,    44,    45,     0,    46,    47,     0,
     0,    48,    49,    50,    51,     0,    52,    40,    41,    42,
    43,    44,    45,     0,     0,     0,     0,     0,    48,    49,
    50,    51
};

static const short yycheck[] = {    11,
    26,    27,    14,    18,    16,    30,    29,     6,    23,     6,
     6,     6,    24,    13,    14,    15,    16,    17,    18,    29,
    20,    21,     6,     6,    24,    25,    26,    27,    40,    41,
    42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
    55,     8,     9,    10,    11,    24,    25,    26,    27,     6,
    62,    63,    64,    65,     6,    30,    30,     3,     4,     5,
     6,     7,     8,     9,    10,    11,    30,    30,    30,    81,
    82,    83,    84,    19,    30,    30,    22,    23,     0,    25,
    30,     0,    55,    29,    -1,    31,    -1,    33,    34,     3,
     4,     5,     6,     7,     8,     9,    10,    11,    12,    -1,
    -1,    -1,    -1,    -1,    -1,    19,    -1,    -1,    22,    23,
    -1,    25,    -1,    -1,    -1,    29,    -1,    31,    -1,    33,
     3,     4,     5,     6,     7,     8,     9,    10,    11,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    19,    -1,    -1,    22,
    23,    -1,    25,    -1,    -1,    -1,    29,    -1,    31,    -1,
    33,     3,     4,     5,     6,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    19,    -1,    -1,
    22,    23,    -1,    25,    -1,    -1,    -1,    -1,    -1,    31,
    13,    14,    15,    16,    17,    18,    -1,    20,    21,    -1,
    -1,    24,    25,    26,    27,    -1,    -1,    -1,    -1,    32,
    13,    14,    15,    16,    17,    18,    -1,    20,    21,    -1,
    -1,    24,    25,    26,    27,    -1,    29,    13,    14,    15,
    16,    17,    18,    -1,    -1,    -1,    -1,    -1,    24,    25,
    26,    27
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "/cygnus/cygwin-b20/share/bison.simple"

/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

#ifndef alloca
#ifdef __GNUC__
#define alloca __builtin_alloca
#else /* not GNU C.  */
#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc) || defined (__sgi)
#include <alloca.h>
#else /* not sparc */
#if defined (MSDOS) && !defined (__TURBOC__)
#include <malloc.h>
#else /* not MSDOS, or __TURBOC__ */
#if defined(_AIX)
#include <malloc.h>
 #pragma alloca
#else /* not MSDOS, __TURBOC__, or _AIX */
#ifdef __hpux
#ifdef __cplusplus
extern "C" {
void *alloca (unsigned int);
};
#else /* not __cplusplus */
void *alloca ();
#endif /* not __cplusplus */
#endif /* __hpux */
#endif /* not _AIX */
#endif /* not MSDOS, or __TURBOC__ */
#endif /* not sparc.  */
#endif /* not GNU C.  */
#endif /* alloca not defined.  */

/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

/* Note: there must be only one dollar sign in this file.
   It is replaced by the list of actions, each action
   as one case of the switch.  */

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	return(0)
#define YYABORT 	return(1)
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.
   This remains here temporarily to ease the
   transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    { yychar = (token), yylval = (value);			\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { yyerror ("syntax error: cannot back up"); YYERROR; }	\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

#ifndef YYPURE
#define YYLEX		yylex()
#endif

#ifdef YYPURE
#ifdef YYLSP_NEEDED
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, &yylloc, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval, &yylloc)
#endif
#else /* not YYLSP_NEEDED */
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval)
#endif
#endif /* not YYLSP_NEEDED */
#endif

/* If nonreentrant, generate the variables here */

#ifndef YYPURE

int	yychar;			/*  the lookahead symbol		*/
YYSTYPE	yylval;			/*  the semantic value of the		*/
				/*  lookahead symbol			*/

#ifdef YYLSP_NEEDED
YYLTYPE yylloc;			/*  location data for the lookahead	*/
				/*  symbol				*/
#endif

int yynerrs;			/*  number of parse errors so far       */
#endif  /* not YYPURE */

#if YYDEBUG != 0
int yydebug;			/*  nonzero means print parse trace	*/
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif

/*  YYINITDEPTH indicates the initial size of the parser's stacks	*/

#ifndef	YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
int yyparse (void);
#endif

#if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
#define __yy_memcpy(TO,FROM,COUNT)	__builtin_memcpy(TO,FROM,COUNT)
#else				/* not GNU C or C++ */
#ifndef __cplusplus

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (to, from, count)
     char *to;
     char *from;
     int count;
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#else /* __cplusplus */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (char *to, char *from, int count)
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#endif
#endif

#line 196 "/cygnus/cygwin-b20/share/bison.simple"

/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
#ifdef __cplusplus
#define YYPARSE_PARAM_ARG void *YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#else /* not __cplusplus */
#define YYPARSE_PARAM_ARG YYPARSE_PARAM
#define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
#endif /* not __cplusplus */
#else /* not YYPARSE_PARAM */
#define YYPARSE_PARAM_ARG
#define YYPARSE_PARAM_DECL
#endif /* not YYPARSE_PARAM */

int
yyparse(YYPARSE_PARAM_ARG)
     YYPARSE_PARAM_DECL
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YYSTYPE *yyvsp;
  int yyerrstatus;	/*  number of tokens to shift before error messages enabled */
  int yychar1 = 0;		/*  lookahead token as an internal (translated) token number */

  short	yyssa[YYINITDEPTH];	/*  the state stack			*/
  YYSTYPE yyvsa[YYINITDEPTH];	/*  the semantic value stack		*/

  short *yyss = yyssa;		/*  refer to the stacks thru separate pointers */
  YYSTYPE *yyvs = yyvsa;	/*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YYLSP_NEEDED
  YYLTYPE yylsa[YYINITDEPTH];	/*  the location stack			*/
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;

#ifdef YYPURE
  int yychar;
  YYSTYPE yylval;
  int yynerrs;
#ifdef YYLSP_NEEDED
  YYLTYPE yylloc;
#endif
#endif

  YYSTYPE yyval;		/*  the variable used to return		*/
				/*  semantic values from the action	*/
				/*  routines				*/

  int yylen;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Starting parse\n");
#endif

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
#ifdef YYLSP_NEEDED
  yylsp = yyls;
#endif

/* Push a new state, which is found in  yystate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
yynewstate:

  *++yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YYSTYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#ifdef YYLSP_NEEDED
      YYLTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
#ifdef YYLSP_NEEDED
      /* This used to be a conditional around just the two extra args,
	 but that might be undefined if yyoverflow is a macro.  */
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yyls1, size * sizeof (*yylsp),
		 &yystacksize);
#else
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yystacksize);
#endif

      yyss = yyss1; yyvs = yyvs1;
#ifdef YYLSP_NEEDED
      yyls = yyls1;
#endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	{
	  yyerror("parser stack overflow");
	  return 2;
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
      yyss = (short *) alloca (yystacksize * sizeof (*yyssp));
      __yy_memcpy ((char *)yyss, (char *)yyss1, size * sizeof (*yyssp));
      yyvs = (YYSTYPE *) alloca (yystacksize * sizeof (*yyvsp));
      __yy_memcpy ((char *)yyvs, (char *)yyvs1, size * sizeof (*yyvsp));
#ifdef YYLSP_NEEDED
      yyls = (YYLTYPE *) alloca (yystacksize * sizeof (*yylsp));
      __yy_memcpy ((char *)yyls, (char *)yyls1, size * sizeof (*yylsp));
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YYLSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Entering state %d\n", yystate);
#endif

  goto yybackup;
 yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Reading a token: ");
#endif
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(yychar);

#if YYDEBUG != 0
      if (yydebug)
	{
	  fprintf (stderr, "Next token is %d (%s", yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise meaning
	     of a token, for further debugging info.  */
#ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
#endif
	  fprintf (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting token %d (%s), ", yychar, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (yyerrstatus) yyerrstatus--;

  yystate = yyn;
  goto yynewstate;

/* Do the default action for the current state.  */
yydefault:

  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;

/* Do a reduction.  yyn is the number of a rule to reduce with.  */
yyreduce:
  yylen = yyr2[yyn];
  if (yylen > 0)
    yyval = yyvsp[1-yylen]; /* implement default value of the action */

#if YYDEBUG != 0
  if (yydebug)
    {
      int i;

      fprintf (stderr, "Reducing via rule %d (line %d), ",
	       yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
	fprintf (stderr, "%s ", yytname[yyrhs[i]]);
      fprintf (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif


  switch (yyn) {

case 1:
#line 119 "bas.y"
{printErrors(); exit(0);;
    break;}
case 2:
#line 122 "bas.y"
{;
    break;}
case 4:
#line 124 "bas.y"
{;
    break;}
case 5:
#line 128 "bas.y"
{;
    break;}
case 6:
#line 129 "bas.y"
{;
    break;}
case 7:
#line 130 "bas.y"
{;
    break;}
case 8:
#line 131 "bas.y"
{;
    break;}
case 9:
#line 132 "bas.y"
{;
    break;}
case 11:
#line 137 "bas.y"
{
                                              checkType(T_INT, yyvsp[0].info.type); 
                                              varType[yyvsp[-2].name] = T_INT; 
                                              declareVar(yyvsp[-2].name, 1, T_INT, yyvsp[0].info.val, 1, 0, yylineno);
                                            ;
    break;}
case 12:
#line 142 "bas.y"
{
                                              checkType(T_FLOAT, yyvsp[0].info.type); 
                                              varType[yyvsp[-2].name] = T_FLOAT; 
                                              declareVar(yyvsp[-2].name, 1, T_FLOAT, yyvsp[0].info.val, 1, 0, yylineno);
                                            ;
    break;}
case 13:
#line 147 "bas.y"
{
                                              checkType(T_CHAR, yyvsp[0].info.type); 
                                              varType[yyvsp[-2].name] = T_CHAR; 
                                              declareVar(yyvsp[-2].name, 1, T_CHAR, yyvsp[0].info.val, 1, 0, yylineno);
                                            ;
    break;}
case 14:
#line 152 "bas.y"
{
                                              checkType(T_BOOL, yyvsp[0].info.type); 
                                              varType[yyvsp[-2].name] = T_BOOL; 
                                              declareVar(yyvsp[-2].name, 1, T_BOOL, yyvsp[0].info.val, 1, 0, yylineno);
                                            ;
    break;}
case 15:
#line 159 "bas.y"
{
                                              checkType(T_INT, yyvsp[0].info.type); 
                                              varType[yyvsp[-2].name] = T_INT; 
                                              declareVar(yyvsp[-2].name, 0, T_INT, yyvsp[0].info.val, 1, 0, yylineno);
                                            ;
    break;}
case 16:
#line 164 "bas.y"
{
                                              checkType(T_FLOAT, yyvsp[0].info.type); 
                                              varType[yyvsp[-2].name] = T_FLOAT; 
                                              declareVar(yyvsp[-2].name, 0, T_FLOAT, yyvsp[0].info.val, 1, 0, yylineno);
                                            ;
    break;}
case 17:
#line 169 "bas.y"
{
                                              checkType(T_CHAR, yyvsp[0].info.type); 
                                              varType[yyvsp[-2].name] = T_CHAR; 
                                              declareVar(yyvsp[-2].name, 0, T_CHAR, yyvsp[0].info.val, 1, 0, yylineno);
                                            ;
    break;}
case 18:
#line 174 "bas.y"
{
                                              checkType(T_BOOL, yyvsp[0].info.type); 
                                              varType[yyvsp[-2].name] = T_BOOL; 
                                              declareVar(yyvsp[-2].name, 0, T_BOOL, yyvsp[0].info.val, 1, 0, yylineno);
                                            ;
    break;}
case 19:
#line 181 "bas.y"
{
                                              varType[yyvsp[0].name] = T_INT; 
                                              declareVar(yyvsp[0].name, 0, T_INT, "0", 0, 0, yylineno);
                                            ;
    break;}
case 20:
#line 185 "bas.y"
{
                                              varType[yyvsp[0].name] = T_FLOAT; 
                                              declareVar(yyvsp[0].name, 0, T_FLOAT, "0", 0, 0, yylineno);
                                            ;
    break;}
case 21:
#line 189 "bas.y"
{
                                              varType[yyvsp[0].name] = T_CHAR; 
                                              declareVar(yyvsp[0].name, 0, T_CHAR, "", 0, 0, yylineno);
                                            ;
    break;}
case 22:
#line 193 "bas.y"
{
                                              varType[yyvsp[0].name] = T_BOOL; 
                                              declareVar(yyvsp[0].name, 0, T_BOOL, "0", 0, 0, yylineno);
                                            ;
    break;}
case 23:
#line 200 "bas.y"
{
                                              checkType(varType[yyvsp[-2].name], yyvsp[0].info.type); 
                                              assignVar(yyvsp[-2].name, yyvsp[0].info.val);
                                            ;
    break;}
case 24:
#line 207 "bas.y"
{ 
                                              yyval.info.type = T_INT;
                                              string ret = RegNoGen();
                                              strcpy(yyval.info.val, ret.c_str());  
                                              printTripleOperandOperation("MOV", yyvsp[0].val, yyval.info.val);
                                            ;
    break;}
case 25:
#line 213 "bas.y"
{ 
                                              yyval.info.type = T_FLOAT; 
                                              string ret = RegNoGen();
                                              strcpy(yyval.info.val, ret.c_str());
                                              printTripleOperandOperation("MOV", yyvsp[0].val, yyval.info.val);
                                            ;
    break;}
case 26:
#line 219 "bas.y"
{ 
                                              yyval.info.type = T_CHAR; 
                                              string ret = RegNoGen();
                                              strcpy(yyval.info.val, ret.c_str());
                                              printTripleOperandOperation("MOV", yyvsp[0].val, yyval.info.val);
                                            ;
    break;}
case 27:
#line 225 "bas.y"
{
                                              yyval.info.type = varType[yyvsp[0].name]; 
                                              string ret = RegNoGen();
                                              strcpy(yyval.info.val, ret.c_str()); 
                                              /*check if defined before*/
                                              isDefined(yyvsp[0].name);
                                              printTripleOperandOperation("MOV", yyvsp[0].name, yyval.info.val);
                                            ;
    break;}
case 28:
#line 233 "bas.y"
{
                                              yyval.info.type = T_BOOL; 
                                              string ret = RegNoGen();
                                              strcpy(yyval.info.val, ret.c_str());
                                              printTripleOperandOperation("MOV", "1", yyval.info.val);
                                            ;
    break;}
case 29:
#line 239 "bas.y"
{
                                              yyval.info.type = T_BOOL; 
                                              string ret = RegNoGen();
                                              strcpy(yyval.info.val, ret.c_str());
                                              printTripleOperandOperation("MOV", "0", yyval.info.val);
                                            ;
    break;}
case 30:
#line 246 "bas.y"
{
                                              yyval.info.type = yyvsp[0].info.type;
                                              string ret = RegNoGen(); 
                                              strcpy(yyval.info.val, ret.c_str());
                                              printTripleOperandOperation("NEG", yyvsp[0].info.val, yyval.info.val);
                                            ;
    break;}
case 31:
#line 252 "bas.y"
{ 
                                              yyval.info.type = checkType(yyvsp[-2].info.type, yyvsp[0].info.type); 
                                              string ret = RegNoGen(); 
                                              strcpy(yyval.info.val, ret.c_str());
                                              printQuadOperandOperation("ADD",yyvsp[-2].info.val,yyvsp[0].info.val,yyval.info.val);
                                            ;
    break;}
case 32:
#line 258 "bas.y"
{ 
                                              yyval.info.type = checkType(yyvsp[-2].info.type, yyvsp[0].info.type); 
                                              string ret = RegNoGen();
                                              strcpy(yyval.info.val,ret.c_str());
                                              printQuadOperandOperation("SUB", yyvsp[-2].info.val, yyvsp[0].info.val, yyval.info.val);
                                            ;
    break;}
case 33:
#line 264 "bas.y"
{ 
                                              yyval.info.type = checkType(yyvsp[-2].info.type, yyvsp[0].info.type); 
                                              string ret = RegNoGen();
                                              strcpy(yyval.info.val, ret.c_str());
                                              printQuadOperandOperation("MUL", yyvsp[-2].info.val, yyvsp[0].info.val, yyval.info.val);
                                            ;
    break;}
case 34:
#line 270 "bas.y"
{ 
                                              yyval.info.type = checkType(yyvsp[-2].info.type, yyvsp[0].info.type); 
                                              string ret = RegNoGen();
                                              strcpy(yyval.info.val, ret.c_str());
                                              printQuadOperandOperation("DIV", yyvsp[-2].info.val, yyvsp[0].info.val, yyval.info.val);
                                            ;
    break;}
case 35:
#line 276 "bas.y"
{ 
                                              yyval.info.type = checkType(yyvsp[-2].info.type, yyvsp[0].info.type); 
                                              string ret = RegNoGen();
                                              strcpy(yyval.info.val, ret.c_str());
                                              printQuadOperandOperation("LTN", yyvsp[-2].info.val, yyvsp[0].info.val, yyval.info.val);
                                            ;
    break;}
case 36:
#line 282 "bas.y"
{ 
                                              yyval.info.type = checkType(yyvsp[-2].info.type, yyvsp[0].info.type); 
                                              string ret = RegNoGen();
                                              strcpy(yyval.info.val, ret.c_str());
                                              printQuadOperandOperation("GTN", yyvsp[-2].info.val, yyvsp[0].info.val, yyval.info.val);
                                            ;
    break;}
case 37:
#line 288 "bas.y"
{ 
                                              yyval.info.type = checkType(yyvsp[-2].info.type, yyvsp[0].info.type); 
                                              string ret = RegNoGen();
                                              strcpy(yyval.info.val, ret.c_str());
                                              printQuadOperandOperation("GTE", yyvsp[-2].info.val, yyvsp[0].info.val, yyval.info.val);
                                            ;
    break;}
case 38:
#line 294 "bas.y"
{ 
                                              yyval.info.type = checkType(yyvsp[-2].info.type, yyvsp[0].info.type);
                                              string ret = RegNoGen(); 
                                              strcpy(yyval.info.val, ret.c_str());
                                              printQuadOperandOperation("LTE", yyvsp[-2].info.val, yyvsp[0].info.val, yyval.info.val);
                                            ;
    break;}
case 39:
#line 300 "bas.y"
{ 
                                              yyval.info.type = checkType(yyvsp[-2].info.type, yyvsp[0].info.type);
                                              string ret = RegNoGen(); 
                                              strcpy(yyval.info.val, ret.c_str());
                                              printQuadOperandOperation("NEQ", yyvsp[-2].info.val, yyvsp[0].info.val, yyval.info.val);
                                            ;
    break;}
case 40:
#line 306 "bas.y"
{ 
                                              yyval.info.type = checkType(yyvsp[-2].info.type, yyvsp[0].info.type); 
                                              string ret = RegNoGen();
                                              strcpy(yyval.info.val, ret.c_str());
                                              printQuadOperandOperation("EQU", yyvsp[-2].info.val, yyvsp[0].info.val, yyval.info.val);
                                            ;
    break;}
case 41:
#line 312 "bas.y"
{ 
                                              yyval.info.type = yyvsp[0].info.type; 
                                              string ret = RegNoGen();
                                              strcpy(yyval.info.val, ret.c_str());
                                              printTripleOperandOperation("NOT", yyvsp[0].info.val, yyval.info.val);
                                            ;
    break;}
case 42:
#line 318 "bas.y"
{ 
                                              yyval.info.type = checkType(yyvsp[-2].info.type, yyvsp[0].info.type);
                                              string ret = RegNoGen(); 
                                              strcpy(yyval.info.val, ret.c_str());
                                              printQuadOperandOperation("AND", yyvsp[-2].info.val, yyvsp[0].info.val, yyval.info.val);
                                            ;
    break;}
case 43:
#line 324 "bas.y"
{ 
                                              yyval.info.type = checkType(yyvsp[-2].info.type, yyvsp[0].info.type); 
                                              string ret = RegNoGen();
                                              strcpy(yyval.info.val, ret.c_str());
                                              printQuadOperandOperation("OR", yyvsp[-2].info.val, yyvsp[0].info.val, yyval.info.val);
                                            ;
    break;}
case 44:
#line 330 "bas.y"
{ 
                                              yyval.info.type = yyvsp[-1].info.type; 
                                              string ret = RegNoGen();
                                              strcpy(yyval.info.val, ret.c_str());
                                              printTripleOperandOperation("MOV", yyvsp[-1].info.val, yyval.info.val);
                                            ;
    break;}
case 45:
#line 339 "bas.y"
{;
    break;}
case 46:
#line 340 "bas.y"
{;
    break;}
case 47:
#line 344 "bas.y"
{
                                    ++scopeID; 
                                    symbolTable.push_back(map<string, symNode> ());
                                  ;
    break;}
case 48:
#line 351 "bas.y"
{symbolTable.pop_back(); --scopeID;;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */
#line 498 "/cygnus/cygwin-b20/share/bison.simple"

  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YYLSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = yylloc.first_line;
      yylsp->first_column = yylloc.first_column;
      yylsp->last_line = (yylsp-1)->last_line;
      yylsp->last_column = (yylsp-1)->last_column;
      yylsp->text = 0;
    }
  else
    {
      yylsp->last_line = (yylsp+yylen-1)->last_line;
      yylsp->last_column = (yylsp+yylen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;

yyerrlab:   /* here on detecting error */

  if (! yyerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  int size = 0;
	  char *msg;
	  int x, count;

	  count = 0;
	  /* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
	  for (x = (yyn < 0 ? -yyn : 0);
	       x < (sizeof(yytname) / sizeof(char *)); x++)
	    if (yycheck[x + yyn] == x)
	      size += strlen(yytname[x]) + 15, count++;
	  msg = (char *) malloc(size + 15);
	  if (msg != 0)
	    {
	      strcpy(msg, "parse error");

	      if (count < 5)
		{
		  count = 0;
		  for (x = (yyn < 0 ? -yyn : 0);
		       x < (sizeof(yytname) / sizeof(char *)); x++)
		    if (yycheck[x + yyn] == x)
		      {
			strcat(msg, count == 0 ? ", expecting `" : " or `");
			strcat(msg, yytname[x]);
			strcat(msg, "'");
			count++;
		      }
		}
	      yyerror(msg);
	      free(msg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror("parse error");
    }

  goto yyerrlab1;
yyerrlab1:   /* here on error raised explicitly by an action */

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Discarding token %d (%s).\n", yychar, yytname[yychar1]);
#endif

      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;

yyerrdefault:  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (yyn) goto yydefault;
#endif

yyerrpop:   /* pop the current state because it cannot handle the error token */

  if (yyssp == yyss) YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#ifdef YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

yyerrhandle:

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;
}
#line 355 "bas.y"


void yyerror(char *s) {
  printf("%s at line: %d\n", s, yylineno);
  errFile << s << " at line " << yylineno << endl;
}

// generate register number string
string RegNoGen(){
  return "R" + to_string(RegID++);
}

void declareVar(char* varName, bool isConst, dataType datatype, string value, bool isInit, bool isUsed, int line){
    //check if already declared
    if(findVar(varName) != -1) {
        redefinitionError(varName);
        c_failed = true;  
        cout<<"scopeID: "<<scopeID<<endl;        
    }
    else{
      printTripleOperandOperation("MOV", value, varName);
      symbolTable[scopeID][varName] = symNode(isConst, datatype, value, isInit, isUsed, line);
      unusedVar.insert(varName); 
      symNode& n = symbolTable[scopeID][varName];
      n.printSym(varName);  
    }
    return;
}

void isDefined(char* varName){
    //check if defined before or not
    int idx = findVar(varName);
    if(idx == -1){
          notDefinedError(varName);
          c_failed = true;
    }
    else {
          symNode& n = symbolTable[idx][varName];
          if(n.isInit == 0){
            uninitializedWarning(varName);
          }
          if(n.isUsed != 1){
            n.isUsed = 1;
            n.line = yylineno;
            n.printSym(varName);
          }
          unusedVar.erase(varName);
    }
}

int findVar(char* varName){
    int currentScopeID = scopeID;
     for(int i = currentScopeID; i >= 0; i--){
       if(symbolTable[i].find(varName) != symbolTable[i].end()) return i;
     }
     return -1;
}

int checkType(int t1, int t2) {
    if(t1 != t2){
        conflictWarning();
    }
    return t1;
}

void assignVar(char* varName, char* value){
  int idx = findVar(varName);
   if(idx == -1){
      notDefinedError(varName);
      c_failed = true;
   }
   else {
     symNode& n = symbolTable[idx][varName];
     if(n.isConst){
        constError(varName);
        c_failed = true;
     }
     else {
       n.strValue = value;
       if(n.isInit != 1) {
          n.isInit = 1;
          n.line = yylineno;
          n.printSym(varName);
       }
       printTripleOperandOperation("MOV", value, varName);
     }
   }
}

// quadrables handlers
void printTripleOperandOperation(string opType, string src, char* dest){
  qudFile<<opType<<" \t"<<src<<" \t"<<dest<<"\n";
}

void printQuadOperandOperation(string opType, string src1, string src2, char* dest){
  qudFile<<opType<<" \t"<<src1<<" \t"<<src2<<" \t"<<dest<<"\n";
}


// Error handlers

void printErrors() {
    for (auto i : unusedVar) {
        errFile << "WARNING: Variable " << i << " is not used.\n";
    }
    if(c_failed){
      errFile << "Compilation Error.\n";
    }
    else {
      errFile << "Compiled Successfully.\n";
    }
}

void constError(char* varName){
  string str = "ERROR: variable ";
  str += varName;
  str += " is a constant and can not be changed at line " + to_string(yylineno) + '\n';
  errFile << str;
}

void notDefinedError(char* varName){
  string str = "ERROR: variable ";
  str += varName;
  str += " is not defined before line " + to_string(yylineno) + '\n';
  errFile << str;         
}

void uninitializedWarning(char* varName){
  string str = "WARNING: variable ";
  str += varName;
  str += " is not initialized before line " + to_string(yylineno) + '\n';
  errFile << str;
}

void conflictWarning() {
  errFile<<"WARNING: conflict data types at line: " + to_string(yylineno) + '\n';
}

void redefinitionError(char* varName){
  string str = "ERROR: variable: ";
  str += varName;
  str += " is defined before line: " + to_string(yylineno) + '\n';
  errFile << str;
}

void initSymFile() {
  symFile << "Variable Name\t\tConst\t\tDatatype\t\tValue\t\tInitialized\t\tUsed\t\tLine\n";
}

int main(void) {
  qudFile.open("quadrables.txt");
  errFile.open("Error Handler.txt");
  symFile.open("Symbol Table.txt");
  initSymFile();
  yyparse();
  return 0;
}