#include <iostream>
#include <string>
#include <vector>


int main() {
    int t = 0;
    std::string str {};
    int count = 0;
    std::cin >> t;
    for (int i = 0; i < t; i += 1) {
        count = 0;
        for (int y = 0; y < 10; y += 1) {
            std::cin >> str;
            //std::getline(std::cin, str);
            
            for (int x = 0; x < 10; x += 1) {

                if (str[x] == 'X') {
                    //count += ((((1 - (y / 5)) * y + 1) * ((1 - (x / 5)) * x + 1)) / 5  + ((y / 5) * (10 - y))  * ((x / 5) * (10 - x)) / 5   ) 
                    //count += ((((1 - (y / 5)) * y + 1) * ((1 - (x / 5)) * x + 1))  * ((((y / 5) * (10 - y)) + 1) * (((x / 5) * (10 - x)) + 1))) ;
                    //count += ((((1 - (y / 5)) * y + 1) + ((1 - (x / 5)) * x + 1)) );
                    if (x == 0 || y == 0 || x == 9 || y == 9) {
                        count += 1;
                    }else
                    if (x == 1 || x == 8 || y == 1 || y == 8) {
                        count += 2;
                    }
                    else
                        if (x == 2 || x == 7 || y == 2 || y == 7) {
                            count += 3;
                        }
                        else
                            if (x == 3 || x == 6 || y == 3 || y == 6) {
                                count += 4;
                            }
                            else
                                if (x == 4 || x == 5 || y == 4 || y == 5) {
                                    count += 5;
                                }
                    //std::cout << count << " ";
                }
                
            }
            //std::cout << std::endl;
        }
        std::cout << count << std::endl;
    }
    
}
