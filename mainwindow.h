#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void LogoDetection(const std::string& logo_filename, const std::string& img_filename);
    std::vector<std::string> GetListOfFiles(const std::string& logo_dir, const std::string& img_dir);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
