del bas.tab.c
del bas.tab.h
del lex.yy.c
del bas.exe
flex bas.l
bison bas.y -d
g++ bas.tab.c lex.yy.c -o bas.exe
.\bas.exe < source_code.cpp
