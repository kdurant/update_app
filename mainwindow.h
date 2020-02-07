#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QUdpSocket>
#include <QMessageBox>
#include <QTime>
#include <QFileDialog>
#include <QThread>

#include "protocol.h"
#include "config.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
protected:
    void closeEvent(QCloseEvent *event);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void initParameter();
    void saveParameter();
    void initSignalSlot();

private slots:
    void processPendingDatagram();
    void debugNorFlash();
    void udpBind();

    void selectFile();
    void writeFirmwire();

private:
    Ui::MainWindow *ui;
    QSettings *     configIni;

    QString firmwireBin;

    QUdpSocket *udpSocket;
    QHostAddress deviceIP;
    quint16      devicePort;
    QString      mWriteData;
    QString      mReadData;
};
#endif  // MAINWINDOW_H
