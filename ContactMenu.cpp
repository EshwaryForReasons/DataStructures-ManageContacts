
#include "ContactMenu.h"
#include "ContactList.h"

#include <sstream>
#include <thread>
#include <iomanip>
#include <iostream>

using namespace std::chrono_literals;

static void block_and_go_back()
{
	cout << "Press q to go back." << endl;

	string input;
	getline(cin, input);

	if(input != "q")
		block_and_go_back();
	else
		cout << "Going back..." << endl;
}

ContactMenu::ContactMenu()
	: Menu("Contact Menu")
{
	add_option("List Contacts");
	add_option("View a Contact");
	add_option("Add Contact");
	add_option("Edit Contact");
	add_option("Delete Contact");
	add_option("Exit");

	//Initialize menus to ask user about listing options. Doing this here do we do not initialize everytime the user lists the contacts
	sort_direction_menu.set_name("Select Direction To Sort");
	sort_direction_menu.add_option("Acsending");
	sort_direction_menu.add_option("Descending");

	sort_field_menu.set_name("Select Field To Sort By");
	sort_field_menu.add_option("Id");
	sort_field_menu.add_option("First Name");
	sort_field_menu.add_option("Middle Name");
	sort_field_menu.add_option("Last Name");
	sort_field_menu.add_option("Role");
	sort_field_menu.add_option("Company");
	sort_field_menu.add_option("Address");
	sort_field_menu.add_option("City");
	sort_field_menu.add_option("Country");
	sort_field_menu.add_option("State");
	sort_field_menu.add_option("Zip");
	sort_field_menu.add_option("Primary Phone");
	sort_field_menu.add_option("Secondary Phone");
	sort_field_menu.add_option("Email");

	contacts = new ContactList();
	contacts->init_contacts();
}

void ContactMenu::begin()
{
	bool b_exit = false;
	
	while (!b_exit)
	{
		clear_console();
		int selected_option = display_menu();
		clear_console();

		if (selected_option == CONTACT_MENU_LIST)
		{
			list_contacts();
			block_and_go_back();
		}
		else if (selected_option == CONTACT_MENU_VIEW)
		{
			view_single_contact();
			block_and_go_back();
		}
		else if (selected_option == CONTACT_MENU_ADD)
		{
			add_contact();
			block_and_go_back();
		}
		else if (selected_option == CONTACT_MENU_EDIT)
		{
			edit_contact();
			block_and_go_back();
		}
		else if (selected_option == CONTACT_MENU_DELETE)
		{
			delete_contact();
			block_and_go_back();
		}
		else if (selected_option == CONTACT_MENU_EXIT)
		{
			cout << "Goodbye!" << endl;
			b_exit = true;
		}

		this_thread::sleep_for(3s);
	}
}

void ContactMenu::list_contacts()
{
	const int direction_option = sort_direction_menu.display_menu();

	cout << "Sorting list by " << sort_direction_menu.get_options()[direction_option - 1] << endl;
	this_thread::sleep_for(2s);
	clear_console();
	
	const int field_option = sort_field_menu.display_menu();

	cout << "Sorting list by " << sort_field_menu.get_options()[field_option - 1] << " in " << sort_direction_menu.get_options()[direction_option - 1] << " order" << endl;
	this_thread::sleep_for(2s);
	clear_console();
	
	//Print header
	cout << left;
	cout << setw(SHORT_COLUMN_WIDTH) << "Id";

	cout << setw(MEDIUM_COLUMN_WIDTH) << "First Name";
	cout << setw(SHORT_COLUMN_WIDTH) << "M";
	cout << setw(MEDIUM_COLUMN_WIDTH) << "Last Name";

	cout << setw(MEDIUM_COLUMN_WIDTH) << "Role";
	cout << setw(SUPER_LONG_COLUMN_WIDTH) << "Company";

	cout << setw(LONG_COLUMN_WIDTH) << "Address";
	cout << setw(LONG_COLUMN_WIDTH) << "City";
	cout << setw(LONG_COLUMN_WIDTH) << "Country";
	cout << setw(SHORT_COLUMN_WIDTH) << "State";
	cout << setw(SHORT_COLUMN_WIDTH) << "Zip";

	cout << setw(MEDIUM_COLUMN_WIDTH) << "Primary Phone";
	cout << setw(MEDIUM_COLUMN_WIDTH) << "Secondary Phone";
	cout << setw(LONG_COLUMN_WIDTH) << "Email";
	cout << setfill('-') << setw((MEDIUM_COLUMN_WIDTH * 5) + (SHORT_COLUMN_WIDTH * 3) + (SUPER_LONG_COLUMN_WIDTH * 1) + (LONG_COLUMN_WIDTH * 4)) << "\n";
	cout << endl;

	contacts->print_list(InfoTypes(field_option - 1), direction_option == 1);

	//Reset fill after printing list
	cout << setfill(' ');
}

void ContactMenu::view_single_contact()
{
	cout << "***** View a Contact *****" << endl;

	string id;
	cout << "Enter contact Id: ";
	getline(cin, id);

	contacts->view_single_contact(stoi(id));
}

void ContactMenu::add_contact()
{
    cout << "***** Add Contact *****" << endl;

    string first_name;
    string middle_name;
    string last_name;
    string role;
    string organization;
    string address;
    string city;
    string county;
    string state;
    string zip;
    string primary_phone_number;
    string secondary_phone_number;
    string email;

	//Lambda to get input from user and strip newline character
	auto get_input = [](const string& message, string& output)
	{
		cout << message;
		getline(cin, output);

		//Strip the input of the newline character to prevent problems with formatting later
		if(output.find("\r") != string::npos || output.find("\n") != string::npos)
			output.erase(output.size() - 1);
	};

	get_input("First Name: ", first_name);
	get_input("Middle Name: ", middle_name);
	get_input("Last Name: ", last_name);
	get_input("Role: ", role);
	get_input("Organization: ", organization);
	get_input("Address: ", address);
    get_input("City: ", city);
    get_input("County: ", county);
    get_input("State: ", state);
    get_input("Zip: ", zip);
    get_input("Primary Phone Number: ", primary_phone_number);
    get_input("Secondary Phone Number: ", secondary_phone_number);
    get_input("Email: ", email);

	Contact new_contact(0, first_name, middle_name, last_name, role, organization, address, city, county, state, stoi(zip), primary_phone_number, secondary_phone_number, email);
	contacts->add_contact(new_contact);

	cout << "Contact Added Successfully! New Contact Id: " << new_contact.get_id() << endl;
}

void ContactMenu::edit_contact()
{
	cout << "***** Edit Contact *****" << endl;

	string id;
    string first_name;
    string middle_name;
    string last_name;
    string role;
    string organization;
    string address;
    string city;
    string county;
    string state;
    string zip;
    string primary_phone_number;
    string secondary_phone_number;
    string email;

	//Lambda to get input from user and strip newline character
	auto get_input = [](const string& message, string& output)
	{
		cout << message;
		getline(cin, output);

		//Strip the input of the newline character to prevent problems with formatting later
		if(output.find("\r") != string::npos || output.find("\n") != string::npos)
			output.erase(output.size() - 1);
	};

	get_input("Enter Contact Id To Edit: ", id);
	get_input("First Name: ", first_name);
	get_input("Middle Name: ", middle_name);
	get_input("Last Name: ", last_name);
	get_input("Role: ", role);
	get_input("Organization: ", organization);
	get_input("Address: ", address);
    get_input("City: ", city);
    get_input("County: ", county);
    get_input("State: ", state);
    get_input("Zip: ", zip);
    get_input("Primary Phone Number: ", primary_phone_number);
    get_input("Secondary Phone Number: ", secondary_phone_number);
    get_input("Email: ", email);

	contacts->edit_contact(Contact(stoi(id), first_name, middle_name, last_name, role, organization, address, city, county, state, stoi(zip), primary_phone_number, secondary_phone_number, email));

	cout << "Contact Edited Successfully!" << endl;
}

void ContactMenu::delete_contact()
{
	cout << "***** Delete a Contact *****" << endl;

	string id;
	cout << "Enter Contact Id To Delete: ";
	getline(cin, id);

	contacts->delete_contact(stoi(id));

	cout << "Contact Deleted Successfully" << endl;
}