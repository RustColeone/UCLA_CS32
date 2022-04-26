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
    assert(s.insert(5, 10) == -1);
    assert(!s.empty());
    assert(s.size() == 3);
    for (int i = 1; i <= 5; i++) {
        s.insert(40 + i);
        assert(s.size() == 3 + i);
    }
    ItemType x = 999;
    assert(!s.get(-1, x) && x == 999);
    assert(!s.get(s.size(), x) && x == 999);
    assert(s.get(0, x) && x == 20);
    assert(s.get(1, x) && x == 10);
    assert(s.get(2, x) && x == 40);
    assert(!s.erase(8));
    assert(s.erase(7));
    assert(!s.get(7, x) && x == 40);
    assert(s.get(6, x) && x == 44);
    for (int i = 0; i < 3; i++) {
        s.insert(369);
    }
    s.swap(s1);
    assert(s.empty());
    s.swap(s1);
    s1.insert(19);
    s.swap(s1);
    assert(s.get(0, x) && x == 19);
    assert(s.size() == 1);
    assert(s1.get(s1.size() - 1, x) && x == 369);
    s = s1;
    assert(s.find(369) == 7);
    assert(s1.find(369) == 7);
    assert(s1.remove(369) == 3);
    assert(s1.remove(819) == 0);
    assert(s1.size() == 7);
    assert(s1.set(1, 17));
    assert(s1.get(1, x) && x == 17);
}

void test1() {
    Sequence s, s1, s2, si1, si2, si3, empty;

    assert(subsequence(s, s1) == -1);
    interleave(si1, si2, si1);
    assert(si1.empty());

    unsigned long values [] = {30, 21, 63, 42, 17, 63, 17, 29, 8, 32};

    unsigned long valuesi1[] = { 30, 21, 63, 42, 17, 63 };
    unsigned long valuesi2[] = { 42, 63, 84, 19 };
    unsigned long valuesi3[] = { 30, 42, 21, 63, 63, 84, 42, 19, 17, 63 };
    for (int i = 0; i < 10; i++) {
        s.insert(i, values[i]);
        si3.insert(i, valuesi3[i]);
    }
    assert(subsequence(s, s1) == -1);
    assert(subsequence(s1, s) == -1);
    //s.dump();
    for (int i = 0; i < 6; i++) {
        si1.insert(i, valuesi1[i]);
    }
    for (int i = 0; i < 4; i++) {
        si2.insert(i, valuesi2[i]);
    }

    s1.insert(0, 63);
    s1.insert(1, 17);
    s1.insert(2, 29);
    assert(subsequence(s, s1) == 5);
    assert(subsequence(s1, s) == -1);

    assert(subsequence(s1, empty) == -1);
    assert(subsequence(empty, s) == -1);
    assert(subsequence(empty, empty) == -1);

    s2.insert(0, 21);
    s2.insert(1, 63);
    s2.insert(2, 42);
    s2.insert(3, 17);
    assert(subsequence(s, s2) == 1);

    interleave(si1, si2, si1);
    for (int i = 0; i < 10; i++) {
        ItemType x1 = -1;
        ItemType x2 = -1;
        si1.get(i, x1);
        si3.get(i, x2);
        assert(x1 == x2);
    }

    interleave(si1, empty, si3);
    for (int i = 0; i < 10; i++) {
        ItemType x1 = -1;
        ItemType x2 = -1;
        si1.get(i, x1);
        si3.get(i, x2);
        assert(x1 == x2);
    }
    interleave(empty, si1, si3);
    for (int i = 0; i < 10; i++) {
        ItemType x1 = -1;
        ItemType x2 = -1;
        si1.get(i, x1);
        si3.get(i, x2);
        assert(x1 == x2);
    }

    interleave(empty, empty, si3);
    assert(si3.empty());

}

int main()
{
    test();
    test1();
    cout << "Passed all tests" << endl;
}