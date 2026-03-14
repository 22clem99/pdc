/**
 * @file PDCView.cpp
 * @brief Implement the PDCView method
 */

#include <QSplitter>
#include <QLabel>
#include <QCloseEvent>

#include "PDCView.hpp"

PDCView::PDCView(QUndoStack* undo_stack, QWidget* parent) : QMainWindow(parent)
{
    stack = undo_stack;

    setup_user_interface();

    setup_MenuBar();
}

void PDCView::setup_user_interface()
{
    auto* hsplitter = new QSplitter(Qt::Horizontal, this);
    auto* vsplitter = new QSplitter(Qt::Vertical, this);

    node_editor = new GraphViewer(this);

    input_image_view = new ImageView(this);
    output_image_view = new ImageView(this);

    vsplitter->addWidget(input_image_view);
    vsplitter->addWidget(output_image_view);

    hsplitter->addWidget(vsplitter);
    hsplitter->addWidget(node_editor);

    hsplitter->setSizes({300, 700});

    setCentralWidget(hsplitter);

    // suppose input_image_view et output_image_view sont ImageView*
    connect(input_image_view, &ImageView::zoomChanged, output_image_view, &ImageView::setScale);
    connect(output_image_view, &ImageView::zoomChanged, input_image_view, &ImageView::setScale);

    // // Scroll synchronisé
    // connect(input_image_view, &ImageView::scrolled, output_image_view, [output_image_view](int dx, int dy){
    //     output_image_view->horizontalScrollBar()->setValue(output_image_view->horizontalScrollBar()->value() + dx);
    //     output_image_view->verticalScrollBar()->setValue(output_image_view->verticalScrollBar()->value() + dy);
    // });
    // connect(output_image_view, &ImageView::scrolled, input_image_view, [input_image_view](int dx, int dy){
    //     input_image_view->horizontalScrollBar()->setValue(input_image_view->horizontalScrollBar()->value() + dx);
    //     input_image_view->verticalScrollBar()->setValue(input_image_view->verticalScrollBar()->value() + dy);
    // });
}

void PDCView::setup_MenuBar()
{
    menu_bar = new PDCMenuBar(stack, this);
}

void PDCView::closeEvent(QCloseEvent* event)
{
    Log::info("View ask to close the window");

    if(request_close_window())
    {
        event->accept();
    }
    else
    {
        event->ignore();
    }
}