// clang++ -O3 null_dereferencing.cpp 

#include <iostream>


typedef int (*func_t)();

static func_t func;

int call_your_ex() {
    std::cout << "67" << std::endl;
    return 0;
}
void never_called() {
    func = call_your_ex;
}

int main() {
    return func();
}
