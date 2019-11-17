#include "input_dialog_provider.h"

input_dialog_provider::input_dialog_provider(QWidget *parent) : QDialog(parent), i_validator(1, 10000, this)
{
    ok = new QPushButton("ok", this);

    name_label = new QLabel("Name", this);
    surname_label = new QLabel("Surname", this);
    address_label = new QLabel("Address", this);
    email_label = new QLabel("Email", this);
    number_label = new QLabel("Number", this);
    provided_id_label = new QLabel("Product ID", this);
    provided_quantity_label = new QLabel("Quantity", this);

    name_le = new QLineEdit(this);
    surname_le = new QLineEdit(this);
    address_le = new QLineEdit(this);
    email_le = new QLineEdit(this);
    number_le = new QLineEdit(this);
    provided_id_le = new QLineEdit(this);
    provided_quantity_le = new QLineEdit(this);

    manager = new QGridLayout(this);

    manager->addWidget(name_label, 0, 0);
    manager->addWidget(surname_label, 0, 1);
    manager->addWidget(address_label, 0, 2);
    manager->addWidget(email_label, 0, 3);
    manager->addWidget(number_label, 0, 4);
    manager->addWidget(provided_id_label, 0, 5);
    manager->addWidget(provided_quantity_label, 0, 6);

    manager->addWidget(name_le, 1, 0);
    manager->addWidget(surname_le, 1, 1);
    manager->addWidget(address_le, 1, 2);
    manager->addWidget(email_le, 1, 3);
    manager->addWidget(number_le, 1, 4);
    manager->addWidget(provided_id_le, 1, 5);
    manager->addWidget(provided_quantity_le, 1, 6);

    provided_id_le->setValidator(&i_validator);
    provided_quantity_le->setValidator(&i_validator);
    connect(provided_id_le, SIGNAL(textChanged(QString)), this, SLOT(on_changed()));
    connect(provided_quantity_le, SIGNAL(textChanged(QString)), this, SLOT(on_changed()));

    manager->addWidget(ok, 2, 6);
    connect(ok, SIGNAL(clicked()), this, SLOT(accept()));
}

void input_dialog_provider::on_ok_button_clicked() {

}

void input_dialog_provider::on_changed() {

}

input_dialog_provider::~input_dialog_provider() {
    delete ok;
}
