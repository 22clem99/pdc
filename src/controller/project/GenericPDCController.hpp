#ifndef GENERIC_PDC_CONTROLLER_H
#define GENERIC_PDC_CONTROLLER_H

#include <QObject>
#include <QUndoStack>
#include "../../view/PDCView.hpp"
#include "../../model/PDCState.hpp"

class GenericPDCController : public QObject
{
    Q_OBJECT

protected:
    PDCState* model;
    PDCView* view;
    QUndoStack* undo_stack;

public:
    GenericPDCController(PDCState* model, PDCView* view, QUndoStack* undoStack, QObject* parent = nullptr)
        : QObject(parent), model(model), view(view), undo_stack(undoStack)
    {}
};

#endif