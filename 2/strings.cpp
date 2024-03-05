

#include <iostream>
#include <cstring>
using namespace std;

void copy_string(char* d, char* s) {
    while (*s) {
        *d = *s;
        d++;
        s++;
    }
    *d = '\0';
}

int main()
{
    char str[] = "hello!";
    cout << str << endl;

    cout << strlen(str) << ' ' << sizeof(str) << endl;

    char t[32];
    copy_string(t, str);
    cout << t << endl;

    return 0;
}

