#include "AVLScene.h"

#include "NumItem.h"

AVLScene::AVLScene(QObject* parent /*= NULL*/)
	:QGraphicsScene(parent)
	,c_minInterval(100)
{
}


AVLScene::~AVLScene(void)
{
}

void AVLScene::setData(AVLTree::Node* pRootNode)
{
	QList<QGraphicsItem*> itemList = this->items();
	for (int i=0; i<itemList.size(); i++) {
		itemList[i]->setParentItem(NULL);
		delete itemList[i];
	}

	layout(pRootNode);
}

void AVLScene::layout(AVLTree::Node* pRootNode)
{
	if (NULL == pRootNode)
		return;

	int maxDeep = AVLTree::Node::maxDeep(pRootNode);
	long maxLeafCount = 1;
	for (long i=1; i<maxDeep; i++)
		maxLeafCount *= 2;

	QPoint rootPos(maxLeafCount/2 * c_minInterval, 0);

	NumItem* pRootItem = new NumItem(pRootNode->st_Value);
	this->addItem(pRootItem);
	pRootItem->setPos(rootPos);

	int interval = maxLeafCount/2 * c_minInterval;

	layoutChild(pRootNode->st_pLeftChild, QPoint(rootPos.x() - interval/2, c_minInterval), interval);
	layoutChild(pRootNode->st_pRightChild, QPoint(rootPos.x() + interval/2, c_minInterval), interval);
}

void AVLScene::layoutChild(AVLTree::Node* pNode, const QPoint& pos, qreal interval)
{
	if (NULL == pNode)
		return;

	NumItem* pItem = new NumItem(pNode->st_Value);
	this->addItem(pItem);
	pItem->setPos(pos);

	qreal childInterval = interval / 2;


	layoutChild(pNode->st_pLeftChild, QPoint(pos.x() - childInterval/2, pos.y() + c_minInterval), interval);
	layoutChild(pNode->st_pRightChild, QPoint(pos.x() + childInterval/2, pos.y() + c_minInterval), interval);
}


