#include "lib1.h"

int NOD(int a, int b) {
    while (a != b) {
        if (a > b) a = a - b;
        else if (b > a) b = b - a;
        else return a;
    }
    return a;
}

float Pi(int k) {
    float znam = 3.0;
    float slag;
    float sum = 1;
    int c = 0;
    for (int i = 0; i < k; i++) {
        slag = (1.0 / znam);
        c += 1;
        if (c % 2 != 0) {
            sum -= slag;
        }
        else {
            sum += slag;
        }
        znam += 2;
    }
    return sum * 4.0;
}



// int main() {
//     int c = Evklid(18, 27);
//     std::cout << c << std::endl;
//     int res = Naive(243, 54);
//     std::cout << res << std::endl;;
//     return 0;
// }