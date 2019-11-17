#include "legalentity.h"

string LegalEntity::get_name()
{
    return this->name;
}

string LegalEntity::get_surname()
{
    return this->surname;
}

string LegalEntity::get_address()
{
    return this->address;
}

string LegalEntity::get_email()
{
    return this->email;
}

long long LegalEntity::get_number()
{
    return this->number;
}

void LegalEntity::set_name(string name)
{
    this->name = name;
}

void LegalEntity::set_surname(string surname)
{
    this->surname = surname;
}

void LegalEntity::set_address(string address)
{
    this->address = address;
}

void LegalEntity::set_email(string email)
{
    this->email = email;
}

void LegalEntity::set_number(long long number)
{
    this->number = number;
}
