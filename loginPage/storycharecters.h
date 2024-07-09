#ifndef STORYCHARECTERS_H
#define STORYCHARECTERS_H

#include <QMainWindow>

namespace Ui {
class storyCharecters;
}

class storyCharecters : public QMainWindow
{
    Q_OBJECT

public:
    explicit storyCharecters(QString userName,QWidget *parent = nullptr);
    ~storyCharecters();

private slots:
    void on_pushButton_clicked();

private:
    Ui::storyCharecters *ui;
     QString userName;
};

#endif // STORYCHARECTERS_H
