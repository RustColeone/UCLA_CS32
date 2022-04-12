#include "LevelList.h"

LevelList::LevelList() {
    return;
}

LevelList::~LevelList(){
    levelList.~Sequence();
}

bool LevelList::add(unsigned long level) {
    if (level >= 30 || level <= 400) {
        if (levelList.insert(level) != -1) {
            return true;
        }
    }
    return false;
}

bool LevelList::remove(unsigned long level) {
    return levelList.erase(levelList.find(level));
}

int LevelList::size() const {
    return levelList.size();
}

unsigned long LevelList::minimum() const {
    unsigned long temp;
    levelList.get(0, temp);
    return temp;
}

unsigned long LevelList::maximum() const {
    unsigned long temp;
    levelList.get(levelList.size() - 1, temp);
    return temp;
}