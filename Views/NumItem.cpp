#include "NumItem.h"

#include <QPen>

NumItem::NumItem(int num, QGraphicsItem* parent /*= NULL*/)
	:QGraphicsEllipseItem(parent)
{
	m_pTextItem = new QGraphicsTextItem(QString::number(num), this);

	QRectF textRect = m_pTextItem->boundingRect();
	
	if (textRect.width() > textRect.height())
		textRect.setHeight(textRect.width());
	else 
		textRect.setWidth(textRect.height());

	this->setRect(textRect);

	QPen pen = this->pen();
	pen.setColor(Qt::green);
	pen.setWidth(2);
	this->setPen(pen);
}


NumItem::~NumItem(void)
{
}

void NumItem::SetBkColor(const QColor& color)
{
	QPen pen = this->pen();
	pen.setBrush(QBrush(color));
	this->setPen(pen);
}

int NumItem::number()const
{
	if (NULL == m_pTextItem)
		return 0;

	return m_pTextItem->toPlainText().toInt();
}