#include "clipboardprocessor.h"
#include <QClipboard>
#include <QGuiApplication>
#include <QDebug>


void ClipboardProcessor::processClipboardText()
{
    static QClipboard *board = QGuiApplication::clipboard();
    static QString tempStr = "";

    // 处理
    tempStr = board->text();
    if(containChineseText(tempStr)){    // 中文，直接去掉换行
        tempStr = tempStr.replace("\n", "");
    }else{                              // 非中文，去掉换行，添加空格
        tempStr = tempStr.replace("\n", " ");
    }

    // 重新设置回剪切板
    board->setText(tempStr);
}

bool ClipboardProcessor::containChineseText(const QString &text)
{
    for(int i=0; i< text.count(); ++i)
    {
        QChar c = text.at(i);
        ushort uni = c.unicode();
        if(uni >= 0x4E00 && uni <= 0x9FA5)  return true;
    }

    return false;
}
