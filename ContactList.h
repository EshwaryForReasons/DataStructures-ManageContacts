
#pragma once

#include "ArrayList.h"
#include "Contact.h"
#include "Util.h"

/**
    Class specifically designed to abstract ArrayList functionality behind easy to read and understand functions
*/
class ContactList : public ArrayList<Contact>
{
public:

    ContactList() = default;

    static InfoTypes CurrentComparisionField;

    void print_list(InfoTypes _CurrentComparisionField, bool b_ascending);
    void view_single_contact(int id);
    void add_contact(Contact& new_contact);
    void edit_contact(const Contact& edited_contact);
    void delete_contact(int id);

    //Called when menu is constructed to initialize contacts from contacts_data file
	void init_contacts();
    
    //Called to update contacts file. The passed in contact will be updated in the file, the rest will be reconstructed in place; append means add to the end, used for adding new contacts
	void update_contacts_file(const Contact& update_contact = Contact(), bool b_append = false);
};