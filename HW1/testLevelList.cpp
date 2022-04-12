#include "Sequence.h"
#include "LevelList.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    LevelList s;
    assert(s.size() == 0);
    s.add(42);
    s.add(6);
    s.add(38);
    s.add(3);
    assert(s.size() == 4);
    assert(s.maximum() == 42);
    assert(s.minimum() == 3);
    s.add(6);
    s.remove(6);
    assert(s.size() == 4);
    s.remove(3);
    assert(s.size() == 3 && s.minimum() == 6);
    s.add(7);
    s.add(7);
    s.add(7);
    assert(s.size() == 6 && s.minimum() == 6);
    cout << "Passed all tests" << endl;
}