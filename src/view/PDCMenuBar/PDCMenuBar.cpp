#include <QMenu>

#include "PDCMenuBar.hpp"


PDCMenuBar::PDCMenuBar(QUndoStack* undo_stack, QMainWindow* window): QObject(window)
{
    stack = undo_stack;

    QMenu* project_menu = window->menuBar()->addMenu("Project");

    QAction* new_action = project_menu->addAction("New");
    QAction* open_action = project_menu->addAction("Open");
    QAction* save_action = project_menu->addAction("Save");
    QAction* export_action = project_menu->addAction("Export");
    QAction* close_action = project_menu->addAction("Close");

    // Add undo/redo buttons
    QAction *undo_action = stack->createUndoAction(this);
    QAction *redo_action = stack->createRedoAction(this);

    undo_action->setIcon(QIcon::fromTheme("edit-undo"));
    redo_action->setIcon(QIcon::fromTheme("edit-redo"));

    undo_action->setShortcut(QKeySequence::Undo);
    redo_action->setShortcut(QKeySequence::Redo);

    window->menuBar()->addAction(undo_action);
    window->menuBar()->addAction(redo_action);

    connect(new_action, &QAction::triggered, this, &PDCMenuBar::new_requested);
    connect(open_action, &QAction::triggered, this, &PDCMenuBar::open_requested);
    connect(save_action, &QAction::triggered, this, &PDCMenuBar::save_requested);
    connect(export_action, &QAction::triggered, this, &PDCMenuBar::export_requested);
    connect(close_action, &QAction::triggered, this, &PDCMenuBar::close_requested);
}