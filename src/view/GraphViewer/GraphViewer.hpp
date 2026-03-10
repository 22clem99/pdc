/**
 * @file GraphViewer.hpp
 * @brief Define the GraphViewer widget
 */

#ifndef GRAPH_VIEWER_H
#define GRAPH_VIEWER_H

#include <QGraphicsView>
#include <QMainWindow>
#include <QWidget>

#include "GraphScene.hpp"

class GraphViewer : public QGraphicsView
{
    Q_OBJECT

public:
    explicit GraphViewer(QWidget* parent);

    GraphScene * scene;
};

#endif