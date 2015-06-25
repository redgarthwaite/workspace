#include "Item.h"

Item::Item()
{
	stuff = "";
	prev = NULL;
	next = NULL;

}
Item::Item(string work)
{
	stuff = work;
	prev = NULL;
	next = NULL;
}
void Item::setPrev(Item* new_prev)
{
	prev = new_prev;
}
void Item::setNext(Item* new_next)
{
	next = new_next;
}
string Item::viewStuff()
{
	return stuff;
}
Item* Item::getPrev()
{
	return prev;
}
Item* Item::getNext()
{
	return next;
}
