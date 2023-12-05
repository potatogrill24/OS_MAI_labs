#include "lib2.h"

int NOD(int a, int b) {
    std::vector<int> container;
    int max;
    double num1 = static_cast<double>(a);
    double num2 = static_cast<double>(b);
    if (a > b) max = a;
    else if (a < b) max = b;
    else return a;
    for (int i = 1; i <= max; i++) {
        if (floor(num1 / i) == num1 / i && floor(num2 / i) == num2 / i) {
            container.push_back(i);
        }
        i++;
    }
    int result = container[container.size() - 1];
    return result;
}

float Pi(int k) {
    float pi = 1;
    float znam = 1.0;
    float chisl = 2.0;
    for (int i = 0; i < k; i++) {
        if (i % 2 != 0) znam += 2;
        if (i % 2 == 0 && i != 0) chisl += 2;
        pi = pi * (chisl / znam);
    }
    return pi * 2.0;
}
