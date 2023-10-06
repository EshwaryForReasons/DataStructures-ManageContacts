
#pragma once

#include "Menu.h"
#include "Contact.h"
#include "ArrayList.h"

#include <fstream>

enum LOGIN_MENU_OPTION
{
	CONTACT_NONE,
	CONTACT_MENU_LIST,
	CONTACT_MENU_VIEW,
	CONTACT_MENU_ADD,
	CONTACT_MENU_EDIT,
	CONTACT_MENU_DELETE,
	CONTACT_MENU_EXIT
};

class ContactMenu : public Menu
{
public:

	ContactMenu();

	bool list_contacts();
	bool view_single_contact();
	bool add_contact();
	bool edit_contact();
	bool delete_contact();

	const Contact& get_contact() const {return contact;}

private:

	//Represents a contact being edited
	Contact contact;
	//List of all contacts
	ArrayList<Contact> contacts;

	//Called when menu is constructed to initialize user_list from users_data file
	void init_contacts();

	//Called to update contacts file. The passed in contact will be updated in the file, the rest will be reconstructed in place; append means add to the end, used for adding new contacts
	void update_contacts_file(const Contact& update_contact, bool b_append = false);
};

