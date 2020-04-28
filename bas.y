%{
#include <bits/stdc++.h>
using namespace std;

ofstream qudFile, symFile, errFile;
map<string, string> varValue;
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

string typeArr[] = {"UNDEFINED",
  "BOOL",
  "INT",
  "FLOAT",
  "CHAR"};
// Symbol Table node
struct symNode{
	bool isConst;
	dataType type;
	string Value;
	bool isInit;
	bool isUsed;
	int line;

	symNode(bool isConst = 0, dataType type = UNDEFINED, string val = "", bool isInit = 0, bool isUsed = 0, int line = 0) 
		: isConst(isConst), type(type), Value(val), isInit(isInit), isUsed(isUsed), line(line) {}


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
     symFile<<varName<<setw(15)<<this->isConst<<setw(15)<<t_str<<setw(15)<<varValue[this->Value]<<setw(15)<<this->isInit<<setw(15)<<this->isUsed<<setw(15)<<this->line<<"\n";
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
void exitCompilation(void);
void constError(char*);
void notDefinedError(char*);
void uninitializedError(char*);
void conflictWarning(void);
void redefinitionError(char*);
void symboTableFileInit(void);
void tripleOperation(string, string, char*);
void quadOperation(string, string, string, char*);
string castType(dataType, char*);

%}

%union {
  char* val;    		
	char* name;
  
  struct Type_Value{
    int type;
    char val[100];
  }Type_Value;
};


%token <val> INTEGER DECIMAL CHARACTER
%token <name> VAR
%token CONST INT FLOAT CHAR BOOL 
%token ENDOFFILE
%token B_TRUE B_FALSE

%left '+' '-'
%left '*' '/'

%nonassoc UMINUS

%type <name> declaration
%type <Type_Value> expr 


%start program

%%
program: 
	function                                          {exitCompilation();}
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
                                              varValue[$5.val] = castType(T_INT, (char*)varValue[$5.val].c_str());
                                              declareVar($3, 1, T_INT, $5.val, 1, 0, yylineno);
                                            }
  | CONST FLOAT VAR '=' expr                {
                                              checkType(T_FLOAT, $5.type); 
                                              varType[$3] = T_FLOAT; 
                                              varValue[$5.val] = castType(T_FLOAT, (char*)varValue[$5.val].c_str());
                                              declareVar($3, 1, T_FLOAT, $5.val, 1, 0, yylineno);
                                            }
  | CONST CHAR VAR '=' expr                 {
                                              checkType(T_CHAR, $5.type); 
                                              varType[$3] = T_CHAR; 
                                              varValue[$5.val] = castType(T_CHAR, (char*)varValue[$5.val].c_str());
                                              declareVar($3, 1, T_CHAR, $5.val, 1, 0, yylineno);
                                            }
  | CONST BOOL VAR '=' expr                 {
                                              checkType(T_BOOL, $5.type); 
                                              varType[$3] = T_BOOL; 
                                              varValue[$5.val] = castType(T_BOOL, (char*)varValue[$5.val].c_str());
                                              declareVar($3, 1, T_BOOL, $5.val, 1, 0, yylineno);
                                            }
  
  
  | INT VAR '=' expr                        {
                                              checkType(T_INT, $4.type); 
                                              varType[$2] = T_INT;
                                              varValue[$4.val] = castType(T_INT, (char*)varValue[$4.val].c_str());
                                              declareVar($2, 0, T_INT , $4.val, 1, 0, yylineno);
                                            }
  | FLOAT VAR '=' expr                      {
                                              checkType(T_FLOAT, $4.type); 
                                              varType[$2] = T_FLOAT; 
                                              varValue[$4.val] = castType(T_FLOAT, (char*)varValue[$4.val].c_str());
                                              declareVar($2, 0, T_FLOAT, $4.val, 1, 0, yylineno);
                                            }
  | CHAR VAR '=' expr                       {
                                              checkType(T_CHAR, $4.type); 
                                              varType[$2] = T_CHAR;
                                              varValue[$4.val] = castType(T_CHAR, (char*)varValue[$4.val].c_str());
                                              declareVar($2, 0, T_CHAR, $4.val, 1, 0, yylineno);
                                            }
  | BOOL VAR '=' expr                       {
                                              checkType(T_BOOL, $4.type); 
                                              varType[$2] = T_BOOL; 
                                              varValue[$4.val] = castType(T_BOOL, (char*)varValue[$4.val].c_str());
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
                                              declareVar($2, 0, T_CHAR, "0", 0, 0, yylineno);
                                            }
  | BOOL VAR                                {
                                              varType[$2] = T_BOOL; 
                                              declareVar($2, 0, T_BOOL, "0", 0, 0, yylineno);
                                            }
  ;

assignment:
		VAR '=' expr 													  {
                                              checkType(varType[$1], $3.type);
                                              varValue[$3.val] = castType(varType[$1], (char*)varValue[$3.val].c_str());
                                              assignVar($1, $3.val);
                                            }
	;

expr:
  INTEGER                                   { 
                                              $$.type = T_INT;
                                              string ret = RegNoGen();
                                              varValue[ret] = to_string(atoi($1));
                                              strcpy($$.val, ret.c_str());  
                                              tripleOperation("MOV", $1, $$.val);
                                            } 
  | DECIMAL                                 { 
                                              $$.type = T_FLOAT; 
                                              string ret = RegNoGen();
                                              varValue[ret] = to_string(atof($1));
                                              strcpy($$.val, ret.c_str());
                                              tripleOperation("MOV", $1, $$.val);
                                            }
  | CHARACTER                               { 
                                              $$.type = T_CHAR; 
                                              string ret = RegNoGen();
                                              varValue[ret] = $1;
                                              strcpy($$.val, ret.c_str());
                                              tripleOperation("MOV", $1, $$.val);
                                            }
  | VAR                                     {
                                              $$.type = varType[$1]; 
                                              isDefined($1);
                                              if(!c_failed){
                                                string ret = RegNoGen();
                                                int scID = findVar($1);
                                                symNode& n = symbolTable[scID][$1];
                                                varValue[ret] = varValue[n.Value];
                                                strcpy($$.val, ret.c_str()); 
                                                tripleOperation("MOV", $1, $$.val);
                                              }
                                              else{
                                                yyerror("terminating due to an undefined variable error");
                                                exitCompilation();
                                              }
                                            } 
  | B_TRUE                               {
                                              $$.type = T_BOOL; 
                                              string ret = RegNoGen();
                                              varValue[ret] = "1";
                                              strcpy($$.val, ret.c_str());
                                              tripleOperation("MOV", "1", $$.val);
                                            }
  | B_FALSE                              {
                                              $$.type = T_BOOL; 
                                              string ret = RegNoGen();
                                              varValue[ret] = "0";
                                              strcpy($$.val, ret.c_str());
                                              tripleOperation("MOV", "0", $$.val);
                                            }

  | '-' expr %prec UMINUS                   {
                                              $$.type = $2.type;
                                              string ret = RegNoGen();
                                              string s = $2.val;
                                              if($$.type == T_INT) varValue[ret] = to_string(-stoi(varValue[s]));
                                              else if($$.type == T_FLOAT) varValue[ret] = to_string(-stof(varValue[s]));
                                              else{
                                                string str = "Incompatible operation with the type ";
                                                str += typeArr[$$.type];
                                                yyerror((char*)str.c_str());
                                                c_failed = true;
                                                exitCompilation();
                                              }
                                              strcpy($$.val, ret.c_str());
                                              tripleOperation("NEG", $2.val, $$.val);
                                            }
  | expr '+' expr                           { 
                                              $$.type = checkType($1.type, $3.type); 
                                              string ret = RegNoGen(); 
                                              string s1 = $1.val;
                                              string s2 = $3.val;
                                              if($$.type == T_INT) varValue[ret] = to_string(stoi(varValue[s1]) + stoi(varValue[s2]));
                                              else if($$.type == T_FLOAT) varValue[ret] = to_string(stof(varValue[s1]) + stof(varValue[s2]));
                                              else{
                                                string str = "Incompatible operation with the type ";
                                                str += typeArr[$$.type];
                                                yyerror((char*)str.c_str());
                                                c_failed = true;
                                                exitCompilation();
                                              }
                                              strcpy($$.val, ret.c_str());
                                              quadOperation("ADD",$1.val,$3.val,$$.val);
                                            }
  | expr '-' expr                           { 
                                              $$.type = checkType($1.type, $3.type); 
                                              string ret = RegNoGen();
                                              string s1 = $1.val;
                                              string s2 = $3.val;
                                              if($$.type == T_INT) varValue[ret] = to_string(stoi(varValue[s1]) - stoi(varValue[s2]));
                                              else if($$.type == T_FLOAT) varValue[ret] = to_string(stof(varValue[s1]) - stof(varValue[s2]));
                                              else{
                                                string str = "Incompatible operation with the type ";
                                                str += typeArr[$$.type];
                                                yyerror((char*)str.c_str());
                                                c_failed = true;
                                                exitCompilation();
                                              }
                                              strcpy($$.val,ret.c_str());
                                              quadOperation("SUB", $1.val, $3.val, $$.val);
                                            }
  | expr '*' expr                           { 
                                              $$.type = checkType($1.type, $3.type); 
                                              string ret = RegNoGen();
                                              string s1 = $1.val;
                                              string s2 = $3.val;
                                              if($$.type == T_INT) varValue[ret] = to_string(stoi(varValue[s1]) * stoi(varValue[s2]));
                                              else if($$.type == T_FLOAT) varValue[ret] = to_string(stof(varValue[s1]) * stof(varValue[s2]));
                                              else{
                                                string str = "Incompatible operation with the type ";
                                                str += typeArr[$$.type];
                                                yyerror((char*)str.c_str());
                                                c_failed = true;
                                                exitCompilation();
                                              }
                                              strcpy($$.val, ret.c_str());
                                              quadOperation("MUL", $1.val, $3.val, $$.val);
                                            }
  | expr '/' expr                           { 
                                              $$.type = checkType($1.type, $3.type); 
                                              string ret = RegNoGen();
                                              string s1 = $1.val;
                                              string s2 = $3.val;
                                              if(!stoi(varValue[s2])){
                                                c_failed = true;
                                                yyerror("terminating due to divide by zero error...");
                                                exitCompilation();
                                              }
                                              else{
                                                if($$.type == T_INT) varValue[ret] = to_string(stoi(varValue[s1]) / stoi(varValue[s2]));
                                                else if($$.type == T_FLOAT) varValue[ret] = to_string(stof(varValue[s1]) / stof(varValue[s2]));
                                                else{
                                                  string str = "Incompatible operation with the type ";
                                                  str += typeArr[$$.type];
                                                  yyerror((char*)str.c_str());
                                                  c_failed = true;
                                                  exitCompilation();
                                                }
                                                strcpy($$.val, ret.c_str());
                                                quadOperation("DIV", $1.val, $3.val, $$.val);
                                              }
                                              
                                            }
  | '(' expr ')'                            { 
                                              $$.type = $2.type; 
                                              string ret = RegNoGen();
                                              varValue[ret] = varValue[$2.val];
                                              strcpy($$.val, ret.c_str());
                                              tripleOperation("MOV", $2.val, $$.val);
                                            }
  ;

nested_stmt:
    nested_stmt stmt                                  {}
  | stmt                                              {}
  ;

Obrace:
            '{'                   {
                                    scopeID++; 
                                    symbolTable.push_back(map<string, symNode> ());
                                  }
             ;

Cbrace:
             '}'                                  {symbolTable.pop_back(); scopeID--;}
             ;


%%

void yyerror(char *s) {
  printf("line %d : %s \n", yylineno, s);
  errFile << "line " << yylineno << " : " << s << endl;
}

string castType(dataType typ, char* obj){
    string ret = "";
    stringstream ss;
    switch(typ){
      case T_BOOL:
        {
          bool x = obj;
          ss << x;
          ss >> ret;
          break;
        }
      case T_INT:
        {
          int x = atoi(obj);
          ss << x;
          ss >> ret;
          break;
        }
      case T_FLOAT:
        {
          float x = atof(obj);
          ss << x;
          ss >> ret;
          break;
        }
      case T_CHAR:
        {
          ret = obj;
          break;
        }
      default:
        break;
    }
    return ret;
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
        //cout<<"scopeID: "<<scopeID<<endl;        
    }
    else{
      tripleOperation("MOV", value, varName);
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
            uninitializedError(varName);
            c_failed = true;
            yyerror("terminating due to using uninitialized variable error..");
            exitCompilation();
          }
          n.isUsed = 1;
          n.line = yylineno;
          n.printSym(varName);
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
        n.Value = value;
        n.isInit = 1;
        n.line = yylineno;
        n.printSym(varName);
       tripleOperation("MOV", value, varName);
     }
   }
}

// Triples
void tripleOperation(string opType, string src, char* dest){
  qudFile<<opType<<" \t"<<src<<" \t"<<dest<<"\n";
}

// Quadruples
void quadOperation(string opType, string src1, string src2, char* dest){
  qudFile<<opType<<" \t"<<src1<<" \t"<<src2<<" \t"<<dest<<"\n";
}


// Error handlers

void exitCompilation() {
    for (auto i : unusedVar) {
        errFile << "WARNING: Variable " << i << " is not used.\n";
    }
    if(c_failed){
      errFile << "Compilation Error.\n";
    }
    else {
      errFile << "Compiled Successfully.\n";
    }
    exit(0);
}

void constError(char* varName){
  string str = "line " + to_string(yylineno) + " : ERROR: variable ";
  str += varName;
  str += " is a constant and can not be changed.\n";
  errFile << str;
}

void notDefinedError(char* varName){
  string str = "line " + to_string(yylineno) + " : ERROR: variable ";
  str += varName;
  str += " is not defined.\n";
  errFile << str;         
}

void uninitializedError(char* varName){
  string str = "line " + to_string(yylineno) + " : ERROR: variable ";
  str += varName;
  str += " is not initialized.\n";
  errFile << str;
}

void conflictWarning() {
  errFile<<"line " + to_string(yylineno) + " : WARNING: conflict data types.\n";
}

void redefinitionError(char* varName){
  string str = "line " + to_string(yylineno) + " : ERROR: variable: ";
  str += varName;
  str += " is already defined.\n";
  errFile << str;
}

void initSymFile() {
  symFile << "Name"<<setw(15)<<"Const"<<setw(15)<<"Datatype"<<setw(15)<<"Value"<<setw(15)<<"Initialized"<<setw(15)<<"Used"<<setw(15)<<"Line\n";
}

int main(void) {
  qudFile.open("Quadrables.txt");
  errFile.open("Error_Handler.txt");
  symFile.open("Symbol_Table.txt");
  initSymFile();
  yyparse();
  return 0;
}