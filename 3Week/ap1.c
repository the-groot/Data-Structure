#include <stdio.h>
#include <stdlib.h>     //malloc 라이브러리 함수

int main() {
    printf("[---- [임상우]   [2018038072] ----]\n");

int list[5];                //int형 배열
int *plist[5]={NULL,};      //포인터형 배열 NULL로 초기화함

plist[0]=(int*)malloc(sizeof(int));     //plist[0]에 힙영역의 4바이트 메모리의 주솟값 할당(동적할당 malloc)

list[0]=1;  //list[0] 초기화
list[1]=100;    //list[1] 초기화

*plist[0]=200;  //plist[0]에 담긴 주솟값에 할당된 메모리 안의 값 200으로 초기화

printf("value of list[0]        = %d\n",list[0]);       //list[0]은 그대로 1
printf("address of list[0]      = %p\n",&list[0]);      // &list[0]==list==&list
printf("value of list           = %p\n",list);          //배열의 이름에는 첫번째 인덱스의 주솟값이 담긴 것을 확인가능
printf("address of list (&list) = %p\n",&list);

printf("-------------------------------------------------\n\n");
printf("value of list[1]    = %d\n",list[1]);       //list[1]은 그대로 100
printf("address of list[1]  = %p\n", &list[1]);     
printf("value of *(list+1)  = %d\n", *(list+1));    //list가 int형 이기때문에 (list+1)은 &list[0]의 메모리주솟값에 4바이트를 더한게 된다
                                                    //즉 (list+1)==&list[1]이고 그 주솟값의 값을 참조하면 list[1]=100이나온다
                                                    //*(list+1)==list[1] 임을 확인가능
printf("address of list+1   = %p\n", list+1);       //이와 마찬가지로 list+1==&list[1]임을 확인가능

printf("-------------------------------------------------\n\n");

printf("value of *plist[0] = %d\n",*plist[0]);      //plist[0]에는 힙영역의 메모리가 들어있고, *plist[0] 힙영역의 메모리에 저장된 값을
                                                    //참조하면 아까 초기화한 200이나온다
printf("&plist[0]          = %p\n", &plist[0]);     //&plist[0]은 스택영역에 생성된 주솟값이다
printf("&plist             = %p\n", &plist);        
printf("plist              = %p\n", plist);         //&plist[0]==plist==&plist
printf("plist[0]           = %p\n",plist[0]);       //plist[0]을 출력했을때 나오는 주솟값은
                                                    //&plist[0]과 다르다 
                                                    //&plist[0]은 스택영역, plist[0]은 힙영역의 메모리 주소가 저장돼있다.
printf("plist[1]           = %p\n",plist[1]);
printf("plist[2]           = %p\n",plist[2]);
printf("plist[3]           = %p\n",plist[3]);
printf("plist[4]           = %p\n",plist[4]);       //plist[0]을 제외한 인덱스들은 null로 초기화돼있기 때문에 널이 출력된다.


free(plist[0]);     //동적할당 해제

    return 0;
}