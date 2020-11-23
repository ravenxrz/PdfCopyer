#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "clipboardprocessor.h"


#include <QAction>
#include <QDialog>
#include <QMenu>


MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    // 初始化action和trayicon
    createActions();
    createTrayIcon();
    crateHotKey();

    // 绑定动作
    connect(hotKey, &QHotkey::activated, this,&MainWindow::clipboardContentProcess);

    trayIcon->show();
}

MainWindow::~MainWindow()
{

}

void MainWindow::setVisible(bool visible)
{}

void MainWindow::clipboardContentProcess()
{
    ClipboardProcessor::processClipboardText();
}


void MainWindow::createActions()
{
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
    hotKey = new QHotkey(QKeySequence("alt+1"), true, this);//The hotkey will be automatically registered
}

