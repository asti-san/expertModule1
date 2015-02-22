#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
	srand(QDateTime::currentDateTime().toTime_t());
	ui->setupUi(this);

	ui->plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes | QCP::iSelectLegend | QCP::iSelectPlottables);
	ui->plot->xAxis->setRange(-8, 8);
	ui->plot->yAxis->setRange(-5, 5);
	ui->plot->axisRect()->setupFullAxesBox();

	ui->plot->plotLayout()->insertRow(0);
	ui->plot->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->plot, "Interaction Example"));

	ui->plot->xAxis->setLabel("x Axis");
	ui->plot->yAxis->setLabel("y Axis");

	connect(ui->plot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(onPlotClicked()));
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::onPlotClicked()
{
	double dotSize=0.01;
	QPoint p = ui->plot->mapFromGlobal(QCursor::pos());

	//Get click coordinates in plot scale
	double x = ui->plot->xAxis->pixelToCoord(p.x());
	double y = ui->plot->yAxis->pixelToCoord(p.y());

	//Log coordinates
	std::cout<<x<<"\t"<<y<<std::endl;

	//This shit doesn't work
	QCPItemEllipse *dot = new QCPItemEllipse(ui->plot);
	ui->plot->addItem(dot);
	dot->topLeft->setCoords(x+dotSize,y+dotSize);
	dot->bottomRight->setCoords(x-dotSize,y-dotSize);
}

void MainWindow::on_button_new_clicked()
{
	//Clear the plot
	ui->plot->clearItems();
	ui->plot->replot();

	//Clear the list
	ui->dots_edit_list->clear();

	//Add items to list
	//TODO: See if I need to free this memory(it doesn't work if I do)
	ui->dots_edit_list->setColumnCount(2);
	ui->dots_edit_list->insertRow(0);
	ui->dots_edit_list->verticalScrollBar()->setVisible(true);
	ui->dots_edit_list->setColumnWidth(0,ui->dots_edit_list->width()*0.7);
	ui->dots_edit_list->horizontalHeader()->setStretchLastSection(true);
	ui->dots_edit_list->verticalHeader()->setVisible(false);
	ui->dots_edit_list->horizontalHeader()->setVisible(false);
	QTableWidgetItem *item=new QTableWidgetItem;
	//Add plus buttom
	QPushButton *button=new QPushButton;
	button->setText("+");
	connect(button,SIGNAL(clicked()),this,SLOT(addDotItem()));
	ui->dots_edit_list->setItem(0,0,item);
	ui->dots_edit_list->setCellWidget(0,0,button);
	ui->dots_edit_list->setSpan(0,0,1,2);
	//Add two first dots
	for(int i=0; i<2; i++)
	{
		addDotItem();
	}
}

void MainWindow::addDotItem()
{
	ui->dots_edit_list->insertRow(ui->dots_edit_list->rowCount()-1);
	QTableWidgetItem *item=new QTableWidgetItem;
	QLineEdit *line=new QLineEdit;
	ui->dots_edit_list->setItem(ui->dots_edit_list->rowCount()-2, 0, item);
	ui->dots_edit_list->setCellWidget(ui->dots_edit_list->rowCount()-2, 0, line);
	item=new QTableWidgetItem;
	QPushButton *button=new QPushButton;
	button->setText("-");
	ui->dots_edit_list->setItem(ui->dots_edit_list->rowCount()-2, 1, item);
	ui->dots_edit_list->setCellWidget(ui->dots_edit_list->rowCount()-2, 1, button);
	ui->dots_edit_list->horizontalHeader()->setStretchLastSection(true);
}

void MainWindow::on_button_clear_item_clicked()
{
	//Clear the plot
	ui->plot->clearItems();
	ui->plot->replot();
	//Clear the list
	ui->dots_edit_list->clear();
	ui->dots_edit_list->setRowCount(0);
}
