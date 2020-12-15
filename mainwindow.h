#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qhotkey.h"

#include <QSystemTrayIcon>
#include <QDialog>
#include <QWidget>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setVisible(bool visible) override;

private slots:
    void normalModeProcess();

    void codeModeProcess();

private:
    void createActions();
    void createTrayIcon();
    void crateHotKey();

private:
    QAction *quitAction;

    QHotkey *normalModeHotKey;      // 文本处理快捷键
    QHotkey *codeModeHotKey;        // 代码处理快捷键

    QSystemTrayIcon *trayIcon;

};
#endif // MAINWINDOW_H
