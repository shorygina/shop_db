#ifndef LEGALENTITY_H
#define LEGALENTITY_H

#include <string>

using namespace std;


class LegalEntity
{
public:
    virtual ~LegalEntity() {}

    virtual int nameUrself() = 0;

    string get_name();
    string get_surname();
    string get_address();
    string get_email();
    long long get_number();

    void set_name(string name);
    void set_surname(string surname);
    void set_address(string address);
    void set_email(string email);
    void set_number(long long number);

protected:
    string name;
    string surname;
    string address;
    string email;
    long long number;
};

#endif // LEGALENTITY_H
