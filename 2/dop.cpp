
#include <iostream>
using namespace std;

int len(const char* s)
{
	int length = 0;
	while (*s != '\0') {
		length++;
		s++;
	}
	return length;
}

int compare(const char* s, const char* t)
{
	while (*s==*t) {
		if (*s == '\0')
			return 0;
		s++;
		t++;
	}
	return *s - *t;
}

int main()
{
	const char* str1 = "poka";
	const char* str2 = "hello";
	cout << "len: " << len(str1) << endl;
	cout << "len: " << len(str2) << endl;
	cout << "compare: " << compare(str1, str2) << endl;

}

