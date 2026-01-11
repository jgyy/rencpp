#include "gameengine.h"
#include "storyloader.h"
#include <QDebug>

GameEngine::GameEngine(QObject *parent)
    : QObject(parent), m_currentNode(nullptr)
{
}

GameEngine::~GameEngine()
{
    clearStory();
}

QString GameEngine::currentText() const
{
    if (m_currentNode) {
        return m_currentNode->text();
    }
    return QString();
}

QVariantList GameEngine::choices() const
{
    QVariantList result;
    if (m_currentNode) {
        const QList<Choice*> &choices = m_currentNode->choices();
        for (Choice *choice : choices) {
            QVariantMap choiceMap;
            choiceMap["text"] = choice->text();
            result.append(choiceMap);
        }
    }
    return result;
}

bool GameEngine::canGoBack() const
{
    return !m_history.isEmpty();
}

bool GameEngine::isGameEnded() const
{
    return m_currentNode && m_currentNode->isEndNode();
}

void GameEngine::loadStory(const QString &filePath)
{
    clearStory();

    QString errorMsg;
    m_storyNodes = StoryLoader::loadFromJson(filePath, errorMsg);

    if (!errorMsg.isEmpty()) {
        qWarning() << "Error loading story:" << errorMsg;
        emit errorOccurred(errorMsg);
        return;
    }

    m_startNodeId = StoryLoader::getStartNodeId(filePath, errorMsg);
    if (!errorMsg.isEmpty()) {
        qWarning() << "Error getting start node:" << errorMsg;
        emit errorOccurred(errorMsg);
        return;
    }

    if (m_storyNodes.contains(m_startNodeId)) {
        m_currentNode = m_storyNodes[m_startNodeId];
        m_history.clear();
        emit currentTextChanged();
        emit choicesChanged();
        emit canGoBackChanged();
    } else {
        errorMsg = "Start node not found: " + m_startNodeId;
        emit errorOccurred(errorMsg);
    }
}

void GameEngine::makeChoice(int choiceIndex)
{
    if (!m_currentNode || choiceIndex < 0) {
        return;
    }

    const QList<Choice*> &choices = m_currentNode->choices();
    if (choiceIndex >= choices.size()) {
        return;
    }

    m_history.push(m_currentNode->id());

    Choice *choice = choices[choiceIndex];
    QString targetNodeId = choice->targetNodeId();

    if (m_storyNodes.contains(targetNodeId)) {
        StoryNode *nextNode = m_storyNodes[targetNodeId];
        updateCurrentNode(nextNode);
    } else {
        qWarning() << "Target node not found:" << targetNodeId;
        emit errorOccurred("Invalid choice: target node not found");
    }
}

void GameEngine::goBack()
{
    if (!m_history.isEmpty()) {
        QString previousNodeId = m_history.pop();
        if (m_storyNodes.contains(previousNodeId)) {
            StoryNode *previousNode = m_storyNodes[previousNodeId];
            updateCurrentNode(previousNode);
        }
    }
}

void GameEngine::restart()
{
    if (!m_startNodeId.isEmpty() && m_storyNodes.contains(m_startNodeId)) {
        m_currentNode = m_storyNodes[m_startNodeId];
        m_history.clear();
        emit currentTextChanged();
        emit choicesChanged();
        emit canGoBackChanged();
    }
}

void GameEngine::updateCurrentNode(StoryNode *node)
{
    if (node != m_currentNode) {
        m_currentNode = node;
        emit currentTextChanged();
        emit choicesChanged();

        bool oldCanGoBack = m_history.isEmpty();
        bool newCanGoBack = !m_history.isEmpty();
        if (oldCanGoBack != newCanGoBack) {
            emit canGoBackChanged();
        }

        if (m_currentNode->isEndNode()) {
            emit gameEnded(m_currentNode->text());
        }
    }
}

void GameEngine::clearStory()
{
    m_currentNode = nullptr;
    m_startNodeId.clear();
    m_history.clear();

    for (StoryNode *node : m_storyNodes) {
        delete node;
    }
    m_storyNodes.clear();
}
