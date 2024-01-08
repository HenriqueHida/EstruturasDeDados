#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main () {
        int n,j,z,diff,cont=0,saldo;
        while(scanf("%d", &n) != 0) {
                for(int i=0; i < n; i++){
                        scanf("%d %d", &j,&z);
                        diff= j-z;
			if(i==0) {
				diff = saldo;
			}else {
				saldo += diff;
				push(&s, saldo);
			}
                }
                cont++;
                printf("Teste %d\n", cont);
                for(int j=s.top; j >= 0; j--){
                        int *var = pop(&s);
                        dept += *var;
                        printf("%d\n", dept);
                }
        }
        return 0;
}


