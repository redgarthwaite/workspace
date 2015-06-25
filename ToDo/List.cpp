#include "List.h"

List::List()
{
	first = NULL;
	last = NULL;

	ifstream file("LeBeouf.txt");
	if (file.is_open())
	{
		string input;
		for(int i = 0; i < 10; i++)
		{
			getline(file,input);
			LeBeouf[i] = input;

		}
	}

}
void List::addItem(string x)
{

	Item* newItem = new Item(x);
	if(first&&last)
	{
		newItem->setPrev(last);
		last->setNext(newItem);
		last = newItem;

	}
	else
	{
		first = newItem;
		last = newItem;

	}
}
void List::delItem(string x)
{
	if(first)
	{
		Item* i = first;
		while(i)
		{

			if(x == i->viewStuff())
			{
				Item* prev = i->getPrev();
				Item* next = i->getNext();

				if(i->viewStuff() == first->viewStuff())
				{
					if(first->getNext())
					{
						first = first->getNext();
						i->setNext(NULL);
						first->setPrev(NULL);
						cout << "delete successful\n";
					}
					else
					{
						first = NULL;
						last = NULL;
						cout << "delete successful\n";
					}
				}
				else if(i->viewStuff() == last->viewStuff())
				{
					last = last->getPrev();
					i->setPrev(NULL);
					last->setNext(NULL);
					cout << "delete successful\n";
				}

				else
				{
					prev->setNext(next);
					next->setPrev(prev);
					cout << "delete successful\n";
				}
				i = i->getNext();
			}
			else
				i = i->getNext();
		}
		delete i;
	}
	else
	{
		cout << "Your to-do list is empty.\n";
	}
}
void List::viewList()
{
	int rand = static_cast<int>(time(0));
	srand(rand);
	Item* i = first;
	if(!i)
	{
		cout << "Your to-do list is empty.\n";
	}

	else
	{
		while(i)
		{
			cout << i->viewStuff() << endl;
			i = i->getNext();
		}

		cout << LeBeouf[rand%10] << endl;
		delete i;
	}
}

