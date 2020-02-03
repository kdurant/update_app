#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    udpSocket = new QUdpSocket(this);

    configIni = new QSettings("./config.ini", QSettings::IniFormat);

    initParameter();
    initSignalSlot();
    udpBind();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// configIni->value("System/oceanPort")
void MainWindow::initParameter()
{
}

void MainWindow::initSignalSlot()
{
    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(processPendingDatagram()));
    connect(ui->rbt_StatusEnable, SIGNAL(clicked()), this, SLOT(udpBind()));
}

//configIni->setValue("Laser/freq", 1111);
void MainWindow::saveParameter()
{
    configIni->setValue("System/RadarType", "land");
    configIni->setValue("Laser/freq", 1111);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    saveParameter();
}

void MainWindow::udpBind()
{
    if(!udpSocket->bind(QHostAddress(ui->lineEdit_HostIP->text()), ui->lineEdit_HostIP->text().toInt()))
    {
        QMessageBox::warning(this, "警告", "雷达连接失败");
        ui->rbt_StatusDisable->setChecked(true);
    }
    else
    {
        ui->rbt_StatusDisable->setChecked(false);
        ui->statusBar->showMessage(tr("连接设备成功"), 0);
    }
}

void MainWindow::processPendingDatagram()
{
    return;
}
