#ifndef OPEN_PROJECT_DIALOG_H
#define OPEN_PROJECT_DIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QLabel>

class OpenProjectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OpenProjectDialog(QWidget* parent = nullptr);

    QString project_path() const;

private:
    QLineEdit* path_edit;
};


#endif