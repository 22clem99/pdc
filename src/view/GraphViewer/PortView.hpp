#ifndef PORT_VIEW_H
#define PORT_VIEW_H

#include <QGraphicsObject>
#include <QPainter>

#include <dto/NodeData.hpp>
#include <utils/Log.hpp>

enum class ShapeType
{
    Circle,
    Square,
    Triangle
};

class PortView: public QGraphicsObject
{
    Q_OBJECT

public:
    explicit PortView(const PortData& data, QGraphicsItem* parent = nullptr): QGraphicsObject(parent)
    {
        port_id = data.port_id;

        switch (data.type)
        {
        case PortTypes::Image:
            shape = ShapeType::Circle;
            break;
        case PortTypes::Int:
            shape = ShapeType::Square;
            break;
        case PortTypes::Float:
            shape = ShapeType::Triangle;
            break;
        case PortTypes::Error:
            Log::error("Unable to display the port " + data.port_id + " as the Type is unknow");
            shape = ShapeType::Square;
            return;

        default:
            break;
        }
    }

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override
    {
        painter->setRenderHint(QPainter::Antialiasing);

        QColor fill = isSelected() ? QColor(120,120,180) : QColor(80,80,80);

        painter->setBrush(fill);
        painter->setPen(Qt::red);
        switch (shape)
        {
        case ShapeType::Circle:
            painter->drawEllipse(boundingRect());
            break;

        case ShapeType::Square:
            painter->drawRect(boundingRect());
            break;

        case ShapeType::Triangle:
            {
                QPolygonF triangle;
                triangle << QPointF(0, -2.5)
                        << QPointF(2.5, 2.5)
                        << QPointF(-2.5, 2.5);

                painter->drawPolygon(triangle);
                break;
            }
        }
    }

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override
    {
        if (event->button() == Qt::LeftButton)
        {
            emit start_connection(port_id);
            event->accept();
        }
    }

    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override
    {
        if (event->button() == Qt::LeftButton)
        {
            Log::debug("Get a release event on " + port_id);
            emit stop_connection(port_id);
            event->accept();
        }
    }

    QRectF boundingRect() const override
    {
        return QRectF(-2.5, -2.5, 5.0, 5.0);
    }

signals:
    void start_connection(const Id& id);
    void stop_connection(const Id& id);

private:
    Id port_id;
    ShapeType shape;
};


#endif