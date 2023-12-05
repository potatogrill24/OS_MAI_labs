#include <iostream>
#include "./lib1/lib1.h"

void info() {
    std::cout << "Please select: K arg1, arg2" << std::endl;
    std::cout << "K - selected function from library" << std::endl;
    std::cout << "K = 0 - complete the execution" << std::endl;
    std::cout << "K = 1 - Evklid's algorithm; arg1, arg2 - numbers" << std::endl;
    std::cout << "K = 2 - Leibniz series; arg1 - row length" << std::endl;
}

int main() {
    info();
    int K, arg1, arg2;
    while (scanf("%d", &K) != EOF) {
        if (K != 1 && K != 2 && K != 0) {
            std::cout << "You can only choose '0' or '1' or '2' for K" << std::endl; 
            return 1;
        }
        if (K == 1) {
            std::cin >> arg1 >> arg2;
            int res1 = NOD(arg1, arg2);
            std::cout << "Result of Evklid's algorithm working - " << res1 << std::endl;
        }
        else if (K == 2) {
            std::cin >> arg1;
            float res2 = Pi(arg1);
            std::cout << "Result of Leibniz series algorithm working - " << res2 << std::endl;
        }
        else {
            std::cout << "Bye Bye" << std::endl;
            return 0;
        }
    }
    return 0;
}
