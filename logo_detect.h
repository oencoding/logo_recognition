#ifndef LOGO_DETECT_H
#define LOGO_DETECT_H

#include <QMainWindow>

namespace Ui {
class logo_detect;
}

class logo_detect : public QMainWindow
{
    Q_OBJECT

public:
    explicit logo_detect(QWidget *parent = 0);
    ~logo_detect();

private:
    Ui::logo_detect *ui;
};

#endif // LOGO_DETECT_H
