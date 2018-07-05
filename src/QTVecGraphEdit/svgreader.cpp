#include "svgreader.h"

#include <QDomDocument>
#include <QFile>
#include <QStringList>
#include<QDebug>
#include <algorithm>
#include"myline.h"
#include"mypolygone.h"


SvgReader::SvgReader()
{

}

QList<ShapeItem *> SvgReader::getElements(const QString filename)
{

    QList<ShapeItem *> items;
    QDomDocument doc;
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly) || !doc.setContent(&file))
        return items;
    //search all objecs with tag "g" in document
    QDomNodeList gList = doc.elementsByTagName("g");

    for (int i = 0; i < gList.size(); i++) {
        QDomNode gNode = gList.item(i);  // get node from list

        QDomElement shapeElement = gNode.firstChildElement(); // get element from node



        if (shapeElement.isNull())
            continue;
        else {
            QString nodeName = shapeElement.nodeName();
            QDomElement gNodeElement = gNode.toElement();

            if (nodeName == "polyline" )
            {
                //   line = new MyLine( QLineF(shapeElement.attribute(), pt));

                qDebug() << "polyline";

            }
            else if (nodeName == "ellipse" )
            {
                qDebug() << "ellipse";
            }
            else if(nodeName == "path")
            {
                qDebug() << "path";
                qDebug() << shapeElement.attribute("d");
                std::string points = shapeElement.attribute("d").toStdString();
                QVector<QPointF> polygonesPoints = parseSVG(points);

                MyPolygone *polygone = new MyPolygone(QPolygonF(polygonesPoints) );
                ShapeItem *newShapeItem = new ShapeItem(ShapeItem::Polygone, polygone);
                items.append( newShapeItem);

            }
        }

    }
    return items;

}





QRectF  SvgReader::getSizes(const QString filename)
{
    QDomDocument doc;       // init object QDomDocument
    QFile file(filename);   // Open SVG file
    // If it is not opened, or have failed to transmit the contents in QDocDocument
    if (!file.open(QIODevice::ReadOnly) || !doc.setContent(&file))
        return QRectF(0,0,200,200); // return default size of graphics scene

    /* Pick up list of items with the tag svg.
         * If list of elements is not empty,
         * take the size of graphics scene.
         * */
    QDomNodeList list = doc.elementsByTagName("svg");
    if(list.length() > 0) {
        QDomElement svgElement = list.item(0).toElement();
        QStringList parameters = svgElement.attribute("viewBox").split(" ");
        return QRectF(parameters.at(0).toInt(),
                      parameters.at(1).toInt(),
                      parameters.at(2).toInt(),
                      parameters.at(3).toInt());
    }
    return QRectF(0,0,200,200);


}

QVector<QPointF> SvgReader::parseSVG(std::string attr)
{

    QVector<QPointF> result;

    //remove useless symbols
    attr.erase(std::remove(attr.begin(), attr.end(), 'L'), attr.end());
    attr.erase(std::remove(attr.begin(), attr.end(), 'M'), attr.end());
    attr.erase(std::remove(attr.begin(), attr.end(), 'C'), attr.end());

    // divide big string of numbers to vector numbers type string
    QVector<std::string> stringPoints = split(attr , " " );
    //convert array string to QPointF
    for (int i = 0; i < stringPoints.length(); i++)
    {
        float x, y;
        QVector<std::string> xyCoordString = split(stringPoints[i] , ",");

        x = ::atof(xyCoordString[0].c_str());
        y = ::atof(xyCoordString[1].c_str());


        result.append(QPointF(x,y));
    }

    return result;

}

QVector<std::string> SvgReader::split(const std::string str, const std::string delimiter)
{
    QVector<std::string> tokens;
       // Skip delimiters at beginning.
      std::string::size_type lastPos = str.find_first_not_of(delimiter, 0);

      // Find first non-delimiter.
      std::string::size_type pos = str.find_first_of(delimiter, lastPos);

      while (std::string::npos != pos || std::string::npos != lastPos) {
        // Found a token, add it to the vector.
        tokens.push_back(str.substr(lastPos, pos - lastPos));

        // Skip delimiters.
        lastPos = str.find_first_not_of(delimiter, pos);

        // Find next non-delimiter.
        pos = str.find_first_of(delimiter, lastPos);
      }
      return tokens;

}

