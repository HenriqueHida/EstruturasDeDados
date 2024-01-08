#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char name[11];
    int price;
    int day;
} Stock;

int compareStocks(const void* a, const void* b) {
    return ((Stock*)a)->price - ((Stock*)b)->price;
}

int main() {
    int N;
    scanf("%d", &N);
    
    Stock* stocks = (Stock*)malloc(N * sizeof(Stock));
    int stockCount = 0;

    for (int i = 0; i < N; ++i) {
        int type;
        char name[11];
        int price;
        scanf("%d", &type);
        if (type == 1) {
            scanf("%s %d", name, &price);
            strcpy(stocks[stockCount].name, name);
            stocks[stockCount].price = price;
            stocks[stockCount].day = i + 1;
            ++stockCount;
        } else if (type == 2) {
            scanf("%s %d", name, &price);
            for (int j = 0; j < stockCount; ++j) {
                if (strcmp(stocks[j].name, name) == 0) {
                    stocks[j].price = price;
                    break;
                }
            }
        } else if (type == 3) {
            char buy[4];
            scanf("%s", buy);
            if(strcmp(buy, "BUY") == 0){
                qsort(stocks, stockCount, sizeof(Stock), compareStocks);
                printf("%s %d\n", stocks[0].name, stocks[0].day);
            }
        }
    }
    
    free(stocks);
    return 0;
}
