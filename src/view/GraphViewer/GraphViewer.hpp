/**
 * @file GraphViewer.hpp
 * @brief Define the GraphViewer widget
 */

#ifndef GRAPH_VIEWER_H
#define GRAPH_VIEWER_H

#include <QWidget>

class GraphViewer : public QWidget
{
    Q_OBJECT

public:
    explicit GraphViewer(QWidget* parent = nullptr);
};

#endif