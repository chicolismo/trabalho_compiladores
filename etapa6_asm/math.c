#include <stdio.h>

int main() {
    int i = 1, i2 = 2, i3 = 3;
    long l = 2, l2 = 3, l3 = 4;
    float f = 3, f2 = 4, f3 = 5;
    double d = 4, d2 = 5, d3 = 6;
    
    i = i2 + i3;
    l = l2 + l3;
    f = f2 + f3;
    d = d2 + d3;
    
    i = i2 * i3;
    l = l2 * l3;
    f = f2 * f3;
    d = d2 * d3;
    
    i = i2 / i3;
    l = l2 / l3;
    f = f2 / f3;
    d = d2 / d3;
    
    i = i2 - i3;
    l = l2 - l3;
    f = f2 - f3;
    d = d2 - d3;
    
    return 0;
}
