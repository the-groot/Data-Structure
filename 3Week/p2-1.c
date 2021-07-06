#include <stdio.h>

#define MAX_SIZE 100        //#define으로 MAX_SIZE를 100으로 정의

float sum(float[], int);
float input[MAX_SIZE],answer;   //배열의 크기가 100인 input, answer선언
int i;

int main() {
    printf("[---- [임상우]   [2018038072] ----]\n");

for(i=0; i<MAX_SIZE; i++)
    input[i]=i;             //input[0]=0, input[1]=1 이렇게 100까지 채움

    
   
    printf("address of input = %p\n",&input);    //&input[0]의 값 출력


    answer=sum(input, MAX_SIZE);                //sum 함수에 input[0]의 주솟값과 MAX_SIZE전달 그리고 반환값 answer에 저장
    printf("The sum is: %f\n",answer);          //input[0]~input[100]의합 4950출력

    return 0;
}

float sum(float list[], int n){
    printf("value of list = %p\n",list);            //main함수에서 &input==input일것이다.
    printf("address of list = %p\n\n",&list);       //하지만 sum함수에서는 list!=&list이다.
                                                    //그이유는 float list[]는 얼핏보면 배열형태같지만
                                                    //float *list 포인터 변수라고 보면 된다.
                                                    //main함수에서 sum함수를 호출할때 input의 주소를 넘겨줬다.
                                                    //따라서 list에 담겨있는 것은 input[0]의 주솟값이고,
                                                    //&list는 스택영역에 생긴 list라는 포인터 변수 자체의 주소이다.

    int i;
    float tempsum=0;
    for(i=0; i<n; i++)
        tempsum+=list[i];       //list[0]~list[100]의 합

        return tempsum;     //tempsum 리턴
    
}