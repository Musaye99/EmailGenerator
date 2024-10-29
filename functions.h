#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <QString>
#include <QStringList>
#include <QMap>
#include <QRegularExpression> // Ensure this include is present if it's used

// Function declarations
void writeOutput(const QString& filePath, const QStringList& lines);
QString getFileLocation(const QString& path);
QMap<QString, QString> getJsonData(const QString& filePath);
QStringList getFileData(const QString& filePath);
QStringList generateEmail(const QStringList& temp, const QMap<QString, QString>& data);

#endif // FUNCTIONS_H
