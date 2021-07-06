#include <stdio.h>
#include <stdlib.h>

int main(){
printf("[---- [임상우]   [2018038072] ----]\n");
int list[5];
int *plist[5];

list[0]=10;     //list[0]초기화
list[1]=11;     //list[1]초기화

plist[0]=(int*)malloc(sizeof(int));     //plist[0]에 동적할당 4바이트한 메모리의 주소값으로 초기화

printf("list[0] \t= %d\n",list[0]);                         //list[0]은 초기화한대로 10이나온다
printf("address of list \t= %p\n", list);                         
printf("address of list[0] \t= %p\n", &list[0]);
printf("address of list + 0 \t= %p\n", list+0);             //list==&list[0]==list+0
printf("address of list + 1 \t= %p\n", list+1);             //(list+1)==&list[1]이므로 list[1]의 주솟값이나온다.
printf("address of list + 2 \t= %p\n", list+2);
printf("address of list + 3 \t= %p\n", list+3);             
printf("address of list + 4 \t= %p\n", list+4);             //출력값을 보면 끝에 자릿수가 4씩늘어나는 것을 알 수 있다.
                                                            //그 이유는 list가 int형이기때문에 스택영역에 4바이트씩 메모리를 할당받아
                                                            //list의 각각 인접한 인덱스의 주솟값은 4바이트씩 차이나는 것이다.
printf("address of list[4] \t= %p\n", &list[4]);        

free(plist[0]); //plist[0]동적할당 해제

    return 0;
}