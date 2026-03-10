#ifndef MenuBar_H
#define MenuBar_H

#include <QMenuBar>
#include <QMainWindow>

class PDCMenuBar : public QObject
{
    Q_OBJECT

public:
    explicit PDCMenuBar(QMainWindow* window);

signals:
    void new_requested();
    void open_requested();
    void save_requested();
    void export_requested();
    void close_requested();
};



#endif