// NameTable.cpp

// This is a correct but inefficient implementation of
// the NameTable functionality.

#include "NameTable.h"
#include <string>
//#include <unordered_map>
#include <list>
#include <vector>
using namespace std;

// This class does the real work of the implementation.

class NameTableImpl
{
public:
    void enterScope();
    bool exitScope();
    bool declare(const string& id, int lineNum);
    int find(const string& id) const;
private:

    struct item {
        item() {}
        item(int Scope) : scope(Scope) {}
        item(string ID, int lineNum) :id(ID), lineNumber(lineNum) {}
        item(string ID, int lineNum, int i) :id(ID), lineNumber(lineNum), index(i) {}
        item(string ID, int lineNum, int i, int Scope) :id(ID), lineNumber(lineNum), index(i), scope(Scope) {}
        string id = "";
        int lineNumber = 0;
        int index = -1;
        int scope = 0;

        item * previous = nullptr;

        bool isSame(const item& other) {
            return (other.id == id && other.scope == scope);
        }
        bool isIdentical(const item& other) {
            return (other.id == id && other.index == index && other.lineNumber == lineNumber && other.scope == scope);
        }
    };

    int currentScope = 0;

    int hashFunction(const string& id) const;

    list<item>* table;

    int bucketSize = 10000;
    int count = 0;

    item * lastInsert;

    //vector<item> items;
    //vector<int> m_lines;
};

void NameTableImpl::enterScope()
{
    // Extend the id vector with an empty string that
    // serves as a scope entry marker.

    //m_ids.push_back("");
    //m_lines.push_back(0);
    item entryMarker = item(++currentScope);
    entryMarker.previous = lastInsert;

    if (table == nullptr) {
        table = new list<item>[bucketSize];
    }

    //items.push_back(entryMarker);//Delete this later

    int indexStored = hashFunction(entryMarker.id);
    table[indexStored].push_back(entryMarker);
    lastInsert = &table[indexStored].back();
}

bool NameTableImpl::exitScope()
{
    // Remove ids back to the last scope entry.
    item entryMarker = item(currentScope);

    //TODO: edit this to doesn need the single vector
    /*
    while (!items.empty())
    {
        item current = items.back();
        int indexStored = hashFunction(current.id);

        if (!table[indexStored].empty() && table[indexStored].back().isIdentical(current)) {
            table[indexStored].pop_back();
        }
        else {
            for (int i = table[indexStored].size() - 1; i >= 0; i--) {
                if (table[indexStored][i].isIdentical(current)) {
                    table[indexStored].erase(table[indexStored].begin() + i);
                    break;
                }
            }
        }

        items.pop_back();
        if (current.isSame(entryMarker)) {
            break;
        }
    }

    if (items.empty())
        return false;
    
    */
    while (lastInsert != nullptr) {
        item current = * lastInsert;
        int indexStored = hashFunction(current.id);

        if (!table[indexStored].empty() && table[indexStored].back().isIdentical(current)) {
            table[indexStored].pop_back();
            count--;
        }
        lastInsert = current.previous;
        if (current.isSame(entryMarker)) {
            break;
        }
    }

    if (lastInsert == nullptr) {
        return false;
    }

    // Remember to remove the scope entry marker itself.
    currentScope--;
    return true;
}

bool NameTableImpl::declare(const string& id, int lineNum)
{

    if (id.empty()) {
        return false;
    }

    // Check for another declaration in the same scope.
    // Return if found, break out if encounter the scope
    // entry marker.
    int index = hashFunction(id);

    item currentItem = item(id, lineNum, count, currentScope);
    currentItem.previous = lastInsert;

    if (table == nullptr) {
        table = new list<item>[bucketSize];
    }
    for (item i : table[index]) {
        if (i.isSame(currentItem)) {
            return false;
        }
    }
    //items.push_back(currentItem);//Delete this

    table[index].push_back(currentItem);
    lastInsert = &table[index].back();
    count++;
    return true;
}

int NameTableImpl::find(const string& id) const
{
    if (id.empty())
        return -1;

    // Search back for the most recent declaration still
    // available.
    item currentItem = item(id, -1, count, currentScope);
    int index = hashFunction(id);
    int firstMatchsLN = -1;
    /*
    for (int i = table[index].size() - 1; i >= 0; i--) {
        //If we have a matching id
        if (table[index][i].id == id) {
            if (firstMatchsLN == -1) {
                //Note it down first
                firstMatchsLN = table[index][i].lineNumber;
            }
            if (table[index][i].isSame(currentItem)) {
                //If same scope we have a match and return
                return table[index][i].lineNumber;
            }
        }
    }*/
    list<item>::reverse_iterator i;
    for (i = table[index].rbegin(); i != table[index].rend(); i++) {
        if (i->id == id) {
            if (firstMatchsLN == -1) {
                //Note it down first
                firstMatchsLN = i->lineNumber;
            }
            if (i->isSame(currentItem)) {
                //If same scope we have a match and return
                return i->lineNumber;
            }
            if (firstMatchsLN != -1) {
                break;
            }
        }
    }
    //Nothing found
    return firstMatchsLN;
}

int NameTableImpl::hashFunction(const string& id) const
{
    unsigned long index = 0;
    /*
    if (id.length() > 2) {
        index += id[2];
    }
    else if (id.length() > 1) {
        index += id[1];
    }*/
    for (int i = 0; i < id.length(); i++) {
        index += id[i];
    }
    return index % bucketSize;
}

//*********** NameTable functions **************

// For the most part, these functions simply delegate to NameTableImpl's
// functions.

NameTable::NameTable()
{
    m_impl = new NameTableImpl;
}

NameTable::~NameTable()
{
    delete m_impl;
}

void NameTable::enterScope()
{
    m_impl->enterScope();
}

bool NameTable::exitScope()
{
    return m_impl->exitScope();
}

bool NameTable::declare(const string& id, int lineNum)
{
    return m_impl->declare(id, lineNum);
}

int NameTable::find(const string& id) const
{
    return m_impl->find(id);
}
