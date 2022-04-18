#include "Sequence.h"
#include <iostream>
#include <cassert>
using namespace std;

int subsequence(const Sequence& seq1, const Sequence& seq2) {
    if (seq1.size() < seq2.size() || seq2.empty()) {
        return -1;
    }
    ItemType a = 0;
    ItemType b = 0;
    for (int i = 0; i < seq1.size(); i++) {
        int j = 0;
        for ( ; j < seq2.size(); j++) {
            if (i + j >= seq1.size()) {
                return -1;
            }
            else {
                seq1.get(i+j, a);
                seq2.get(j, b);
                if (a != b) {
                    break;
                }
            }
        }
        if (j == seq2.size()) {
            return i;
        }
    }
    return -1;
}

void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result) {
    int sizeL = seq1.size();
    int position = 0;
    Sequence temp;
    ItemType tempValue = 0;
    if (seq1.size() < seq2.size()) {
        sizeL = seq2.size();
    }
    for (int i = 0; i < sizeL; i++) {
        if (i < seq1.size()) {
            seq1.get(i, tempValue);
            temp.insert(position, tempValue);
            position++;
        }
        if (i < seq2.size()) {
            seq2.get(i, tempValue);
            temp.insert(position, tempValue);
            position++;
        }
    }
    result = temp;
}



void test()
{
    Sequence s;
    Sequence s1;
    assert(s.empty());
    s.insert(0, 10);
    s.insert(0, 20);
    s.insert(40);
    assert(s.size() == 3);
    for (int i = 1; i <= 5; i++) {
        s.insert(40 + i);
        assert(s.size() == 3 + i);
    }
    ItemType x = 999;
    assert(s.get(0, x) && x == 20);
    assert(s.get(1, x) && x == 10);
    assert(s.get(2, x) && x == 40);
    assert(!s.erase(8));
    assert(s.erase(7));
    assert(s.get(6, x) && x == 44);
    for (int i = 0; i < 3; i++) {
        s.insert(369);
    }
    s.swap(s1);
    assert(s.empty());
    assert(s1.get(s1.size() - 1, x) && x == 369);
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

void test2() {
    Sequence s, s1, s2, si1, si2, si3;

    unsigned long values [] = {30, 21, 63, 42, 17, 63, 17, 29, 8, 32};

    unsigned long valuesi1[] = { 30, 21, 63, 42, 17, 63 };
    unsigned long valuesi2[] = { 42, 63, 84, 19 };
    unsigned long valuesi3[] = { 30, 42, 21, 63, 63, 84, 42, 19, 17, 63 };
    for (int i = 0; i < 10; i++) {
        s.insert(i, values[i]);
        si3.insert(i, valuesi3[i]);
    }
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


}

int main()
{
    test();
    test1();
    test2();
    cout << "Passed all tests" << endl;
}