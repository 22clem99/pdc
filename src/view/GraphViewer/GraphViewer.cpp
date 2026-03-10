/**
 * @file GraphViewer.cpp
 * @brief implement GraphViewer class
 */

#include "GraphViewer.hpp"

GraphViewer::GraphViewer(QWidget* parent) : QGraphicsView(parent)
{
    scene = new GraphScene(this);
    setScene(scene);
    setInteractive(false);
}