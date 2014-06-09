#ifndef NUMITEM_H
#define NUMITEM_H

#include <QGraphicsEllipseItem>

#include <QColor>

class QGraphicsTextItem;

class NumItem :
	public QGraphicsEllipseItem
{
public:
	NumItem(int num, QGraphicsItem* parent = NULL);
	~NumItem(void);

public:
	void SetBkColor(const QColor& color);

	int number()const;

private:
	QGraphicsTextItem* m_pTextItem;
};

#endif
