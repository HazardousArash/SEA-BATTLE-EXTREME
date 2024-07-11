#ifndef CLIENTPROJECT_H
#define CLIENTPROJECT_H

#include <QWidget>
#include <QTcpSocket>
#include <QVector>
#include <vector>

class clientProject : public QWidget
{
    Q_OBJECT

public:
    clientProject(QWidget *parent = nullptr);
    ~clientProject();

private slots:
    void onConnected();
    void onReadyRead();
    void onSendData();
    void onDisconnected();
    void sendBoards(); // New function to send boards

private:
    QTcpSocket *socket;

    void processReceivedData(const QByteArray& data);
};

#endif // CLIENTPROJECT_H
