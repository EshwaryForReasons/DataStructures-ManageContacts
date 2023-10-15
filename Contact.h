
#pragma once

#include "Person.h"

#include <string>

using namespace std;

/**
    Contains contact details. For example address for mailing, phone numbers for calling, and email for emailing.
*/
class Contact : public Person
{
public:

    Contact() = default;
    Contact(int _id, string _first_name, string _middle_name, string _last_name, string _role, string _organization, string _address, string _city, string _county, string _state, int _zip, string _primary_phone_number, string _secondary_phone_number, string _email)
        : id(_id)
        , Person(_first_name, _middle_name, _last_name, _role, _organization)
        , address(_address)
        , city(_city)
        , county(_county)
        , state(_state)
        , zip(_zip)
        , primary_phone_number(_primary_phone_number)
        , secondary_phone_number(_secondary_phone_number)
        , email(_email)
    {}

    Contact operator=(const Contact& other);
    const bool operator==(const Contact& other);
    const bool operator!=(const Contact& other);
    const bool operator<(const Contact& other);
    const bool operator>(const Contact& other);
    
    //Returns a comma seperated list of format id,firstname,middlename,lastname,role,organization,address,city,county,state,zip,primaryphonenumber,secondaryphonenumber,email
    virtual const std::string to_string() const override;
    //Same as to_string, but this time each property is on a new line and labeled
    virtual const std::string to_labeled_string() const override;
    //Same as to_string, but it is now split into uniform columns
    virtual const std::string to_column_string() const override;

    //Setters
    void set_id(int new_id) {id = new_id;}

    void set_address(string new_address) {address = new_address;}
    void set_city(string new_city) {city = new_city;}
    void set_county(string new_county) {county = new_county;}
    void set_state(string new_state) {state = new_state;}
    void set_zip(int new_zip) {zip = new_zip;}
    
    void set_primary_phone_number(string new_primary_phone_number) {primary_phone_number = new_primary_phone_number;}
    void set_secondary_phone_number(string new_secondary_phone_number) {secondary_phone_number = new_secondary_phone_number;}
    void set_email(string new_email) {email = new_email;}

    //Getters
    int get_id() const {return id;}

    const string& get_address() const {return address;}
    const string& get_city() const {return city;}
    const string& get_county() const {return county;}
    const string& get_state() const {return state;}
    const int get_zip() const {return zip;}

    const string& get_primary_phone_number() const {return primary_phone_number;}
    const string& get_secondary_phone_number() const {return secondary_phone_number;}
    const string& get_email() const {return email;}

    const std::pair<string, string> retrieve_comparision_string(const Contact& other) const;

private:

    int id;

    string address;
    string city;
    string county;
    string state;
    int zip;

    string primary_phone_number;
    string secondary_phone_number;
    string email;
};