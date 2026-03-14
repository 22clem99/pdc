#ifndef NODE_NOTIFIER_H
#define NODE_NOTIFIER_H

#include <QObject>

#include <utils/Types.hpp>

class NodeNotifier : public QObject
{
    Q_OBJECT
public:
    NodeNotifier(QObject* parent = nullptr) : QObject(parent) {}
signals:
    void node_position_changed(const Id& id, const QPointF& pos);
};


#endif
