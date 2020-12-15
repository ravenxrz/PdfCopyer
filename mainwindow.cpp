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
    connect(hotKey, &QHotkey::activated, this,&MainWindow::clipboardContentProcess);

    trayIcon->show();
}

MainWindow::~MainWindow()
{

}

void MainWindow::setVisible(bool visible)
{
    (void)visible;
}

void MainWindow::clipboardContentProcess()
{
    ClipboardProcessor::processClipboardText();
}

void MainWindow::codeModeSwtich(bool isOpen)
{
    if(isOpen){
        ClipboardProcessor::openCodeMode();
    }else{
        ClipboardProcessor::openNormalMode();
    }
}

void MainWindow::createActions()
{
    // 代码模式
    codeModeAction = new QAction("代码模式",this);
    codeModeAction->setCheckable(true);
    codeModeAction->setChecked(false);
    connect(codeModeAction,&QAction::triggered,this,&MainWindow::codeModeSwtich);

    // 退出
    quitAction = new QAction(tr("退出"),this);
    connect(quitAction,&QAction::triggered,qApp,&QCoreApplication::quit);
}

void MainWindow::createTrayIcon()
{
    QMenu *trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(codeModeAction);
    trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);
    trayIcon->setIcon(QIcon(":/images/heart.png"));
}

void MainWindow::crateHotKey()
{
    hotKey = new QHotkey(QKeySequence("alt+1"), true, this);//The hotkey will be automatically registered
}

