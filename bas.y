%{
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

%}

%union {
  char* val; 
      		
	char* name;

  struct info1{
    int type;
    char val[100];
  }info;
		

};


%token <val> INTEGER DECIMAL CHARACTER
%token <name> VAR
%token CONST INT FLOAT CHAR BOOL 
%token ENDOFFILE
%token GE LE GT LT EQ NE NOT AND OR 
%token B_TRUE B_FALSE

%left AND OR
%left GE LE EQ NE GT LT

%left '+' '-'
%left '*' '/'

%right NOT

%nonassoc UMINUS

%type <name> declaration
%type <info> expr 


%start program

%%
program: 
	function                                          {printErrors(); exit(0);}
	;
function:
		function stmt          											    {}
	| stmt
  |	ENDOFFILE																	      {}
	;

stmt:
   	';'																	         	{}
	|	declaration	';'															  {}
	|	assignment ';'															  {}
  | expr ';'                                      {}
  | Obrace nested_stmt Cbrace                     {}
  | Obrace Cbrace
  ;

declaration:
   CONST INT VAR '=' expr                   {
                                              checkType(T_INT, $5.type); 
                                              varType[$3] = T_INT; 
                                              declareVar($3, 1, T_INT, $5.val, 1, 0, yylineno);
                                            }
  | CONST FLOAT VAR '=' expr                {
                                              checkType(T_FLOAT, $5.type); 
                                              varType[$3] = T_FLOAT; 
                                              declareVar($3, 1, T_FLOAT, $5.val, 1, 0, yylineno);
                                            }
  | CONST CHAR VAR '=' expr                 {
                                              checkType(T_CHAR, $5.type); 
                                              varType[$3] = T_CHAR; 
                                              declareVar($3, 1, T_CHAR, $5.val, 1, 0, yylineno);
                                            }
  | CONST BOOL VAR '=' expr                 {
                                              checkType(T_BOOL, $5.type); 
                                              varType[$3] = T_BOOL; 
                                              declareVar($3, 1, T_BOOL, $5.val, 1, 0, yylineno);
                                            }
  
  
  | INT VAR '=' expr                        {
                                              checkType(T_INT, $4.type); 
                                              varType[$2] = T_INT; 
                                              declareVar($2, 0, T_INT, $4.val, 1, 0, yylineno);
                                            }
  | FLOAT VAR '=' expr                      {
                                              checkType(T_FLOAT, $4.type); 
                                              varType[$2] = T_FLOAT; 
                                              declareVar($2, 0, T_FLOAT, $4.val, 1, 0, yylineno);
                                            }
  | CHAR VAR '=' expr                       {
                                              checkType(T_CHAR, $4.type); 
                                              varType[$2] = T_CHAR; 
                                              declareVar($2, 0, T_CHAR, $4.val, 1, 0, yylineno);
                                            }
  | BOOL VAR '=' expr                       {
                                              checkType(T_BOOL, $4.type); 
                                              varType[$2] = T_BOOL; 
                                              declareVar($2, 0, T_BOOL, $4.val, 1, 0, yylineno);
                                            }
  
  
  | INT VAR                                 {
                                              varType[$2] = T_INT; 
                                              declareVar($2, 0, T_INT, "0", 0, 0, yylineno);
                                            }
  | FLOAT VAR                               {
                                              varType[$2] = T_FLOAT; 
                                              declareVar($2, 0, T_FLOAT, "0", 0, 0, yylineno);
                                            }
  | CHAR VAR                                {
                                              varType[$2] = T_CHAR; 
                                              declareVar($2, 0, T_CHAR, "", 0, 0, yylineno);
                                            }
  | BOOL VAR                                {
                                              varType[$2] = T_BOOL; 
                                              declareVar($2, 0, T_BOOL, "0", 0, 0, yylineno);
                                            }
  ;

assignment:
		VAR '=' expr 													  {
                                              checkType(varType[$1], $3.type); 
                                              assignVar($1, $3.val);
                                            }
	;

expr:
  INTEGER                                   { 
                                              $$.type = T_INT;
                                              string ret = RegNoGen();
                                              strcpy($$.val, ret.c_str());  
                                              printTripleOperandOperation("MOV", $1, $$.val);
                                            } 
  | DECIMAL                                 { 
                                              $$.type = T_FLOAT; 
                                              string ret = RegNoGen();
                                              strcpy($$.val, ret.c_str());
                                              printTripleOperandOperation("MOV", $1, $$.val);
                                            }
  | CHARACTER                               { 
                                              $$.type = T_CHAR; 
                                              string ret = RegNoGen();
                                              strcpy($$.val, ret.c_str());
                                              printTripleOperandOperation("MOV", $1, $$.val);
                                            }
  | VAR                                     {
                                              $$.type = varType[$1]; 
                                              string ret = RegNoGen();
                                              strcpy($$.val, ret.c_str()); 
                                              /*check if defined before*/
                                              isDefined($1);
                                              printTripleOperandOperation("MOV", $1, $$.val);
                                            } 
  | B_TRUE                               {
                                              $$.type = T_BOOL; 
                                              string ret = RegNoGen();
                                              strcpy($$.val, ret.c_str());
                                              printTripleOperandOperation("MOV", "1", $$.val);
                                            }
  | B_FALSE                              {
                                              $$.type = T_BOOL; 
                                              string ret = RegNoGen();
                                              strcpy($$.val, ret.c_str());
                                              printTripleOperandOperation("MOV", "0", $$.val);
                                            }

  | '-' expr %prec UMINUS                   {
                                              $$.type = $2.type;
                                              string ret = RegNoGen(); 
                                              strcpy($$.val, ret.c_str());
                                              printTripleOperandOperation("NEG", $2.val, $$.val);
                                            }
  | expr '+' expr                           { 
                                              $$.type = checkType($1.type, $3.type); 
                                              string ret = RegNoGen(); 
                                              strcpy($$.val, ret.c_str());
                                              printQuadOperandOperation("ADD",$1.val,$3.val,$$.val);
                                            }
  | expr '-' expr                           { 
                                              $$.type = checkType($1.type, $3.type); 
                                              string ret = RegNoGen();
                                              strcpy($$.val,ret.c_str());
                                              printQuadOperandOperation("SUB", $1.val, $3.val, $$.val);
                                            }
  | expr '*' expr                           { 
                                              $$.type = checkType($1.type, $3.type); 
                                              string ret = RegNoGen();
                                              strcpy($$.val, ret.c_str());
                                              printQuadOperandOperation("MUL", $1.val, $3.val, $$.val);
                                            }
  | expr '/' expr                           { 
                                              $$.type = checkType($1.type, $3.type); 
                                              string ret = RegNoGen();
                                              strcpy($$.val, ret.c_str());
                                              printQuadOperandOperation("DIV", $1.val, $3.val, $$.val);
                                            }
  | expr LT expr                            { 
                                              $$.type = checkType($1.type, $3.type); 
                                              string ret = RegNoGen();
                                              strcpy($$.val, ret.c_str());
                                              printQuadOperandOperation("LTN", $1.val, $3.val, $$.val);
                                            }
  | expr GT expr                            { 
                                              $$.type = checkType($1.type, $3.type); 
                                              string ret = RegNoGen();
                                              strcpy($$.val, ret.c_str());
                                              printQuadOperandOperation("GTN", $1.val, $3.val, $$.val);
                                            }
  | expr GE expr                            { 
                                              $$.type = checkType($1.type, $3.type); 
                                              string ret = RegNoGen();
                                              strcpy($$.val, ret.c_str());
                                              printQuadOperandOperation("GTE", $1.val, $3.val, $$.val);
                                            }
  | expr LE expr                            { 
                                              $$.type = checkType($1.type, $3.type);
                                              string ret = RegNoGen(); 
                                              strcpy($$.val, ret.c_str());
                                              printQuadOperandOperation("LTE", $1.val, $3.val, $$.val);
                                            }
  | expr NE expr                            { 
                                              $$.type = checkType($1.type, $3.type);
                                              string ret = RegNoGen(); 
                                              strcpy($$.val, ret.c_str());
                                              printQuadOperandOperation("NEQ", $1.val, $3.val, $$.val);
                                            }
  | expr EQ expr                            { 
                                              $$.type = checkType($1.type, $3.type); 
                                              string ret = RegNoGen();
                                              strcpy($$.val, ret.c_str());
                                              printQuadOperandOperation("EQU", $1.val, $3.val, $$.val);
                                            }
  | NOT expr                                { 
                                              $$.type = $2.type; 
                                              string ret = RegNoGen();
                                              strcpy($$.val, ret.c_str());
                                              printTripleOperandOperation("NOT", $2.val, $$.val);
                                            }
  | expr AND expr                           { 
                                              $$.type = checkType($1.type, $3.type);
                                              string ret = RegNoGen(); 
                                              strcpy($$.val, ret.c_str());
                                              printQuadOperandOperation("AND", $1.val, $3.val, $$.val);
                                            }
  | expr OR expr                            { 
                                              $$.type = checkType($1.type, $3.type); 
                                              string ret = RegNoGen();
                                              strcpy($$.val, ret.c_str());
                                              printQuadOperandOperation("OR", $1.val, $3.val, $$.val);
                                            }
  | '(' expr ')'                            { 
                                              $$.type = $2.type; 
                                              string ret = RegNoGen();
                                              strcpy($$.val, ret.c_str());
                                              printTripleOperandOperation("MOV", $2.val, $$.val);
                                            }
  ;

nested_stmt:
    nested_stmt stmt                                  {}
  | stmt                                              {}
  ;

Obrace:
            '{'                   {
                                    ++scopeID; 
                                    symbolTable.push_back(map<string, symNode> ());
                                  }
             ;

Cbrace:
             '}'                                  {symbolTable.pop_back(); --scopeID;}
             ;


%%

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