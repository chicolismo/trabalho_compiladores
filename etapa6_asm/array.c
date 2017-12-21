#include <stdio.h>

int x[4] = {10, 20, 30, 40};
int y[501];
int z = 0;

int main() {
    x[1] = 111111;
    x[2] = 222222;
    x[3] = 333333;
    
    x[z] = 444444;
    
    return 0;
}
