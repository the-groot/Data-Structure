#include <stdio.h>

void print1(int* ptr, int rows);

int main() {
    printf("[---- [임상우]   [2018038072] ----]\n");

int one[]={0,1,2,3,4};      //1차원 배열 선언그

printf("one     =  %p\n",one);
printf("&one    =  %p\n",&one);
printf("&one[0] =  %p\n" ,&one[0]);         //one==&one==&one[0]
printf("\n");

print1(&one[0], 5);     //one[0]의 주소와 배열의 크기 전달







    return 0;
}


void print1 (int* ptr, int rows){

    int i;
    printf("Address \t Contents\n");
    for(i=0; i<rows; i++)
    printf("%p \t   %5d\n",ptr+i,*(ptr+i));     //ptr+i==&ptr[i]의 값&(&one[i])과 *(ptr+i)==ptr[i]의 값(one[i])출력                                             
    printf("\n");                                //one배열이 int형이기 때문에 주솟값이 4바이트씩 는다.
}