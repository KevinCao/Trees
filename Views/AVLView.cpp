#include "AVLView.h"


#include "AVLScene.h"


AVLView::AVLView(QWidget* parent /*= NULL*/)
	:QGraphicsView(parent)
{
	m_pScene = new AVLScene(this);
	this->setScene(m_pScene);
}

AVLView::~AVLView(void)
{

}

void AVLView::setData(AVLTree::Node* pRootNode)
{
	if (NULL == m_pScene)
		return;
	m_pScene->setData(pRootNode);
}
