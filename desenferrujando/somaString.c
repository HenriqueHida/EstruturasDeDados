#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main () {
    int n, sum = 0;
    scanf("%d", &n);
    char str[100][100];
    for(int i=0; i < n; i++){
        scanf("%s", str[i]);
        sum = 0;
        for(int j=0; j< strlen(str[i]); j++){
            if(isdigit(str[i][j])){
                sum = str[i][j] + sum - 48;
                //printf("entrei e a sum é %d \n", sum);
            }
            //printf("esse é o i:%d o j: %d e o str: %c\n\n",i,j, str[i][j]);
        }
        printf("%d\n", sum);
    }
    return 0;
}
