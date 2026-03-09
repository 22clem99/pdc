#ifndef IMAGE_VIEW_H
#define IMAGE_VIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QLabel>
#include <QWheelEvent>

#include <utils/Qt/ImageUtils.hpp>
#include <utils/Types.hpp>
#include <utils/Log.hpp>

class ImageView : public QGraphicsView
{
    Q_OBJECT
public:
    ImageView(QWidget* parent = nullptr) : QGraphicsView(parent)
    {
        scene = new QGraphicsScene(this);
        this->setScene(scene);
        this->setAlignment(Qt::AlignCenter);
        this->setDragMode(QGraphicsView::ScrollHandDrag);
        this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        this->setResizeAnchor(QGraphicsView::AnchorViewCenter);
    }

    double getScale() const { return transform().m11(); } // facteur de zoom

    void setScale(double s) {
        QTransform t;
        t.scale(s, s);
        setTransform(t);
    }

signals:
    void zoomChanged(double scale);
    void scrolled(int dx, int dy);

public slots:
    void update_image(const Image& img)
    {
        Log::debug("Update input view ask");
        QImage qimg = img.to_QImage();

        Log::debug("Image size: {" + std::to_string(qimg.width()) + "x" + std::to_string(qimg.height()) + "}");

        if (qimg.isNull()) {
            Log::error("QImage is null");
            return;
        }

        scene->clear();
        pixmap_item = scene->addPixmap(QPixmap::fromImage(qimg));
        scene->setSceneRect(pixmap_item->boundingRect());
        fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
    }

protected:
    void wheelEvent(QWheelEvent* event) override {
        double factor = (event->angleDelta().y() > 0) ? 1.1 : 0.9;
        scale(factor, factor);
        // emit zoomChanged(transform().m11());
    }

    void scrollContentsBy(int dx, int dy) override {
        QGraphicsView::scrollContentsBy(dx, dy);
        // emit scrolled(dx, dy);
    }

private:
    QGraphicsScene* scene;
    QGraphicsPixmapItem* pixmap_item = nullptr;
};


#endif