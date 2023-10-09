
#include "ContactMenu.h"

#include <sstream>
#include <thread>
#include <iomanip>

const string USERS_DATA = "contacts_data.csv";

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

	ifstream in_file(USERS_DATA);

	if(in_file.fail())
		cout << "Failed to open " << USERS_DATA << " file!" << endl;

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
	fstream file(USERS_DATA, b_append ? ios::app : ios::out);

	if (b_append)
		//contactid,firstname,middlename,lastname,role,organization,address,city,county,state,zip,primaryphonenumber,secondaryphonenumber,email
		file << update_contact.get_id() << "," << update_contact.get_person().get_first_name() << "," << update_contact.get_person().get_middle_name() << "," << update_contact.get_person().get_last_name() << "," << update_contact.get_person().get_role() << "," << update_contact.get_person().get_organization() << "," << update_contact.get_address() << "," << update_contact.get_city() << "," << update_contact.get_county() << "," << update_contact.get_state() << "," << update_contact.get_zip() << "," << update_contact.get_primary_phone_number() << "," << update_contact.get_secondary_phone_number() << "," << update_contact.get_email() << "\n";
	else
	{
		//Insert header
		file << "id,first_name,middle_name,last_name,role,company_name,address,city,county,state,zip,phone1,phone,email" << endl;

		//For all contacts write to file in format contactid,firstname,middlename,lastname,role,organization,address,city,county,state,zip,primaryphonenumber,secondaryphonenumber,email
		for (int i = 0; i < contacts.get_num_elements(); ++i)
		{
			if (contacts[i].get_id() == update_contact.get_id())
				file << update_contact.get_id() << "," << update_contact.get_person().get_first_name() << "," << update_contact.get_person().get_middle_name() << "," << update_contact.get_person().get_last_name() << "," << update_contact.get_person().get_role() << "," << update_contact.get_person().get_organization() << "," << update_contact.get_address() << "," << update_contact.get_city() << "," << update_contact.get_county() << "," << update_contact.get_state() << "," << update_contact.get_zip() << "," << update_contact.get_primary_phone_number() << "," << update_contact.get_secondary_phone_number() << "," << update_contact.get_email() << "\n";
			else
				file << contacts[i].get_id() << "," << contacts[i].get_person().get_first_name() << "," << contacts[i].get_person().get_middle_name() << "," << contacts[i].get_person().get_last_name() << "," << contacts[i].get_person().get_role() << "," << contacts[i].get_person().get_organization() << "," << contacts[i].get_address() << "," << contacts[i].get_city() << "," << contacts[i].get_county() << "," << contacts[i].get_state() << "," << contacts[i].get_zip() << "," << contacts[i].get_primary_phone_number() << "," << contacts[i].get_secondary_phone_number() << "," << contacts[i].get_email() << "\n";
		}
	}

	file.close();

	//Update contacts after modifying the file
	init_contacts();
}

void ContactMenu::list_contacts()
{
	const char seperator = ' ';
	const int super_long_column_width = 35;
	const int long_column_width = 25;
	const int medium_column_width = 16;
	const int short_column_width = 7;

	//Print header
	cout << left;
	cout << setw(medium_column_width) << "First Name";
	cout << setw(short_column_width) << "M";
	cout << setw(medium_column_width) << "Last Name";

	cout << setw(medium_column_width) << "Role";
	cout << setw(super_long_column_width) << "Company";

	cout << setw(long_column_width) << "Address";
	cout << setw(long_column_width) << "City";
	cout << setw(long_column_width) << "Country";
	cout << setw(short_column_width) << "State";
	cout << setw(short_column_width) << "Zip";

	cout << setw(medium_column_width) << "Primary Phone";
	cout << setw(medium_column_width) << "Secondary Phone";
	cout << setw(long_column_width) << "Email";
	cout << endl;

	for(int i = 0; i < contacts.get_num_elements(); ++i)
	{
		cout << setw(medium_column_width) << contacts[i].get_person().get_first_name();
		cout << setw(short_column_width) << contacts[i].get_person().get_middle_name();
		cout << setw(medium_column_width) << contacts[i].get_person().get_last_name();

		cout << setw(medium_column_width) << contacts[i].get_person().get_role();
		cout << setw(super_long_column_width) << contacts[i].get_person().get_organization();

		cout << setw(long_column_width) << contacts[i].get_address();
		cout << setw(long_column_width) << contacts[i].get_city();
		cout << setw(long_column_width) << contacts[i].get_county();
		cout << setw(short_column_width) << contacts[i].get_state();
		cout << setw(short_column_width) << contacts[i].get_zip();

		cout << setw(medium_column_width) << contacts[i].get_primary_phone_number();
		cout << setw(medium_column_width) << contacts[i].get_secondary_phone_number();
		cout << setw(long_column_width) << contacts[i].get_email();

		cout << endl;
	}
}

void ContactMenu::view_single_contact()
{
	cout << "***** View a Contact *****" << endl;

	int id;
	cout << "Enter contact Id:";
	cin >> id;
	
	for(int i = 0; i < contacts.get_num_elements(); ++i)
	{
		if(contacts[i].get_id() != id)
			continue;
		
		const int column_width = 25;
		cout << left;
		cout << setw(column_width) << "Id:" << contacts[i].get_id() << endl;
		cout << setw(column_width) << "First Name:" << contacts[i].get_person().get_first_name() << endl;
		cout << setw(column_width) << "Middle Name:" << contacts[i].get_person().get_middle_name() << endl;
		cout << setw(column_width) << "Last Name:" << contacts[i].get_person().get_last_name() << endl;

		cout << setw(column_width) << "Address" << contacts[i].get_address() << endl;
		cout << setw(column_width) << "City" << contacts[i].get_city() << endl;
		cout << setw(column_width) << "County" << contacts[i].get_county() << endl;
		cout << setw(column_width) << "State" << contacts[i].get_state() << endl;
		cout << setw(column_width) << "Zip" << contacts[i].get_zip() << endl;

		cout << setw(column_width) << "Primary Phone Number:" << contacts[i].get_primary_phone_number() << endl;
		cout << setw(column_width) << "Secondary Phone Number:" << contacts[i].get_secondary_phone_number() << endl;
		cout << setw(column_width) << "Email:" << contacts[i].get_email() << endl;

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
	{
		if(contacts[i].get_id() > largest_user_id)
			largest_user_id = contacts[i].get_id();
	}

	update_contacts_file(Contact(largest_user_id + 1, Person(first_name, middle_name, last_name, role, organization), address, city, county, state, stoi(zip), primary_phone_number, secondary_phone_number, email), true);

	cout << "Contact Added Successfully!" << endl;
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

	int id;
	cout << "Enter Contact Id To Delete:";
	cin >> id;

	for(int i = 0; i < contacts.get_num_elements(); ++i)
	{
		if(contacts[i].get_id() == id)
		{
			contacts.remove(i);
			break;
		}
	}

	//Update contacts file to match contacts; contact parameter is just to full the space
	update_contacts_file(Contact());

	cout << "Contact Deleted Successfully" << endl;
}