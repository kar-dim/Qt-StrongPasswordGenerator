#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTimer>
#include <QClipboard>
#include <QMessageBox>
#include <QRandomGenerator>
#include <QMap>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lb_password_copied->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//implement static methods
const QList<QChar> MainWindow::LOWER_CASE_LIST({'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'});
const QList<QChar> MainWindow::UPPER_CASE_LIST({'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'});
const QList<QChar> MainWindow::SYMBOLS_LIST({'!','@','#','$','%','^','&','*','(',')','-','=','_','+','~'});
const QList<QChar> MainWindow::NUMBERS_LIST({'0','1','2','3','4','5','6','7','8','9'});

void MainWindow::on_btn_generate_clicked()
{
    int pwdLen = ui->cbox_pslength->currentText().toInt();
    bool lowerCase = ui->cb_pslowercase->isChecked();
    bool upperCase = ui->cb_psuppercase->isChecked();
    bool symbols = ui->cb_pssymbols->isChecked();
    bool numbers = ui->cb_psnumbers->isChecked();

    //at least ONE option is required!
    if (!lowerCase && !upperCase && !symbols && !numbers){
        QMessageBox::critical(this, "Error", "At least one password option is required", QMessageBox::Ok, QMessageBox::Ok);
        return;
    }
    QMap<int, int> availableCharTypes;
    int cnt = 0;
    if (lowerCase)
        availableCharTypes[cnt++] = LOWER_CASE;
    if (upperCase)
        availableCharTypes[cnt++] = UPPER_CASE;
    if (symbols)
        availableCharTypes[cnt++] = SYMBOLS;
    if (numbers)
        availableCharTypes[cnt++] = NUMBERS;

    QString pwd;
    QChar randomChar;
    //construct the password
    for (int i=0; i<pwdLen; i++){
        //if available char types == 1 -> select it, don't use random
        quint32 selectedCharType = availableCharTypes.size() == 1 ? 0 : QRandomGenerator::global()->bounded((quint32)0, (quint32)availableCharTypes.size());
        switch(availableCharTypes[selectedCharType]){
            case LOWER_CASE:
                pwd.append(LOWER_CASE_LIST[QRandomGenerator::global()->bounded((quint32)0, (quint32)LOWER_CASE_LIST.size())]);
                break;
            case UPPER_CASE:
                pwd.append(UPPER_CASE_LIST[QRandomGenerator::global()->bounded((quint32)0, (quint32)UPPER_CASE_LIST.size())]);
                break;
            case SYMBOLS:
                pwd.append(SYMBOLS_LIST[QRandomGenerator::global()->bounded((quint32)0, (quint32)SYMBOLS_LIST.size())]);
                break;
            case NUMBERS:
                pwd.append(NUMBERS_LIST[QRandomGenerator::global()->bounded((quint32)0, (quint32)NUMBERS_LIST.size())]);
                break;
        }
    }
    this->ui->pet_password->clear();
    this->ui->pet_password->appendPlainText(pwd);
}


void MainWindow::on_btn_copy_clicked()
{
    //copy to system clipboard only if there is a password set
    QString pwd = ui->pet_password->toPlainText();
    if (pwd.length() >= 8) {
        QGuiApplication::clipboard()->setText(pwd);
        //show the label "copied to clipboard" for 2 seconds
        if (!this->ui->lb_password_copied->isVisible()) {
            this->ui->lb_password_copied->setVisible(true);
            QTimer::singleShot(2000, this, [this]()
            {
               this->ui->lb_password_copied->setVisible(false);
            });
        }
    }
}

