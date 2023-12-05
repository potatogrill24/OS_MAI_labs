#include <iostream>
#include <dlfcn.h>
#include <stdlib.h>
#include "./lib1/lib1.h"
#include "./lib2/lib2.h"

void info() {
    std::cout << "Please select: K arg1, arg2" << std::endl;
    std::cout << "K - selected function from library" << std::endl;
    std::cout << "K = -1 - complete the execution" << std::endl;
    std::cout << "K = 0 - change the library" << std::endl;
    std::cout << "K = 1 - NOD algorithm; arg1, arg2 - numbers" << std::endl;
    std::cout << "K = 2 - Pi algorithm; arg1 - row length" << std::endl;
}

int main() {
    info();
    char* libraries[] = {"libLib1.so", "libLib2.so"};
    int selectedLibrary = 0;
    int K, arg1, arg2;
    void *cur_lib;
    cur_lib = dlopen(libraries[selectedLibrary], RTLD_LAZY);
    if (cur_lib == NULL) {
        std::cout << "Library loading error" << std::endl;
        return 1;
    }

    typedef int(*func_ptr1)(int, int);
    typedef float(*func_ptr2)(int);
    func_ptr1 NOD;
    func_ptr2 PI;

    NOD = reinterpret_cast<func_ptr1>(dlsym(cur_lib, "NOD"));
    PI = reinterpret_cast<func_ptr2>(dlsym(cur_lib, "Pi"));

    while(scanf("%d", &K) != EOF) {
        if (K != -1 && K != 0 && K != 1 && K != 2) {
            std::cout << "You can only choose '-1' or '0' or '1' or '2' for K" << std::endl;
            return 1;
        }
        if (K == 0) {
            std::cout << "Your library has been changed" << std::endl;
            dlclose(cur_lib);
            selectedLibrary = 1 - selectedLibrary;
            void* cur_lib = dlopen(libraries[selectedLibrary], RTLD_LAZY);
            if (cur_lib == NULL) {
                std::cout << "Library loading error" << std::endl;
            return 1;
            }
            NOD = reinterpret_cast<func_ptr1>(dlsym(cur_lib, "NOD"));
            PI = reinterpret_cast<func_ptr2>(dlsym(cur_lib, "Pi"));
        }
        else if (K == 1) {
            std::cin >> arg1 >> arg2;
            int res1 = NOD(arg1, arg2);
            std::cout << "Result of NOD finding algorithm working - " << res1 << std::endl;
        }
        else if (K == 2) {
            std::cin >> arg1;
            float res2 = PI(arg1);
            std::cout << "Result of Pi finding algorithm working - " << res2 << std::endl;
        }
        else {
            std::cout << "Bye Bye" << std::endl;
            return 0;
        }
    }
    return 0;
}