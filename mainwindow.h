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
    void clipboardContentProcess();

    void codeModeSwtich(bool isOpen);

private:
    void createActions();
    void createTrayIcon();
    void crateHotKey();

private:
    QAction *quitAction;
    QAction *codeModeAction;

    QHotkey *hotKey;

    QSystemTrayIcon *trayIcon;

};
#endif // MAINWINDOW_H
