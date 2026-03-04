/**
 * @file PDCView.cpp
 * @brief Implement the PDCView method
 */

#include <QSplitter>
#include <QLabel>

#include "PDCView.hpp"

PDCView::PDCView(QWidget* parent) : QMainWindow(parent)
{
    setup_user_interface();

    setup_toolbar();
}

void PDCView::setup_user_interface()
{
    auto* hsplitter = new QSplitter(Qt::Horizontal, this);
    auto* vsplitter = new QSplitter(Qt::Vertical, this);

    node_editor = new GraphViewer(this);

    input_image_view = new QLabel("Image Input");
    output_image_view = new QLabel("Image Output");

    vsplitter->addWidget(input_image_view);
    vsplitter->addWidget(output_image_view);

    hsplitter->addWidget(vsplitter);
    hsplitter->addWidget(node_editor);

    setCentralWidget(hsplitter);
}

void PDCView::setup_toolbar()
{

}
