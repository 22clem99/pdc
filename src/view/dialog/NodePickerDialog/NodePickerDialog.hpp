#ifndef NODE_PICKER_DIALOG_H
#define NODE_PICKER_DIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QTreeWidget>


#include "../../../model/project/node/NodeProperty.hpp"
#include <utils/Log.hpp>

class NodePickerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NodePickerDialog(const std::unordered_map<Id, NodeDescriptor>& nodes, QWidget* parent = nullptr);

    void on_tree_clicked(QTreeWidgetItem* item, int column);

    std::vector<std::string> get_selected_node_id(void);

private:
    std::unordered_map<Id, NodeDescriptor> nodes_desc;

    QLabel* pretty_print;
    QLabel* description;

    QTreeWidget* tree;
};


#endif