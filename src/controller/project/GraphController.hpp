#ifndef GRAPH_CONTROLLER_H
#define GRAPH_CONTROLLER_H

#include "GenericPDCController.hpp"
#include "../../view/PDCView.hpp"
#include "../../model/PDCState.hpp"


class GraphController : public GenericPDCController
{
    Q_OBJECT

public:
    GraphController(PDCState* model, PDCView* view, QUndoStack* stack);

    ~GraphController();

    void on_open_node_picker(const QPointF& scene_pos);
};


#endif