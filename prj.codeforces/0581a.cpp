#include <iostream>
#include <string>

int main() {
    int red = 0;
    int blue = 0;
    std::cin >> red >> blue; 
    int ost = std::max(blue, red) - std::min(blue, red);
    std::cout << std::min(blue, red) << " " << (ost - (ost % 2)) / 2;
}