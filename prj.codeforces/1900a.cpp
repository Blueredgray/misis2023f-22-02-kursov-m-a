#include <iostream>
#include <string>

int main() {
    int t = 0;
    int n = 0;
    int e = 0;
    int posled = 0;

    std::cin >> t;
    
    for (int i = 0; i < t; i += 1) {
        e = 0;
        posled = 0;
        
        std::string str = "";
        std::cin >> n;
        std::cin >> str;
        for (int j = 0; j < n; j += 1) {
            if (str[j] == '.') {
                e += 1;
                posled += 1;
                if (posled > 2) {
                    std::cout << 2 << std::endl;
                    break;
                }
            }
            else {
                posled = 0;
            }
            
        }
        if (posled < 3) {
            std::cout << e <<std::endl;
        }
    }
}