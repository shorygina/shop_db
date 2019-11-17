#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

using namespace std;

class Product
{
public:
    Product();
    Product(string, int, double, int);
    Product(const Product*);
    ~Product() {}

    string get_name();
    int get_id();
    double get_price();
    int get_quantity();

    void set_name(string);
    void set_id(int);
    void set_price(double);
    void set_quantity(int);

protected:
    string name_of_product;
    int id, quantity;
    double price;
};

#endif // PRODUCT_H
