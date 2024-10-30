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
    QVector<Error> errors;


    QMap<QString, QString> dataContent = getJsonData(dataFilePath, errors);

    QStringList templateContent = getFileData(templateFilePath, errors); // Use the correct function here
    if (errors.size() > 0) {
        for (const auto& error : errors){
            outputError(error);
        }
        return 0;
    }


    QStringList generatedEmails = generateEmail(templateContent, dataContent, errors);

    if (errors.size() > 0) {
        for (const auto& error : errors){
            outputError(error);
        }
        return 0;
    }

    QString outputFilePath = getFileLocation("generatedEmails.txt");

    writeOutput(outputFilePath, generatedEmails, errors);
    if (errors.size() > 0) {
        for (const auto& error : errors){
            outputError(error);
        }
    }
    return 0;
}

/*
 getJsonData(dataFilePath) :: HAS ERROR
        } else {
        >>>> qDebug() << "Failed to parse JSON or JSON is not an object in file:" << filePath;
        }

...

>>>> generateEmail(templateContent, dataContent)
 */



