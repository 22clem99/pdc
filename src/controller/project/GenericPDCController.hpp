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
    QUndoStack* undo_stack;

public:
    GenericPDCController(QUndoStack* undoStack, QObject* parent = nullptr)
        : QObject(parent), undo_stack(undoStack)
    {}
};

#endif