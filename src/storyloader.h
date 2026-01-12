#ifndef STORYLOADER_H
#define STORYLOADER_H

#include <QString>
#include <QMap>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include "storynode.h"

class StoryLoader
{
public:
    static QMap<QString, StoryNode*> loadFromJson(const QString &filePath, QString &errorMsg);
    static QMap<QString, StoryNode*> loadFromMultipleJson(const QStringList &filePaths, QString &errorMsg);
    static QString getStartNodeId(const QString &filePath, QString &errorMsg);
    static QString getStoryTitle(const QString &filePath, QString &errorMsg);

private:
    static StoryNode* parseNode(const QJsonObject &nodeObj);
    static Choice* parseChoice(const QJsonObject &choiceObj);
};

#endif
