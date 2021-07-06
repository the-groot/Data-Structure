#include <stdio.h>

int main() {
    int array[3][2][4];

    for(int i=0; i<3; i++)
        for(int j=0; j<2; j++)
            for(int k=0; k<4; k++)
            array[i][j][k]=i*100+j*10+k;


      for(int i=0; i<3; i++) {
          for(int j=0; j<2; j++) {
              for(int k=0; k<4; k++) {
                  printf("a[%d][%d][%d]=%d\t",i,j,k,array[i][j][k]);

              }
              printf("\n");
          }
      }

    printf("--------------------------------------\n");

    for(int i=0; i<3; i++) {
        for(int j=0; j<2; j++) {
            for(int k=0; k<4; k++) {
                printf("addr &(a[%d][%d][%d]) = %p\t",i,j,k,&(array[i][j][k]));
            }
            printf("\n");
        }
    }

return 0;

}