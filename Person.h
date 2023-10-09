
#pragma once

#include <string>

using namespace std;

class Person
{
public:

    Person() = default;
    Person(string _first_name, string _middle_name, string _last_name, string _role, string _organization)
        : first_name(_first_name)
        , middle_name(_middle_name)
        , last_name(_last_name)
        , role(_role)
        , organization(_organization)
    {}

    Person operator=(const Person& other);
    const bool operator==(const Person& other);

    //Setters
    void set_first_name(string new_first_name) {first_name = new_first_name;}
    void set_middle_name(string new_middle_name)  {middle_name = new_middle_name;}
    void set_last_name(string new_last_name) {last_name = new_last_name;}

    void set_role(string new_role) {role = new_role;}
    void set_organization(string new_organization) {organization = new_organization;}

    //Getters
    string get_first_name() const {return first_name;}
    string get_middle_name() const {return middle_name;}
    string get_last_name() const {return last_name;}

    string get_role() const {return role;}
    string get_organization() const {return organization;}

private:

    string first_name;
    string middle_name;
    string last_name;

    string role;
    string organization;
};

inline Person Person::operator=(const Person& other)
{
    first_name = other.get_first_name();
    middle_name = other.get_middle_name();
    last_name = other.get_last_name();
    role = other.get_role();
    organization = other.get_organization();
    return Person(first_name, middle_name, last_name, role, organization);
}

inline const bool Person::operator==(const Person& other)
{
    return (first_name == other.first_name && middle_name == other.middle_name && last_name == other.last_name && role == other.role && organization == other.organization);
}