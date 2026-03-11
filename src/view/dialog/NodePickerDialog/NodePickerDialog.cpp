/**
 * @file NodePickerDialog.cpp
 * @brief Create a dialog window to pick a node to instanciate
 *
 *  +------------------+------------------+
 *  |  Tree with node  | Pretty name : ~~ |
 *  |     by types     | Description : ~~ |
 *  |                  | ~~~~~~~~~~~~~~~~ |
 *  |                  | ~~~~~~~~~~~~~~~~ |
 *  +------------------+------------------+
 */

#include "NodePickerDialog.hpp"

#include <QHBoxLayout>
#include <QTreeWidget>
#include <QDialogButtonBox>
#include <QString>


NodePickerDialog::NodePickerDialog(const std::unordered_map<Id, NodeDescriptor>& nodes, QWidget* parent) : QDialog(parent)
{
    Log::debug("Generate the node picker view");
    setWindowTitle("Add a node");

    QHBoxLayout* layout = new QHBoxLayout(this);

    // Tree
    QTreeWidget* tree = new QTreeWidget();
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

        // créer le node comme enfant de la catégorie
        QTreeWidgetItem* nodeItem = new QTreeWidgetItem(item);
        nodeItem->setText(0, QString::fromStdString(desc.pretty_print));
    }

    layout->addWidget(tree);

    // OK Cancel
    QDialogButtonBox* buttons =
        new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    layout->addWidget(buttons);

    connect(buttons, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);

}