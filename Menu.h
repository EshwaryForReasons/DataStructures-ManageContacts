
#pragma once

#include <iostream>
#include <vector>

using namespace std;

class Menu
{
public:

	Menu() {};
	Menu(string _name)
		: name(_name)
	{}
	~Menu() = default;

	void set_name(const string& new_name);

	void add_option(const string& option);

	int display_menu() const;

protected:

	virtual void display_data() const {};

private:

	string name;
	vector<string> options;
};
