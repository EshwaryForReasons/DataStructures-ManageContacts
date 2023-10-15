
#pragma once

#include "Menu.h"
#include "Contact.h"
#include "ArrayList.h"
#include "Util.h"

#include <fstream>

enum CONTACT_MENU_OPTION
{
	CONTACT_NONE,
	CONTACT_MENU_LIST,
	CONTACT_MENU_VIEW,
	CONTACT_MENU_ADD,
	CONTACT_MENU_EDIT,
	CONTACT_MENU_DELETE,
	CONTACT_MENU_EXIT
};

/**
	Handles all menu functionality and interacts with ContactList appopriately
*/
class ContactMenu : public Menu
{
public:

	ContactMenu();

	//Begins to display options and handling user requests
	void begin();

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
	class ContactList* contacts;

	Menu sort_direction_menu;
	Menu sort_field_menu;
};

