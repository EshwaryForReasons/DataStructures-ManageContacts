
#include "Contact.h"

Contact Contact::operator=(const Contact& other)
{
    id = other.get_id();
    first_name = other.get_first_name();
    middle_name = other.get_middle_name();
    last_name = other.get_last_name();
    role = other.get_role();
    organization = other.get_organization();
    address = other.get_address();
    city = other.get_city();
    county = other.get_county();
    state = other.get_state();
    zip = other.get_zip();
    primary_phone_number = other.get_primary_phone_number();
    secondary_phone_number = other.get_secondary_phone_number();
    email = other.get_email();
    return Contact(id, first_name, middle_name, last_name, role, organization, address, city, county, state, zip, primary_phone_number, secondary_phone_number, email);
}