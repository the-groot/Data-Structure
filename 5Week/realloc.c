#include <stdio.h>
#include <stdlib.h>

void main(){

    int size=10;
    int *mp=(int*)malloc(sizeof(int)*size);

    printf("mp addresss:%p\n",mp);

    mp=(int *)realloc(mp,sizeof(int)*100);
    printf("mp addresss:%p\n",mp);

}