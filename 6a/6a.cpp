
#include <iostream>
#include <string>

class MyString {
private:
    std::string str;

public:
   
    MyString(int x) {
        const int buffSize = 20; 
        char buff[buffSize];
        int result = _itoa_s(x, buff, buffSize, 10); 
        if (result != 0) {
            std::cerr << "Ошибка при конвертации!" << std::endl;
    
        }
        else {
            str = buff; 
        }
    }


    std::string substr(int off, int len) const {

        if (off >= str.length()) {
            return ""; 
        }
        len = std::min(len, static_cast<int>(str.length()) - off);

        return str.substr(off, len);
    }

    void print() const {
        std::cout << str << std::endl;
    }
};

int main() {
    MyString str(123456789); 
    str.print(); 
    std::string sub = str.substr(2, 5); 
    std::cout << "подстрока: " << sub << std::endl; 

    return 0;
}
