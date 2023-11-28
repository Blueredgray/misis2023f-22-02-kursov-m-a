#include "hexbox_old.h"
#include <chrono>


void test_hexbox(cint it) {
    int time = 0;
    for (int i = 0; i < it; i += 1) {
        auto begin = std::chrono::steady_clock::now();
        std::cout << "\n";
        int x = 40;
        int y = 40;
        Hexbox hb(x, y);
        hex_args Hex1{ 5, 6 };
        Hex1.hex_h = 1;
        std::cout << hb.count_st << std::endl;
        //hb.hex_grid[3] = Hex1;
        std::cout << hb.hex_grid[3].hex_h << std::endl;
        //std::cout << "\t\t\t" << hb.hex_grid[3].type_mat;
        int n = 3;
        std::cout << "\t" << hb.hex_grid[n].st[0];
        std::cout << "\t" << hb.hex_grid[n].st[1];
        std::cout << "\t" << hb.hex_grid[n].st[2];
        std::cout << "\t" << hb.hex_grid[n].st[3];
        std::cout << "\t" << hb.hex_grid[n].st[4];
        std::cout << "\t" << hb.hex_grid[n].st[5];
        //hex_args Hex1 = hb.GetHex(0, 0);
        auto end = std::chrono::steady_clock::now();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
        std::cout << "\n" << elapsed_ms.count() << " mcs";
        time += elapsed_ms.count();

    }
    std::cout << std::endl <<"Time avg : \t" << int(time / it);
}

int main() {
    test_hexbox(1000);
}