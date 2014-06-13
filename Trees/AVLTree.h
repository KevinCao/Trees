#ifndef AVLTREE_H
#define AVLTREE_H

#include <vector>

class AVLTree
{
public:
	struct Node
	{
		enum Orientation 
		{
			em_invalid = 0,
			em_left,
			em_righ
		};

		Node(int value)
			:st_Value(value)
			,st_BF(0)
			,st_pLeftChild(0)
			,st_pRightChild(0)
		{

		}

		~Node()
		{
			if (0 != st_pLeftChild)
				delete st_pLeftChild;
			if (0 != st_pRightChild)
				delete st_pRightChild;
		}

		Orientation childOrientation(Node* pNode) const
		{
			if (NULL == pNode)
				return em_invalid;
			if (pNode == st_pLeftChild)
				return em_left;
			else if (pNode == st_pRightChild)
				return em_righ;
			else
				return em_invalid;
		}

		static int maxDeep(Node* pNode) 
		{
			Node* pCurrrentNode = pNode;
			int deep = 0;
			while (pCurrrentNode) {
				if (pCurrrentNode->st_BF < 0)
					pCurrrentNode = pCurrrentNode->st_pRightChild;
				else 
					pCurrrentNode = pCurrrentNode->st_pLeftChild;

				deep ++;
			}

			return deep;
		}

		//return max deep
		static int updateBF(Node* pNode)
		{
			if (NULL == pNode)
				return -1;
			if (NULL == pNode->st_pLeftChild 
				&& NULL == pNode->st_pRightChild) {
					pNode->st_BF = 0;
					return 0;
			}

			int leftDeep = updateBF(pNode->st_pLeftChild);
			int rightDeep = updateBF(pNode->st_pRightChild);

			pNode->st_BF = leftDeep - rightDeep;

			int maxDeep = leftDeep > rightDeep ? leftDeep : rightDeep;

			return maxDeep+1;
		}

		int st_Value;
		int st_BF;
		Node* st_pLeftChild;
		Node* st_pRightChild;
	};
public:
	AVLTree(void);
	~AVLTree(void);

public:
	void addNode(int value);
	void rmNode(int value);

	Node* root()const {return m_pRootNode;}
private:
	/************************************************************************/
	/* find the path to insert a new node                                   */
	/************************************************************************/
	std::vector<Node*> findInsertPath(int value)const;

	/************************************************************************/
	/* adjust the value of st_BF                                            */
	/************************************************************************/
	void updateBFForInsert(std::vector<Node*>& path);

	/************************************************************************/
	/*                                                                      */
	/************************************************************************/
	void adjustTreeForInsert(std::vector<Node*>& path);


	void LLRotate(Node* pNode, const std::vector<Node*>& path);

	void RRRotate(Node* pNode, const std::vector<Node*>& path);

	void LRRotate(Node* pNode, const std::vector<Node*>& path);

	void RLRotate(Node* pNode, const std::vector<Node*>& path);

private:
	Node* updateChildRoot(const std::vector<Node*>& path, int currentRootIndex, int newRootIndex);
private:
	Node* m_pRootNode;
};

#endif