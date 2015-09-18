#include "TidyWorker.h"

TidyWorker::TidyWorker(QString source, bool cleanUp) {
    source_ = source;
    cleanUp_ = cleanUp;
}

TidyWorker::~TidyWorker() {
}

void TidyWorker::process() {
    TidyDoc tidy_document = tidyCreate();

    TidyBuffer output = { 0 };
    TidyBuffer errbuf = { 0 };

    if (cleanUp_)
        tidyOptSetBool(tidy_document, TidyMakeClean, yes);
    else
        tidyOptSetBool(tidy_document, TidyMakeClean, no);

    tidyOptSetBool(tidy_document, TidyXhtmlOut, yes);
    tidyOptSetValue(tidy_document, TidyDoctype, "strict");
    tidyOptSetBool(tidy_document, TidyEncloseBodyText, yes);
    tidyOptSetInt(tidy_document, TidyWrapLen, 0);
    tidyOptSetValue(tidy_document, TidyNewline, "LF");
    tidyOptSetInt(tidy_document, TidyIndentContent, TidyAutoState);
    tidyOptSetBool(tidy_document, TidyMark, no);
    tidySetCharEncoding(tidy_document, "utf8");
    tidyOptSetBool(tidy_document, TidyForceOutput, yes);
    tidySetErrorBuffer(tidy_document, &errbuf);
    tidyParseString(tidy_document, source_.toUtf8().constData());

    tidyCleanAndRepair(tidy_document);
    tidyRunDiagnostics(tidy_document);
    tidySaveBuffer(tidy_document, &output);

    emit finishedTidy(QString::fromUtf8((const char*) output.bp));

    tidyBufFree(&output);
    tidyBufFree(&errbuf);
    tidyRelease(tidy_document);

    emit finished();
}
