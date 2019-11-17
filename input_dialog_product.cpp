#include "input_dialog_product.h"

input_dialog_product::input_dialog_product(QWidget *parent) : QDialog(parent), d_validator(0.01, 10000.00, 2, this), i_validator(1, 10000, this)
{
    ok = new QPushButton("ok", this);

    id_label = new QLabel("Product ID", this);
    name_label = new QLabel("Name of product", this);
    price_label = new QLabel("Price", this);
    quantity_label = new QLabel("Quantity", this);

    id_le = new QLineEdit(this);
    name_le = new QLineEdit(this);
    price_le = new QLineEdit(this);
    quantity_le = new QLineEdit(this);

    manager = new QGridLayout(this);

    manager->addWidget(id_label, 0, 0);
    manager->addWidget(name_label, 0, 1);
    manager->addWidget(price_label, 0, 2);
    manager->addWidget(quantity_label, 0, 3);

    manager->addWidget(id_le, 1, 0);
    manager->addWidget(name_le, 1, 1);
    manager->addWidget(price_le, 1, 2);
    manager->addWidget(quantity_le, 1, 3);

    price_le->setValidator(&d_validator);
    id_le->setValidator(&i_validator);
    quantity_le->setValidator(&i_validator);

    connect(price_le, SIGNAL(textChanged(QString)), this, SLOT(on_changed()));
    connect(id_le, SIGNAL(textChanged(QString)), this, SLOT(on_changed()));
    connect(quantity_le, SIGNAL(textChanged(QString)), this, SLOT(on_changed()));

    manager->addWidget(ok, 2, 3);
    connect(ok, SIGNAL(clicked()), this, SLOT(accept()));
}

void input_dialog_product::on_ok_button_clicked() {}

void input_dialog_product::on_changed() {}

input_dialog_product::~input_dialog_product() {
    delete ok;
}
