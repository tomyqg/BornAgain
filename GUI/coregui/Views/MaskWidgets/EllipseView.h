#ifndef ELLIPSEVIEW_H
#define ELLIPSEVIEW_H

#include "IView.h"

class EllipseItem;
class QGraphicsSceneMouseEvent;
class QPainter;

class EllipseView :public IView
{
Q_OBJECT

public:
    //! describes corner
    enum Corner { NONE, TOPLEFT, TOPRIGHT, BOTTOMLEFT, BOTTOMRIGHT };
    enum Mode { ROTATION, RESIZE };
    enum {Type = UserType + 1};

    //! create Rectangle
    //! @param posX x position in scene
    //! @param posY y position in scene
    //! @param width of rectangle
    //! @param heigth of rectangle
    EllipseView();

    //! bounding box of rectangle
    QRectF boundingRect() const;

    //! check if resize rules are correct
    //! @param event mouse event to check if resizes correct
    void checkResizeRules(QGraphicsSceneMouseEvent *event);

    //! calculates resized rectangle
    //! @param event mouse event to set new coordinates
    void calculateResize(QGraphicsSceneMouseEvent *event);

    //! calculates rotated rectangle
    //! @param event mouse event to set new coordinates
    //! @return degree of rotation
    qreal getRotationAngle(QGraphicsSceneMouseEvent *event);

    int type() const {return Type;}
    void setInclude();
    void setExclude();
    QRectF getTopLeftCorner();
    QRectF getTopRightCorner();
    QRectF getBottomLeftCorner();
    QRectF getBottomRightCorner();
    ParameterizedItem *getParameterizedItem();
    void setParameterizedItem(ParameterizedItem *item);
public slots:
    void onChangedX();
    void onChangedY();
    void onPropertyChange(const QString &propertyName);
protected:
    //! paintEvent paints Rectangle and corners
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);

private:
    ParameterizedItem *m_item;
    Corner m_corner;                        //!< enum with all corners
    Mode m_mode;
    bool m_block_mode;
    bool m_resizeMode;
    bool m_rotationMode;
    void updateRotationArrows();
    void initializeArrow();
    void setSelectedCorner(QPointF currentMousePosition);
};
#endif
