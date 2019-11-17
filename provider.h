#ifndef PROVIDER_H
#define PROVIDER_H

#include "legalentity.h"
#include "product.h"

class Provider : public LegalEntity
{
public:
    Provider();
    Provider(int, int, string, string, string, string, long long);
    Provider(const Provider*);
    virtual ~Provider() {}

    int nameUrself();

    int get_delivered_quantity();
    int get_delivered_id();

    void set_delivered_id(int);
    void set_delivered_quantity(int);

private:
    int delivered_id, delivered_quantity;
};

#endif // PROVIDER_H
