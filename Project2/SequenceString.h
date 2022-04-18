#ifndef SEQUENCE
#define SEQUENCE

#include <string>

using ItemType = std::string;

class Sequence
{
    struct Node {
        ItemType data;
        Node* next;
    };
    int itemCount;
    Node* head;

public:
    Sequence();
    Sequence(const Sequence& other);
    ~Sequence();
    Sequence& operator=(const Sequence& rhs);

    bool empty() const;
    int size() const;
    int insert(int pos, const ItemType& value);
    int insert(const ItemType& value);
    bool erase(int pos);
    int remove(const ItemType& value);
    bool get(int pos, ItemType& value) const;
    bool set(int pos, const ItemType& value);
    int find(const ItemType& value) const;
    void swap(Sequence& other);
};


int subsequence(const Sequence& seq1, const Sequence& seq2);
void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result);

#endif // !SEQUENCE