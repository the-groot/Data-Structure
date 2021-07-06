#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Method Declaration */
int** create_matrix(int row, int col);                  //배열 동적할당하는 함수
void print_matrix(int** matrix, int row, int col);      //배열에 저장된 값 출력하는 함수
int free_matrix(int** matrix, int row, int col);        //동적할당 해제하는 함수
int fill_data(int** matrix, int row, int col);          //배열에 랜덤으로 데이터 입력하는 함수
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col);  //a배열과 b배열 더하는 함수
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col);   //a배열과 b배열 빼는 함수
int transpose_matrix(int** matrix, int** matrix_t, int row, int col);       //전치행렬을 구하는 함수
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col);      //a배열과 b배열을 곱하는 함수

int main()
{

    char command;       //메뉴 입력값
    printf("[----- [임상우]  [2018038072] -----]\n");

    int row, col;
    srand(time(NULL));  //난수생성

    printf("Input row and col : ");
    scanf("%d %d", &row, &col);
    int** matrix_a = create_matrix(row, col);   //입력받은 row,col으로 동적할당한 배열 생성
    int** matrix_b = create_matrix(row, col);
    int** matrix_a_t = create_matrix(col, row);

    printf("Matrix Created.\n");

    if (matrix_a == NULL || matrix_b == NULL) { return -1; }  //비정상종료

    do {
        printf("----------------------------------------------------------------\n");
        printf("                     Matrix Manipulation                        \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize Matrix   = z           Print Matrix        = p \n");
        printf(" Add Matrix          = a           Subtract Matrix     = s \n");
        printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");
        printf(" Quit                = q \n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command);

        switch (command) {       //command값에 따라 동작 구현
        case 'z': case 'Z':     //z나Z는 fill_data호출
            printf("Matrix Initialized\n");
            fill_data(matrix_a, row, col);
            fill_data(matrix_b, row, col);
            break;
        case 'p': case 'P':     //p나P는 print_matrix호출
            printf("Print matrix\n");
            printf("matrix_a\n");
            print_matrix(matrix_a, row, col);
            printf("matrix_b\n");
            print_matrix(matrix_b, row, col);
            break;
        case 'a': case 'A': //a나A는 addition_matrix호출
            printf("Add two matrices\n");
            addition_matrix(matrix_a, matrix_b, row, col);
            break;
        case 's': case 'S': //s나S는 subtraction_matrix호출
            printf("Subtract two matrices \n");
            subtraction_matrix(matrix_a, matrix_b, row, col);
            break;
        case 't': case 'T': //t나T는 transpose_matrix와 print_matrix호출
            printf("Transpose matrix_a \n");
            printf("matrix_a\n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            print_matrix(matrix_a_t, col, row);
            break;
        case 'm': case 'M':     //m이나 M은 transpose_matrix와 mutiply_matrix호출
            printf("Multiply matrix_a with transposed matrix_a \n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            multiply_matrix(matrix_a, matrix_a_t, row, col);
            break;
        case 'q': case 'Q':     //q나 Q는 free_matrix를 호출
            printf("Free all matrixes..\n");
            free_matrix(matrix_a_t, col, row);
            free_matrix(matrix_a, row, col);
            free_matrix(matrix_b, row, col);
            break;
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");  //나머지값을입력했을때 Concentration을 출력한다.
            break;
        }

    } while (command != 'q' && command != 'Q');       //q나 Q가 입력되면 종료된다.



    return 1;
}

/* create a 2d array whose size is row x col using malloc() */
int** create_matrix(int row, int col)
{


    /*check pre conditions */

    if (row <= 0 || col <= 0) {
        printf("Check the sizes of row and col!\n");
        return NULL;
    }

    int** matrix = (int**)malloc(sizeof(int*) * row);   //더블형포인터인 matrix에 행의 개수만큼 동적할당한다
                                                    //matrix[0],matrix[1],..matrix[row-1]에는 heap영역의 주소가 담기므로
                                                    //선언할때 sizeof(int*)로 선언하고 더블형 포인터로 malloc을 할당해야한다.

    for (int i = 0; i < row; i++) {
        matrix[i] = (int*)malloc(sizeof(int) * col);        //그 후에 열의개수만큼 동적할당한다
    }

    //


    /*check post conditions*/
    if (matrix == NULL) {
        printf("matrix is Null\n");
        return NULL;
    }


    return matrix;        //matrix를 리턴한다.
}

/* print matrix whose size is row x col */
void print_matrix(int** matrix, int row, int col)
{



    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            printf("%d\t", matrix[i][j]);     //행과 열에 저장된 값을 간격에 맞춰 출력한다.
        }
        printf("\n");
    }



}


/* free memory allocated by create_matrix() */
int free_matrix(int** matrix, int row, int col)
{
    /*check pre conditons*/
    if (row <= 0 || col <= 0) {
        printf("Check the sizes of row and col!\n");
        return -1;      //비정상종료
    }


    for (int i = 0; i < row; i++) {       //우선 matrix[i]가 가리키고 있는 heap영역의 주소를 할당해제하고
        free(matrix[i]);
    }

    free(matrix);           //matrix가 가리키고 있는 heap영역의 주소를 할당해제한다.

    /*check post conditions*/
    if (matrix == NULL) {
        printf("matrix is NULL\n");
        return -1;      //비정상종료
    }


    return 1;           //정상종료


}


/* assign random values to the given matrix */
int fill_data(int** matrix, int row, int col)
{
    /*check pre conditions*/
    if (row <= 0 || col <= 0) {
        printf("Check the sizes of row and col!\n");
        return -1;      //비정상종료
    }


    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            matrix[i][j] = rand() % 20;     //matrix를 0~19의 난수로 채운다
        }
    }



    /*check post conditions*/
    if (matrix = NULL) {
        printf("matrix is NULL\n");
        return -1;      //비정상종료
    }


    return 1;       //정상종료


}

/* matrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    /*check pre conditions*/
    if (row <= 0 || col <= 0) {
        printf("Check the sizes of row and col!\n");
        return -1;      //비정상종료
    }


    int** matrix_sum = (int**)malloc(sizeof(int*) * row);
    for (int i = 0; i < row; i++) {
        matrix_sum[i] = (int*)malloc(sizeof(int) * col);        //2차원배열을 동적할당으로 생성하고
    }


    for (int i = 0; i < row; i++) {               //0으로 초기화해준다
        for (int j = 0; j < col; j++) {
            matrix_sum[i][j] = 0;
        }
    }



    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {                   //matrix_a와 matrix_b의합을 matrix_sum에저장한다.
            matrix_sum[i][j] = matrix_a[i][j] + matrix_b[i][j];
        }
    }

    print_matrix(matrix_sum, row, col);       //matrix_sum을 출력하고

    free_matrix(matrix_sum, row, col);        //matrix_sum을 할당해제하기위해 free_matrix를 호출한다

        /*check post conditions*/
    if (matrix_a == NULL) {
        printf("matrix_a is NULL\n");
        return -1;      //비정상종료
    }
    else if (matrix_b == NULL) {
        printf("matrix_b is NULL\n");
        return -1;      //비정상종료
    }

    else if (matrix_sum == NULL) {
        printf("matrix_sum is NULL\n");
        return -1;  //비정상종료
    }





    return 1;   //정상종료

}

/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    /*check pre conditions*/
    if (row <= 0 || col <= 0) {
        printf("Check the sizes of row and col!\n");
        return -1;  //비정상종료
    }


    int** matrix_sub = (int**)malloc(sizeof(int*) * row);
    for (int i = 0; i < row; i++) {
        matrix_sub[i] = (int*)malloc(sizeof(int) * col);        //2차원배열을 동적할당으로 생성하고
    }



    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {       //matrix_sub을 0으로 초기화해준다
            matrix_sub[i][j] = 0;
        }
    }


    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            matrix_sub[i][j] = matrix_a[i][j] - matrix_b[i][j];     //matrix_a와 matrix_b의 차를 matrix_sub에 저장한다.
        }
    }


    print_matrix(matrix_sub, row, col);       //matrix_sub을 출력하고
    free_matrix(matrix_sub, row, col);        //matrix_sub을 할당해제하기 위해 free_matrix를호출한다

    /*check post conditions*/
    if (matrix_a == NULL) {
        printf("matrix_a is NULL\n");
        return -1;      //비정상종료
    }

    else if (matrix_b == NULL) {
        printf("matrix_b is NULL\n");
        return -1;      //비정상종료
    }

    else if (matrix_sub == NULL) {
        printf("matrix_sub is NULL\n");
        return -1; //비정상종료
    }

    return 1;   //정상종료
}

/* transpose the matrix to matrix_t */
int transpose_matrix(int** matrix, int** matrix_t, int row, int col)
{
    /*check pre conditions*/
    if (row <= 0 || col <= 0) {
        printf("Check the sizes of row and col!\n");
        return -1;      //비정상종료
    }


    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            matrix_t[i][j] = matrix[j][i];        //matrix_t에 matrix의 전치행렬을 저장한다.
        }
    }



    /*check post conditions*/
    if (matrix == NULL) {
        printf("matrix is NULL\n");
        return -1;  //비정상종료
    }
    else if (matrix_t == NULL) {
        printf("matrix_t is NULL\n");
        return -1;  //비정상종료
    }


    return 1;       //정상종료

}

/* matrix_axt - matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col)
{
    /*check pre conditions*/
    if (row <= 0 || col <= 0) {
        printf("Check the sizes of row and col!\n");
        return -1;      //비정상종료
    }


    int** matrix_axt = (int**)malloc(sizeof(int*) * row);
    for (int i = 0; i < row; i++) {
        matrix_axt[i] = (int*)malloc(sizeof(int) * col);            //2차원배열을 동적할당 한다.
    }

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            matrix_axt[i][j] = 1;                 //matrix_axt를 1로초기화한다
        }
    }

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            matrix_axt[i][j] = matrix_a[i][j] * matrix_t[i][j];     //matrix_axt에 matrix_a와 matrix_t의 곱을 저장한다
        }
    }

    print_matrix(matrix_axt, row, col);       //matrix_axt를 출력한다.
    free_matrix(matrix_axt, row, col);        //matrix_axt를 할당해제하기 위해 free_matrix를 호출한다


    /*check post conditions*/
    if (matrix_a == NULL) {
        printf("matrix_a is NULL\n");
        return -1;  //비정상종료
    }

    else if (matrix_t == NULL) {
        printf("matrix_t is NULL\n");
        return -1;  //비정상종료
    }
    else if (matrix_axt == NULL) {
        printf("matrix_axt is NULL\n");
        return -1;  //비정상종료
    }

    return 1;       //정상종료
}