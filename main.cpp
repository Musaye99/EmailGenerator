#include <QCoreApplication>
#include <QDebug>
#include "functions.h"

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    if (argc != 3) {
        qDebug() << "Incorrect number of arguments. Usage: program templateFile dataFile";
        return 1;
    }

    QString templateFilePath = getFileLocation(argv[1]);
    QString dataFilePath = getFileLocation(argv[2]);

    QMap<QString, QString> dataContent = getJsonData(dataFilePath);
    QStringList templateContent = getFileData(templateFilePath); // Use the correct function here

    QStringList generatedEmails = generateEmail(templateContent, dataContent);

    QString outputFilePath = getFileLocation("generatedEmails.txt");
    writeOutput(outputFilePath, generatedEmails);

    return 0;
}
