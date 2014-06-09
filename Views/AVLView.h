#ifndef AVLVIEW_H
#define AVLVIEW_H

#include <QGraphicsView>

#include "AVLTree.h"


class AVLScene;

class AVLView :
	public QGraphicsView
{
public:
	AVLView(QWidget* parent = NULL);
	~AVLView(void);
public:
	void setData(AVLTree::Node* pRootNode);


private:
	AVLScene* m_pScene;
};

#endif
