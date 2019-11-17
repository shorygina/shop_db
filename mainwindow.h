#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QFileDialog>

#include <input_dialog.h>
#include <input_dialog_provider.h>
#include <input_dialog_product.h>
#include <base.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_add_client_clicked();
    void on_add_provider_clicked();
    void on_add_product_clicked();

    void on_read_from_file_clicked();

    void fill_table_clients(Base, int);
    void fill_table_products(Base, int);
    void fill_table_providers(Base, int);

    void on_write_into_file_clicked();

    void on_clicked_clients(const QModelIndex &index);
    void on_clicked_providers(const QModelIndex &index);
    void on_clicked_products(const QModelIndex &index);

    void on_delete_client_clicked();
    void on_delete_provider_clicked();
    void on_delete_product_clicked();

    void on_edit_client_finished();
    void on_edit_provider_finished();
    void on_edit_product_finished();

    bool is_number(const std::string& s)
    {
        return !s.empty() && std::find_if(s.begin(),
            s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
    }

private:
    Ui::MainWindow *ui;

    input_dialog *form;
    input_dialog_provider *form_provider;
    input_dialog_product *form_product;

    QStandardItemModel *model_clients; //указатели на таблицы
    QStandardItemModel *model_products;
    QStandardItemModel *model_providers;

    QModelIndex backup_index;
    Base b;
    string key, backup_name;
    int backup_id;
};

#endif // MAINWINDOW_H
