#include "hexbox.h"
#include <chrono>


void test_hexbox(cint it) {
    int time = 0;
    for (int i = 0; i < it; i += 1) {
        auto begin = std::chrono::steady_clock::now();
        //std::cout << "\n";
        int x = 100;
        int y = 100;
        Hexbox hb(x, y);
        hex_args Hex1{ 5, 6 };
        Hex1.hex_h = 3;
        hb.hex_grid[2] = Hex1;
        int n = 3;

        auto end = std::chrono::steady_clock::now();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);

        time += elapsed_ms.count();

    }
    std::cout << std::endl <<"Time avg : \t" << int(time / it);
}

int main() {
    test_hexbox(1000);
}