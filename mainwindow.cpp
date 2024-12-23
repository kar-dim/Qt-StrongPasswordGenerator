#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTimer>
#include <QClipboard>
#include <QMessageBox>
#include <QRandomGenerator>
#include <QVector>
#include "passwordutils.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lb_password_copied->setVisible(false);

    connect(ui->btn_generate, &QPushButton::clicked, this, &MainWindow::onGenerateClick);
    connect(ui->btn_copy, &QPushButton::clicked, this, &MainWindow::onCopyClick);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onGenerateClick()
{
    const int pwdLen = ui->cbox_pslength->currentText().toInt();
    const bool lowerCase = ui->cb_pslowercase->isChecked();
    const bool upperCase = ui->cb_psuppercase->isChecked();
    const bool symbols = ui->cb_pssymbols->isChecked();
    const bool numbers = ui->cb_psnumbers->isChecked();

    //at least ONE option is required!
    if (!lowerCase && !upperCase && !symbols && !numbers)
    {
        QMessageBox::critical(this, "Error", "At least one password option is required", QMessageBox::Ok, QMessageBox::Ok);
        return;
    }
    QVector<int> availableCharTypes;
    if (lowerCase) availableCharTypes.append(LOWER_CASE);
    if (upperCase) availableCharTypes.append(UPPER_CASE);
    if (symbols) availableCharTypes.append(SYMBOL);
    if (numbers) availableCharTypes.append(NUMBER);

    QString pwd;
    const auto randomGenerator = QRandomGenerator::global();
    //construct the password
    for (int i = 0; i < pwdLen; i++)
    {
        const int selectedCharType = availableCharTypes[randomGenerator->bounded(availableCharTypes.size())];
        const QVector<QChar>& selectedList = PasswordUtils::charTypeLists[selectedCharType];
        pwd.append(selectedList[randomGenerator->bounded(selectedList.size())]);
    }
    ui->pet_password->clear();
    ui->pet_password->appendPlainText(pwd);
}


void MainWindow::onCopyClick()
{
    //copy to system clipboard only if there is a password set
    const QString pwd = ui->pet_password->toPlainText();
    if (pwd.length() >= 8)
    {
        QGuiApplication::clipboard()->setText(pwd);
        //show the label "copied to clipboard" for 2 seconds
        if (!ui->lb_password_copied->isVisible())
        {
            ui->lb_password_copied->setVisible(true);
            QTimer::singleShot(2000, this, [this](){ ui->lb_password_copied->setVisible(false); });
        }
    }
}

