#include <iostream>
#include "List.h"
#include "Item.h"

using namespace std;

void startup()
{
	cout
			<< "\n\n\n"
			<< "1. press a to add an item to the list.\n"
			<< "2. press d to delete an item from the list.\n"
			<< "3. press v to view the list.\n"
			<< "4. press q to quit.\n"
			<< "what would you like to do?\n";
}

int main()
{

	List L;
	string c;
	cout << "Welcome to Shia LeBeouf's TO-DO List!\n";
	startup();
	getline(cin,c);
	while(c != "q")
	{
		string item;
		if (c == "v")
		{
			L.viewList();
		}
		else if(c == "d")
		{

			cout << "What would you like to delete?\n";
			getline(cin,item);
			L.delItem(item);

		}
		else if(c == "a")
		{
			cout << "What would you like to add?\n";
			getline(cin,item);
			L.addItem(item);

		}
		else
		{
			cout << "not a valid input, try again.\n";
		}
		startup();
		getline(cin,c);
	}

	return 0;
}
