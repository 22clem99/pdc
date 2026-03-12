#ifndef MenuBar_H
#define MenuBar_H

#include <QMenuBar>
#include <QMainWindow>
#include <QUndoStack>

class PDCMenuBar : public QObject
{
    Q_OBJECT

public:
    explicit PDCMenuBar(QUndoStack* undo_stack, QMainWindow* window);

signals:
    void new_requested();
    void open_requested();
    void save_requested();
    void export_requested();
    void close_requested();

private:
    QUndoStack* stack;
};



#endif