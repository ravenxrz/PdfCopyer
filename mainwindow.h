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

    // 初始化热键
    // 从默认hotKeyFilePath中读取键位映射
    // 若hotKeyFilePath文件不存在，则创建默认文件
    // 默认规则：
    // Alt+1 --> Normal Mode
    // Alt+2 --> Code Mode
    void initHotKeyMap();

private:
    QAction *quitAction;


    QHotkey *normalModeHotKey;                  // 文本处理快捷键
    QHotkey *codeModeHotKey;                    // 代码处理快捷键
    QMap<QString,QString> hotKeyMap;            // hot key映射
    QString hotKeyFilePath;                     // 自定义hot key文件路径

    QSystemTrayIcon *trayIcon;

public:
    static const QString kNormalModeKey;
    static const QString kCodeModeKey;

};
#endif // MAINWINDOW_H
