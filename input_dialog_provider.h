#ifndef INPUT_DIALOG_PROVIDER_H
#define INPUT_DIALOG_PROVIDER_H

#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include <QValidator>

class input_dialog_provider : public QDialog
{
    Q_OBJECT
public:
    input_dialog_provider(QWidget *parent = nullptr);
    ~input_dialog_provider();

    QLineEdit *name_le, *surname_le, *address_le, *email_le, *number_le, *provided_id_le, *provided_quantity_le;

      private slots:
        void on_ok_button_clicked();
        void on_changed();

      private:
        QLabel *name_label, *surname_label, *address_label, *email_label, *number_label, *provided_id_label, *provided_quantity_label;
        QPushButton *ok;
        QGridLayout *manager;
        QIntValidator i_validator;
};

#endif // INPUT_DIALOG_PROVIDER_H
