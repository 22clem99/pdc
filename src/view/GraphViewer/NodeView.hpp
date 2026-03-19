#ifndef NODE_VIEW_H
#define NODE_VIEW_H

#include <QGraphicsObject>
#include <QPainter>
#include <QMenu>
#include <QAction>
#include <QGraphicsSceneContextMenuEvent>

#include <dto/NodeData.hpp>
#include <utils/Log.hpp>

#include "PortView.hpp"

class NodeView : public QGraphicsObject
{
    Q_OBJECT

public:
    explicit NodeView(const NodeData& data, QGraphicsItem* parent = nullptr): QGraphicsObject(parent), label(QString::fromStdString(data.pretty_print)), node_id(data.node_id)
    {
        Log::debug("Add a node " + data.pretty_print + " at (" + std::to_string(data.position.x()) + ")(" + std::to_string(data.position.y()) + ") to the view ");
        setPos(data.position);
        setAcceptedMouseButtons(Qt::AllButtons);
        setFlag(QGraphicsItem::ItemIsMovable);
        setFlag(QGraphicsItem::ItemIsSelectable);
        setFlag(QGraphicsItem::ItemSendsGeometryChanges);

        // Default size of the rectangle
        const double min_size_rect = 150.0;

        // Get number of inputs and outputs
        auto nb_in = data.in_ports_data.size();
        auto nb_out = data.out_ports_data.size();

        int nb_point;

        if (nb_in > nb_out) {
            nb_point = nb_in;
        } else {
            nb_point = nb_out;
        }

        double size_rect = ((nb_point * 0.25) + 1) * min_size_rect;

        rect = QRectF(-(size_rect / 2.0), -25.0, size_rect, 50.0);

        // First print all input ports
        auto input_ports_location = get_ports_locations(nb_in, size_rect);

        for (int i = 0; i < nb_in; i++)
        {
            Log::debug("Will add the port " + data.in_ports_data[i].port_id + " to the node view");

            auto port = new PortView(data.in_ports_data[i], this);

            port->setPos(QPointF(input_ports_location[i], -25.0));

            input_ports.insert({data.in_ports_data[i].port_id, port});
        }


        // Then print all output ports
        auto output_ports_location = get_ports_locations(nb_out, size_rect);

        for (int i = 0; i < nb_out; i++)
        {
            Log::debug("Will add the port " + data.out_ports_data[i].port_id + " to the node view");

            auto port = new PortView(data.out_ports_data[i], this);

            port->setPos(QPointF(output_ports_location[i], 25.0));

            output_ports.insert({data.out_ports_data[i].port_id, port});
        }
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

    void mousePressEvent(QGraphicsSceneMouseEvent* event)
    {
        // Ignore right button click
        if (event->button() == Qt::RightButton)
        {
            event->ignore();
            return;
        }

        // Catch only left click event
        if (event->button() == Qt::LeftButton)
        {
            start_pos = pos();
            QGraphicsObject::mousePressEvent(event);
        }
    }

    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
    {
        // Ignore right button click
        if (event->button() == Qt::RightButton)
        {
            event->ignore();
            return;
        }
        // Catch only left click event
        if (event->button() == Qt::LeftButton)
        {
            QGraphicsObject::mouseReleaseEvent(event);
            if (pos() != start_pos)
            {
                emit node_moved(node_id, pos());
            }
        }
    }

    std::vector<double> get_ports_locations(int nb_port, double lengh)
    {
        std::vector<double> points;

        if (nb_port <= 0)
        {
            return points;
        }
        else if (nb_port == 1)
        {
            points.push_back(0.0);
            return points;
        }

        double d = lengh / (nb_port + 1);

        for (int i = 0; i < nb_port; i++)
        {
            points.push_back((i + 1) * d - (lengh / 2.0));
        }

        return points;
    }


    void contextMenuEvent(QGraphicsSceneContextMenuEvent* event)
    {
        QMenu menu;

        QAction* remove_node = menu.addAction("Remove Node");
        QAction* action = menu.exec(event->screenPos());

        if (action == remove_node)
        {
            Log::info("View ask to remove node " + node_id);
            emit request_remove_node(node_id);
        }

        event->accept();
    }

signals:
    void node_moved(const Id& id, const QPointF& position);
    void request_remove_node(const Id& id);

private:
    QString label;
    QRectF rect;
    QPointF start_pos;
    Id node_id;

    std::unordered_map<Id, PortView*> input_ports;
    std::unordered_map<Id, PortView*> output_ports;
};


#endif