
#include <string>
#include <inttypes.h>

using namespace std;

enum ROLES
{
    ROLE_NONE,
    ROLE_INSTRUCTOR,
    ROLE_STUDENT,
};

class Contact
{
public:

    Contact() = default;
    Contact(int _id, string _first_name, string _middle_name, string _last_name, ROLES _role, string _organization, string _address, string _city, string _county, string _state, int _zip, string _primary_phone_number, string _secondary_phone_number, string _email)
        : id(_id)
        , first_name(_first_name)
        , middle_name(_middle_name)
        , last_name(_last_name)
        , role(_role)
        , organization(_organization)
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

    //Setters
    void set_id(int new_id) {id = new_id;}
    void set_first_name(string new_first_name) {first_name = new_first_name;}
    void set_middle_name(string new_middle_name)  {middle_name = new_middle_name;}
    void set_last_name(string new_last_name) {last_name = new_last_name;}

    void set_role(ROLES new_role) {role = new_role;}
    void set_organization(string new_organization) {organization = new_organization;}

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
    string get_first_name() const {return first_name;}
    string get_middle_name() const {return middle_name;}
    string get_last_name() const {return last_name;}

    ROLES get_role() const {return role;}
    string get_organization() const {return organization;}

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
    string first_name;
    string middle_name;
    string last_name;

    ROLES role;
    string organization;

    string address;
    string city;
    string county;
    string state;
    int zip;

    string primary_phone_number;
    string secondary_phone_number;
    string email;
};