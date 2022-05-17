#include <iostream>
extern "C" {
    int f(int, int);
}
int main() {
    std::cout << "f(0,0): " << f(0, 0) << std::endl;
}
