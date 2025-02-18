#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QFileInfo>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_encryptButton_clicked() {
    QString filePath = QFileDialog::getOpenFileName(this, "Select File to Encrypt");
    if (!filePath.isEmpty()) {
        processFile(filePath, "encrypt");
    }
}

void MainWindow::on_decryptButton_clicked() {
    QString filePath = QFileDialog::getOpenFileName(this, "Select File to Decrypt");
    if (!filePath.isEmpty()) {
        processFile(filePath, "decrypt");
    }
}

void MainWindow::processFile(const QString &filePath, const QString &mode) {
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, "Error", "Could not open the file!");
        return;
    }

    QByteArray fileData = file.readAll();
    file.close();

    const char key = 0x5A;  // XOR key

    // XOR-based encryption/decryption
    for (auto &byte : fileData) {
        byte ^= key;
    }

    // Generate new file name
    QFileInfo fileInfo(filePath);
    QString newFilePath;

    if (mode == "encrypt") {
        newFilePath = fileInfo.absolutePath() + "/" + fileInfo.completeBaseName() + "_encrypted" + fileInfo.suffix().prepend(".");
    } else if (mode == "decrypt") {
        newFilePath = fileInfo.absolutePath() + "/" + fileInfo.completeBaseName() + "_decrypted" + fileInfo.suffix().prepend(".");
    }

    QFile newFile(newFilePath);
    if (!newFile.open(QIODevice::WriteOnly)) {
        QMessageBox::critical(this, "Error", "Could not create the new file!");
        return;
    }

    newFile.write(fileData);
    newFile.close();

    QString successMessage = QString("File %1 successfully!\nSaved as: %2")
                                 .arg(mode == "encrypt" ? "encrypted" : "decrypted")
                                 .arg(newFilePath);
    QMessageBox::information(this, "Success", successMessage);
}

