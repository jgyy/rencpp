#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QObject>
#include <QString>
#include <QVariant>
#include <QVariantList>
#include <QStack>
#include <QMap>
#include "storynode.h"

class GameEngine : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString currentText READ currentText NOTIFY currentTextChanged)
    Q_PROPERTY(QVariantList choices READ choices NOTIFY choicesChanged)
    Q_PROPERTY(bool canGoBack READ canGoBack NOTIFY canGoBackChanged)
    Q_PROPERTY(bool isGameEnded READ isGameEnded NOTIFY gameEnded)

public:
    explicit GameEngine(QObject *parent = nullptr);
    ~GameEngine();

    QString currentText() const;
    QVariantList choices() const;
    bool canGoBack() const;
    bool isGameEnded() const;

    Q_INVOKABLE void loadStory(const QString &filePath);
    Q_INVOKABLE void makeChoice(int choiceIndex);
    Q_INVOKABLE void goBack();
    Q_INVOKABLE void restart();

signals:
    void currentTextChanged();
    void choicesChanged();
    void canGoBackChanged();
    void gameEnded(const QString &endingText);
    void errorOccurred(const QString &error);

private:
    void updateCurrentNode(StoryNode *node);
    void clearStory();

    QMap<QString, StoryNode*> m_storyNodes;
    StoryNode* m_currentNode;
    QString m_startNodeId;
    QStack<QString> m_history;
};

#endif
