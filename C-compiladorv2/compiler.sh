flex cminus.l
bison -d cminus.y
cc -c *.c
cc -o compiler *.o -ly -ll
rm -rf *.o
rm -rf *.yy.*
rm -rf *.gch
