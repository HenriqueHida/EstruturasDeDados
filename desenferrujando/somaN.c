#include<stdio.h>

int main () {
	int num, sum=0, n;
	scanf("%d", &n);
	for(int j=0; j < n; j++) {
		scanf("%d", &num);
		sum += num;
	}
	printf("%d\n", sum);
	return 0;
}
