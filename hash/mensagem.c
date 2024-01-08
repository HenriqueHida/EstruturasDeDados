#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char b[1<<21+2], m;
    int min=0, cod=0, offset;
    char *c = &b[1<<20];
    scanf("%d %c", &cod, &m);
    c[0] = m;
    offset = cod;
    while (scanf("%d %c", &cod, &m)== 2){
        c[cod-offset] = m;
        if(cod - offset < min) {
            min = cod-offset;
        }
        printf("%s", &c[min]);
    }
    
    return 0;
}
