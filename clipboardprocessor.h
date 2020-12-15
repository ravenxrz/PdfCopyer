#ifndef CLIPBOARDPROCESSOR_H
#define CLIPBOARDPROCESSOR_H


#include <QClipboard>
#include <QGuiApplication>
#include <QDebug>
#include "processmode.h"


class ClipboardProcessor
{
public:
    ClipboardProcessor()=delete;

    /**
     * @brief processClipboardText 处理当前剪切板中的文本，
     *  对于中文，直接去掉换行符。
     *  对于非中文，去掉换行符后，添加空格
     */
    static void processClipboardText();


    static void openCodeMode();

    static void openNormalMode();

private:

    /**
     * @brief systemBoard 获取系统剪切板
     * @return
     */
    static QClipboard* systemBoard(){
        static QClipboard *board;
        if(board == nullptr){
            board = QGuiApplication::clipboard();
        }
        return board;
    }


    /**
     * @brief isChineseText 检查是否含有中文文本
     * @param text 被检查文本
     * @return true，含有中文文本
     *         flase, 不含有中文文本
     */
    static bool containChineseText(const QString& text);


    /**
     * @brief normalModeProcess
     * 普通文本模式处理
     * 去掉换行符，中英文分别处理
     */
    static void normalModeProcess();

    /**
     * @brief codeModeProcess
     * 代码模式处理
     * 去掉
     */
    static void codeModeProcess();





private:
    static ProcessMode currentMode;

};




#endif // CLIPBOARDPROCESSOR_H
