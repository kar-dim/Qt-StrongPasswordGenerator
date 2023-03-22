#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static constexpr int LOWER_CASE = 1;
    static constexpr int UPPER_CASE = 2;
    static constexpr int SYMBOLS = 3;
    static constexpr int NUMBERS = 4;
    static const QList<QChar> LOWER_CASE_LIST;
    static const QList<QChar> UPPER_CASE_LIST;
    static const QList<QChar> SYMBOLS_LIST;
    static const QList<QChar> NUMBERS_LIST;
private slots:
    void on_btn_generate_clicked();

    void on_btn_copy_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
