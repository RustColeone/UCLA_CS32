#include "newSequence.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    newSequence a(1000);   // a can hold at most 1000 items
    newSequence b(5);      // b can hold at most 5 items
    newSequence c;         // c can hold at most DEFAULT_MAX_ITEMS items
    ItemType v = 11;

    // No failures inserting 5 items into b
    for (int k = 0; k < 5; k++)
        assert(b.insert(v) != -1);

    // Failure if we try to insert a sixth item into b
    assert(b.insert(v) == -1);

    // When two Sequences' contents are swapped, their capacities are
    // swapped as well:
    a.swap(b);
    assert(a.insert(v) == -1 && b.insert(v) != -1);

    return 0;
}