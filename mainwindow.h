#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QDir>
#include <QStringList>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QDir logo_dir = QDir();
    QDir img_dir = QDir();
    void LogoDetection(const std::string& logo_filename, const std::string& img_filename);
    QStringList GetListOfFiles(QDir dir);
    QString BtClick();

private slots:
    void on_pushButton_clicked();

    void on_img_dir_bt_clicked();

    void on_logo_dir_bt_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
