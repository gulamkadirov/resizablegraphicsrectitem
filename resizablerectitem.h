#ifndef RESIZABLERECTITEM_H
#define RESIZABLERECTITEM_H

#include <QGraphicsRectItem>
#include <QObject>
#include <QDebug>
#include <QGraphicsSceneEvent>
#include <QCursor>
#include <QPen>

class ResizableRectItem : public QGraphicsRectItem
{
    enum State {
        Center = 0,
        Top = 0x1,
        Right = 0x2,
        Bottom = 0x4,
        Left = 0x8,
        TopLeft = Top | Left,
        TopRight = Top | Right,
        BottomLeft = Bottom | Left,
        BottomRight = Bottom | Right,
    };

    State m_current_state;
    bool isMousePressed;
    QGraphicsItem* m_child;

    void updateTop(const QPointF& pos);
    void updateBottom(const QPointF& pos);
    void updateLeft(const QPointF& pos);
    void updateRight(const QPointF& pos);
public:
    ResizableRectItem(QGraphicsItem* parent = nullptr);
    void setChildItem(QGraphicsItem* child);
    QGraphicsItem* removeChildItem();

protected:
    virtual void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
};

#endif // RESIZABLERECTITEM_H
