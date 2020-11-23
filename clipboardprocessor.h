#ifndef CLIPBOARDPROCESSOR_H
#define CLIPBOARDPROCESSOR_H

class QString;

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

private:
    /**
     * @brief isChineseText 检查是否含有中文文本
     * @param text 被检查文本
     * @return true，含有中文文本
     *         flase, 不含有中文文本
     */
    static bool containChineseText(const QString& text);
};

#endif // CLIPBOARDPROCESSOR_H
