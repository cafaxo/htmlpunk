#ifndef LINENUMBERAREA_H
#define LINENUMBERAREA_H

class CodeEditor;

class LineNumberArea : public QWidget {
public:
    LineNumberArea(CodeEditor *editor);

    QSize sizeHint() const {
        return QSize(codeEditor->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event);

private:
    CodeEditor *codeEditor;
};

#endif // LINENUMBERAREA_H
