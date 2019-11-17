#ifndef INPUT_DIALOG_PRODUCT_H
#define INPUT_DIALOG_PRODUCT_H

#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include <QValidator>

class input_dialog_product : public QDialog
{
    Q_OBJECT
public:
    input_dialog_product(QWidget *parent = nullptr);
    ~input_dialog_product();
    QLineEdit *id_le, *name_le, *price_le, *quantity_le;

  private slots:
    void on_ok_button_clicked();
    void on_changed();

  private:
    QLabel *id_label, *name_label, *price_label, *quantity_label;
    QPushButton *ok;
    QGridLayout *manager;
    QDoubleValidator d_validator;
    QIntValidator i_validator;
};

#endif // INPUT_DIALOG_PRODUCT_H
