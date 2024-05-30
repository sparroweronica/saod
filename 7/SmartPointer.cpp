#include <iostream>
#include <memory>
#include"Test.h"
using namespace std;

weak_ptr<Test> wp;

int main()
{

    {
        shared_ptr<Test> sp(new Test);
        cout << sp.use_count() << endl;

        wp = sp;
        cout << sp.use_count() << endl;
        auto p = wp.lock();
        if (p) {
            cout << "object is alive, " << sp.use_count() << endl;
        }
        else {
            cout << "no object";
        }
        wp = sp;
        cout << sp.use_count() << endl;
        p = wp.lock();
        if (p) {
            cout << "object is alive, " << sp.use_count() << endl;
        }
        else {
            cout << "no object";
        }
    }

}
