
#include "Contact.h"

#include <sstream>
#include <iomanip>

Contact Contact::operator=(const Contact& other)
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

const bool Contact::operator==(const Contact& other)
{
    return (id == other.id && person == other.person && address == other.address && city == other.city && county == other.county && state == other.state && zip == other.zip && primary_phone_number == other.primary_phone_number && secondary_phone_number == other.secondary_phone_number && email == other.email);
}

const std::string Contact::to_string() const
{
    return string(std::to_string(get_id()) + "," + get_person().to_string() + "," + get_address() + "," + get_city() + "," + get_county() + "," + get_state() + "," + std::to_string(get_zip()) + "," + get_primary_phone_number() + "," + get_secondary_phone_number() + "," + get_email());
}

const std::string Contact::to_labeled_string() const
{
    stringstream formatted;
	formatted << left;
	formatted << setw(COLUMN_WIDTH) << "Id:" << get_id() << endl;
    formatted << person.to_labeled_string();

	formatted << setw(COLUMN_WIDTH) << "Address" << get_address() << endl;
	formatted << setw(COLUMN_WIDTH) << "City" << get_city() << endl;
	formatted << setw(COLUMN_WIDTH) << "County" << get_county() << endl;
	formatted << setw(COLUMN_WIDTH) << "State" << get_state() << endl;
	formatted << setw(COLUMN_WIDTH) << "Zip" << get_zip() << endl;

	formatted << setw(COLUMN_WIDTH) << "Primary Phone Number:" << get_primary_phone_number() << endl;
	formatted << setw(COLUMN_WIDTH) << "Secondary Phone Number:" << get_secondary_phone_number() << endl;
	formatted << setw(COLUMN_WIDTH) << "Email:" << get_email() << endl;
    return formatted.str();
}

const std::string Contact::to_column_string() const
{
    stringstream formatted;
    formatted << left;
    formatted << person.to_column_string();

	formatted << setw(LONG_COLUMN_WIDTH) << get_address();
	formatted << setw(LONG_COLUMN_WIDTH) << get_city();
	formatted << setw(LONG_COLUMN_WIDTH) << get_county();
	formatted << setw(SHORT_COLUMN_WIDTH) << get_state();
	formatted << setw(SHORT_COLUMN_WIDTH) << get_zip();

	formatted << setw(MEDIUM_COLUMN_WIDTH) << get_primary_phone_number();
	formatted << setw(MEDIUM_COLUMN_WIDTH) << get_secondary_phone_number();
	formatted << setw(LONG_COLUMN_WIDTH) << get_email();
    return formatted.str();
}
