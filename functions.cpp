#include "functions.h"
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
#include <QRegularExpression>
#include <QMap>




void outputError(const Error& error) {
    if (error.type == FAILED_TO_OPEN_FILE) {
        qDebug() << "Failed to open a file: " << error.data << "\n";
    }
    else if(error.type == FAILED_TO_PARSE_JSON_FILE){
        qDebug() << "Failed to open a file: " << error.data << "\n";
    }
    else if(error.type == UNKNOWN_PLACEHOLDER){
         qDebug() << "Unknown placeholder" << error.data << "\n";
    }
}




void writeOutput(const QString& filePath, const QStringList& lines, QVector<Error>& errors) {
    QFile outputFile(filePath);
    if (outputFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&outputFile);
        for (const QString& line : lines)
            stream << line << '\n';
        outputFile.close();
    } else {
        errors.push_back({FAILED_TO_OPEN_FILE, filePath});
    }
}

QString getFileLocation(const QString& path) {
    return QDir::cleanPath(QDir::current().absoluteFilePath(path));
}


QMap<QString, QString> getJsonData(const QString& filePath, QVector<Error>& errors) {
    QFile file(filePath);
    QMap<QString, QString> dataMap;
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QJsonDocument document = QJsonDocument::fromJson(file.readAll());
        if (!document.isNull() && document.isObject()) {
            QJsonObject jsonObject = document.object();
            for (const QString& key : jsonObject.keys()) {
                dataMap[key] = jsonObject.value(key).toString();
            }
        } else {
            errors.push_back({FAILED_TO_PARSE_JSON_FILE, filePath});
        }
    } else {
        errors.push_back({FAILED_TO_OPEN_FILE, filePath});
    }
    return dataMap;
}


QStringList getFileData(const QString& filePath, QVector<Error>& errors) {
    QFile file(filePath);
    QStringList lines;
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            lines.append(in.readLine());
        }
    } else {
        errors.push_back({FAILED_TO_OPEN_FILE, filePath});
    }
    return lines;
}


QStringList generateEmail(const QStringList& temp, const QMap<QString, QString>& data, QVector<Error>& errors) {
    QStringList generated = temp;
    QRegularExpression regex("#([^#\\n]*)#"); // Matches placeholders like #name#
    for (QString& line : generated) {
        QRegularExpressionMatchIterator it = regex.globalMatch(line);
        while (it.hasNext()) {
            QRegularExpressionMatch match = it.next();
            QString key = match.captured(1);
            if (data.contains(key)) {
                line.replace(match.captured(0), data[key]);
            } else {
                // errors.push_back({"Placeholder not found in data", match.captured(0)});
                errors.push_back({UNKNOWN_PLACEHOLDER, match.captured(0)});
            }
        }
    }
    return generated;
}







// \n,\t,\0,\",\\
