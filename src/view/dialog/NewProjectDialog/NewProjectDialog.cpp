#include "NewProjectDialog.hpp"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QFileDialog>

NewProjectDialog::NewProjectDialog(QWidget* parent) : QDialog(parent)
{
    setWindowTitle("Create Project");

    QVBoxLayout* layout = new QVBoxLayout(this);

    // Name
    QHBoxLayout* name_layout = new QHBoxLayout();
    name_layout->addWidget(new QLabel("Project path:"));

    name_edit = new QLineEdit();
    name_layout->addWidget(name_edit);

    layout->addLayout(name_layout);

    // project Path
    QHBoxLayout* path_layout = new QHBoxLayout();
    path_layout->addWidget(new QLabel("Project file:"));

    path_edit = new QLineEdit();
    path_layout->addWidget(path_edit);

    QPushButton* browse_button_path = new QPushButton("Browse");
    path_layout->addWidget(browse_button_path);

    layout->addLayout(path_layout);

    // Image path
    QHBoxLayout* path_img_Layout = new QHBoxLayout();
    path_img_Layout->addWidget(new QLabel("Image file:"));

    image_edit = new QLineEdit();
    path_img_Layout->addWidget(image_edit);

    QPushButton* browse_button_img = new QPushButton("Browse");
    path_img_Layout->addWidget(browse_button_img);

    layout->addLayout(path_img_Layout);

    // Project creation preview
    preview = new QLabel();
    layout->addWidget(preview);

    connect(browse_button_path, &QPushButton::clicked, this, [this]()
    {
        QString file = QFileDialog::getExistingDirectory(
            this,
            "Choose a project folder",
            "",
            QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
        );

        if (!file.isEmpty())
            path_edit->setText(file);
    });

    connect(browse_button_img, &QPushButton::clicked, this, [this]()
    {
        QString img = QFileDialog::getOpenFileName(
            this,
            "Choose image file",
            "",
            "Images (*.png *.jpg *.jpeg *.jpe *.jp2 *.tif *.tiff *.bmp *.dib *.webp *.pbm, *.pgm, *.ppm *.pxm, *.pnm);;All files (*.*)"
        );

        if (!img.isEmpty())
            image_edit->setText(img);
    });

    auto update_preview = [this]()
    {
        preview->setText(path_edit->text() + std::filesystem::path::preferred_separator + name_edit->text() + ".pdc");
    };

    connect(path_edit, &QLineEdit::textChanged, this, update_preview);
    connect(name_edit, &QLineEdit::textChanged, this, update_preview);


    // OK Cancel
    QDialogButtonBox* buttons =
        new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    layout->addWidget(buttons);

    connect(buttons, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

QString NewProjectDialog::project_name() const
{
    return name_edit->text();
}

QString NewProjectDialog::project_path() const
{
    return path_edit->text();
}

QString NewProjectDialog::image_path() const
{
    return image_edit->text();
}