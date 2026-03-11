#ifndef NODE_PICKER_DIALOG_H
#define NODE_PICKER_DIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QLabel>


#include "../../../model/project/node/NodeProperty.hpp"
#include <utils/Log.hpp>

class NodePickerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NodePickerDialog(const std::unordered_map<Id, NodeDescriptor>& nodes, QWidget* parent = nullptr);

private:
};


#endif