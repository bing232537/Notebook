#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QListWidget>
#include <QListWidgetItem>
#include <QJsonDocument>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public:
    QString currentFileName;
    QString config = "D:/NoteConfig.txt";

public:
    void openFile(const QString &fileName);
    void fileListWgtInit();

public slots:
    void onNewClicked();
    void onOpenClicked();
    void onSaveClicked();
    void onSaveAsClicked();
    void onItemClicked(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
