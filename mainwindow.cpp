#include <QAction>
#include <QDialog>
#include <QMenu>
#include <QCoreApplication>
#include <QFile>
#include "mainwindow.h"
#include "clipboardprocessor.h"

// init static vars
const QString MainWindow::kNormalModeKey = "去除末尾换行符";
const QString MainWindow::kCodeModeKey = "去除行号";


MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent), hotKeyFilePath("./自定义快捷键.txt")
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
    qDebug() << "Normal Mode Process";
    ClipboardProcessor::normalModeProcess();
}

void MainWindow::codeModeProcess()
{
    qDebug() << "Code Mode Process";
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

/**
 * 向file所在文件中，写入 "key=value" 键值对
 * @brief writeKeyValue
 * @param file
 * @param key
 * @param value
 */
static void writeKeyValue(QFile *file,const QString &key,const QString &value){
    Q_ASSERT(file->isOpen() && file->isWritable());
    QString line = key + "=" + value  + "\n";

    const auto &bytes = line.toUtf8();
    file->write(bytes.data(),bytes.size());
}

/**
 * @brief readKeyFromFile
 * @param file
 * @param key
 * @param value
 * @return
 */
static bool setHotkeyMapFromFile(const QString &filePath, QMap<QString, QString> *map){
    Q_ASSERT(QFile::exists(filePath));
    char buf[1024];
    bool ret = false;
    QFile fileObj(filePath);
    ret = fileObj.open(QIODevice::ReadOnly);
    Q_ASSERT(ret);

    while(fileObj.readLine(buf,sizeof(buf)) != -1){
        QString tmp(buf);
        QString line = tmp.trimmed();
        if(line.startsWith(MainWindow::kNormalModeKey)){
            (*map)[MainWindow::kNormalModeKey] = line.mid(MainWindow::kNormalModeKey.length()+1);
        }else if(line.startsWith(MainWindow::kCodeModeKey)){
            (*map)[MainWindow::kCodeModeKey] = line.mid(MainWindow::kCodeModeKey.length()+1);
        }else{
            qDebug() << "Parse custom shortcut file failed\n";
            exit(-1);
        }
    }
    return true;
}

void MainWindow::initHotKeyMap()
{
    Q_ASSERT(!hotKeyFilePath.isEmpty());
    QFile file(hotKeyFilePath);
    bool ret = false;
    QString keyForNormalMode ="alt+1";
    QString keyForCodeMode = "alt+2";

    qDebug() << file.exists();
    if (!file.exists()){
        ret = file.open(QIODevice::WriteOnly | QIODevice::Text);
        Q_ASSERT(ret);
        // write default hot key
        writeKeyValue(&file,kNormalModeKey,keyForNormalMode);
        writeKeyValue(&file,kCodeModeKey,keyForCodeMode);
        file.close();
    }

    ret = setHotkeyMapFromFile(hotKeyFilePath,&hotKeyMap);
    Q_ASSERT(ret);
}


void MainWindow::crateHotKey()
{
    initHotKeyMap();

    QString keyForNormalMode = hotKeyMap[MainWindow::kNormalModeKey];
    QString keyForCodeMode = hotKeyMap[MainWindow::kCodeModeKey];

    qDebug() << "Normal mode key:" << keyForNormalMode;
    qDebug() << "Code mode key:" << keyForCodeMode;

    // 文本处理快捷键
    normalModeHotKey = new QHotkey(QKeySequence(keyForNormalMode), true, this);//The hotkey will be automatically registered
    // 代码处理快捷键
    codeModeHotKey = new QHotkey(QKeySequence(keyForCodeMode),true,this);
}
