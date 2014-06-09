#include "AVLTree.h"
#include <iostream>
#include <assert.h>

using namespace std;


template <typename T>
int indexAt(T node, const std::vector<T>& vec)
{
	int size = vec.size();
	for (int i=0; i < size; i++) {
		if (vec[i] == node)
			return i;
	}
	return -1;
}

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
	int pathLength = path.size();
	if (pathLength < 2)
		return;

	for (int i=path.size()-1; i>=0; i--) {
		if (abs(path[i]->st_BF) != 2)
			continue;

		Node::Orientation firstOrientation = path[i]->childOrientation(path[i+1]);

		Node::Orientation secondOrientation = path[i+1]->childOrientation(path[i+2]);

		if (Node::em_left == firstOrientation) {
			if (Node::em_left == secondOrientation)
				LLRotate(path[i], path);
			else if (Node::em_righ == secondOrientation)
				LRRotate(path[i], path);
		}else if (Node::em_righ == firstOrientation) {
			if (Node::em_left == secondOrientation)
				RLRotate(path[i], path);
			else if (Node::em_righ == secondOrientation)
				RRRotate(path[i], path);
		}
	}
}

void AVLTree::LLRotate(Node* pNode, const std::vector<Node*>& path)
{
	assert(NULL != pNode);
	int index = indexAt<Node*>(pNode, path);
	if (-1 == index)
		return;

	pNode->st_pLeftChild = path[index+1]->st_pRightChild;
	path[index+1]->st_pRightChild = pNode;
	
	path[index+1]->st_BF = pNode->st_BF - 2;



	updateChildRoot(path, index, index+1);

}

void AVLTree::RRRotate(Node* pNode, const std::vector<Node*>& path)
{
	assert(NULL != pNode);
	int index = indexAt<Node*>(pNode, path);
	if (-1 == index)
		return;

	pNode->st_pRightChild = path[index+1]->st_pLeftChild;
	path[index+1]->st_pLeftChild = path[index];


	updateChildRoot(path, index, index+1);

}

void AVLTree::LRRotate(Node* pNode, const std::vector<Node*>& path)
{
	assert(NULL != pNode);
	int index = indexAt(pNode, path);
	if (-1 == index)
		return;


	path[index+1]->st_pRightChild = path[index+2]->st_pLeftChild;
	path[index]->st_pLeftChild = path[index+2]->st_pRightChild;
	path[index+2]->st_pLeftChild = path[index+1];
	path[index+2]->st_pRightChild = path[index];


	updateChildRoot(path, index, index+2);
}

void AVLTree::RLRotate(Node* pNode, const std::vector<Node*>& path)
{
	assert(NULL != pNode);
	int index = indexAt(pNode, path);
	if (-1 == index)
		return;

	path[index+1]->st_pLeftChild = path[index+2]->st_pLeftChild;
	path[index]->st_pRightChild = path[index+2]->st_pRightChild;
	path[index+2]->st_pRightChild = path[index+1];
	path[index+2]->st_pLeftChild = path[index];


	updateChildRoot(path, index, index+2);
}


void AVLTree::updateChildRoot(const std::vector<Node*>& path, int currentRootIndex, int newRootIndex)
{
	assert(currentRootIndex >= 0 && currentRootIndex < path.size());
	assert(newRootIndex >= 0 && newRootIndex < path.size());

	if (currentRootIndex!= 0) {
		if (path[currentRootIndex-1]->st_pLeftChild == path[currentRootIndex])
			path[currentRootIndex-1]->st_pLeftChild = path[newRootIndex];
		else if (path[currentRootIndex-1]->st_pRightChild == path[currentRootIndex])
			path[currentRootIndex-1]->st_pRightChild = path[newRootIndex];
		else
			std::cerr << "there is something wrong at "<< __LINE__ << " of " << __FILE__;


		path[currentRootIndex-1]->st_BF
			= Node::maxDeep(path[currentRootIndex-1]->st_pLeftChild)
			- Node::maxDeep(path[currentRootIndex-1]->st_pRightChild);

		path[currentRootIndex]->st_BF
			= Node::maxDeep(path[currentRootIndex]->st_pLeftChild)
			- Node::maxDeep(path[currentRootIndex]->st_pRightChild);

		path[newRootIndex]->st_BF
			= Node::maxDeep(path[newRootIndex]->st_pLeftChild)
			- Node::maxDeep(path[newRootIndex]->st_pRightChild);

	}else { 
		m_pRootNode = path[newRootIndex];
	}


}






