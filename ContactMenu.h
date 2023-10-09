
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

	//Lists the contacts
	void list_contacts();
	//View a single contact by id
	void view_single_contact();
	//Add a new contact to the data
	void add_contact();
	//Edit an existing contact in the data
	void edit_contact();
	//Delete a contact from the data
	void delete_contact();

private:

	//List of all contacts
	ArrayList<Contact> contacts;

	//Called when menu is constructed to initialize contacts from contacts_data file
	void init_contacts();

	//Called to update contacts file. The passed in contact will be updated in the file, the rest will be reconstructed in place; append means add to the end, used for adding new contacts
	void update_contacts_file(const Contact& update_contact, bool b_append = false);
};

