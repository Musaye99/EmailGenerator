#ifndef FUNCTIONS_H
#define FUNCTIONS_H


#include <QString>
#include <QStringList>
#include <QMap>
#include <QRegularExpression> // Ensure this include is present if it's used
enum ErrorType {
    FAILED_TO_OPEN_FILE,
    FAILED_TO_PARSE_JSON_FILE,
    UNKNOWN_PLACEHOLDER,
    UNKNOWN_ESCAPE_SEQUENCE
};

struct Error {
    ErrorType type;
    QString data;
};

void outputError(const Error& error);

// Function declarations
void  writeOutput(const QString& filePath, const QStringList& lines, QVector<Error>& errors);
QString getFileLocation(const QString& path);
QMap<QString, QString> getJsonData(const QString& filePath, QVector<Error>& errors);
QStringList getFileData(const QString& filePath, QVector<Error>& errors);
QStringList generateEmail(const QStringList& temp, const QMap<QString, QString>& data, QVector<Error>& errors);

#endif // FUNCTIONS_H
