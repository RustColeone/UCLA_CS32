#include "Sequence.h"


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


Sequence::Sequence() {
	head = new Node();
	itemCount = 0;
}
Sequence::Sequence(const Sequence& other) {
	head = new Node();
	Node* current = head;
	Node* currentOther = other.head;
	while (currentOther != nullptr) {
		current->data = currentOther->data;
		currentOther = currentOther->next;
		if (currentOther != nullptr) {
			current->next = new Node();
			current = current->next;
		}
	}
	itemCount = other.itemCount;
}
Sequence::~Sequence() {
	Node* current = head;
	Node* temp;
	while (current != nullptr) {
		temp = current->next;
		delete current;
		current = temp;
	}
}
Sequence& Sequence::operator=(const Sequence& rhs) {
	if (this != &rhs) {
		Sequence temp(rhs); 
		swap(temp);
	} 
	return *this;
}

bool Sequence::empty() const {
	return itemCount == 0;
}
int Sequence::size() const {
	return itemCount;
}
int Sequence::insert(int pos, const ItemType& value) {
	if (pos < 0 || pos > itemCount) {
		return -1;
	}
	if (itemCount == 0) {
		head->data = value;
		itemCount++;
		return 0;
	}
	itemCount++;
	Node* current = head;
	Node* prev = head;
	for (int i = 0; i < pos; i++) {
		current = current->next;
	}
	for (int i = 0; i < pos - 1; i++) {
		prev = prev->next;
	}

	Node* temp = new Node();
	temp->data = value;
	temp->next = current;

	if (current != prev) {
		prev->next = temp;
	}
	else {
		head = temp;
	}
	return pos;

}
int Sequence::insert(const ItemType& value) {
	Node* current = head;
	int pos = 0;
	while (current != nullptr) {
		if (current->data >= value) {
			insert(pos, value);
			return pos;
		}
		pos++;
		current = current->next;
	}
	insert(itemCount, value);
	return itemCount;
}
bool Sequence::erase(int pos) {
	if (pos < 0 || pos >= itemCount) {
		return false;
	}
	itemCount--;
	Node* current = head;
	Node* prev = head;
	for (int i = 0; i < pos - 1; i++) {
		prev = prev->next;
	}
	if (current != prev) {
		current = prev->next;
		prev->next = current->next;
	}
	else {
		head = current -> next;
	}
	delete current;
	return true;
}
int Sequence::remove(const ItemType& value) {
	Node* current = head;
	int count = 0;
	int pos = 0;
	while (current != nullptr) {
		bool erased = false;
		if (current->data == value) {
			current = current->next;
			erased = erase(pos);
			if (erased)
				count++;
		}
		if (!erased) {
			current = current->next;
			pos++;
		}
	}
	return count;
}
bool Sequence::get(int pos, ItemType& value) const {
	if (pos < 0 || pos >= itemCount) {
		return false;
	}
	Node* current = head;
	int position = 0;
	while (current != nullptr){
		if (position == pos) {
			value = current->data;
			return true;
		}
		current = current->next;
		position++;
	}
	return false;
}
bool Sequence::set(int pos, const ItemType& value) {
	if (pos < 0 || pos >= itemCount) {
		return false;
	}
	Node* current = head;
	int position = 0;
	while (current != nullptr) {
		if (position == pos) {
			current->data = value;
			return true;
		}
		current = current->next;
		position++;
	}
	return false;
}
int Sequence::find(const ItemType& value) const {
	Node* current = head;
	int position = 0;
	while (current != nullptr) {
		if (current->data == value) {
			return position;
		}
		current = current->next;
		position++;
	}
	return -1;
}
void Sequence::swap(Sequence& other) {
	Node* temp = head;
	head = other.head;
	other.head = temp;

	int tempCount = itemCount;
	itemCount = other.itemCount;
	other.itemCount = tempCount;
}