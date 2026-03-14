#ifndef NODE_VIEW_H
#define NODE_VIEW_H

#include <QGraphicsObject>
#include <QPainter>

#include <dto/NodeData.hpp>
#include <utils/Log.hpp>

class NodeView : public QGraphicsObject
{
    Q_OBJECT

public:
    explicit NodeView(const NodeData& data, QGraphicsItem* parent = nullptr): QGraphicsObject(parent), label(QString::fromStdString(data.pretty_print)), rect(-75.0, -25.0, 150.0, 50.0), node_id(data.node_id)
    {
        Log::debug("Add a node " + data.pretty_print + " at (" + std::to_string(data.position.x()) + ")(" + std::to_string(data.position.y()) + ") to the view ");
        setPos(data.position);
        setFlag(QGraphicsItem::ItemIsMovable);
        setFlag(QGraphicsItem::ItemIsSelectable);
        setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    }

    QRectF boundingRect() const override
    {
        return rect;
    }

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override
    {
        painter->setRenderHint(QPainter::Antialiasing);

        QColor fill = isSelected() ? QColor(120,120,180) : QColor(80,80,80);

        painter->setBrush(fill);
        painter->setPen(Qt::black);

        painter->drawRoundedRect(rect, 5, 5);

        painter->setPen(Qt::white);

        painter->drawText(
            rect,
            Qt::AlignCenter,
        label
        );
    }

    QVariant itemChange(GraphicsItemChange change, const QVariant& value) override
    {
        Log::debug("The node moved! need to update the model");
        if (change == ItemPositionHasChanged) {
            Log::debug("Position changed, need to be updated");
            emit node_moved(node_id, pos());
        }

        return QGraphicsObject::itemChange(change, value);
    }

signals:
    void node_moved(const Id& id, const QPointF& position);

private:
    QString label;
    QRectF rect;
    Id node_id;
};


#endif