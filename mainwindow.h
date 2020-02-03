#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QUdpSocket>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
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
    void udpBind();

private:
    Ui::MainWindow *ui;
    QSettings *configIni;


    QUdpSocket *    udpSocket;
};
#endif // MAINWINDOW_H
