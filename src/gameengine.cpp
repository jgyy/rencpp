#include "gameengine.h"
#include "storyloader.h"
#include <QDebug>
#include <QTimer>

GameEngine::GameEngine(QObject *parent)
    : QObject(parent), m_currentNode(nullptr),
      m_playTimerUpdate(new QTimer(this)) {
  connect(m_playTimerUpdate, &QTimer::timeout, this,
          &GameEngine::updatePlayTime);
}

GameEngine::~GameEngine() { clearStory(); }

QString GameEngine::currentText() const {
  if (m_currentNode) {
    return m_currentNode->text();
  }
  return QString();
}

QString GameEngine::currentNodeId() const {
  if (m_currentNode) {
    return m_currentNode->id();
  }
  return QString();
}

QString GameEngine::storyTitle() const { return m_storyTitle; }

QVariantList GameEngine::choices() const {
  QVariantList result;
  if (m_currentNode) {
    const QList<Choice *> &choices = m_currentNode->choices();
    for (Choice *choice : choices) {
      QVariantMap choiceMap;
      choiceMap["text"] = choice->text();
      result.append(choiceMap);
    }
  }
  return result;
}

bool GameEngine::canGoBack() const { return !m_history.isEmpty(); }

bool GameEngine::isGameEnded() const {
  return m_currentNode && m_currentNode->isEndNode();
}

int GameEngine::health() const { return m_health; }

int GameEngine::strength() const { return m_strength; }

int GameEngine::intelligence() const { return m_intelligence; }

int GameEngine::wisdom() const { return m_wisdom; }

int GameEngine::choicesMade() const { return m_choicesMade; }

int GameEngine::nodesVisited() const { return m_visitedNodes.size(); }

int GameEngine::playTimeSeconds() const { return m_playTimeSeconds; }

QStringList GameEngine::inventory() const { return m_inventory; }

QStringList GameEngine::endingsFound() const { return m_endingsFound; }

bool GameEngine::isChoicePreviouslySelected(const QString &nodeId,
                                            int choiceIndex) const {
  QString key = nodeId + ":" + QString::number(choiceIndex);
  return m_selectedChoices.contains(key);
}

void GameEngine::loadStory(const QString &filePath) {
  clearStory();

  QString errorMsg;
  QStringList storyFiles;
  storyFiles << ":/stories/story_part1.json" << ":/stories/story_part2.json";
  m_storyNodes = StoryLoader::loadFromMultipleJson(storyFiles, errorMsg);

  if (!errorMsg.isEmpty()) {
    qWarning() << "Error loading story:" << errorMsg;
    emit errorOccurred(errorMsg);
    return;
  }

  m_startNodeId =
      StoryLoader::getStartNodeId(":/stories/story_part1.json", errorMsg);
  if (!errorMsg.isEmpty()) {
    qWarning() << "Error getting start node:" << errorMsg;
    emit errorOccurred(errorMsg);
    return;
  }

  m_storyTitle =
      StoryLoader::getStoryTitle(":/stories/story_part1.json", errorMsg);
  if (m_storyTitle.isEmpty()) {
    m_storyTitle = "Text Adventure Game";
  }

  if (m_storyNodes.contains(m_startNodeId)) {
    m_currentNode = m_storyNodes[m_startNodeId];
    m_history.clear();

    m_playTimeSeconds = 0;
    m_playTimer.start();
    m_playTimerUpdate->start(1000);

    emit currentTextChanged();
    emit choicesChanged();
    emit canGoBackChanged();
  } else {
    errorMsg = "Start node not found: " + m_startNodeId;
    emit errorOccurred(errorMsg);
  }
}

void GameEngine::makeChoice(int choiceIndex) {
  if (!m_currentNode || choiceIndex < 0) {
    return;
  }

  const QList<Choice *> &choices = m_currentNode->choices();
  if (choiceIndex >= choices.size()) {
    return;
  }

  m_history.push(m_currentNode->id());

  Choice *choice = choices[choiceIndex];

  markChoiceAsSelected(m_currentNode->id(), choiceIndex);

  StateChange change;
  change.statChanges = choice->statChanges();
  change.itemsGained = choice->itemsGained();
  m_stateHistory.push(change);

  applyStatChanges(choice->statChanges());
  addItems(choice->itemsGained());

  m_choicesMade++;
  emit choicesMadeChanged();

  QString targetNodeId = choice->targetNodeId();

  if (m_storyNodes.contains(targetNodeId)) {
    StoryNode *nextNode = m_storyNodes[targetNodeId];
    updateCurrentNode(nextNode);
  } else {
    qWarning() << "Target node not found:" << targetNodeId;
    emit errorOccurred("Invalid choice: target node not found");
  }
}

void GameEngine::goBack() {
  if (!m_history.isEmpty() && !m_stateHistory.isEmpty()) {
    StateChange lastChange = m_stateHistory.pop();

    for (auto it = lastChange.statChanges.constBegin();
         it != lastChange.statChanges.constEnd(); ++it) {
      const QString &statName = it.key();
      int change = it.value();

      if (statName == "health") {
        m_health = qBound(0, m_health - change, 100);
        emit healthChanged();
      } else if (statName == "strength") {
        m_strength -= change;
        emit strengthChanged();
      } else if (statName == "intelligence") {
        m_intelligence -= change;
        emit intelligenceChanged();
      } else if (statName == "wisdom") {
        m_wisdom -= change;
        emit wisdomChanged();
      }
    }

    for (const QString &item : lastChange.itemsGained) {
      m_inventory.removeAll(item);
    }
    emit inventoryChanged();

    m_choicesMade--;
    emit choicesMadeChanged();

    QString previousNodeId = m_history.pop();
    if (m_storyNodes.contains(previousNodeId)) {
      StoryNode *previousNode = m_storyNodes[previousNodeId];
      updateCurrentNode(previousNode);
    }
  }
}

void GameEngine::restart() {
  if (!m_startNodeId.isEmpty() && m_storyNodes.contains(m_startNodeId)) {
    m_currentNode = m_storyNodes[m_startNodeId];
    m_history.clear();
    m_stateHistory.clear();

    m_health = 100;
    m_strength = 10;
    m_intelligence = 10;
    m_wisdom = 10;
    m_choicesMade = 0;
    m_visitedNodes.clear();
    m_inventory.clear();
    m_playTimeSeconds = 0;

    m_playTimer.restart();

    emit healthChanged();
    emit strengthChanged();
    emit intelligenceChanged();
    emit wisdomChanged();
    emit choicesMadeChanged();
    emit nodesVisitedChanged();
    emit inventoryChanged();
    emit playTimeChanged();
    emit currentTextChanged();
    emit choicesChanged();
    emit canGoBackChanged();
  }
}

void GameEngine::updateCurrentNode(StoryNode *node) {
  if (node != m_currentNode) {
    m_currentNode = node;

    if (!m_visitedNodes.contains(m_currentNode->id())) {
      m_visitedNodes.insert(m_currentNode->id());
      emit nodesVisitedChanged();
    }

    if (m_currentNode->isEndNode()) {
      recordEnding(m_currentNode->id());
    }

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

void GameEngine::clearStory() {
  m_currentNode = nullptr;
  m_startNodeId.clear();
  m_history.clear();
  m_stateHistory.clear();

  for (StoryNode *node : m_storyNodes) {
    delete node;
  }
  m_storyNodes.clear();
}

void GameEngine::applyStatChanges(const QMap<QString, int> &changes) {
  for (auto it = changes.constBegin(); it != changes.constEnd(); ++it) {
    const QString &statName = it.key();
    int change = it.value();

    if (statName == "health") {
      m_health = qBound(0, m_health + change, 100);
      emit healthChanged();
    } else if (statName == "strength") {
      m_strength += change;
      emit strengthChanged();
    } else if (statName == "intelligence") {
      m_intelligence += change;
      emit intelligenceChanged();
    } else if (statName == "wisdom") {
      m_wisdom += change;
      emit wisdomChanged();
    }
  }
}

void GameEngine::addItems(const QStringList &items) {
  if (!items.isEmpty()) {
    m_inventory.append(items);

    for (const QString &item : items) {
      if (item.contains("Crystal", Qt::CaseInsensitive)) {
        m_intelligence += 2;
        emit intelligenceChanged();
      }
      if (item.contains("Sword", Qt::CaseInsensitive)) {
        m_strength += 2;
        emit strengthChanged();
      }
      if (item.contains("Jade", Qt::CaseInsensitive)) {
        m_wisdom += 2;
        emit wisdomChanged();
      }
      if (item.contains("Celestial", Qt::CaseInsensitive)) {
        m_strength += 1;
        m_intelligence += 1;
        m_wisdom += 1;
        emit strengthChanged();
        emit intelligenceChanged();
        emit wisdomChanged();
      }
      if (item.contains("Token", Qt::CaseInsensitive)) {
        m_health += 5;
        emit healthChanged();
      }
      if (item.contains("Blessing", Qt::CaseInsensitive)) {
        m_wisdom += 3;
        emit wisdomChanged();
      }
      if (item.contains("Manual", Qt::CaseInsensitive)) {
        m_intelligence += 3;
        emit intelligenceChanged();
      }
    }

    emit inventoryChanged();
  }
}

void GameEngine::recordEnding(const QString &endingId) {
  if (!m_endingsFound.contains(endingId)) {
    m_endingsFound.append(endingId);
    emit endingsFoundChanged();
  }
}

void GameEngine::updatePlayTime() {
  m_playTimeSeconds = m_playTimer.elapsed() / 1000;
  emit playTimeChanged();
}

void GameEngine::markChoiceAsSelected(const QString &nodeId, int choiceIndex) {
  QString key = nodeId + ":" + QString::number(choiceIndex);
  m_selectedChoices.insert(key);
}
