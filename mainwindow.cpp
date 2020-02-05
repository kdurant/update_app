#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    udpSocket = new QUdpSocket(this);

    configIni = new QSettings("./config.ini", QSettings::IniFormat);

    deviceIP = QHostAddress(ui->lineEdit_DevIP->text());
    devicePort = ui->lineEdit_DevPort->text().toInt();

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
    connect(ui->bt_Erase, SIGNAL(clicked()), this, SLOT(debugNorFlash()));
    connect(ui->bt_Read, SIGNAL(clicked()), this, SLOT(debugNorFlash()));
    connect(ui->bt_Write, SIGNAL(clicked()), this, SLOT(debugNorFlash()));
    connect(ui->bt_GenerateData, SIGNAL(clicked()), this, SLOT(debugNorFlash()));
    connect(ui->bt_Compare, SIGNAL(clicked()), this, SLOT(debugNorFlash()));
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

void MainWindow::debugNorFlash()
{
    QPushButton *bt = qobject_cast<QPushButton *>(sender());
    QString send = bt->text();
    Protocol p;
    QByteArray frame;
    if(send == "erase data")
    {
        frame = p.encode(ERASE_BLOCK_RUN, 4, ui->lineEdit_EraseAddr->text().toInt());
    }
    else if(send == "read data")
    {
        frame = p.encode(READ_BLOCK_RUN, 4, ui->lineEdit_ReadAddr->text().toInt());
    }
    else if(send == "write data")
    {
        frame = p.encode(WRITE_BLOCK_ADDR, 4, ui->lineEdit_WriteAddr->text().toInt());
        if(ui->pte_WriteData->toPlainText().length() != 256)
        {
            QMessageBox::warning(this, "警告", "Enter correct data");
        }

        frame = p.encode(WRITE_BLOCK_RUN, 4, 0x01);
    }
    else if(send == "generate data")
    {
        QString s;
        if(ui->comboBox_Pattern->currentText() == "Inc")
        {
            for(int i = 0; i < 128; i++)
                //                s.append(QString::number(i, 16));
                s.append(QString("%1").arg(i, 2, 16, QChar('0')));
        }
        else if(ui->comboBox_Pattern->currentText() == "Dec")
        {
            for(int i = 255; i >= 128; i--)
                s.append(QString("%1").arg(i, 2, 16, QChar('0')));
        }
        else if(ui->comboBox_Pattern->currentText() == "Random")
        {
            for(int i = 0; i < 128; i++)
            {
                s.append(QString("%1").arg(qrand() % 256, 2, 16, QChar('0')));
            }
        }
        qDebug() << s.length();
        ui->pte_WriteData->setPlainText(s);
    }
    else if(send == "compare")
    {
        if((ui->pte_ReadData->toPlainText() != 256) || (ui->pte_WriteData->toPlainText() != 256))
        {
            QMessageBox::warning(this, "警告", "Please write data or read data");
        }
        else if(ui->pte_ReadData->toPlainText() == ui->pte_WriteData->toPlainText())
            QMessageBox::information(this, "Info", "Compare success");
        else
            QMessageBox::warning(this, "警告", "Compare fail.");
    }
    udpSocket->writeDatagram(frame.data(), frame.size(), deviceIP, devicePort);
    return;
}
