#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setStyleSheet("border-color: black;"
                        "border: 2px solid;");
    QHBoxLayout *mainHLayout = new QHBoxLayout(this);
    mainHLayout->addWidget(ui->textEdit, 7);
    mainHLayout->addWidget(ui->fileListWgt, 1);
    this->setLayout(mainHLayout);


    connect(ui->newBtn, SIGNAL(clicked()), this, SLOT(onNewClicked()));
    connect(ui->openBtn, SIGNAL(clicked()), this, SLOT(onOpenClicked()));
    connect(ui->saveBtn, SIGNAL(clicked()), this, SLOT(onSaveClicked()));
    connect(ui->saveAsBtn, SIGNAL(clicked()), this, SLOT(onSaveAsClicked()));
    connect(ui->fileListWgt, &QListWidget::itemClicked, this, &MainWindow::onItemClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}


// 创建一个文件列表，默认读取里面的文件，里面存放的是文件路径
void MainWindow::fileListWgtInit()
{
    QFile file(config);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {



    }
}

void MainWindow::onNewClicked()
{
    ui->statusLab->setText("这是一个新的文件");
    ui->textEdit->setText("请输入文本内容");
    QString newFile = "Untitled";
    QString newFilePath = "D:/" + newFile + ".txt";
    QListWidgetItem *item = new QListWidgetItem(newFile);
    ui->fileListWgt->addItem(item);
}
void MainWindow::onOpenClicked()
{
    ui->statusLab->setText("打开文件");
    ui->textEdit->clear();
    QStringList fileNames = QFileDialog::getOpenFileNames(this,
                                            tr("Open File"),
                                            "D:/",
                                            tr("Image Files (*.txt *.md)"));
    for(const QString &fileName : fileNames) {
        QFileInfo fileInfo(fileName);
        QString fileNameOnly = fileInfo.fileName();
        QListWidgetItem *item = new QListWidgetItem(fileNameOnly);
        ui->fileListWgt->addItem(item);
    }


    // currentFileName = fileNames[0];
    // openFile(currentFileName);
}

void MainWindow::onItemClicked(QListWidgetItem *item)
{
    QString fileName = item->text();
    QString filePath = "D:/" + fileName;
    qDebug() << filePath;
    openFile(filePath);
}

void MainWindow::openFile(const QString &fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::ReadWrite| QIODevice::Text)){
        QMessageBox::critical(nullptr, "Error", "Open file failed!");
        return;
    }
    QTextStream textStream(&file); // 读取文件
    while(!textStream.atEnd()){
        ui->textEdit->setPlainText(textStream.readAll());
    }
    file.close();
}

void MainWindow::onSaveClicked()
{

    ui->statusLab->setText("保存文件");

    if(ui->textEdit->toPlainText() == ""){
        QMessageBox::warning(this, tr("警告"), tr("内容不能为空"), QMessageBox::Ok);
        return;
    }
    QFile file(currentFileName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        qDebug() << "Could not open file for writing: " << file.errorString();
        return;
    }
    QTextStream out(&file);
    out << ui->textEdit->toPlainText(); // 获取文本内容
    file.close();
    qDebug() << "File saved successfully!";


}

void MainWindow::onSaveAsClicked()
{
    ui->statusLab->setText("另存文件");
    QFileDialog fileDialog;
    QString fileName = fileDialog.getSaveFileName(this, tr("另存为"),
                                             "D:/", tr("Text File(*.txt *.md)"));
    if(!fileName.isEmpty()){
        QFile file(fileName);
        if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
            QTextStream out(&file);
            out << ui->textEdit->toPlainText();
            file.close();
        } else {
            QMessageBox::critical(this, tr("错误"),
                                  tr("无法写入文件: %1").arg(file.errorString()));
        }
    }

}
