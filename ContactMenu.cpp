
#include "ContactMenu.h"

#include <sstream>
#include <thread>
#include <iomanip>
#include <iostream>

const string CONTACTS_DATA = "contacts_data.csv";

//Define a clear function based on OS the code is compiled for since there is no standard way to do this
#ifdef _WIN32
void clear_console()
{
	system("cls");
}
#elif __linux__
void clear_console()
{
	system("clear");
}
#endif

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

	init_contacts();
}

void ContactMenu::init_contacts()
{
	contacts.clear();

	ifstream in_file(CONTACTS_DATA);

	if(in_file.fail())
		cout << "Failed to open " << CONTACTS_DATA << " file!" << endl;

	//Enum to help access certain elements in the vector since the elements will always be in the same location; this is better than accessing them with numeric indices
	enum
	{
		INFO_ID = 0,
    	INFO_FIRST_NAME = 1,
    	INFO_MIDDLE_NAME = 2,
    	INFO_LAST_NAME = 3,
    	INFO_ROLE = 4,
    	INFO_ORGANIZATION = 5,
    	INFO_ADDRESS = 6,
    	INFO_CITY = 7,
    	INFO_COUNTY = 8,
    	INFO_STATE = 9,
    	INFO_ZIP = 10,
    	INFO_PRIMARY_PHONE_NUMBER = 11,
    	INFO_SECONDARY_PHONE_NUMBER = 12,
    	INFO_EMAIL = 13
	} CONTACT_INFO_LOCATION;

	//Construct a User and put it in the user_list for every user in the file
    string read_contact;
	bool b_header = true;
	while (getline(in_file, read_contact))
	{
		//Ignore first line
		if(b_header)
		{
			b_header = false;
			continue;
		}

		//Vector in order: string id, first_name, middle_name, last_name, role, organization, address, city, county, state, zip, primary_phone_number, secondary_phone_number, email
		vector<string> contact_information;
		bool b_in_quotes = false;

		stringstream single_contact_stream(read_contact);
		string field_data;
		string quoted_field_data;
		while (getline(single_contact_stream, field_data, ','))
		{
			//Strip the field of the newline character to prevent problems with formatting later
			if(field_data.find("\r") != string::npos || field_data.find("\n") != string::npos)
				field_data.erase(field_data.size() - 1);

			//If we are in quotes, then set in quotes flag to true; otherwise false
			if(field_data.find("\"") != string::npos)
			{
				b_in_quotes = !b_in_quotes;
				quoted_field_data += field_data;

				//Once we are out of quotes, append the quoted field data to the vector and clear the string
				if(!b_in_quotes)
				{
					contact_information.push_back(quoted_field_data);
					quoted_field_data = "";
				}
				else
					quoted_field_data += ",";
				
				continue;
			}
			
			//If in quotes, then we simply create the entire quoted field
			if(b_in_quotes)
				quoted_field_data += field_data += ",";
			else
				contact_information.push_back(field_data);
		}

        contacts.insert(Contact(stoi(contact_information[INFO_ID]), Person(contact_information[INFO_FIRST_NAME], contact_information[INFO_MIDDLE_NAME], contact_information[INFO_LAST_NAME], contact_information[INFO_ROLE], contact_information[INFO_ORGANIZATION]), contact_information[INFO_ADDRESS], contact_information[INFO_CITY], contact_information[INFO_COUNTY], contact_information[INFO_STATE], stoi(contact_information[INFO_ZIP]), contact_information[INFO_PRIMARY_PHONE_NUMBER], contact_information[INFO_SECONDARY_PHONE_NUMBER], contact_information[INFO_EMAIL]));
	}

	in_file.close();
}

void ContactMenu::update_contacts_file(const Contact& update_contact, bool b_append)
{
	fstream file(CONTACTS_DATA, b_append ? ios::app : ios::out);

	//WIll always be added in the following format: contactid,firstname,middlename,lastname,role,organization,address,city,county,state,zip,primaryphonenumber,secondaryphonenumber,email

	if (b_append)
		file << update_contact.to_string() << "\n";
	else
	{
		//Insert header
		file << "id,first_name,middle_name,last_name,role,company_name,address,city,county,state,zip,phone1,phone,email" << endl;

		for (int i = 0; i < contacts.get_num_elements(); ++i)
		{
			if (contacts[i].get_id() == update_contact.get_id())
				file << update_contact.to_string() << "\n";
			else
				file << contacts[i].to_string() << "\n";
		}
	}

	file.close();

	//Update contacts after modifying the file
	init_contacts();
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
	//Print header
	cout << left;
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
	cout << endl;

	for(int i = 0; i < contacts.get_num_elements(); ++i)
		cout << contacts[i].to_column_string() << endl;
}

void ContactMenu::view_single_contact()
{
	cout << "***** View a Contact *****" << endl;

	string id;
	cout << "Enter contact Id:";
	getline(cin, id);
	
	for(int i = 0; i < contacts.get_num_elements(); ++i)
	{
		if(contacts[i].get_id() != stoi(id))
			continue;

		cout << contacts[i].to_labeled_string() << endl;
		break;
	}
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

	//Get largest contact id; the new contact will be one more than the largest
	int largest_user_id = 0;
	for (int i = 0; i < contacts.get_num_elements(); ++i)
		if(contacts[i].get_id() > largest_user_id)
			largest_user_id = contacts[i].get_id();

	update_contacts_file(Contact(largest_user_id + 1, Person(first_name, middle_name, last_name, role, organization), address, city, county, state, stoi(zip), primary_phone_number, secondary_phone_number, email), true);

	cout << "Contact Added Successfully! New Contact Id: " << largest_user_id + 1 << endl;
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

	update_contacts_file(Contact(stoi(id), Person(first_name, middle_name, last_name, role, organization), address, city, county, state, stoi(zip), primary_phone_number, secondary_phone_number, email), false);

	cout << "Contact Edited Successfully!" << endl;
}

void ContactMenu::delete_contact()
{
	cout << "***** Delete a Contact *****" << endl;

	string id;
	cout << "Enter Contact Id To Delete:";
	getline(cin, id);

	for(int i = 0; i < contacts.get_num_elements(); ++i)
	{
		if(contacts[i].get_id() == stoi(id))
		{
			contacts.remove(i);
			break;
		}
	}

	//Update contacts file to match contacts; contact parameter is just to full the space
	update_contacts_file(Contact());

	cout << "Contact Deleted Successfully" << endl;
}