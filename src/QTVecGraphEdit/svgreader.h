#ifndef SVGREADER_H
#define SVGREADER_H

#include"shapeitem.h"
#include <QList>
#include <QGraphicsItem>


class SvgReader
{
public:
    SvgReader();
    static QList<ShapeItem *> getElements(const QString filename);
    static QRectF  getSizes(const QString filename);

private:
  static QVector<QPointF> parseSVG(std::string attr);
  static QVector<std::string> split(std::string str, std::string delimiter);


};

#endif // SVGREADER_H
