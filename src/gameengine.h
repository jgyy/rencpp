#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QObject>
#include <QString>
#include <QVariant>
#include <QVariantList>
#include <QStack>
#include <QMap>
#include <QSet>
#include <QElapsedTimer>
#include <QTimer>
#include <QPair>
#include "storynode.h"

struct StateChange {
    QMap<QString, int> statChanges;
    QStringList itemsGained;
};

class GameEngine : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString currentText READ currentText NOTIFY currentTextChanged)
    Q_PROPERTY(QVariantList choices READ choices NOTIFY choicesChanged)
    Q_PROPERTY(bool canGoBack READ canGoBack NOTIFY canGoBackChanged)
    Q_PROPERTY(bool isGameEnded READ isGameEnded NOTIFY gameEnded)

    Q_PROPERTY(int health READ health NOTIFY healthChanged)
    Q_PROPERTY(int strength READ strength NOTIFY strengthChanged)
    Q_PROPERTY(int intelligence READ intelligence NOTIFY intelligenceChanged)
    Q_PROPERTY(int wisdom READ wisdom NOTIFY wisdomChanged)

    Q_PROPERTY(int choicesMade READ choicesMade NOTIFY choicesMadeChanged)
    Q_PROPERTY(int nodesVisited READ nodesVisited NOTIFY nodesVisitedChanged)
    Q_PROPERTY(int playTimeSeconds READ playTimeSeconds NOTIFY playTimeChanged)

    Q_PROPERTY(QStringList inventory READ inventory NOTIFY inventoryChanged)

    Q_PROPERTY(QStringList endingsFound READ endingsFound NOTIFY endingsFoundChanged)

public:
    explicit GameEngine(QObject *parent = nullptr);
    ~GameEngine();

    QString currentText() const;
    QString currentNodeId() const;
    QString storyTitle() const;
    QVariantList choices() const;
    bool canGoBack() const;
    bool isGameEnded() const;

    int health() const;
    int strength() const;
    int intelligence() const;
    int wisdom() const;

    int choicesMade() const;
    int nodesVisited() const;
    int playTimeSeconds() const;

    QStringList inventory() const;

    QStringList endingsFound() const;

    bool isChoicePreviouslySelected(const QString &nodeId, int choiceIndex) const;

    Q_INVOKABLE void loadStory(const QString &filePath);
    Q_INVOKABLE void makeChoice(int choiceIndex);
    Q_INVOKABLE void goBack();
    Q_INVOKABLE void restart();

signals:
    void currentTextChanged();
    void choicesChanged();
    void canGoBackChanged();
    void gameEnded(const QString &endingText);
    void gameOver(const QString &reason);
    void errorOccurred(const QString &error);

    void healthChanged();
    void strengthChanged();
    void intelligenceChanged();
    void wisdomChanged();

    void choicesMadeChanged();
    void nodesVisitedChanged();
    void playTimeChanged();

    void inventoryChanged();

    void endingsFoundChanged();

private slots:
    void updatePlayTime();

private:
    void updateCurrentNode(StoryNode *node);
    void clearStory();
    void applyStatChanges(const QMap<QString, int> &changes);
    void addItems(const QStringList &items);
    void recordEnding(const QString &endingId);
    void markChoiceAsSelected(const QString &nodeId, int choiceIndex);

    QMap<QString, StoryNode*> m_storyNodes;
    StoryNode* m_currentNode;
    QString m_startNodeId;
    QString m_storyTitle;
    QStack<QString> m_history;
    QStack<StateChange> m_stateHistory;

    int m_health = 100;
    int m_strength = 10;
    int m_intelligence = 10;
    int m_wisdom = 10;

    int m_choicesMade = 0;
    QSet<QString> m_visitedNodes;
    int m_playTimeSeconds = 0;
    QElapsedTimer m_playTimer;

    QStringList m_inventory;

    QStringList m_endingsFound;

    QSet<QString> m_selectedChoices;

    QTimer *m_playTimerUpdate;
};

#endif
