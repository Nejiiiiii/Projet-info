all.exec
CODE_FINAL.o:CODE_FINAL.c Fonctionsducode.h
              gcc -c CODE_FINAL.c -o CODE_FINAL.o

exec : CODE_FINAL.o
        gcc CODE_FINAL.o -o exec
