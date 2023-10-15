
#include "ContactList.h"

#include <fstream>
#include <vector>
#include <sstream>

static const string CONTACTS_DATA = "contacts_data.csv";

InfoTypes ContactList::CurrentComparisionField = INFO_NONE;

void ContactList::init_contacts()
{
	clear();

	ifstream in_file("contacts_data.csv");

	if(in_file.fail())
		cout << "Failed to open " << "contacts_data.csv" << " file!" << endl;

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

        insert(Contact(stoi(contact_information[INFO_ID]), contact_information[INFO_FIRST_NAME], contact_information[INFO_MIDDLE_NAME], contact_information[INFO_LAST_NAME], contact_information[INFO_ROLE], contact_information[INFO_ORGANIZATION], contact_information[INFO_ADDRESS], contact_information[INFO_CITY], contact_information[INFO_COUNTY], contact_information[INFO_STATE], stoi(contact_information[INFO_ZIP]), contact_information[INFO_PRIMARY_PHONE_NUMBER], contact_information[INFO_SECONDARY_PHONE_NUMBER], contact_information[INFO_EMAIL]));
	}

	in_file.close();
}

void ContactList::print_list(InfoTypes _CurrentComparisionField, bool b_ascending)
{
    ContactList::CurrentComparisionField = _CurrentComparisionField;

    ArrayList<Contact> sorted_contacts(*this);
    sorted_contacts.sort_list(b_ascending);

    for(int i = 0; i < sorted_contacts.get_num_elements(); ++i)
		cout << sorted_contacts[i].to_column_string() << "\n";

	cout << endl;
}

void ContactList::view_single_contact(int id)
{
    for(int i = 0; i < get_num_elements(); ++i)
	{
		if(data[i].get_id() != id)
			continue;

		cout << data[i].to_labeled_string() << endl;
		break;
	}
}

void ContactList::add_contact(Contact& new_contact)
{
    //Get largest contact id; the new contact will be one more than the largest
	int largest_user_id = 0;
	for (int i = 0; i < get_num_elements(); ++i)
		if(data[i].get_id() > largest_user_id)
			largest_user_id = data[i].get_id();

    new_contact.set_id(largest_user_id + 1);

    //Update contacts file to match contacts; contact parameter is just to full the space
	update_contacts_file(new_contact, true);
}

void ContactList::edit_contact(const Contact& edited_contact)
{
    update_contacts_file(edited_contact, false);
}

void ContactList::delete_contact(int id)
{
    for(int i = 0; i < get_num_elements(); ++i)
	{
		if(data[i].get_id() == id)
		{
			remove(i);
			break;
		}
	}

    //Update contacts file to match contacts; contact parameter is just to full the space
    update_contacts_file();
}

void ContactList::update_contacts_file(const Contact& update_contact, bool b_append)
{
	fstream file(CONTACTS_DATA, b_append ? ios::app : ios::out);

	//WIll always be added in the following format: contactid,firstname,middlename,lastname,role,organization,address,city,county,state,zip,primaryphonenumber,secondaryphonenumber,email

	if (b_append)
		file << update_contact.to_string() << "\n";
	else
	{
		//Insert header
		file << "id,first_name,middle_name,last_name,role,company_name,address,city,county,state,zip,phone1,phone,email" << endl;

		for (int i = 0; i < get_num_elements(); ++i)
		{
			if (get_data()[i].get_id() == update_contact.get_id())
				file << update_contact.to_string() << "\n";
			else
				file << get_data()[i].to_string() << "\n";
		}
	}

	file.close();

	//Update contacts after modifying the file
	init_contacts();
}