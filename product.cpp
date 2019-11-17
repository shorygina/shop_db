#include "product.h"

Product::Product()
{
    this->id = 0;
    this->name_of_product = "-";
    this->price = 0;
    this->quantity = 0;
}

Product::Product(string nameOfProduct, int id, double price, int quantity)
{
    this->name_of_product = nameOfProduct;
    this->id = id;
    this->price = price;
    this->quantity = quantity;
}

Product::Product(const Product* other)
{
    this->id = other->id;
    this->name_of_product = other->name_of_product;
    this->price = other->price;
    this->quantity = other->quantity;
}

string Product::get_name()
{
    return this->name_of_product;
}

int Product::get_id()
{
    return this->id;
}

double Product::get_price()
{
    return this->price;
}

int Product::get_quantity()
{
    return this->quantity;
}

void Product::set_name(string name)
{
    this->name_of_product = name;
}

void Product::set_id(int id)
{
    this->id = id;
}

void Product::set_price(double price)
{
    this->price = price;
}

void Product::set_quantity(int quantity)
{
    this->quantity = quantity;
}
