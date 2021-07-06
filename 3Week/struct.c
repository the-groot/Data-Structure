#include <stdio.h>

struct student1 {   //struct로만 구조체 선언
    char lastName;
    int studentId;
    char grade;
};

typedef struct {        //typedef을 써서 구조체 선언
    char lastName;
    int studentId;
    char grade;
}student2;

int main() {
    printf("[---- [임상우]   [2018038072] ----]\n");
    struct student1 st1= {'A',100,'A'}; //student1은 struct로만 선언해서 첫 선언시 struct를 붙여서 작성해야함

    printf("st1.lastName = %c\n",st1.lastName);
    printf("st1.studentId = %d\n",st1.studentId);
    printf("st1.grade = %c\n",st1.grade);           // studnet1의 lastName,studentId,grade는 A,100,A로초기화했으니 그대로 값이 나온다
                                            
    student2 st2={'B',200,'B'};     //studnet2는 typedef을 했기때문에 따로 struct를 붙이지 않아도된다.

    printf("\nst2.lastName = %c\n",st2.lastName);
    printf("st2.studentId = %d\n",st2.studentId);
    printf("st2.grade = %c\n",st2.grade);   //student2의 lastName,studentId,grad는 B,200,B로 초기화했으니 그대로 값이 나온다

    student2 st3;   //st3변수 새로 선언

    st3=st2;        //st2를 st3에 대입

    printf("\nst3.lastName = %c\n",st3.lastName);
    printf("st3.studentId = %d\n",st3.studentId);
    printf("st3.grade = %c\n",st3.grade);   //st3의 변수들이 st2의 변수들과 값이 같게 나온다 대입이 제대로 되었다.

    /* equality test */
    /*if(st3==st2)                              //구조체 전체 비교연산은 불가능
    printf("equal\n");
    else 
    printf("not equal\n");
    */
    return 0;
}