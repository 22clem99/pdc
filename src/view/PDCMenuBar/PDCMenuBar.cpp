#include <QMenu>

#include "PDCMenuBar.hpp"


PDCMenuBar::PDCMenuBar(QMainWindow* window): QObject(window)
{
    QMenu* projectMenu = window->menuBar()->addMenu("Project");

    QAction* new_action = projectMenu->addAction("New");
    QAction* open_action = projectMenu->addAction("Open");
    QAction* save_action = projectMenu->addAction("Save");
    QAction* export_action = projectMenu->addAction("Export");

    connect(new_action, &QAction::triggered, this, &PDCMenuBar::new_requested);
    connect(open_action, &QAction::triggered, this, &PDCMenuBar::open_requested);
    connect(save_action, &QAction::triggered, this, &PDCMenuBar::save_requested);
    connect(export_action, &QAction::triggered, this, &PDCMenuBar::export_requested);
}