#include "newSequence.h"

Sequence::Sequence() {
    sequenceSize = 0;
    max = DEFAULT_MAX_ITEMS;
    sequenceItems = new ItemType[max];
}

Sequence::Sequence(int setMax) {
	if (setMax > 0) {
		sequenceSize = 0;
		max = setMax;
		sequenceItems = new ItemType[max];
	}
}
Sequence::Sequence(const Sequence& other) {
	sequenceSize = other.size();
	max = other.max;
	sequenceItems = new ItemType[max];
	for (int i = 0; i < max; i++) {
		sequenceItems[i] = other.sequenceItems[i];
	}
}
Sequence&Sequence::operator=(const Sequence& incoming){
	if (this != &incoming) {
		return * new Sequence(incoming);
	}
    return *this;
}
Sequence::~Sequence() {
	delete[] sequenceItems;
}

bool Sequence::empty() {
	return(sequenceSize == 0);
}
int Sequence::size() const {
	return sequenceSize;
}
int Sequence::insert(int pos, const ItemType& value) {

    if(sequenceSize >= max){
        return -1;
    }
    else if(sequenceSize == 0){
        sequenceSize += 1;
        sequenceItems[0] = value;
        return 0;
    }
	for (int j = sequenceSize; j > pos; j--) {
		sequenceItems[j] = sequenceItems[j - 1];
	}
	sequenceItems[pos] = value;
	sequenceSize++;
	return pos;
}

int Sequence::insert(const ItemType& value) {
	if (sequenceSize >= max) {
		return -1;
	}
	else if (sequenceSize == 0) {
		sequenceItems[0] = value;
	}
	int p = 0;
	for (; p < sequenceSize; p++) {
		if (value <= sequenceItems[p]) {
			for (int j = sequenceSize; j > p; j--) {
				sequenceItems[j] = sequenceItems[j - 1];
			}
			sequenceItems[p] = value;
			break;
		}
	}
	sequenceSize++;
	return p;
}

bool Sequence::erase(int pos) {
	if (pos < 0 || pos >= sequenceSize) {
		return false;
	}
	int p = 0;
	for (; p < sequenceSize; p++) {
		if (p == pos) {
			for (int j = p; j < sequenceSize; j++) {
				sequenceItems[j] = sequenceItems[j + 1];
			}
			break;
		}
	}
	//sequenceItems[sequenceSize--] = "";
	sequenceSize--;
	return true;
}

int Sequence::remove(const ItemType& value) {
	int count = 0;
	for (int i = 0; i < sequenceSize; i++) {
		if (sequenceItems[i] == value) {
			erase(i);
			count++;
		}
	}
	return count;
}

bool Sequence::get(int pos, ItemType& value) const {
	if (pos < 0 || pos >= sequenceSize) {
		return false;
	}
	value = sequenceItems[pos];
	return true;
}

bool Sequence::set(int pos, const ItemType& value) {
	if (pos < 0 || pos >= sequenceSize) {
		return false;
	}
	sequenceItems[pos] = value;
	return true;
}

int Sequence::find(const ItemType& value) {
	for (int i = 0; i < sequenceSize; i++) {
		if (sequenceItems[i] == value) {
			return i;
		}
	}
	return -1;
}

void Sequence::swap(Sequence& other) {

	int temp = other.sequenceSize;
	other.sequenceSize = sequenceSize;
	sequenceSize = temp;

	// Switch max capacity.
	temp = other.max;
	other.max = max;
	max = temp;

	// Switch pointer.
	ItemType* tempPointer = other.sequenceItems;
	other.sequenceItems = sequenceItems;
	sequenceItems = tempPointer;
}
