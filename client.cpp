#include "client.h"

Client::Client()
{
    this->name = "-";
    this->surname = "-";
    this->address = "-";
    this->email = "-";
    this->number = 0;
    this->needed_id = 0;
    this->quantity_needed = 0;
}

Client::Client(string name, string surname, string address, string email, long long number, int needed_id, int quantity_needed)
{
    this->name = name;
    this->surname = surname;
    this->address = address;
    this->email = email;
    this->number = number;
    this->needed_id = needed_id;
    this->quantity_needed = quantity_needed;
}

Client::Client(const Client* other)
{
    this->name = other->name;
    this->surname = other->surname;
    this->address = other->address;
    this->email = other->email;
    this->number = other->number;
    this->needed_id = other->needed_id;
    this->quantity_needed = other->quantity_needed;
}

int Client::nameUrself() { return 2;}

int Client::get_needed_id()
{
    return this->needed_id;
}

int Client::get_quantity_needed()
{
    return this->quantity_needed;
}

void Client::set_needed_id(int id)
{
    this->needed_id = id;
}

void Client::set_quantity_needed(int quantity)
{
    this->quantity_needed = quantity;
}
