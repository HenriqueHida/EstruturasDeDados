#include <stdio.h>
#include <stdlib.h>

void ultrapassa(int *v, int ini, int fin, int ls) {
    if(ini >= fin) return;
    int soma=0;
    while(ini < fin && soma < ls) {
        soma += v[ini++];
    }
    ultrapassa(v, ini, fin, ls);
    if(soma > ls) printf("%d\n", v[ini-1]);

}

int main () {

    int ls,v_size=100, e,cont=0;
    int *v = malloc(sizeof(int)*v_size);
    
    while (scanf("%d", &e) == 1 && e != 0) {
        v[cont] = e;
        cont++;
        if (cont >= v_size){
            v_size*=2;
            v = realloc(v, sizeof(int)*v_size);
        }
    }
    scanf("%d", &ls);
    ultrapassa(v, 0, cont, ls);
    free(v);
    return 0;
}