#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QUdpSocket>
#include <QMessageBox>
#include <QTime>
#include <QFileDialog>

#include "protocol.h"

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

private:
    Ui::MainWindow *ui;
    QSettings *     configIni;

    QUdpSocket *udpSocket;
    QHostAddress deviceIP;
    quint16      devicePort;
};
#endif  // MAINWINDOW_H
