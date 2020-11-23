#include "clipboardprocessor.h"
#include <QClipboard>
#include <QGuiApplication>
#include <QDebug>


ClipboardProcessor::ClipboardProcessor()
{

}

void ClipboardProcessor::processClipboardText()
{
    static QClipboard *board = QGuiApplication::clipboard();
    static QString tempStr = "";

    // 处理
    qDebug() << "before process :" << board->text();
    tempStr = board->text();
    tempStr = tempStr.replace("\n", " ");
    qDebug() << "after process :" <<tempStr;

    // 重新设置回剪切板
    board->setText(tempStr);
}
