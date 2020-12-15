#include <QAction>
#include <QDialog>
#include <QMenu>
#include <QCoreApplication>
#include "mainwindow.h"
#include "clipboardprocessor.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    // 初始化action和trayicon
    createActions();
    createTrayIcon();
    crateHotKey();

    // 绑定动作
    connect(normalModeHotKey, &QHotkey::activated, this,&MainWindow::normalModeProcess);
    connect(codeModeHotKey, &QHotkey::activated, this,&MainWindow::codeModeProcess);

    trayIcon->show();
}

MainWindow::~MainWindow()
{

}

void MainWindow::setVisible(bool visible)
{
    (void)visible;
}

void MainWindow::normalModeProcess()
{
    ClipboardProcessor::normalModeProcess();
}

void MainWindow::codeModeProcess()
{
    ClipboardProcessor::codeModeProcess();
}



void MainWindow::createActions()
{
    // 退出
    quitAction = new QAction(tr("退出"),this);
    connect(quitAction,&QAction::triggered,qApp,&QCoreApplication::quit);
}

void MainWindow::createTrayIcon()
{
    QMenu *trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);
    trayIcon->setIcon(QIcon(":/images/heart.png"));
}

void MainWindow::crateHotKey()
{
    // 文本处理快捷键
    normalModeHotKey = new QHotkey(QKeySequence("alt+1"), true, this);//The hotkey will be automatically registered
    // 代码处理快捷键
    codeModeHotKey = new QHotkey(QKeySequence("alt+2"),true,this);

}

