#ifndef SERVERPROJECT_H
#define SERVERPROJECT_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui { class serverProject; }
QT_END_NAMESPACE

class serverProject : public QWidget
{
    Q_OBJECT

public:
    serverProject(QWidget *parent = nullptr);
    ~serverProject();
    void sentData() ;

private slots:
    void newConnectionSlot();
    void writingData();
    void disconnectedFromServer();
    void connectedToServer();
    void readingData();

private:
    Ui::serverProject *ui;
    QTcpServer *myServer;
    QTcpSocket *mySocket;

    std::vector<std::vector<int>> serverBoard;
    std::vector<std::vector<int>> enemyBoard;

    void sendBoards();
    void receiveBoards(const QByteArray& data); // New function to receive boards
};

#endif // SERVERPROJECT_H
