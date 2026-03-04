/**
 * @file PDCView.hpp
 * @brief This file define the GUI of the PDC project
 */

#ifndef PDC_VIEW_H
#define PDC_VIEW_H

#include <QMainWindow>

#include "GraphViewer/GraphViewer.hpp"

/**
 * @brief This class represent the GUI of the PDC project based on Qt
 *
 */
class PDCView : public QMainWindow
{
    Q_OBJECT

public:
    explicit PDCView(QWidget* parent = nullptr);

private:
    /**
     * @brief Setup the main user ineterface
     *
     */
    void setup_user_interface();

    /**
     * @brief Setup the MenuBar
     *
     */
    void setup_MenuBar();

    GraphViewer* node_editor;
    QWidget* input_image_view;
    QWidget* output_image_view;
};

#endif