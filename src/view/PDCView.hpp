/**
 * @file PDCView.hpp
 * @brief This file define the GUI of the PDC project
 */

#ifndef PDC_VIEW_H
#define PDC_VIEW_H

#include <QMainWindow>

#include "GraphViewer/GraphViewer.hpp"
#include "PDCMenuBar/PDCMenuBar.hpp"
#include "ImageView.hpp"

/**
 * @brief This class represent the GUI of the PDC project based on Qt
 *
 */
class PDCView : public QMainWindow
{
    Q_OBJECT

public:
    explicit PDCView(QWidget* parent = nullptr);

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
    ImageView* input_image_view;
    ImageView* output_image_view;
    PDCMenuBar* menu_bar;
};

#endif