#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <ctime>

#include "../ToDo/Item.h"

using namespace std;

class List
{
private:
	string LeBeouf[10];
	Item* first;
	Item* last;
public:
	List();
	void addItem(string i);
	void delItem(string i);
	void viewList();
};

#endif
