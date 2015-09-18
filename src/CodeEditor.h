#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QPlainTextEdit>
#include <QThread>
#include <QPainter>

#include "TidyWorker.h"
#include "CodeHighlighter.h"

class LineNumberArea;

class CodeEditor : public QPlainTextEdit {
    Q_OBJECT

public:
    explicit CodeEditor(QWidget *parent = 0);

    void setText(QString string);

    bool find(QRegExp searchString);
    bool replace(QRegExp search, QString replace);
    long replaceAll(QRegExp search, QString replace);

    void tidy(bool cleanUp);

    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();

protected:
    void resizeEvent(QResizeEvent *event);
    void keyPressEvent(QKeyEvent *e);

signals:

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &, int);

    void finishedTidy(QString tidiedSource);

private:
    QWidget *lineNumberArea;
};

#endif // CODEEDITOR_H
