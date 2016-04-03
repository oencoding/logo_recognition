#include "logo_detect.h"
#include "ui_logo_detect.h"

logo_detect::logo_detect(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::logo_detect)
{
    ui->setupUi(this);
}

logo_detect::~logo_detect()
{
    delete ui;
}
