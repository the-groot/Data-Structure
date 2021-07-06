#include <stdio.h>

struct student {            //구조체 선언
    char lastName[13];      //13바이트
    int studentId;          //4바이트
    short grade;            //2바이트
};

int main() {
    printf("[---- [임상우]   [2018038072] ----]\n");
    struct student pst;     //변수하나선언

    printf("size of student = %ld\n",sizeof(struct student));   //원래라면 13+4+2=19바이트가 나올걸 예상했지만
                                                                //24바이트가나온다 그러면 5바이트는 어디서 추가된걸까
                                                                //padding으로 인한 현상인데
                                                                //구조체에서 lastName이 메모리상 1바이트씩 13개 구현되는것이아니라
                                                                //4바이트씩 4개를 생성하기때문에 3바이트가 추가되고
                                                                //short도 4바이트로 생성돼 2바이트가 더 추가되어 결국 student의 size는 24가 나온다.
    printf("size of int = %ld\n",sizeof(int));      //4바이트
    printf("size of short = %ld\n",sizeof(short));  //2바이트





    return 0;
}