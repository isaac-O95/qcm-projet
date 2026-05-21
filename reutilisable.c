#include <stdio.h>
#include "reutilisable.h"

void ViderBuffer(void){
  int c;
do {
    c = getchar();
} while(c != '\n');
}

