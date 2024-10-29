#include "functions.h"
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
#include <QRegularExpression>
#include <QMap>

void writeOutput(const QString& filePath, const QStringList& lines) {
    QFile outputFile(filePath);
    if (outputFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&outputFile);
        for (const QString& line : lines)
            stream << line << '\n';
        outputFile.close();
    }
}

QString getFileLocation(const QString& path) {
    return QDir::cleanPath(QDir::current().absoluteFilePath(path));
}

QMap<QString, QString> getJsonData(const QString& filePath) {
    QFile file(filePath);
    QMap<QString, QString> dataMap;
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QJsonDocument document = QJsonDocument::fromJson(file.readAll());
        if (!document.isNull() && document.isObject()) {
            QJsonObject jsonObject = document.object();
            for (const QString& key : jsonObject.keys()) {
                dataMap[key] = jsonObject.value(key).toString();
            }
        }
    }
    return dataMap;
}

QStringList getFileData(const QString& filePath) {
    QFile file(filePath);
    QStringList lines;
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            lines.append(in.readLine());
        }
    }
    return lines;
}


QStringList generateEmail(const QStringList& temp, const QMap<QString, QString>& data) {
    QStringList generated = temp;
    // Updated regular expression to match new placeholder format
    QRegularExpression regex("#(\\w+)#");  // Matches placeholders like #name#
    for (QString& line : generated) {
        QRegularExpressionMatchIterator it = regex.globalMatch(line);
        while (it.hasNext()) {
            QRegularExpressionMatch match = it.next();
            QString key = match.captured(1);
            if (data.contains(key)) {
                line.replace(match.captured(0), data[key]);
            } else {
                qDebug() << "Placeholder not found in data:" << match.captured(0);
            }
        }
    }
    return generated;
}
