#include "OpenProjectDialog.hpp"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QFileDialog>

OpenProjectDialog::OpenProjectDialog(QWidget* parent) : QDialog(parent)
{
    setWindowTitle("Open Project");

    QVBoxLayout* layout = new QVBoxLayout(this);

    // project Path
    QHBoxLayout* path_layout = new QHBoxLayout();
    path_layout->addWidget(new QLabel("Project file:"));

    path_edit = new QLineEdit();
    path_layout->addWidget(path_edit);

    QPushButton* browse_button_path = new QPushButton("Browse");
    path_layout->addWidget(browse_button_path);

    layout->addLayout(path_layout);

    connect(browse_button_path, &QPushButton::clicked, this, [this]()
    {
        QString file = QFileDialog::getOpenFileName(
            this,
            "Choose a project file",
            "",
            "PDC project (*.pdc)"
        );

        if (!file.isEmpty())
            path_edit->setText(file);
    });

    // OK Cancel
    QDialogButtonBox* buttons =
        new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    layout->addWidget(buttons);

    connect(buttons, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

QString OpenProjectDialog::project_path() const
{
    return path_edit->text();
}
