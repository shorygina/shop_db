#ifndef BASE_H
#define BASE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <typeinfo.h>

using namespace std;

#include "legalentity.h"
#include "client.h"
#include "product.h"
#include "provider.h"

class Base
{
public:
    Base();
    Base(const Base *other);
    ~Base();

    void add_product(Product* product);
    template <typename T>
    void add_legal_entity(T* clientOrProvider)
    {
        T* tmp = new T(clientOrProvider);
        LegalEntity *helper = nullptr;
        helper = static_cast<T*>(tmp);
        providers_and_clients.push_back(helper);
    }

    void read_from_file(string file_name);

    int get_number_of_providers();
    int get_number_of_clients();
    int get_number_of_products();

    friend ofstream& operator<<(ofstream &file, Base &base)
    {
        int cnt = 0;
        vector<LegalEntity*>::iterator cl_iter = base.providers_and_clients.begin();
        vector<LegalEntity*>::iterator provider_iter = base.providers_and_clients.begin();

        file << base.get_number_of_products() << endl;
        for (vector<Product*>::iterator pr_iter = base.products.begin(); pr_iter != base.products.end(); pr_iter++)
                file << (*pr_iter)->get_id() << " " << (*pr_iter)->get_name() << " " << (*pr_iter)->get_price() << " " << (*pr_iter)->get_quantity() << endl;

        for (vector<LegalEntity*>::iterator iter = base.providers_and_clients.begin(); iter != base.providers_and_clients.end(); iter++)
            if ((*iter)->nameUrself() == 2) ++cnt;
        file << cnt << endl;
        for (; cl_iter != base.providers_and_clients.end(); cl_iter++)
            if ((*cl_iter)->nameUrself() == 2)
            {
                Client* client_helper;
                client_helper = static_cast<Client*>(*cl_iter);
                file << client_helper->get_name() << " " << client_helper->get_surname()  << " " << client_helper->get_address()  << " " << client_helper->get_email()  << " " << client_helper->get_number()  << " " << client_helper->get_needed_id()  << " " << client_helper->get_quantity_needed() << endl;
            }

        cnt = 0;
        for (vector<LegalEntity*>::iterator iter = base.providers_and_clients.begin(); iter != base.providers_and_clients.end(); iter++)
            if ((*iter)->nameUrself() == 1) ++cnt;
        file << cnt << endl;
        for (; provider_iter != base.providers_and_clients.end(); provider_iter++)
            if ((*provider_iter)->nameUrself() == 1)
            {
                Provider* provider_helper;
                provider_helper = static_cast<Provider*>(*provider_iter);
                file << provider_helper->get_name()  << " " << provider_helper->get_surname()  << " " << provider_helper->get_address()  << " " << provider_helper->get_email()  << " " << provider_helper->get_number()  << " " << provider_helper->get_delivered_id()  << " " << provider_helper->get_delivered_quantity() << endl;
            }
        return file;
    }

private:
    vector<LegalEntity*> providers_and_clients;
    vector<Product*> products;
    friend class MainWindow;
};

#endif // BASE_H
