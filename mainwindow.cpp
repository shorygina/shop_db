#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "base.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->MainWindow::centralWidget->setMinimumSize(1000, 700);
    ui->centralWidget->setMaximumSize(1000, 700);
    ui->table_clients->setMinimumSize(650, 300);
    ui->table_products->setMinimumSize(300, 300);
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);

    model_clients = new QStandardItemModel(0, 7, this);
    model_products = new QStandardItemModel(0, 4, this);
    model_providers = new QStandardItemModel(0, 7, this);

    ui->table_clients->setModel(model_clients);
    ui->table_products->setModel(model_products);
    ui->table_providers->setModel(model_providers);

    model_clients->setHeaderData(0, Qt::Horizontal, "Name");
    model_clients->setHeaderData(1, Qt::Horizontal, "Surname");
    model_clients->setHeaderData(2, Qt::Horizontal, "Address");
    model_clients->setHeaderData(3, Qt::Horizontal, "Email");
    model_clients->setHeaderData(4, Qt::Horizontal, "Number");
    model_clients->setHeaderData(5, Qt::Horizontal, "Product");
    model_clients->setHeaderData(6, Qt::Horizontal, "Quantity");

    model_products->setHeaderData(0, Qt::Horizontal, "ID");
    model_products->setHeaderData(1, Qt::Horizontal, "Product");
    model_products->setHeaderData(2, Qt::Horizontal, "Price");
    model_products->setHeaderData(3, Qt::Horizontal, "Quantity");

    model_providers->setHeaderData(0, Qt::Horizontal, "Name");
    model_providers->setHeaderData(1, Qt::Horizontal, "Surname");
    model_providers->setHeaderData(2, Qt::Horizontal, "Address");
    model_providers->setHeaderData(3, Qt::Horizontal, "Email");
    model_providers->setHeaderData(4, Qt::Horizontal, "Number");
    model_providers->setHeaderData(5, Qt::Horizontal, "Product's ID");
    model_providers->setHeaderData(6, Qt::Horizontal, "Quantity");

    ui->table_clients->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->table_clients->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->table_clients->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    ui->table_clients->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
    ui->table_clients->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);
    ui->table_clients->horizontalHeader()->setSectionResizeMode(5, QHeaderView::Stretch);
    ui->table_clients->horizontalHeader()->setSectionResizeMode(6, QHeaderView::Stretch);

    ui->table_products->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->table_products->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->table_products->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    ui->table_products->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);

    ui->table_providers->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->table_providers->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->table_providers->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    ui->table_providers->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
    ui->table_providers->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);
    ui->table_providers->horizontalHeader()->setSectionResizeMode(5, QHeaderView::Stretch);
    ui->table_providers->horizontalHeader()->setSectionResizeMode(6, QHeaderView::Stretch);

    ui->table_products->setMaximumSize(ui->table_clients->size().width()*3, 600);

    ui->table_clients->setEditTriggers(QAbstractItemView::DoubleClicked);
    ui->table_products->setEditTriggers(QAbstractItemView::DoubleClicked);
    ui->table_providers->setEditTriggers(QAbstractItemView::DoubleClicked);
    ui->delete_client->setEnabled(false);
    ui->delete_provider->setEnabled(false);
    ui->delete_product->setEnabled(false);

    connect(ui->table_clients, SIGNAL(clicked(QModelIndex)), this, SLOT(on_clicked_clients(QModelIndex)));
    connect(ui->table_providers, SIGNAL(clicked(QModelIndex)), this, SLOT(on_clicked_providers(QModelIndex)));
    connect(ui->table_products, SIGNAL(clicked(QModelIndex)), this, SLOT(on_clicked_products(QModelIndex)));
    connect(ui->table_clients->itemDelegate(),SIGNAL(closeEditor(QWidget*,QAbstractItemDelegate::EndEditHint)),SLOT(on_edit_client_finished()));
    connect(ui->table_providers->itemDelegate(),SIGNAL(closeEditor(QWidget*,QAbstractItemDelegate::EndEditHint)),SLOT(on_edit_provider_finished()));
    connect(ui->table_products->itemDelegate(),SIGNAL(closeEditor(QWidget*,QAbstractItemDelegate::EndEditHint)),SLOT(on_edit_product_finished()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_add_client_clicked()
{
    string name, surname, address, email;
    long long number;
    int id, quantity;

    form = new input_dialog(this);
    form->show();
    form->exec();
    if(form->result() == QDialog::Accepted) {
        name = form->name_le->text().toStdString();
        surname = form->surname_le->text().toStdString();
        address = form->address_le->text().toStdString();
        email = form->email_le->text().toStdString();
        number = form->number_le->text().toLongLong();
        id = form->needed_id_le->text().toInt();
        quantity = form->needed_quantity_le->text().toInt();
        Client client_helper(name, surname, address, email, number, id, quantity);
        b.add_legal_entity(&client_helper);
        fill_table_clients(b, b.get_number_of_clients());
    }
    delete form;
}

void MainWindow::on_read_from_file_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this, tr("Open file"), "C:/users/tanya/desktop/", "Text files (*.txt);;");
    string input_file_name = file_name.toStdString();
    b.read_from_file(input_file_name);

    fill_table_clients(b, b.get_number_of_clients());
    fill_table_providers(b, b.get_number_of_providers());
    fill_table_products(b, b.get_number_of_products());
}

void MainWindow::fill_table_clients(Base b, int row) {
    model_clients->setRowCount(row);
    int current_row = 0;
    QVariant helper;
    QModelIndex index;
    Client* client_helper;

    for (vector<LegalEntity*>::iterator it = b.providers_and_clients.begin(); it != b.providers_and_clients.end(); ++it)
    {
        if ((*it)->nameUrself() == 2)
        {
            client_helper = static_cast<Client*>(*it);

            index = model_clients->index(current_row, 0);
            helper = QString::fromStdString(client_helper->get_name());
            model_clients->setData(index, helper);

            index = model_clients->index(current_row, 1);
            helper = QString::fromStdString(client_helper->get_surname());
            model_clients->setData(index, helper);

            index = model_clients->index(current_row, 2);
            helper = QString::fromStdString(client_helper->get_address());
            model_clients->setData(index, helper);

            index = model_clients->index(current_row, 3);
            helper = QString::fromStdString(client_helper->get_email());
            model_clients->setData(index, helper);

            index = model_clients->index(current_row, 4);
            model_clients->setData(index, client_helper->get_number());

            index = model_clients->index(current_row, 5);
            model_clients->setData(index, client_helper->get_needed_id());

            index = model_clients->index(current_row, 6);
            model_clients->setData(index, client_helper->get_quantity_needed());

            ++current_row;
        }
    }
}

void MainWindow::fill_table_providers(Base b, int row)
{
    model_providers->setRowCount(row);
    int current_row = 0;
    QVariant helper;
    QModelIndex index;
    Provider* provider_helper;

    for (vector<LegalEntity*>::iterator it = b.providers_and_clients.begin(); it != b.providers_and_clients.end(); ++it)
    {
        if ((*it)->nameUrself() == 1)
        {
            provider_helper = static_cast<Provider*>(*it);

            index = model_providers->index(current_row, 0);
            helper = QString::fromStdString(provider_helper->get_name());
            model_providers->setData(index, helper);

            index = model_providers->index(current_row, 1);
            helper = QString::fromStdString(provider_helper->get_surname());
            model_providers->setData(index, helper);

            index = model_providers->index(current_row, 2);
            helper = QString::fromStdString(provider_helper->get_address());
            model_providers->setData(index, helper);

            index = model_providers->index(current_row, 3);
            helper = QString::fromStdString(provider_helper->get_email());
            model_providers->setData(index, helper);

            index = model_providers->index(current_row, 4);
            model_providers->setData(index, provider_helper->get_number());

            index = model_providers->index(current_row, 5);
            model_providers->setData(index, provider_helper->get_delivered_id());

            index = model_providers->index(current_row, 6);
            model_providers->setData(index, provider_helper->get_delivered_quantity());

            ++current_row;
        }
    }
}

void MainWindow::fill_table_products(Base b, int row)
{
    model_products->setRowCount(row);
    int current_row = 0;
    QVariant helper;
    QModelIndex index;

    for (vector<Product*>::iterator it = b.products.begin(); it != b.products.end(); ++it)
    {
        index = model_products->index(current_row, 0);
        model_products->setData(index, (*it)->get_id());

        index = model_products->index(current_row, 1);
        helper = QString::fromStdString((*it)->get_name());
        model_products->setData(index, helper);

        index = model_products->index(current_row, 2);
        model_products->setData(index, double((*it)->get_price()));

        index = model_products->index(current_row, 3);
        model_products->setData(index, (*it)->get_quantity());

        ++current_row;
    }
}

void MainWindow::on_add_provider_clicked()
{
    string name, surname, address, email;
    long long number;
    int id, quantity;

    form_provider = new input_dialog_provider(this);
    form_provider->show();
    form_provider->exec();
    if(form_provider->result() == QDialog::Accepted) {
        name = form_provider->name_le->text().toStdString();
        surname = form_provider->surname_le->text().toStdString();
        address = form_provider->address_le->text().toStdString();
        email = form_provider->email_le->text().toStdString();
        number = form_provider->number_le->text().toLongLong();
        id = form_provider->provided_id_le->text().toInt();
        quantity = form_provider->provided_quantity_le->text().toInt();
        Provider provider_helper(quantity, id, name, surname, address, email, number);
        b.add_legal_entity(&provider_helper);
        fill_table_providers(b, b.get_number_of_providers());
    }
    delete form_provider;
}

void MainWindow::on_add_product_clicked()
{
    string name;
    double price;
    int id, quantity;

    form_product = new input_dialog_product(this);
    form_product->show();
    form_product->exec();
    if(form_product->result() == QDialog::Accepted) {
        id = form_product->id_le->text().toInt();
        name = form_product->name_le->text().toStdString();
        price = form_product->price_le->text().toDouble();
        quantity = form_product->quantity_le->text().toInt();

        Product product_helper(name, id, price, quantity);
        b.add_product(&product_helper);
        fill_table_products(b, b.get_number_of_products());
    }
    delete form_product;
}

void MainWindow::on_write_into_file_clicked()
{
    QString file_name = QFileDialog::getSaveFileName(this, tr("Save data"), "C:/users/tanya/desktop/", tr("Text files (*.txt)"));
    std::ofstream output_file;
    output_file.open(file_name.toStdString());
    output_file << b;
    output_file.close();
}

void MainWindow::on_delete_client_clicked()
{
    for (vector<LegalEntity*>::iterator it = b.providers_and_clients.begin(); it != b.providers_and_clients.end(); ++it)
        if ((*it)->nameUrself() == 2)
            if ((*it)->get_name() == key)
            {
                b.providers_and_clients.erase(it);
                break;
            }
    fill_table_clients(b, b.get_number_of_clients());
    ui->delete_client->setEnabled(false);
    ui->delete_provider->setEnabled(false);
    ui->delete_product->setEnabled(false);
}

void MainWindow::on_clicked_clients(const QModelIndex &index) {
    QModelIndex ind = model_clients->index(index.row(), 0);
    backup_index = index;
    backup_name = (ind.model()->data(ind.model()->index(ind.row(),0)).toString()).toStdString();
    backup_id = (ind.model()->data(ind.model()->index(ind.row(),5)).toString()).toInt();
    QString get_information = (ind.model()->data(ind.model()->index(ind.row(),ind.column())).toString());
    ui->delete_client->setEnabled(true);
    ui->delete_provider->setEnabled(false);
    ui->delete_product->setEnabled(false);
    key = get_information.toStdString();
}

void MainWindow::on_clicked_providers(const QModelIndex &index) {
    QModelIndex ind = model_providers->index(index.row(), 0);
    backup_index = index;
    backup_name = (ind.model()->data(ind.model()->index(ind.row(),0)).toString()).toStdString();
    backup_id = (ind.model()->data(ind.model()->index(ind.row(),5)).toString()).toInt();
    QString get_information = (ind.model()->data(ind.model()->index(ind.row(),ind.column())).toString());
    ui->delete_provider->setEnabled(true);
    ui->delete_client->setEnabled(false);
    ui->delete_product->setEnabled(false);
    key = get_information.toStdString();
}

void MainWindow::on_clicked_products(const QModelIndex &index) {
    QModelIndex ind = model_products->index(index.row(), 1);
    backup_index = index;
    backup_name = (ind.model()->data(ind.model()->index(ind.row(),1)).toString()).toStdString();
    backup_id = (ind.model()->data(ind.model()->index(ind.row(),0)).toString()).toInt();
    QString get_information = (ind.model()->data(ind.model()->index(ind.row(),ind.column())).toString());
    ui->delete_product->setEnabled(true);
    ui->delete_provider->setEnabled(false);
    ui->delete_client->setEnabled(false);
    key = get_information.toStdString();
}

void MainWindow::on_delete_provider_clicked()
{
    for (vector<LegalEntity*>::iterator it = b.providers_and_clients.begin(); it != b.providers_and_clients.end(); ++it)
        if ((*it)->nameUrself() == 1)
            if ((*it)->get_name() == key)
            {
                b.providers_and_clients.erase(it);
                break;
            }
    fill_table_providers(b, b.get_number_of_providers());
    ui->delete_client->setEnabled(false);
    ui->delete_provider->setEnabled(false);
    ui->delete_product->setEnabled(false);
}

void MainWindow::on_delete_product_clicked()
{
    for (vector<Product*>::iterator it = b.products.begin(); it != b.products.end(); ++it)
            if ((*it)->get_name() == key)
            {
                b.products.erase(it);
                break;
            }
    fill_table_products(b, b.get_number_of_products());
    ui->delete_client->setEnabled(false);
    ui->delete_provider->setEnabled(false);
    ui->delete_product->setEnabled(false);
}

void MainWindow::on_edit_client_finished()
{
    QString get_information = (backup_index.model()->data(backup_index.model()->index(backup_index.row(),backup_index.column())).toString());
    string helper_str = get_information.toStdString();
    int helper_int = get_information.toInt();
    QString get_client_information = (backup_index.model()->data(backup_index.model()->index(backup_index.row(), 0)).toString());
    string key_client = get_information.toStdString();
    //cout << key_client;

    Client* helper_client;
    for (vector<LegalEntity*>::iterator it = b.providers_and_clients.begin(); it != b.providers_and_clients.end(); ++it)
        if ((*it)->nameUrself() == 2)
        {
            helper_client = static_cast<Client*>(*it);

            if (backup_index.column() == 0 && (backup_name == helper_client->get_name() || backup_id == helper_client->get_needed_id()))
            {
                helper_client->set_name(helper_str);
                break;
            }
            if (backup_index.column() == 1 && (backup_name == helper_client->get_name() || backup_id == helper_client->get_needed_id()))
            {
                helper_client->set_surname(helper_str);
                break;
            }
            if (backup_index.column() == 2 && (backup_name == helper_client->get_name() || backup_id == helper_client->get_needed_id()))
            {
                helper_client->set_address(helper_str);
                break;
            }
            if (backup_index.column() == 3 && (backup_name == helper_client->get_name() || backup_id == helper_client->get_needed_id()))
            {
                helper_client->set_email(helper_str);
                break;
            }
            if (backup_index.column() == 4 && (backup_name == helper_client->get_name() || backup_id == helper_client->get_needed_id()))
            {
                helper_client->set_number(stoll(helper_str));
                break;
            }
            if (backup_index.column() == 5 && (backup_name == helper_client->get_name() || backup_id == helper_client->get_needed_id()))
            {
                helper_client->set_needed_id(helper_int);
                break;
            }
            if (backup_index.column() == 6 && (backup_name == helper_client->get_name() || backup_id == helper_client->get_needed_id()))
            {
                helper_client->set_quantity_needed(helper_int);
                break;
            }
        }
    fill_table_clients(b, b.get_number_of_clients());
}

void MainWindow::on_edit_provider_finished()
{
    QString get_information = (backup_index.model()->data(backup_index.model()->index(backup_index.row(),backup_index.column())).toString());
    string helper_str = get_information.toStdString();
    int helper_int = get_information.toInt();
    QString get_provider_information = (backup_index.model()->data(backup_index.model()->index(backup_index.row(), 0)).toString());
    string key_provider= get_information.toStdString();

    Provider* helper_provider;
    for (vector<LegalEntity*>::iterator it = b.providers_and_clients.begin(); it != b.providers_and_clients.end(); ++it)
        if ((*it)->nameUrself() == 1)
        {
            helper_provider = static_cast<Provider*>(*it);

            if (backup_index.column() == 0 && (backup_name == helper_provider->get_name() || backup_id == helper_provider->get_delivered_id()))
            {
                helper_provider->set_name(helper_str);
                break;
            }
            if (backup_index.column() == 1 && (backup_name == helper_provider->get_name() || backup_id == helper_provider->get_delivered_id()))
            {
                helper_provider->set_surname(helper_str);
                break;
            }
            if (backup_index.column() == 2 && (backup_name == helper_provider->get_name() || backup_id == helper_provider->get_delivered_id()))
            {
                helper_provider->set_address(helper_str);
                break;
            }
            if (backup_index.column() == 3 && (backup_name == helper_provider->get_name() || backup_id == helper_provider->get_delivered_id()))
            {
                helper_provider->set_email(helper_str);
                break;
            }
            if (backup_index.column() == 3 && (backup_name == helper_provider->get_name() || backup_id == helper_provider->get_delivered_id()))
            {
                helper_provider->set_number(stoll(helper_str));
                break;
            }
            if (backup_index.column() == 4 && (backup_name == helper_provider->get_name() || backup_id == helper_provider->get_delivered_id()))
            {
                helper_provider->set_delivered_id(helper_int);
                break;
            }
            if (backup_index.column() == 5 && (backup_name == helper_provider->get_name() || backup_id == helper_provider->get_delivered_id()))
            {
                helper_provider->set_delivered_quantity(helper_int);
                break;
            }
        }
    fill_table_providers(b, b.get_number_of_providers());
}

void MainWindow::on_edit_product_finished()
{
    QString get_information = (backup_index.model()->data(backup_index.model()->index(backup_index.row(),backup_index.column())).toString());
    string helper_str = get_information.toStdString();
    int helper_int = get_information.toInt();
    QString get_product_information = (backup_index.model()->data(backup_index.model()->index(backup_index.row(), 0)).toString());
    string key_product= get_information.toStdString();

    for (vector<Product*>::iterator it = b.products.begin(); it != b.products.end(); ++it)
    {
        if (backup_index.column() == 0 && (backup_name == (*it)->get_name() || backup_id == (*it)->get_id()))
        {
            (*it)->set_id(helper_int);
            break;
        }
        if (backup_index.column() == 1 && (backup_name == (*it)->get_name() || backup_id == (*it)->get_id()))
        {
            (*it)->set_name(helper_str);
            break;
        }
        if (backup_index.column() == 2 && (backup_name == (*it)->get_name() || backup_id == (*it)->get_id()))
        {
            (*it)->set_price(stod(helper_str));
            break;
        }
        if (backup_index.column() == 3 && (backup_name == (*it)->get_name() || backup_id == (*it)->get_id()))
        {
            (*it)->set_quantity(helper_int);
            break;
        }
    }
    fill_table_products(b, b.get_number_of_products());
}
