#ifndef PDC_CMD_LINE_PARSER_H
#define PDC_CMD_LINE_PARSER_H


#include <QCommandLineParser>

class PDCCMDLineParser : public QCommandLineParser
{
public:
    PDCCMDLineParser();

    const QCommandLineOption logLevelOption;
    const QCommandLineOption fileOption;
};



#endif