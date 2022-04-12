#include "Sequence.h"

Sequence::Sequence() {
	sequenceSize = 0;
}
bool Sequence::empty() {
	return(sequenceSize == 0);
}
int Sequence::size() const {
	return sequenceSize;
}
int Sequence::insert(int pos, const ItemType& value) {
	if (pos < 0 || pos > sequenceSize) {
		return -1;
	}
	for (int j = sequenceSize; j > pos; j--) {
		sequenceItems[j] = sequenceItems[j - 1];
	}
	sequenceItems[pos] = value;
	sequenceSize++;
	return pos;
}

int Sequence::insert(const ItemType& value) {
	if (sequenceSize >= DEFAULT_MAX_ITEMS) {
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
	int size = (this->size() > other.size()) ? this->size() : other.size();
	for (int i = 0; i < size; i++) {
		ItemType temp = other.sequenceItems[i];
		other.sequenceItems[i] = sequenceItems[i];
		sequenceItems[i] = temp;
	}
	int tempSize = other.sequenceSize;
	other.sequenceSize = sequenceSize;
	sequenceSize = tempSize;
}
