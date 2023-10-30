#include "hexbox.h"

int main() {
    int x = 4;
    int y = 4;
    Hexbox hb(x, y);
    hex_args Hex1{ 5, 6 };
    Hex1.hex_h = 1;
    std::cout << hb.count_st << std::endl;
    hb.hex_grid[3] = Hex1;
    std::cout << hb.hex_grid[3].hex_h << std::endl;
    std::cout << "\t\t\t" << hb.hex_grid[3].type_mat;
    //hex_args Hex1 = hb.GetHex(0, 0);
}