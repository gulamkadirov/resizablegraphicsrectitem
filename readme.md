<h3>Resizable Graphics Item</h3>
A simple graphics item can be resized with mouse. It's just a container. Here's an example how to use:

```C++
ResizableRectItem* item = new ResizableRectItem;
item->setAcceptHoverEvents(true);
m_scene->addItem(item);
QGraphicsEllipseItem* ellipse = new QGraphicsEllipseItem(0, 0, 300, 300);
item->setChildItem(ellipse);
```
ResizableRectItem just a subclass of QGraphicsRectItem, and it adds 2 methods:
```C++
void setChildItem(QGraphicsItem* child);
```
This method sets a child to our container, and the container resizes to it's child's geometry.
```C++
QGraphicsItem* removeChildItem();
```
This method removes(not deletes) child item, and returns a pointer to it.

**Note:** When you resize with mouse, it's child's size is not changed, instead transformation performed on it.
**Note:** This is the 1st version, so it may have bugs :)
