#include <stdio.h>

int main() {
    int v[100], res[100];
    int i = 0, divisor, sum=0, cont=0, j=0;
    scanf("%d", &v[i]);
    while (v[i] != 0) {
        i++;
        scanf("%d", &v[i]);
    }
    scanf("%d", &divisor);
  //  printf("i: %d  ", i);
    for (j=0; j <= i; j++) {
        if(sum > divisor) {
            res[cont] = v[j-1];
           // printf("\ndentro do if e temos v[j] = %d e j = %d sum = %d e o res: %d", v[j-1], j, sum, res[cont]);
            cont++;
            sum = 0;
        }
        sum += v[j];
       // printf("\n\nv[%d]: %d\n\n",j,v[j] );
    }
    //printf("cont:  %d\n e res[0]= %d", cont, res[0]);
    if(sum > divisor) {
        res[cont] = v[j-1];
        cont++;
    }
    for (int k = cont-1; k >= 0; k--){
        printf("%d ", res[k]);
        printf("\n");
    }
    return 0;
}
