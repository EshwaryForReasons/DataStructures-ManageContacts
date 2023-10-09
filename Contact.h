
#pragma once

#include "Person.h"

#include <string>

using namespace std;

class Contact
{
public:

    Contact() = default;
    Contact(int _id, const Person& _person, string _address, string _city, string _county, string _state, int _zip, string _primary_phone_number, string _secondary_phone_number, string _email)
        : id(_id)
        , person(_person)
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

    //Setters
    void set_id(int new_id) {id = new_id;}
    void set_person(const Person& new_person) {person = new_person;}

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
    Person get_person() const {return person;}

    string get_address() const {return address;}
    string get_city() const {return city;}
    string get_county() const {return county;}
    string get_state() const {return state;}
    int get_zip() const {return zip;}

    string get_primary_phone_number() const {return primary_phone_number;}
    string get_secondary_phone_number() const {return secondary_phone_number;}
    string get_email() const {return email;}

private:

    int id;
    Person person;

    string address;
    string city;
    string county;
    string state;
    int zip;

    string primary_phone_number;
    string secondary_phone_number;
    string email;
};

inline Contact Contact::operator=(const Contact& other)
{
    id = other.get_id();
    person = other.get_person();
    address = other.get_address();
    city = other.get_city();
    county = other.get_county();
    state = other.get_state();
    zip = other.get_zip();
    primary_phone_number = other.get_primary_phone_number();
    secondary_phone_number = other.get_secondary_phone_number();
    email = other.get_email();
    return Contact(id, person, address, city, county, state, zip, primary_phone_number, secondary_phone_number, email);
}

inline const bool Contact::operator==(const Contact& other)
{
    return (id == other.id && person == other.person && address == other.address && city == other.city && county == other.county && state == other.state && zip == other.zip && primary_phone_number == other.primary_phone_number && secondary_phone_number == other.secondary_phone_number && email == other.email);
}