#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QFileDialog>
#include <QString>

#include "ProjectProperties.hpp"

ProjectProperties::ProjectProperties(const ProjectData& data, QWidget* parent) : QDialog(parent)
{
    setWindowTitle("Edit project properties");

    QVBoxLayout* layout = new QVBoxLayout(this);

    /* Change Project name
     * +------------------+-------------------------------------+
     * | Project name:    |  *Project name*                     |
     * +------------------+-------------------------------------+
     */

    QHBoxLayout* project_layout = new QHBoxLayout();
    project_layout->addWidget(new QLabel("Project name:"));

    project_name_edit = new QLineEdit();
    project_name_edit->setText(QString::fromStdString(data.name));
    project_layout->addWidget(project_name_edit);

    layout->addLayout(project_layout);

    /* Change image with a new image from a path
     * +------------------+----------------------------+--------+
     * | New image file:  |  *typing area*             | Browse |
     * +------------------+----------------------------+- ------+
     */

    QHBoxLayout* img_path_layout = new QHBoxLayout();
    img_path_layout->addWidget(new QLabel("New image file:"));

    img_path_edit = new QLineEdit();
    img_path_layout->addWidget(img_path_edit);

    QPushButton* browse_button_path = new QPushButton("Browse");
    img_path_layout->addWidget(browse_button_path);

    layout->addLayout(img_path_layout);

    /* Change description
     * +--------------------------------------------------------+
     * | Description                                            |
     * +--------------------------------------------------------+
     * | *description*                                          |
     * +--------------------------------------------------------+
     */
    layout->addWidget(new QLabel("Description:"));

    description_edit = new QTextEdit();
    if (data.description)
        description_edit->setText(QString::fromStdString(data.description.value()));

    layout->addWidget(description_edit);

    connect(browse_button_path, &QPushButton::clicked, this, [this]()
    {
        QString img = QFileDialog::getOpenFileName(
            this,
            "Choose image file",
            "",
            "Images (*.png *.jpg *.jpeg *.jpe *.jp2 *.tif *.tiff *.bmp *.dib *.webp *.pbm, *.pgm, *.ppm *.pxm, *.pnm);;All files (*.*)"
        );

        if (!img.isEmpty())
            img_path_edit->setText(img);
    });


    // OK Cancel
    QDialogButtonBox* buttons =
        new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    layout->addWidget(buttons);

    connect(buttons, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);
}


ProjectData ProjectProperties::project_data(void) const
{
    return ProjectData(project_name_edit->text().toStdString(),
                       img_path_edit->text().toStdString(),
                       description_edit->toPlainText().toStdString());
}