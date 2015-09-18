#include "CodeHighlighter.h"

CodeHighlighter::CodeHighlighter(QObject *parent) : QSyntaxHighlighter(parent) {
    textFont_ = QTextCharFormat();
    textFont_.setFont(QFont("Andale Mono", 12));

    elementFont_ = QTextCharFormat();
    elementFont_.setFont(QFont("Andale Mono", 12));
    elementFont_.setForeground(QBrush(Qt::blue));

    attributeFont_ = QTextCharFormat();
    attributeFont_.setFont(QFont("Andale Mono", 12));
    attributeFont_.setForeground(QBrush(Qt::darkRed));

    quotedFont_ = QTextCharFormat();
    quotedFont_.setFont(QFont("Andale Mono", 12));
    quotedFont_.setForeground(QBrush(Qt::darkCyan));
}

void CodeHighlighter::highlightBlock(const QString& text) {
    setFormat(0, text.length(), textFont_);

    for (int i = 0; i < text.length(); ++i) {
        if (text.mid(i, 2) == "</") {
            int element_end = text.indexOf('>', i);

            if (element_end == -1)
                element_end = text.length();

            setFormat(i, element_end - i + 1, elementFont_);
        } else if (text[i] == '<') {
            int element_name_end = text.indexOf(' ', i);
            int element_end = text.indexOf('>', i);

            if (element_end == -1)
                element_end = text.length();

            if (element_name_end == -1)
                element_name_end = text.length();

            if (element_name_end < element_end) {
                setFormat(i, element_name_end - i, elementFont_);

                for (i = element_name_end; i < element_end; ++i) {
                    if (text[i] == '\"') {
                        int quoted_text_end = text.indexOf('\"', i + 1);

                        if (quoted_text_end == -1)
                            quoted_text_end = text.length();

                        setFormat(i, quoted_text_end - i + 1, quotedFont_);
                        i = quoted_text_end;
                    } else {
                        setFormat(i, 1, attributeFont_);
                    }
                }
            } else {
                setFormat(i, element_end - i + 1, elementFont_);
            }

            if (element_end != element_name_end) {
                setFormat(i, 1, elementFont_);
            }
        }
    }
}
