#include<stdio.h>

int main() {
	int n, j,z, diff, cont=1;
	scanf("%d", &n);
	while(n != 0) {
		diff = 0;
		printf("Teste %d\n", cont);
		cont++;
		for(int i=0; i<n;i++){
			scanf("%d %d", &j, &z);
			diff += j-z;
			printf("%d\n", diff);
		}
		printf("\n");
		scanf("%d", &n);
	}
	return 0;
}	
