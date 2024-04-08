#include <iostream>
using namespace std;
class Test
{
public:
    static  int Count;
    Test()    
    {
        cout << "created--Test" << endl;
        Count++;
        cout << Count << endl;
    }

    Test(const Test& c) {
        *this = c;
        cout << Count << endl;
        Count++;
        cout << "Copying--Test" << endl;
    }

    ~Test() { cout << "deleted--Test" << endl; Count--; cout << Count << endl; }
};
class Child : public Test
{
public:
    Child() { cout << "created--Child" << endl; }

    ~Child() { cout << "deleted--Child" << endl; }
};

class Aggregate : public Test
{
public:
    Test m_objTest;
    Aggregate() { cout << "created--Aggregate" << endl;}

    ~Aggregate() { cout << "deleted--Aggregate" << endl; }
};

template <class s>
class AggregateT {
public:
    AggregateT() { cout << "created--AggregateT" << endl;}

    ~AggregateT() { cout << "deleted--AggregateT" << endl;}
};