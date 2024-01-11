/*!
* \file hb_test.cpp
* \brief Файл теста библиотеки 
* \author Курсов Михаил БПМ-22-2
* \date Январь 2024 года
* \details Тестирование функций библиотеки 
*/

#include <iostream>

#include "hexbox.h"
#include <chrono>

void test_hexbox(cint it, cint w, cint h, cint a) {
    int time = 0;
    for (int i = 0; i < it; i += 1) {
        auto begin = std::chrono::steady_clock::now();
        Hexbox hb(w, h, a);
        //std::cout << "\n";
        /*int x = w;
        int y = h;
        Hexbox hb(x, y);
        hex_args Hex1{ 5, 6 };
        int h = hb.GetHeight_hex(1, 2);
        Hex1.hex_h = 3;
        hb.hex_grid[2] = Hex1;
        int n = 3;*/

        auto end = std::chrono::steady_clock::now();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);

        time += elapsed_ms.count();

    }
    std::cout << std::endl <<"Time avg : \t" << int(time / it) << " mcs";
}

void test_view(cint w, cint h, cint a) {
    
    Hexbox hb1(w, h, a);
    for (int y = 0; y < h; y += 1) {
        for (int x = 0; x < w; x += 1) {
            std::cout << hb1.GetCoordX_hex(x, y) << "_" << hb1.GetCoordY_hex(x, y) << "  ";
        }
        std::cout << 5 * sqrt(3) / 2 << std::endl;
    }
    auto begin = std::chrono::steady_clock::now();
    //hb1.Get_hex_near(10, 2, 0);

    //std::cout << hb1.hex_grid[hb1.near_hex[0].second].x2d << " " << hb1.hex_grid[hb1.near_hex[0].second].y2d;
    std::cout << hb1.hex_grid[hb1.Get_hex_near(10, 2, 0)].x2d << " " << hb1.hex_grid[hb1.Get_hex_near(10, 2, 0)].y2d << std::endl;
    

    hb1.save("test");
    Hexbox hb2(w, h, a);
    hb2.load("test");
    std::cout << hb2.GetCoordX_hex_near(10, 2, 0) << " " << hb2.GetCoordY_hex_near(10, 2, 0) << " " << hb2.count_st << " " << hb2.GetSt_num(4,9);

    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    
    std::cout << std::endl << "Time avg : \t" << int(elapsed_ms.count()) << " mcs";
}

int main() {
    //test_hexbox(10000, 50, 50, 5);
    test_view(4, 4, 5);
}