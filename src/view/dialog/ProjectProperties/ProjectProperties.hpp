#ifndef PROJECT_PROPERTIES_H
#define PROJECT_PROPERTIES_H

#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QTextEdit>

#include <dto/ProjectData.hpp>


class ProjectProperties : public QDialog
{
    Q_OBJECT

public:
    explicit ProjectProperties(const ProjectData& data, QWidget* parent = nullptr);

    ProjectData project_data() const;

private:
    QLineEdit* project_name_edit;
    QLineEdit* img_path_edit;
    QTextEdit* description_edit;
};


#endif