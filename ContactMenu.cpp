
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

	// Placeholder variables for data in the file
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

	//Construct a User and put it in the user_list for every user in the file
    string line;
	bool b_in_quotes = false;
	while (getline(in_file, line))
	{
		stringstream ss(line);
		getline(ss, id, ',');
		getline(ss, first_name, ',');
		getline(ss, middle_name, ',');
		getline(ss, last_name, ',');
		getline(ss, role, ',');
		getline(ss, organization, ',');
		getline(ss, address, ',');
		getline(ss, city, ',');
		getline(ss, county, ',');
		getline(ss, state, ',');
		getline(ss, zip, ',');
		getline(ss, primary_phone_number, ',');
		getline(ss, secondary_phone_number, ',');
		getline(ss, email, ',');

		cout << id << " " << zip << endl;

        Contact new_contact(stoi(id), first_name, middle_name, last_name, ROLE_NONE, organization, address, city, county, state, stoi(zip), primary_phone_number, secondary_phone_number, email);
        contacts.insert(new_contact);
	}

	in_file.close();
}

void ContactMenu::update_contacts_file(const Contact& update_contact, bool b_append)
{
	fstream file(USERS_DATA, b_append ? ios::app : ios::out);

	// if (b_append)
	// 	file << update_user.get_user_id() << "," << update_user.get_username() << "," << update_user.get_password() << "," << update_user.get_login_date_time().to_string() << "," << update_user.get_logout_date_time().to_string() << "\n";
	// else
	// {
	// 	//For all users write to file in format userid,username,password,login_date_time,logout_date_time; for user being logged out, use current time as logout_date_time
	// 	for (const User& _user : user_list)
	// 	{
	// 		if (_user == update_user)
	// 			file << update_user.get_user_id() << "," << update_user.get_username() << "," << update_user.get_password() << "," << update_user.get_login_date_time().to_string() << "," << update_user.get_logout_date_time().to_string() << "\n";
	// 		else
	// 			file << _user.get_user_id() << "," << _user.get_username() << "," << _user.get_password() << "," << _user.get_login_date_time().to_string() << "," << _user.get_logout_date_time().to_string() << "\n";
	// 	}
	// }

	file.close();

	//Update contacts after modifying the file
	init_contacts();
}

bool ContactMenu::list_contacts()
{
	const char seperator = ' ';
	const int column_width = 20;

	cout << "asdf";
	for(int i = 0; i < contacts.get_num_elements(); ++i)
	{
		cout << "asdf";
		const Contact _contact = contacts[i];
		cout << left << setw(column_width) << setfill(seperator) << _contact.get_first_name();
		cout << left << setw(column_width) << setfill(seperator) << _contact.get_middle_name();
		cout << left << setw(column_width) << setfill(seperator) << _contact.get_last_name();

		cout << left << setw(column_width) << setfill(seperator) << _contact.get_address();
		cout << left << setw(column_width) << setfill(seperator) << _contact.get_city();
		cout << left << setw(column_width) << setfill(seperator) << _contact.get_county();
		cout << left << setw(column_width) << setfill(seperator) << _contact.get_state();
		cout << left << setw(column_width) << setfill(seperator) << _contact.get_zip();

		cout << left << setw(column_width) << setfill(seperator) << _contact.get_primary_phone_number();
		cout << left << setw(column_width) << setfill(seperator) << _contact.get_secondary_phone_number();
		cout << left << setw(column_width) << setfill(seperator) << _contact.get_email();

		cout << endl;
	}

	return true;
}

bool ContactMenu::view_single_contact()
{
	return true;
}

bool ContactMenu::add_contact()
{
    cout << "***** Add Contact *****" << endl;

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

	cout << "First Name: ";
	cin >> first_name;
	cout << "Middle Name: ";
	cin >> middle_name;
	cout << "Last Name: ";
	cin >> middle_name;
	cout << "Role: ";
	cin >> role;
	cout << "Organization: ";
	cin >> organization;
	cout << "Address: ";
	cin >> address;
    cout << "City: ";
	cin >> city;
    cout << "County: ";
	cin >> county;
    cout << "State: ";
	cin >> state;
    cout << "Zip: ";
	cin >> zip;
    cout << "Primary Phone Number: ";
	cin >> primary_phone_number;
    cout << "Secondary Phone Number: ";
	cin >> secondary_phone_number;
    cout << "Email: ";
	cin >> email;

	//Get largest contact id; the new contact will be one more than the largest
	int largest_user_id = 0;
	//for (const Contact& _contact : contacts)
	//{
	//	if(_contact.get_id() > largest_user_id)
	//		largest_user_id = _contact.get_id();
	//}

	update_contacts_file(Contact(largest_user_id + 1, first_name, middle_name, last_name, ROLE_NONE, organization, address, city, county, state, stoi(zip), primary_phone_number, secondary_phone_number, email), true);

	return true;
}

bool ContactMenu::edit_contact()
{
	return true;
}

bool ContactMenu::delete_contact()
{
	return true;
}

// bool ContactMenu::remove_account()
// {
// 	if (!user.get_logged_in())
// 	{
// 		cout << "No user logged in to remove!" << endl;
// 		return false;
// 	}

// 	//Remove user from the user_list
// 	user_list.erase(find(user_list.begin(), user_list.end(), user));
// 	//Update file to match user_list; user paramater is just to fill the space, passing in User() would construct a new object so I pass in the old user as an optimization
// 	update_user_data_file(user);

// 	//Logout the current user now that we have removed them
// 	logout();

// 	return true;
// }

// bool ContactMenu::reset_password()
// {
// 	int attempt = 0;

// 	cout << "***** Reset Password *****" << endl;

// 	if (!user.get_logged_in())
// 	{
// 		cout << "No user logged in to reset password for!" << endl;
// 		return false;
// 	}

// 	//Loop allows user three attempts at inputting the same password twice; we require a password and a confirmation password before changing it
// 	while (attempt++ < 3)
// 	{
// 		string new_password;
// 		string confirm_new_password;

// 		cout << "New Password: ";
// 		cin >> new_password;
// 		cout << "Confirm New Password: ";
// 		cin >> confirm_new_password;
// 		cout << endl;

// 		if (new_password == confirm_new_password)
// 		{
// 			user.set_password(new_password);
// 			update_user_data_file(user);
// 			return true;
// 		}
// 		else
// 			cout << "Passwords do not match! Try again." << endl;
// 	}

// 	return true;
// }
