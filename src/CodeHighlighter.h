#ifndef CODEHIGHLIGHTER_H
#define CODEHIGHLIGHTER_H

#include <QSyntaxHighlighter>

class CodeHighlighter : public QSyntaxHighlighter {

public:
    CodeHighlighter(QObject *parent = 0);

protected:
    void highlightBlock(const QString& text);

private: 
    QTextCharFormat textFont_;
    QTextCharFormat elementFont_;
    QTextCharFormat attributeFont_;
    QTextCharFormat quotedFont_;
};

#endif // CODEHIGHLIGHTER_H
