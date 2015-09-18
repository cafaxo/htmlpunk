#include "CodeEditor.h"
#include "LineNumberArea.h"

LineNumberArea::LineNumberArea(CodeEditor *editor) : QWidget(editor) {
    codeEditor = editor;
    setFont(QFont("Andale Mono", 12));
}

void LineNumberArea::paintEvent(QPaintEvent *event) {
    codeEditor->lineNumberAreaPaintEvent(event);
}
