#ifndef CLIENT_H
#define CLIENT_H

#include "legalentity.h"

class Client : public LegalEntity
{
public:
    Client();
    Client(string, string, string, string, long long, int, int);
    Client(const Client*);
    virtual ~Client() {}

    int nameUrself();

    int get_needed_id();
    int get_quantity_needed();
    void set_needed_id(int);
    void set_quantity_needed(int);

private:
    int needed_id, quantity_needed;
};

#endif // CLIENT_H
