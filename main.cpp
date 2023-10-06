/******************************
*
* Program Name: Lab 2 Manage User Accounts
* Author: Eshwary Mishra
* Date: 23 September 2023
* Description: This program manages user account provided by a file. It can update the file as account information changes.
*
*******************************/
#include "ContactMenu.h"

#include <thread>

using namespace std::chrono_literals;

int main()
{
	ContactMenu menu = ContactMenu();
	menu.list_contacts();

	return 0;
}