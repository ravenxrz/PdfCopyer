#include "clipboardprocessor.h"



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

void ClipboardProcessor::normalModeProcess()
{

    static QString tempStr = "";

    // 处理
    tempStr = systemBoard()->text();
    if(containChineseText(tempStr)){    // 中文，直接去掉换行
        tempStr = tempStr.replace("\n", "");
    }else{                              // 非中文，去掉换行，添加空格
        tempStr = tempStr.replace("\n", " ");
    }

    // 重新设置回剪切板
    systemBoard()->setText(tempStr);
}



/**
 * @brief firstNonSpaceIndex
 * @param qStr 用于测试的字符串
 * @return  index，首个非空白字符串的偏移量
 *          -1 ，无非空白字符串
 */
static size_t firstNonSpaceOffset(const QString& qStr){
    std::string str = qStr.toStdString();
    for(size_t i = 0;i<str.length();i++){
        if(!isspace(str.at(i))){
            return i;
        }
    }
    return -1;
}

void ClipboardProcessor::codeModeProcess()
{
    static QString tempStr = "";
    QString content = "";

    // 处理
    int minNonSpaceOffset = 0x7fffffff;
    tempStr = systemBoard()->text();
    QStringList lines = tempStr.split("\n");
    for(auto& line : lines){
        int firstSpaceOffset = line.indexOf(" ");
        QString tempLine = line.mid(firstSpaceOffset);
        int nonSpaceOffset = firstNonSpaceOffset(tempLine);
        if(nonSpaceOffset == -1) {
             content.append(tempLine.mid(0)+"\n");
             continue;
        }else{
            minNonSpaceOffset = std::min(nonSpaceOffset,minNonSpaceOffset);
            content.append(tempLine.mid(minNonSpaceOffset)+"\n");
        }
    }

    qDebug() << content;
    // 重新设置回剪切板
    systemBoard()->setText(content);
}
