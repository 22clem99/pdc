#ifndef NEW_PROJECT_DIALOG_H
#define NEW_PROJECT_DIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QLabel>

class NewProjectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewProjectDialog(QWidget* parent = nullptr);

    QString project_name() const;
    QString project_path() const;
    QString image_path() const;

private:
    QLineEdit* name_edit;
    QLineEdit* path_edit;
    QLineEdit* image_edit;
    QLabel* preview;
};


#endif