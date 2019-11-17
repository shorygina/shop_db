#include "provider.h"

Provider::Provider()
{
    this->delivered_id = 0;
    this->delivered_quantity = 0;
    this->address = "-";
    this->email = "-";
    this->name = "-";
    this->number = 0;
    this->surname = "-";
}

Provider::Provider(int deliveredQuantity, int delivered_id, string name, string surname, string address, string email, long long number)
{
    this->delivered_id = delivered_id;
    this->name = name;
    this->surname = surname;
    this->address = address;
    this->email = email;
    this->number = number;
    this->delivered_quantity = deliveredQuantity;
}

Provider::Provider(const Provider *other)
{
    this->delivered_quantity = other->delivered_quantity;
    this->address = other->address;
    this->email = other->email;
    this->name = other->name;
    this->number = other->number;
    this->surname = other->surname;
    this->delivered_id = other->delivered_id;
}

int Provider::nameUrself() { return 1;}

int Provider::get_delivered_quantity()
{
    return this->delivered_quantity;
}

int Provider::get_delivered_id()
{
    return this->delivered_id;
}

void Provider::set_delivered_id(int delivered_id)
{
    this->delivered_id = delivered_id;
}

void Provider::set_delivered_quantity(int delivered_quantity)
{
    this->delivered_quantity = delivered_quantity;
}
