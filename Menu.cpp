
#include "Menu.h"

#include <thread>
#include <iostream>

void Menu::add_option(const string& option)
{
	options.push_back(option);
}

int Menu::display_menu() const
{
	int input = 0;

	while (true)
	{
		system("clear");
		cout << "***** " << name << " *****" << endl;

		for (int i = 0; i < (int)options.size(); i++)
			cout << (i + 1) << ") " << options[i] << endl;

		string temp;
		cout << "\nEnter choice: ";
		getline(cin, temp);
		input = stoi(temp);

		if (input < 1 || input >(int)options.size())
		{
			cout << "Invalid option!" << endl;
			this_thread::sleep_for(2s);
		}
		else
			break;
	}

	return input;
}

void Menu::set_name(const string& new_name)
{
	name = new_name;
}
