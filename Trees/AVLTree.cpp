#include "AVLTree.h"

using namespace std;

AVLTree::AVLTree(void)
	:m_pRootNode(0)
{
}


AVLTree::~AVLTree(void)
{
	if (0 != m_pRootNode)
		delete m_pRootNode;
}


void AVLTree::addNode(int value)
{
	if (0 == m_pRootNode) {
		m_pRootNode = new Node(value);
		return;
	}
	vector<Node*> path = findInsertPath(value);
	if (path.size() == 0)
		return;

	Node* pNewNode = new Node(value);
	if (value < path.back()->st_Value) {
		path.back()->st_pLeftChild = pNewNode;
	}else {
		path.back()->st_pRightChild = pNewNode;
	}
	path.push_back(pNewNode);
	updateBFForInsert(path);
	adjustTreeForInsert(path);
}

void AVLTree::rmNode(int value)
{

}

vector<AVLTree::Node*> AVLTree::findInsertPath(int value)const
{
	vector<AVLTree::Node*> path;
	if (0 == m_pRootNode)
		return path;
	Node* pCurrentNode = m_pRootNode;
	while (pCurrentNode)
	{
		path.push_back(pCurrentNode);
		if (value < pCurrentNode->st_Value) {
			pCurrentNode = pCurrentNode->st_pLeftChild;
		}else {
			pCurrentNode = pCurrentNode->st_pRightChild;
		}
	}
	return path;
}

void AVLTree::updateBFForInsert(vector<Node*>& path)
{
	for (int i=path.size()-1; i>0; i--) {
		if (path[i-1]->st_pLeftChild == path[i]) {
			path[i-1]->st_BF ++;
		}else if (path[i-1]->st_pRightChild == path[i]) {
			path[i-1]->st_BF --;
		}
		if (0 == path[i-1]->st_BF || abs(path[i-1]->st_BF) == 2)
			break;
	}
}

void AVLTree::adjustTreeForInsert(std::vector<Node*>& path)
{
	for (int i=path.size()-1; i>0; i--) {
		if (abs(path[i]->st_BF) != 2)
			continue;

		if (2 == path[i]->st_BF) {

		}else {

		}
	}
}