#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QTime>


const QString logFilePath = "debug.log";
// redirect qDebug to file
void customMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QHash<QtMsgType, QString> msgLevelHash({{QtDebugMsg, "Debug"}, {QtInfoMsg, "Info"}, {QtWarningMsg, "Warning"}, {QtCriticalMsg, "Critical"}, {QtFatalMsg, "Fatal"}});
    QByteArray                localMsg         = msg.toLocal8Bit();
    QTime                     time             = QTime::currentTime();
    QString                   formattedTime    = time.toString("hh:mm:ss.zzz");
    QByteArray                formattedTimeMsg = formattedTime.toLocal8Bit();
    QString                   logLevelName     = msgLevelHash[type];
    QByteArray                logLevelMsg      = logLevelName.toLocal8Bit();
#ifdef LOG2FILE
    QString txt = QString("%1 %2: %3 (%4)").arg(formattedTime, logLevelName, msg, context.file);
    QFile   outFile(logFilePath);
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&outFile);
    ts << txt << endl;
    outFile.close();
#endif
    fprintf(stderr, "%s %s: %s (%s:%u, %s)\n", formattedTimeMsg.constData(), logLevelMsg.constData(), localMsg.constData(), context.file, context.line, context.function);
    fflush(stderr);

    if(type == QtFatalMsg)
        abort();
}

int main(int argc, char *argv[])
{
    qInstallMessageHandler(customMessageOutput);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
