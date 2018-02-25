#include <iostream>
#include <fstream>
int main() {
    std::ifstream f1, f2;
    f1.open("a.out");
    f2.open("real.txt");

    int id(1);
    bool r1(1), r2(1);
    std::string s1, s2;
    while(r1 or r2) {
        r1 = (f1 >> s1);
        r2 = (f2 >> s2);
        if(r1 != r2 or s1 != s2) {
            printf("Word %d\n", id);
            std::cerr << "Your output:     "; if(r1) std::cerr << s1 << '\n';
            std::cerr << "Expected output: "; if(r2) std::cerr << s2 << '\n';
            return 0;
        }
        id++;
    }
    printf("Files matching\n");
    return 0;
}
