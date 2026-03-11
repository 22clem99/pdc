/**
 * @file NodePickerDialog.cpp
 * @brief Create a dialog window to pick a node to instanciate
 *  +-----------------------------------------+
 *  | +------------------+------------------+ |
 *  | |  Tree with node  | Pretty name : ~~ | |
 *  | |     by types     | Description : ~~ | |
 *  | |                  | ~~~~~~~~~~~~~~~~ | |
 *  | |                  | ~~~~~~~~~~~~~~~~ | |
 *  | +------------------+--+----+--------+-+ |
 *  |                       | OK | Cancel |   |
 *  +-----------------------+----+--------+---+
 */

#include "NodePickerDialog.hpp"

#include <QHBoxLayout>
#include <QDialogButtonBox>
#include <QString>


NodePickerDialog::NodePickerDialog(const std::unordered_map<Id, NodeDescriptor>& nodes, QWidget* parent) : QDialog(parent)
{
    Log::debug("Generate the node picker view");

    nodes_desc = nodes;

    setWindowTitle("Add a node");

    QHBoxLayout* h_layout = new QHBoxLayout();

    // Tree
    tree = new QTreeWidget();
    tree->setHeaderHidden(true);
    // map used to remember which categories are created
    std::unordered_map<NodeKind, QTreeWidgetItem*> categories;

    for (auto& pair : nodes)
    {
        const NodeDescriptor& desc = pair.second;
        QTreeWidgetItem* item = nullptr;

        auto it = categories.find(desc.kind);

        // if the category
        if (it != categories.end())
        {
            item = it->second;
        }
        else
        {
            // else
            item = new QTreeWidgetItem(tree);
            item->setText(0, QString::fromStdString(node_kind_to_str(desc.kind)));
            item->setExpanded(true);
            categories[desc.kind] = item;
        }

        // Add the node and link it with the category
        QTreeWidgetItem* nodeItem = new QTreeWidgetItem(item);
        nodeItem->setText(0, QString::fromStdString(desc.pretty_print));
        nodeItem->setData(0, Qt::UserRole, QString::fromStdString(pair.first));
    }

    h_layout->addWidget(tree);

    // Add Description area
    QVBoxLayout* v_layout = new QVBoxLayout();
    h_layout->addLayout(v_layout);

    pretty_print = new QLabel();
    pretty_print->setWordWrap(true);
    pretty_print->setAlignment(Qt::AlignCenter);
    auto font = pretty_print->font();
    font.setUnderline(true);
    font.setBold(true);
    pretty_print->setFont(font);
    pretty_print->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    v_layout->addWidget(pretty_print, 0);

    v_layout->addWidget(new QLabel("Description:"));
    description = new QLabel();
    description->setWordWrap(true);
    v_layout->addWidget(description, 1);

    // Add validates and cancel buttons
    QVBoxLayout* v_layout_head = new QVBoxLayout(this);
    v_layout_head->addLayout(h_layout);

    QDialogButtonBox* buttons =
        new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    v_layout_head->addWidget(buttons);

    connect(buttons, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);
    connect(tree, &QTreeWidget::itemClicked, this, &NodePickerDialog::on_tree_clicked);
}

void NodePickerDialog::on_tree_clicked(QTreeWidgetItem* item, int column)
{
    // Return if it is a category
    if (item->childCount() > 0)
        return;

    auto id = item->data(0, Qt::UserRole).toString().toStdString();

    Log::debug("View detect click on node with ID: " + id);

    pretty_print->setText(QString::fromStdString(nodes_desc[id].pretty_print));
    description->setText(QString::fromStdString(nodes_desc[id].description));
}

std::vector<Id> NodePickerDialog::get_selected_node_id(void)
{
    std::vector<Id> nodes;

    for (auto selected_val : tree->selectedItems())
    {
        if (selected_val->childCount() == 0)
        {
            nodes.push_back(selected_val->data(0, Qt::UserRole).toString().toStdString());
        }
    }

    return nodes;
}