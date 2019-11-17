#include "base.h"

Base::Base()
{
    products.reserve(1);
    providers_and_clients.reserve(1);
}

Base::Base(const Base *other)
{
    this->products = other->products;
    this->providers_and_clients = other->providers_and_clients;
}

Base::~Base()
{
    products.clear();
    providers_and_clients.clear();
}

void Base::add_product(Product* product)
{
    this->products.push_back(product);
}

void Base::read_from_file(string file_name)
{
    products.clear();
    providers_and_clients.clear();
    string buff;
    int n;

    ifstream fin(file_name);
    if (!fin.is_open()) exit(1);

    fin >> buff; //products
    n = stoi(buff);
    for (int i=0; i<n; ++i)
    {
        Product* helper_product = new Product;
        fin >> buff;
        helper_product->set_id(stoi(buff));
        fin >> buff;
        helper_product->set_name(buff);
        fin >> buff;
        helper_product->set_price(stod(buff));
        fin >> buff;
        helper_product->set_quantity(stoi(buff));
        add_product(helper_product);
    }

    fin >> buff; //clients
    n = stoi(buff);
    for (int i=0; i<n; ++i)
    {
        Client* helper_client = new Client;
        fin >> buff;
        helper_client->set_name(buff);
        fin >> buff;
        helper_client->set_surname(buff);
        fin >> buff;
        helper_client->set_address(buff);
        fin >> buff;
        helper_client->set_email(buff);
        fin >> buff;
        helper_client->set_number(stoll(buff));
        fin >> buff;
        helper_client->set_needed_id(stoi(buff));
        fin >> buff;
        helper_client->set_quantity_needed(stoi(buff));
        add_legal_entity(helper_client);
    }

    fin >> buff; //providers
    n = stoi(buff);
    for (int i=0; i<n; ++i)
    {
        Provider* helper_provider = new Provider;
        fin >> buff;
        helper_provider->set_name(buff);
        fin >> buff;
        helper_provider->set_surname(buff);
        fin >> buff;
        helper_provider->set_address(buff);
        fin >> buff;
        helper_provider->set_email(buff);
        fin >> buff;
        helper_provider->set_number(stoll(buff));
        fin >> buff;
        helper_provider->set_delivered_id(stoi(buff));
        fin >> buff;
        helper_provider->set_delivered_quantity(stoi(buff));
        add_legal_entity(helper_provider);
    }
    fin.close();
}

int Base::get_number_of_providers()
{
    int cnt = 0;

    for (vector<LegalEntity*>::iterator it = providers_and_clients.begin(); it != providers_and_clients.end(); ++it)
        if ((*it)->nameUrself() == 1) cnt++;

    return cnt;
}
int Base::get_number_of_clients()
{
    int cnt = 0;

    for (vector<LegalEntity*>::iterator it = providers_and_clients.begin(); it != providers_and_clients.end(); ++it)
        if ((*it)->nameUrself() == 2) cnt++;

    return cnt;
}

int Base::get_number_of_products()
{
    return this->products.size();
}
