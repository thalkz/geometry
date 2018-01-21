#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->tetra_button, SIGNAL(released()), this, SLOT(onTetraButton()));
    connect(ui->cube_button, SIGNAL(released()), this, SLOT(onCubeButton()));
    connect(ui->pyramid_button, SIGNAL(released()), this, SLOT(onPyramidButton()));
    connect(ui->plane_button, SIGNAL(released()), this, SLOT(onPlaneButton()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onTetraButton()
{
    ui->canvasWidget->helloRoland(0);
}

void MainWindow::onCubeButton()
{
    ui->canvasWidget->helloRoland(1);
}

void MainWindow::onPyramidButton()
{
    ui->canvasWidget->helloRoland(2);
}

void MainWindow::onPlaneButton()
{
    ui->canvasWidget->helloRoland(3);
}
