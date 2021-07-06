#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("[---- [임상우]   [2018038072] ----]\n");

    int **x;        //더블형 포인터 변수 선언

    printf("sizeof(x) = %lu\n",sizeof(x));      //주솟값의 크기
    printf("sizeof(*x) = %lu\n",sizeof(*x));    //주솟값의 크기
    printf("sizeof(**x) =  %lu\n", sizeof(**x));    //주솟값을 담는 메모리의 형의 크기

    //x는 더블포인터이기때문에 x와 *x는 주솟값을 가리킨다 그래서 sizeof()를하면 32비트 machine에서는 4바이트 64비트 machine에서는 8바이트가 나올것이다
    //그런데 **x는 가리키는 주소에 저장된 값을 가리킨다 
    //그래서 sizeof(**x)를하면 가리키는 주소의 크기가아니라 가리키는 주소의 메모리의 크기가 몇인지를 출력한다
    //x는 int형으로 선언됐기때문에 int형 변수의 주솟값을 가리키다보면 마지막으로 가리킨
    //메모리의 byte는 4바이트가나온다 





    return 0;
}