#include "DesignerHelper.h"
#include <QPainter>
#include <QtGlobal>
#include <cmath>
#include <iostream>

int DesignerHelper::m_default_layer_height = 30;
int DesignerHelper::m_default_layer_width = 200;


QGradient DesignerHelper::getLayerGradient(const QColor &color, const QRect &rect)
{
    QColor c = color;
    c.setAlpha(160);
    QLinearGradient result(rect.topLeft(), rect.bottomRight());
    result.setColorAt(0, c.dark(150));
    result.setColorAt(0.5, c.light(200));
    result.setColorAt(1, c.dark(150));
    return result;
}


QGradient DesignerHelper::getDecorationGradient(const QColor &color, const QRect &rect)
{
    QColor c = color;
    //c.setAlpha(200);
    QLinearGradient result(rect.x()+rect.width()/2,
                           rect.y(),
                           rect.x()+rect.width()/2,
                           rect.y()+rect.height()
                           );
    result.setColorAt(0, c);
    result.setColorAt(0.5, c.lighter(150));
    result.setColorAt(1, c);
    return result;
}


QGradient DesignerHelper::getMaterialGradient(const QColor &color, const QRect &rect)
{
    QRadialGradient result(-5.0, -5.0, rect.width()/2.);
    result.setCenter(5, 5);
    result.setFocalPoint(5, 5);
    result.setColorAt(1, color.darker(150));
    result.setColorAt(0, color.lighter(150));
    return result;
}


QPixmap DesignerHelper::getSceneBackground()
{
    const int size= 10;
    QPixmap result(size, size);
    result.fill(QColor(250, 250, 250));
    QPainter tilePainter(&result);
    QColor color(220, 220, 220);
    tilePainter.fillRect(0.0, 0.0, 2, 2, color);
    tilePainter.end();

    return result;
}


QPixmap DesignerHelper::getPixmapLayer() {
    QRect rect(0,0, DesignerHelper::getDefaultLayerWidth(), DesignerHelper::getDefaultLayerHeight());
    QPixmap pixmap(rect.width()+1, rect.height()+1);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setPen(Qt::black);
    painter.setBrush(DesignerHelper::getLayerGradient(Qt::lightGray, rect));
    painter.drawRect(rect);
    return pixmap;
}


QPixmap DesignerHelper::getPixmapMultiLayer() {
    QRect rect(0,0, DesignerHelper::getDefaultMultiLayerWidth(), DesignerHelper::getDefaultLayerHeight());
    QPixmap pixmap(rect.width()+1, rect.height()+1);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setPen(Qt::black);
    painter.setBrush(DesignerHelper::getLayerGradient(Qt::lightGray, rect));
    painter.drawRect(rect);
    painter.setPen(Qt::DashLine);
    painter.drawLine(0, DesignerHelper::getDefaultLayerHeight()*0.3, DesignerHelper::getDefaultMultiLayerWidth(), DesignerHelper::getDefaultLayerHeight()*0.3);
    painter.drawLine(0, DesignerHelper::getDefaultLayerHeight()*0.6, DesignerHelper::getDefaultMultiLayerWidth(), DesignerHelper::getDefaultLayerHeight()*0.6);
    return pixmap;
}


QPixmap DesignerHelper::getPixmapParticleDecoration()
{
    QRect rect(0,0, DesignerHelper::getDefaultDecorationWidth(), DesignerHelper::getDefaultDecorationHeight());
    QPixmap pixmap(rect.width()+1, rect.height()+1);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setPen(Qt::black);
    painter.setBrush(DesignerHelper::getDecorationGradient(Qt::lightGray, rect));
    painter.drawRoundedRect(rect, 3, 3);
    return pixmap;
}


QPixmap DesignerHelper::getPixmapInterferenceFunction()
{
    QRect rect(0,0, DesignerHelper::getDefaultInterferenceFunctionWidth(), DesignerHelper::getDefaultInterferenceFunctionHeight());
    QPixmap pixmap(rect.width()+1, rect.height()+1);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setPen(Qt::black);
    painter.setBrush(DesignerHelper::getDecorationGradient(Qt::lightGray, rect));
    painter.drawRoundedRect(rect, 3, 3);
    return pixmap;
}


QPixmap DesignerHelper::getPixmapFormFactor()
{
    QRect rect(0,0, DesignerHelper::getDefaultFormFactorWidth(), DesignerHelper::getDefaultFormFactorHeight());
    QPixmap pixmap(rect.width()+1, rect.height()+1);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setPen(Qt::black);
    painter.setBrush(DesignerHelper::getDecorationGradient(Qt::lightGray, rect));
    painter.drawRoundedRect(rect, 5, 5);
    return pixmap;
}


QPixmap DesignerHelper::getPixmapDefault() {
    return QPixmap(":/images/mode_exp.png");
}


// non-linear convertion of layer's thickness in nanometers to screen size to have reasonable graphics representation
int DesignerHelper::nanometerToScreen(double nanometer)
{
    const int ymin(m_default_layer_height);
    const int ymax(500);
    int result(ymin);
    if(nanometer > 0) result = qBound(ymin, ymin + (int)std::pow(nanometer, 0.9), ymax);
    return result;
}
