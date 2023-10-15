
#include "Contact.h"
#include "ContactList.h"
#include "ContactMenu.h"

#include <iomanip>
#include <sstream>

Contact Contact::operator=(const Contact& other)
{
    id = other.id;
    first_name = other.first_name;
    middle_name = other.middle_name;
    last_name = other.last_name;
    role = other.role;
    organization = other.organization;
    address = other.address;
    city = other.city;
    county = other.county;
    state = other.state;
    zip = other.zip;
    primary_phone_number = other.primary_phone_number;
    secondary_phone_number = other.secondary_phone_number;
    email = other.email;
    return Contact(id, first_name, middle_name, last_name, role, organization, address, city, county, state, zip, primary_phone_number, secondary_phone_number, email);
}

const bool Contact::operator==(const Contact& other)
{
    return (id == other.id && first_name == other.first_name && middle_name == other.middle_name && last_name == other.last_name && role == other.role && organization == other.organization && address == other.address && city == other.city && county == other.county && state == other.state && zip == other.zip && primary_phone_number == other.primary_phone_number && secondary_phone_number == other.secondary_phone_number && email == other.email);
}

const bool Contact::operator!=(const Contact& other)
{
    return (id != other.id || first_name != other.first_name || middle_name != other.middle_name || last_name != other.last_name || role != other.role || organization != other.organization || address != other.address || city != other.city || county != other.county || state != other.state || zip != other.zip || primary_phone_number != other.primary_phone_number || secondary_phone_number != other.secondary_phone_number || email != other.email);
}

const bool Contact::operator<(const Contact& other)
{
    const std::pair<string, string> strings = retrieve_comparision_string(other);
    return compare_strings(strings.first, strings.second) == 1;
}

const bool Contact::operator>(const Contact& other)
{
    const std::pair<string, string> strings = retrieve_comparision_string(other);
    return compare_strings(strings.second, strings.first) == 1;
}

const string Contact::to_string() const
{
    return string(std::to_string(get_id()) + "," + Person::to_string() + "," + get_address() + "," + get_city() + "," + get_county() + "," + get_state() + "," + std::to_string(get_zip()) + "," + get_primary_phone_number() + "," + get_secondary_phone_number() + "," + get_email());
}

const string Contact::to_labeled_string() const
{
    stringstream formatted;
	formatted << left;
	formatted << setw(COLUMN_WIDTH) << "Id:" << get_id() << endl;
    formatted << Person::to_labeled_string();

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

const string Contact::to_column_string() const
{
    stringstream formatted;
    formatted << left;
	formatted << setw(SHORT_COLUMN_WIDTH) << get_id();
    formatted << Person::to_column_string();

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

const std::pair<string, string> Contact::retrieve_comparision_string(const Contact& other) const
{
    string our_field;
    string other_field;

    switch(ContactList::CurrentComparisionField)
    {
    case INFO_NONE:
    case INFO_ID:
    {
        our_field = std::to_string(id);
        other_field = std::to_string(other.id);
        break;
    }
    case INFO_ADDRESS:
    {
        our_field = address;
        other_field = other.address;
        break;
    }
    case INFO_CITY:
    {
        our_field = city;
        other_field = other.city;
        break;
    }
    case INFO_COUNTY:
    {
        our_field = county;
        other_field = other.county;
        break;
    }
    case INFO_STATE:
    {
        our_field = state;
        other_field = other.state;
        break;
    }
    case INFO_ZIP:
    {
        our_field = std::to_string(zip);
        other_field = std::to_string(other.zip);
        break;
    }
    case INFO_PRIMARY_PHONE_NUMBER:
    {
        our_field = primary_phone_number;
        other_field = other.primary_phone_number;
        break;
    }
    case INFO_SECONDARY_PHONE_NUMBER:
    {
        our_field = secondary_phone_number;
        other_field = other.secondary_phone_number;
        break;
    }
    case INFO_EMAIL:
    {
        our_field = email;
        other_field = other.email;
        break;
    }
    //If we are comparing a person field
    case INFO_FIRST_NAME:
    case INFO_MIDDLE_NAME:
    case INFO_LAST_NAME:
    case INFO_ROLE:
    case INFO_ORGANIZATION:
    {
        return Person::retrieve_comparision_string(other);
    }
    };

    return std::pair<string, string>(our_field, other_field);
}