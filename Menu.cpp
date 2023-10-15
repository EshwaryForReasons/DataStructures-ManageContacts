
#include "Menu.h"
#include "Util.h"

#include <thread>
#include <iostream>
#include <algorithm>

void Menu::add_option(const string& option)
{
	options.push_back(option);
}

const int Menu::display_menu() const
{
	while (true)
	{
		clear_console();
		cout << "***** " << name << " *****" << endl;

		for (int i = 0; i < (int)options.size(); i++)
			cout << (i + 1) << ") " << options[i] << endl;

		string temp;
		cout << "\nEnter choice: ";
		getline(cin, temp);

		if(temp == "" || !all_of(temp.begin(), temp.end(), ::isdigit) || (stoi(temp) < 1 || stoi(temp) >(int)options.size()))
		{
			cout << "Invalid input, please try again!" << endl;
			this_thread::sleep_for(2s);
			continue;
		}

		return stoi(temp);
	}
}

void Menu::set_name(const string& new_name)
{
	name = new_name;
}
