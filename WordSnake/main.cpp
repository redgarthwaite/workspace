/*
 * Michael Garthwaite
 * Word Snake (Daily Programmer, C++)
 * https://www.reddit.com/r/dailyprogrammer/comments/3bi5na/20150629_challenge_221_easy_word_snake/
 * Created on 6/29/15
 *
 */


#include <iostream>

using namespace std;


int main()
{
	string text;
	getline(cin,text);
	cout << "\n\n\n\n\n";


	bool vert = false;
	unsigned int behindSpace = 1;
	unsigned int i = 0;
	unsigned int y=0;
	do
	{

		if(text[i] != ' ')
		{
			if(vert)
			{

				cout << endl;
				for(unsigned int x = 0; x < y;++x)
				{
					cout << " ";
				}

				cout << text[i];
			}
			else
			{
				if(y == 0)
				{
					cout << text[i];
				}
				else
				{
					behindSpace++;
					cout << text[i];
				}
			}
		}
		else
		{

			y = i - behindSpace;
			vert = !vert;
			i++;
			behindSpace++;
		}


		i++;

	}while(i < text.size());



	//first word right
	//next word down
	//repeat until done


	return 0;
}
