#include <iostream>
#include <set>
#include <unordered_set> 
#include <algorithm>
using namespace std;

void print_s(set <int> s);
void print_s(unordered_set <int> s);

set<int> unorderedToOrdered(unordered_set<int> us)
{
    set<int> s;
    for (auto val : us) { s.insert(val); }
    return s;
}
set<int> operator+ (set<int> a, set<int> b) {
    a.insert(b.begin(), b.end());
    return a;
}

set<int> operator* (set<int> a, set<int> b) {
    set<int> intersect;
    set_intersection(a.begin(), a.end(), b.begin(), b.end(),
        std::inserter(intersect, intersect.begin()));
    return intersect;
}
set<int> operator+ (unordered_set<int> a, unordered_set<int> b) {
    a.insert(b.begin(), b.end());
    set<int> aa;
    aa = unorderedToOrdered(a);
    return aa;
}

set<int> operator* (unordered_set<int> a, unordered_set<int> b) {
    set<int> intersect;
    set<int> aa;
    set<int> bb;
    aa = unorderedToOrdered(a);
    bb = unorderedToOrdered(b);
    set_intersection(aa.begin(), aa.end(), bb.begin(), bb.end(),
        std::inserter(intersect, intersect.begin()));
    return intersect;
}

int main()
{
    //set<int> a;
    //a.insert(1);
    //a.insert(2);
    //a.insert(3);
    //a.insert(4);
    //a.insert(0);
    //a.insert(10);
    //set<int> b;
    //b.insert(2);
    //b.insert(3);
    //b.insert(8);

    //print_s(a + b);

    //print_s(a * b);

    unordered_set<int> a;
    a.insert(1);
    a.insert(2);
    a.insert(3);
    a.insert(4);
    a.insert(0);
    a.insert(10);
    unordered_set<int> b;
    b.insert(2);
    b.insert(3);
    b.insert(8);
    cout << "a: ";
    print_s(a);
    cout << endl;
    cout << "b: ";
    print_s(b);
    cout << endl;
    cout << "a + b: ";
    print_s(a + b);
    cout << endl;
    cout << "a * b: ";
    print_s(a * b);
}


void print_s(unordered_set <int> s)
{
    for (auto i : s) {
        cout << i << " ";
    }
}
void print_s(set <int> s)
{
    for (set <int>::iterator i = s.begin(); i != s.end(); i++)
    {
        cout << *i<< " ";
    }
}
