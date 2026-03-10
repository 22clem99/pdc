#ifndef YES_NO_DIALOG_H
#define YES_NO_DIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QString>

class YesNoDialog : public QDialog
{
public:
    YesNoDialog(QWidget* parent, const std::string& message) : QDialog(parent)
    {
        QVBoxLayout* layout = new QVBoxLayout(this);

        layout->addWidget(new QLabel(QString::fromStdString(message)));

        QDialogButtonBox* buttons =
            new QDialogButtonBox(QDialogButtonBox::Yes | QDialogButtonBox::No);

        layout->addWidget(buttons);

        connect(buttons, &QDialogButtonBox::accepted, this, &QDialog::accept);
        connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);
    }
};

#endif