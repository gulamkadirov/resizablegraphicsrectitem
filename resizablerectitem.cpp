#include "resizablerectitem.h"

void ResizableRectItem::updateTop(const QPointF &pos)
{
    QRectF rect = this->rect();
    rect.setHeight(rect.height() - pos.y());
    this->setRect(rect);
    this->setY(this->y() + pos.y());
}

void ResizableRectItem::updateBottom(const QPointF &pos)
{
    QRectF rect = this->rect();
    rect.setHeight(pos.y());
    this->setRect(rect);
}

void ResizableRectItem::updateLeft(const QPointF &pos)
{
    QRectF rect = this->rect();
    rect.setWidth(rect.width() - pos.x());
    this->setRect(rect);
    this->setX(this->x() + pos.x());
}

void ResizableRectItem::updateRight(const QPointF &pos)
{
    QRectF rect = this->rect();
    rect.setWidth(pos.x());
    this->setRect(rect);
}

ResizableRectItem::ResizableRectItem(QGraphicsItem *parent) :
    QGraphicsRectItem(parent)
{
    this->setFlag(QGraphicsItem::ItemIsMovable);
    QPen pen(Qt::red);
    pen.setWidth(10);
    this->setPen(pen);
    m_child = nullptr;
}

void ResizableRectItem::setChildItem(QGraphicsItem *child)
{
    if(child == nullptr)
        return;

    m_child = child;
    child->setParentItem(this);
    this->setRect(m_child->boundingRect());
}

QGraphicsItem *ResizableRectItem::removeChildItem()
{
    QGraphicsItem* child = m_child;
    m_child = nullptr;
    return child;
}

void ResizableRectItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{

    int height = this->rect().height(),
        width =  this->rect().width();
    QPointF pos = event->pos();

    if(pos.y() < 10 && pos.x() < 10) {
        this->setCursor(QCursor(Qt::CursorShape::SizeFDiagCursor));
        m_current_state = State::TopLeft;
    } else if(pos.y() < 10 && pos.x() > (width-10)) {
        this->setCursor(QCursor(Qt::CursorShape::SizeBDiagCursor));
        m_current_state = State::TopRight;
    } else if(pos.y() > (height-10) && pos.x() < 10) {
        this->setCursor(QCursor(Qt::CursorShape::SizeBDiagCursor));
        m_current_state = BottomLeft;
    } else if(pos.y() > (height-10) && pos.x() > (width-10)) {
        this->setCursor(QCursor(Qt::CursorShape::SizeFDiagCursor));
        m_current_state = State::BottomRight;
    } else if(pos.x() < 10 || pos.x() > (width-10)) {
        this->setCursor(QCursor(Qt::CursorShape::SizeHorCursor));
        if(pos.x() < 10)
            m_current_state = State::Left;
        else
            m_current_state = State::Right;
    } else if(pos.y() < 10 || pos.y() > (height-10)) {
        this->setCursor(QCursor(Qt::CursorShape::SizeVerCursor));
        if(pos.y() < 10)
            m_current_state = State::Top;
        else
            m_current_state = State::Bottom;
    } else {
        this->setCursor(QCursor(Qt::CursorShape::ArrowCursor));
        m_current_state = State::Center;
    }
}

void ResizableRectItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    isMousePressed = true;
    if(m_current_state == State::Center)
        this->setCursor(QCursor(Qt::CursorShape::SizeAllCursor));

    QGraphicsItem::mousePressEvent(event);
}

void ResizableRectItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    isMousePressed = false;
    if(m_current_state == State::Center)
        this->setCursor(QCursor(Qt::CursorShape::ArrowCursor));

    QGraphicsItem::mouseReleaseEvent(event);
}

void ResizableRectItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(!isMousePressed)
        return;

    QRectF oldRect = this->rect();
    switch(m_current_state) {
    case State::Center: {
        QGraphicsRectItem::mouseMoveEvent(event);
        return;
    };
    case State::Top: {
        this->updateTop(event->pos());
        break;
    };
    case State::Bottom: {
        this->updateBottom(event->pos());
        break;
    };
    case State::Left: {
        this->updateLeft(event->pos());
        break;
    }
    case State::Right: {
        this->updateRight(event->pos());
        break;
    }
    case State::TopLeft: {
        this->updateTop(event->pos());
        this->updateLeft(event->pos());
        break;
    }
    case State::TopRight: {
        this->updateTop(event->pos());
        this->updateRight(event->pos());
        break;
    }
    case State::BottomLeft: {
        this->updateBottom(event->pos());
        this->updateLeft(event->pos());
        break;
    }
    case State::BottomRight: {
        this->updateBottom(event->pos());
        this->updateRight(event->pos());
        break;
    }
    }

    if(m_child != nullptr) {
        QTransform t = m_child->transform();
        t.scale(this->rect().width() / oldRect.width(),
                this->rect().height() / oldRect.height());
        m_child->setTransform(t);
    }
}
