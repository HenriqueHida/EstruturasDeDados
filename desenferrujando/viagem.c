#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, cod, nota, maiorcod, maiornota, cont=0;
    
    while (scanf("%d", &n) != EOF) {
        maiorcod = maiornota = -1;
        cont++;

        for (int i = 0; i < n; i++) {
            scanf("%d %d", &cod, &nota);
            if (nota > maiornota || nota == maiornota && maiorcod > cod)  {
                maiornota = nota;
                maiorcod = cod;
            }
        }
        
        printf("Dia %d\n", cont);
        printf("%d\n\n", maiorcod);
    }
    
    return 0;
}

