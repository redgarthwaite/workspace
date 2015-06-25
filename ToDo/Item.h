#ifndef ITEM_H
#define ITEM_H

#include <string>
using namespace std;

class Item
{
private:
	string stuff;
	Item* prev;
	Item* next;

public:
	Item();
	Item(string work);
	string viewStuff();
	void setPrev(Item* new_prev);
	void setNext(Item* new_next);
	Item* getPrev();
	Item* getNext();
};

#endif
