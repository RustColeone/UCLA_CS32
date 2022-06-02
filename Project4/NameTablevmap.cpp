// NameTable.cpp

// This is a correct but inefficient implementation of
// the NameTable functionality.

#include "NameTable.h"
#include <string>
#include <unordered_map>
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
        item(string ID) :id(ID) {}
        item(string ID, int Scope) :id(ID), scope(Scope) {}
        string id = "";
        int lineNumber = 0;
        int scope = 0;

        bool isSame(const item & other) {
            return (other.id == id && other.scope == scope);
        }
        bool isIdentical(const item& other) {
            return (other.id == id && other.lineNumber == lineNumber && other.scope == scope);
        }
        bool operator==(const item& rhs) const
        {
            return (rhs.id == id && rhs.lineNumber == lineNumber && rhs.scope == scope);
        }
    };

    struct hasher {
        size_t operator() (item const& key) const {     // the parameter type should be the same as the type of key of unordered_map
            size_t hash = 0;
            unsigned long index = 0;
            for (int i = 0; i < key.id.length(); i++) {
                index += key.id[i];
            }
            return hash % 500;
        }
    };

    int markerId = 0;
    int currentScope = 0;
    unordered_map<item, int, hasher> umap;
    vector<item> itemsInScope;
};

void NameTableImpl::enterScope()
{
    item entryMarker = item(++currentScope);
    itemsInScope.push_back(entryMarker);
    umap.insert(make_pair(entryMarker, -1));
}

bool NameTableImpl::exitScope()
{
    item entryMarker = item(currentScope--);
    while(!itemsInScope.empty()) {
        item current = itemsInScope.back();
        auto itemFound = umap.find(current);
        umap.erase(itemFound);
        itemsInScope.pop_back();
        if (current == entryMarker) {
            break;
        }
    }
    if (itemsInScope.empty()) {
        return false;
    }
    return true;
}

bool NameTableImpl::declare(const string& id, int lineNum)
{
    
    if (id.empty()) {
        return false;
    }

    item currentItem = item(id, currentScope);
    auto itemFound = umap.find(currentItem);
    if (itemFound != umap.end()) {
        //Already exist
        return false;
    }
    else {
        itemsInScope.push_back(currentItem);
        umap.insert(make_pair(currentItem, lineNum));
    }
    return true;
}

int NameTableImpl::find(const string& id) const
{
    /*
    for (int i = currentScope; i >= 0; i--) {
        item currentItem = item(id, i);
        auto itemFound = umap.find(currentItem);
        if (itemFound != umap.end()) {
            return itemFound->second;
        }
    }
    return -1;
    */
    if (id.empty())
        return -1;

    // Search back for the most recent declaration still
    // available.

    size_t k = itemsInScope.size();
    while (k > 0)
    {
        k--;
        if (itemsInScope[k].id == id)
            return umap.find(itemsInScope[k])->second;
    }
    return -1;
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
