#ifndef AVLSCENE_H
#define AVLSCENE_H

#include <QGraphicsScene>

#include "AVLTree.h"

class AVLScene :
	public QGraphicsScene
{
public:
	AVLScene(QObject* parent = NULL);
	~AVLScene(void);

public:
	void setData(AVLTree::Node* pRootNode);

private:
	void layout(AVLTree::Node* pRootNode);
	void layoutChild(AVLTree::Node* pNode, const QPoint& pos, qreal interval);

private:
	const int c_minInterval;
};

#endif
