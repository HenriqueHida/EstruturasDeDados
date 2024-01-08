#include<stdio.h>

int main () {
	int num, maior=-1, n;
	scanf("%d", &n);
	for(int j=0; j < n; j++) {
		scanf("%d", &num);
        if(num > maior) {
            maior = num;
        }
	}
	printf("%d\n", maior);
	return 0;
}
