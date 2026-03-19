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

    void mousePressEvent(QGraphicsSceneMouseEvent* event)
    {
        if (event->button() == Qt::LeftButton)
        {
            // emit start_connection(this);
            event->accept();
        }
    }

    QRectF boundingRect() const override
    {
        return QRectF(-2.5, -2.5, 5.0, 5.0); // centré
    }


signals:
    // emit start_connection(this);

private:
    Id node_id;
    ShapeType shape;
};


#endif