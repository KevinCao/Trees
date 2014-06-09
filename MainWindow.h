#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QLineEdit;

class AVLTree;

class AVLView;

class MainWindow
	:public QMainWindow
{
	Q_OBJECT
public:
	MainWindow(void);
	~MainWindow(void);

private:
	void initTree();
	void initUI();

private slots:
	void addNum();

private:
	AVLTree* m_pTree;

	AVLView* m_pView;

	QLineEdit* m_pNumInputs;
};

#endif
