#include "storyloader.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

QMap<QString, StoryNode*> StoryLoader::loadFromJson(const QString &filePath, QString &errorMsg)
{
    QMap<QString, StoryNode*> storyNodes;
    errorMsg.clear();

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        errorMsg = "Failed to open story file: " + filePath;
        return storyNodes;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isObject()) {
        errorMsg = "Invalid JSON format in story file";
        return storyNodes;
    }

    QJsonObject root = doc.object();
    QJsonObject story = root["story"].toObject();

    if (story.isEmpty()) {
        errorMsg = "No 'story' object found in JSON file";
        return storyNodes;
    }

    QJsonArray nodesArray = story["nodes"].toArray();
    for (const QJsonValue &nodeValue : nodesArray) {
        QJsonObject nodeObj = nodeValue.toObject();
        StoryNode *node = parseNode(nodeObj);
        if (node) {
            storyNodes[node->id()] = node;
        }
    }

    if (storyNodes.isEmpty()) {
        errorMsg = "No valid nodes found in story file";
    }

    return storyNodes;
}

QString StoryLoader::getStartNodeId(const QString &filePath, QString &errorMsg)
{
    errorMsg.clear();

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        errorMsg = "Failed to open story file: " + filePath;
        return QString();
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isObject()) {
        errorMsg = "Invalid JSON format in story file";
        return QString();
    }

    QJsonObject root = doc.object();
    QJsonObject story = root["story"].toObject();

    if (story.isEmpty()) {
        errorMsg = "No 'story' object found in JSON file";
        return QString();
    }

    QString startNode = story["startNode"].toString();
    if (startNode.isEmpty()) {
        errorMsg = "No 'startNode' defined in story";
    }

    return startNode;
}

StoryNode* StoryLoader::parseNode(const QJsonObject &nodeObj)
{
    QString id = nodeObj["id"].toString();
    QString text = nodeObj["text"].toString();

    if (id.isEmpty() || text.isEmpty()) {
        qWarning() << "Invalid node: missing id or text";
        return nullptr;
    }

    StoryNode *node = new StoryNode(id, text);

    QJsonArray choicesArray = nodeObj["choices"].toArray();
    for (const QJsonValue &choiceValue : choicesArray) {
        QJsonObject choiceObj = choiceValue.toObject();
        Choice *choice = parseChoice(choiceObj);
        if (choice) {
            node->addChoice(choice);
        }
    }

    return node;
}

Choice* StoryLoader::parseChoice(const QJsonObject &choiceObj)
{
    QString text = choiceObj["text"].toString();
    QString target = choiceObj["target"].toString();

    if (text.isEmpty() || target.isEmpty()) {
        qWarning() << "Invalid choice: missing text or target";
        return nullptr;
    }

    return new Choice(text, target);
}
