#include "CodeEditor.h"
#include "LineNumberArea.h"

CodeEditor::CodeEditor(QWidget *parent) : QPlainTextEdit(parent) {
    lineNumberArea = new LineNumberArea(this);

    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect,int)));
    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));

    updateLineNumberAreaWidth(0);
    highlightCurrentLine();

    CodeHighlighter *highlighter = new CodeHighlighter(document());
    highlighter->setDocument(document());
}

int CodeEditor::lineNumberAreaWidth() {
    int digits = 1;
    int max = qMax(1, blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }

    int space = 10 + fontMetrics().width(QLatin1Char('9')) * digits;

    return space;
}

void CodeEditor::updateLineNumberAreaWidth(int /* newBlockCount */) {
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void CodeEditor::updateLineNumberArea(const QRect &rect, int dy) {
    if (dy)
        lineNumberArea->scroll(0, dy);
    else
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth(0);
}

void CodeEditor::resizeEvent(QResizeEvent *e) {
    QPlainTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

void CodeEditor::keyPressEvent(QKeyEvent *e) {
    if (e->key() == Qt::Key_Tab) {
        textCursor().insertText("  ");

    } else if(e->key() == Qt::Key_Return) {
        int whitespaceNumber = textCursor().block().text().indexOf(QRegExp("[\\S]"));
        textCursor().insertText("\n");

        for (int i = 0; i < whitespaceNumber; ++i) {
            textCursor().insertText(QString(" "));
        }
    } else {
        QPlainTextEdit::keyPressEvent(e);
    }
}

void CodeEditor::lineNumberAreaPaintEvent(QPaintEvent *event) {
    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), QColor(225, 225, 225));

    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + (int) blockBoundingRect(block).height();

    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(QColor(125, 125, 125));
            painter.drawText(0, top, lineNumberArea->width(), fontMetrics().height(),
                             Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + (int) blockBoundingRect(block).height();
        ++blockNumber;
    }
}

void CodeEditor::setText(QString string) {
    document()->clear();
    insertPlainText(string);
}

void CodeEditor::highlightCurrentLine() {
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;

        QColor lineColor = QColor(Qt::yellow).lighter(175);

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);
}

bool CodeEditor::find(QRegExp search) {
    search.setMinimal(true);
    QTextCursor cursor = document()->find(search, textCursor().selectionEnd());

    if (!cursor.isNull()) {
        setTextCursor(cursor);
    }

    return true;
}

bool CodeEditor::replace(QRegExp search, QString replace) {
    if (textCursor().hasSelection()) {
        textCursor().insertText(textCursor().selectedText().replace(search, replace));
    } else {
        search.setMinimal(true);
        QTextCursor cursor = document()->find(search, textCursor().selectionEnd());

        if (!cursor.isNull()) {
            setTextCursor(cursor);
            textCursor().insertText(cursor.selectedText().replace(search, replace));
        }
    }

    return true;
}

long CodeEditor::replaceAll(QRegExp search, QString replace) {
    search.setMinimal(true);
    QString sourceCode = document()->toPlainText();

    document()->clear();
    insertPlainText(sourceCode.replace(search, replace));

    return 0;
}

void CodeEditor::tidy(bool cleanUp) {
    QThread* thread = new QThread;
    TidyWorker* worker = new TidyWorker(document()->toPlainText(), cleanUp);

    worker->moveToThread(thread);

    connect(thread, SIGNAL(started()), worker, SLOT(process()));
    connect(worker, SIGNAL(finishedTidy(QString)), this, SLOT(finishedTidy(QString)));
    connect(worker, SIGNAL(finished()), thread, SLOT(quit()));
    connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

    thread->start();
}

void CodeEditor::finishedTidy(QString tidiedSource) {
    document()->clear();
    insertPlainText(tidiedSource);
}
