/******************************
*
* Program Name: Lab 3 Manage Contacts
* Author: Eshwary Mishra
* Date: 14 October 2023
* Description: This program manages contacts provided by a file. It can update the file as contact information changes.
*
*******************************/
#include "ContactMenu.h"

#include <thread>

using namespace std::chrono_literals;

void block_and_go_back()
{
	cout << "Press q to go back." << endl;

	string input;
	cin >> input;

	if(input != "q")
	{
		block_and_go_back();
	}
	else
		cout << "Going back..." << endl;
}

int main()
{
	ContactMenu menu = ContactMenu();

	bool b_exit = false;
	
	while (!b_exit)
	{
		system("clear");
		int selected_option = menu.display_menu();
		system("clear");

		if (selected_option == CONTACT_MENU_LIST)
		{
			menu.list_contacts();
			block_and_go_back();
		}
		else if (selected_option == CONTACT_MENU_VIEW)
		{
			menu.view_single_contact();
			block_and_go_back();
		}
		else if (selected_option == CONTACT_MENU_ADD)
		{
			menu.add_contact();
		}
		else if (selected_option == CONTACT_MENU_EDIT)
		{
			menu.edit_contact();
		}
		else if (selected_option == CONTACT_MENU_DELETE)
		{
			menu.delete_contact();
		}
		else if (selected_option == CONTACT_MENU_EXIT)
		{
			cout << "Goodbye!" << endl;
			b_exit = true;
		}

		this_thread::sleep_for(3s);
	}

	return 0;
}