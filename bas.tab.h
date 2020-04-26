typedef union {
  char* val; 
      		
	char* name;

  struct info1{
    int type;
    char val[100];
  }info;
		

} YYSTYPE;
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


extern YYSTYPE yylval;
