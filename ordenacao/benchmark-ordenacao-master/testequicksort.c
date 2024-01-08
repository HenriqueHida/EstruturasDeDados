#include "ordenacaomacros.h"

#include "stdio.h"


int separa(int *v, int l, int r){
	int ponteiro = v[r];
	int j = l;
	for (int k=l; k<r; k++){
		if(less(v[k], ponteiro)){
			exch(v[k], v[j]);
			j++;;
		}
	}
	exch(v[j], v[r]);
	return j;
}

void quicksort(int *v, int l, int r) {
	if (r <= l) return;
	int j = separa(v,l,r);
	quicksort(v, l, j-1);
	quicksort(v, j+1, r);
}
int main () {
	int j=3, V[10] = {23,32,65,43,345,3456,345,3432,654,723};
	quicksort(V,0,9);
	for(int k=0; k <= 9; k++) {
		printf("%d \n", V[k]);
	}
	printf("\n\n%d\n\n", j);
}
