#include "Sequence.h"
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
    Sequence s;
    Sequence s1;
    assert(s.empty());
    s.insert(0, 10);
    s.insert(0, 20);
    s.insert(40);
    assert(s.size() == 3);
    for(int i = 1; i <= 5; i ++){
        s.insert(40+i);
        assert(s.size() == 3+i);
    }
    ItemType x = 999;
    assert(s.get(0, x) && x == 20);
    assert(s.get(1, x) && x == 10);
    assert(s.get(2, x) && x == 40);
    assert(!s.erase(8));
    assert(s.erase(7));
    assert(s.get(6, x) && x == 44);
    for(int i = 0; i < 3; i ++){
        s.insert(369);
    }
    s.swap(s1);
    assert(s.empty());
    assert(s1.get(s1.size()-1, x) && x == 369);
    assert(s1.find(369) == 7);
    assert(s1.remove(369) == 3);
    assert(s1.size() == 7);
    assert(s1.set(1, 17));
    assert(s1.get(1, x) && x == 17);

}

void test1()
{
    Sequence s;
    s.insert(0, 10);
    s.insert(0, 20);
    assert(s.size() == 2);
    ItemType x = 999;
    assert(s.get(0, x) && x == 20);
    assert(s.get(1, x) && x == 10);
}

int main()
{
    test();
    test1();
    cout << "Passed all tests" << endl;
}