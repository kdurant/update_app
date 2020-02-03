#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    configIni = new QSettings("./config.ini", QSettings::IniFormat);

    initParameter();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// configIni->value("System/oceanPort")
void MainWindow::initParameter()
{
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
    udpSocket = new QUdpSocket(this);
    if(!udpSocket->bind(QHostAddress(ui->lineEdit_HostIP->text()), ui->lineEdit_HostIP->text().toInt()))
        QMessageBox::warning(this, "警告", "雷达连接失败");
    else
        ui->statusBar->showMessage(tr("连接设备成功"), 0);
}
