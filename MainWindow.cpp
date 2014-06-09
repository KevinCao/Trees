#include "MainWindow.h"

#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>

#include "./Views/AVLView.h"

#include "AVLTree.h"

MainWindow::MainWindow(void)
	:m_pTree(NULL)
	,m_pView(NULL)
	,m_pNumInputs(NULL)
{
	initTree();
	initUI();
}


MainWindow::~MainWindow(void)
{
	if (NULL != m_pTree)
		delete m_pTree;
}

void MainWindow::initTree()
{
	m_pTree = new AVLTree();
}

void MainWindow::initUI()
{
	QWidget* pCenterWidget = new QWidget(this);
	this->setCentralWidget(pCenterWidget);
	QGridLayout* pMainLayout = new QGridLayout(pCenterWidget);
	pCenterWidget->setLayout(pMainLayout);

	m_pView = new AVLView(pCenterWidget);
	pMainLayout->addWidget(m_pView, 0, 0, 5, 5);

	m_pNumInputs = new QLineEdit(pCenterWidget);
	pMainLayout->addWidget(m_pNumInputs, 0, 5, 1, 1);

	QPushButton* pAddBtn = new QPushButton("Add", pCenterWidget);
	pMainLayout->addWidget(pAddBtn, 1, 5, 1, 1);
	connect(pAddBtn, SIGNAL(clicked()), this, SLOT(addNum()));

	pMainLayout->setColumnStretch(1, 1);
}


void MainWindow::addNum()
{
	if (NULL == m_pNumInputs
		|| NULL == m_pTree
		|| NULL == m_pView)
		return;

	int num = m_pNumInputs->text().toInt();
	m_pTree->addNode(num);

	m_pView->setData(m_pTree->root());
}