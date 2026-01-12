#include "mainwindow.h"
#include <QApplication>
#include <QGuiApplication>
#include <QKeyEvent>
#include <QMessageBox>
#include <QScreen>
#include <QScrollArea>
#include <QScrollBar>
#include <QWidget>

MainWindow::MainWindow(GameEngine *gameEngine, QWidget *parent)
    : QMainWindow(parent), m_gameEngine(gameEngine), m_statsLabel(nullptr),
      m_progressLabel(nullptr), m_inventoryLabel(nullptr),
      m_achievementsLabel(nullptr), m_animationGroup(nullptr),
      m_storyFadeAnimation(nullptr) {
  QScreen *screen = QGuiApplication::primaryScreen();
  QRect screenGeometry = screen->availableGeometry();
  qreal dpiScale = screen->logicalDotsPerInch() / 96.0;

  int windowWidth = static_cast<int>(screenGeometry.width() * 0.85);
  int windowHeight = static_cast<int>(screenGeometry.height() * 0.85);
  int windowX = screenGeometry.x() + (screenGeometry.width() - windowWidth) / 2;
  int windowY =
      screenGeometry.y() + (screenGeometry.height() - windowHeight) / 2;

  QWidget *centralWidget = new QWidget(this);
  setCentralWidget(centralWidget);

  int spacing = static_cast<int>(10 * dpiScale);
  int margins = static_cast<int>(15 * dpiScale);

  QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
  mainLayout->setSpacing(spacing);
  mainLayout->setContentsMargins(margins, margins, margins, margins);

  int statsSpacing = static_cast<int>(20 * dpiScale);
  int statsPadding = static_cast<int>(10 * dpiScale);
  int smallPadding = static_cast<int>(5 * dpiScale);
  int baseFontSize = static_cast<int>(14 * dpiScale);

  QHBoxLayout *statsLayout = new QHBoxLayout();
  statsLayout->setSpacing(statsSpacing);
  statsLayout->setContentsMargins(statsPadding, smallPadding, statsPadding,
                                  smallPadding);

  m_statsLabel = new QLabel("Qi Vitality: 100 | Spiritual Power: 10 | "
                            "Comprehension: 10 | Fortune: 10",
                            this);
  m_statsLabel->setStyleSheet(QString("QLabel {"
                                      "  color: #FFD700;"
                                      "  font-weight: bold;"
                                      "  font-size: %1px;"
                                      "}")
                                  .arg(baseFontSize));
  statsLayout->addWidget(m_statsLabel);

  m_progressLabel = new QLabel("Choices: 0 | Nodes: 1 | Time: 0:00", this);
  m_progressLabel->setStyleSheet(QString("QLabel {"
                                         "  color: #87CEEB;"
                                         "  font-weight: bold;"
                                         "  font-size: %1px;"
                                         "}")
                                     .arg(baseFontSize));
  statsLayout->addWidget(m_progressLabel);

  m_inventoryLabel = new QLabel("Items: none", this);
  m_inventoryLabel->setWordWrap(true);
  m_inventoryLabel->setStyleSheet(QString("QLabel {"
                                          "  color: #90EE90;"
                                          "  font-weight: bold;"
                                          "  font-size: %1px;"
                                          "}")
                                      .arg(baseFontSize));
  statsLayout->addWidget(m_inventoryLabel);

  m_achievementsLabel = new QLabel("Endings: 0", this);
  m_achievementsLabel->setStyleSheet(QString("QLabel {"
                                             "  color: #FF69B4;"
                                             "  font-weight: bold;"
                                             "  font-size: %1px;"
                                             "}")
                                         .arg(baseFontSize));
  statsLayout->addWidget(m_achievementsLabel);

  QFrame *statsFrame = new QFrame(this);
  statsFrame->setLayout(statsLayout);
  statsFrame->setStyleSheet("QFrame {"
                            "  background-color: #0a1420;"
                            "  border: 1px solid #3d5a80;"
                            "  border-radius: 3px;"
                            "}");
  mainLayout->addWidget(statsFrame, 0);

  int titleFontSize = static_cast<int>(28 * dpiScale);
  int storyFontSize = static_cast<int>(16 * dpiScale);
  int titlePadding = static_cast<int>(10 * dpiScale);
  int storyPadding = static_cast<int>(10 * dpiScale);

  m_titleLabel = new QLabel(this);
  m_titleLabel->setStyleSheet(QString("QLabel {"
                                      "  color: #ffffff;"
                                      "  font-size: %1px;"
                                      "  font-weight: bold;"
                                      "  padding: %2px;"
                                      "}")
                                  .arg(titleFontSize)
                                  .arg(titlePadding));
  mainLayout->addWidget(m_titleLabel);

  m_storyDisplay = new QTextEdit(this);
  m_storyDisplay->setReadOnly(true);
  m_storyDisplay->setStyleSheet(QString("QTextEdit {"
                                        "  background-color: #1a2a3a;"
                                        "  color: #e8e8e8;"
                                        "  border: 2px solid #3d5a80;"
                                        "  border-radius: 5px;"
                                        "  padding: %1px;"
                                        "  font-family: Georgia;"
                                        "  font-size: %2px;"
                                        "}")
                                    .arg(storyPadding)
                                    .arg(storyFontSize));
  mainLayout->addWidget(m_storyDisplay, 1);

  m_choicesContainer = new QWidget(this);
  m_choicesLayout = new QVBoxLayout(m_choicesContainer);
  int choicesSpacing = static_cast<int>(8 * dpiScale);
  m_choicesLayout->setSpacing(choicesSpacing);

  QScrollArea *choicesScroll = new QScrollArea(this);
  choicesScroll->setWidget(m_choicesContainer);
  choicesScroll->setWidgetResizable(true);
  choicesScroll->setStyleSheet("QScrollArea {"
                               "  background-color: #0f1a25;"
                               "  border: 1px solid #3d5a80;"
                               "  border-radius: 5px;"
                               "}");
  mainLayout->addWidget(choicesScroll, 0);

  QHBoxLayout *controlLayout = new QHBoxLayout();
  int controlSpacing = static_cast<int>(10 * dpiScale);
  controlLayout->setSpacing(controlSpacing);

  int buttonPaddingV = static_cast<int>(8 * dpiScale);
  int buttonPaddingH = static_cast<int>(15 * dpiScale);
  int buttonFontSize = static_cast<int>(12 * dpiScale);

  m_backButton = new QPushButton("Back", this);
  m_backButton->setStyleSheet(QString("QPushButton {"
                                      "  background-color: #3d5a80;"
                                      "  color: #ffffff;"
                                      "  border: 1px solid #1a2a3a;"
                                      "  border-radius: 3px;"
                                      "  padding: %1px %2px;"
                                      "  font-size: %3px;"
                                      "}"
                                      "QPushButton:hover:enabled {"
                                      "  background-color: #4a6a90;"
                                      "}"
                                      "QPushButton:disabled {"
                                      "  background-color: #1a2a3a;"
                                      "  color: #666666;"
                                      "}")
                                  .arg(buttonPaddingV)
                                  .arg(buttonPaddingH)
                                  .arg(buttonFontSize));
  connect(m_backButton, &QPushButton::clicked, this,
          &MainWindow::onBackClicked);
  controlLayout->addWidget(m_backButton);

  m_restartButton = new QPushButton("Restart", this);
  m_restartButton->setStyleSheet(QString("QPushButton {"
                                         "  background-color: #3d5a80;"
                                         "  color: #ffffff;"
                                         "  border: 1px solid #1a2a3a;"
                                         "  border-radius: 3px;"
                                         "  padding: %1px %2px;"
                                         "  font-size: %3px;"
                                         "}"
                                         "QPushButton:hover {"
                                         "  background-color: #4a6a90;"
                                         "}")
                                     .arg(buttonPaddingV)
                                     .arg(buttonPaddingH)
                                     .arg(buttonFontSize));
  connect(m_restartButton, &QPushButton::clicked, this,
          &MainWindow::onRestartClicked);
  controlLayout->addWidget(m_restartButton);

  controlLayout->addStretch();

  mainLayout->addLayout(controlLayout);

  int endingPadding = static_cast<int>(10 * dpiScale);
  m_endingLabel = new QLabel("", this);
  m_endingLabel->setStyleSheet(QString("QLabel {"
                                       "  color: #90EE90;"
                                       "  font-weight: bold;"
                                       "  padding: %1px;"
                                       "}")
                                   .arg(endingPadding));
  m_endingLabel->setVisible(false);
  mainLayout->addWidget(m_endingLabel);

  setWindowTitle("Text Adventure - The Mysterious Room");
  setGeometry(windowX, windowY, windowWidth, windowHeight);
  setStyleSheet("QMainWindow {"
                "  background-color: #0f1a25;"
                "}");

  connect(m_gameEngine, &GameEngine::currentTextChanged, this,
          &MainWindow::onStoryTextChanged);
  connect(m_gameEngine, &GameEngine::choicesChanged, this,
          &MainWindow::onChoicesChanged);
  connect(m_gameEngine, &GameEngine::canGoBackChanged, this,
          &MainWindow::onCanGoBackChanged);
  connect(m_gameEngine, &GameEngine::gameEnded, this, &MainWindow::onGameEnded);
  connect(m_gameEngine, &GameEngine::gameOver, this, &MainWindow::onGameOver);
  connect(m_gameEngine, &GameEngine::errorOccurred, this,
          &MainWindow::onErrorOccurred);

  connect(m_gameEngine, &GameEngine::healthChanged, this,
          &MainWindow::onStatsChanged);
  connect(m_gameEngine, &GameEngine::strengthChanged, this,
          &MainWindow::onStatsChanged);
  connect(m_gameEngine, &GameEngine::intelligenceChanged, this,
          &MainWindow::onStatsChanged);
  connect(m_gameEngine, &GameEngine::wisdomChanged, this,
          &MainWindow::onStatsChanged);
  connect(m_gameEngine, &GameEngine::choicesMadeChanged, this,
          &MainWindow::onProgressChanged);
  connect(m_gameEngine, &GameEngine::nodesVisitedChanged, this,
          &MainWindow::onProgressChanged);
  connect(m_gameEngine, &GameEngine::playTimeChanged, this,
          &MainWindow::onProgressChanged);
  connect(m_gameEngine, &GameEngine::inventoryChanged, this,
          &MainWindow::onInventoryChanged);
  connect(m_gameEngine, &GameEngine::endingsFoundChanged, this,
          &MainWindow::onProgressChanged);

  m_gameEngine->loadStory(":/stories/story.json");
  m_titleLabel->setText(m_gameEngine->storyTitle());

  setFocusPolicy(Qt::StrongFocus);
  setFocus();
}

MainWindow::~MainWindow() {}

void MainWindow::onStoryTextChanged() {
  m_storyDisplay->setText(m_gameEngine->currentText());
  m_storyDisplay->verticalScrollBar()->setValue(0);
  animateStoryText();
}

void MainWindow::onChoicesChanged() {
  clearChoiceButtons();
  m_selectedChoiceIndex = 0;

  QScreen *screen = QGuiApplication::primaryScreen();
  qreal dpiScale = screen->logicalDotsPerInch() / 96.0;
  int choiceFontSize = static_cast<int>(16 * dpiScale);
  int choicePadding = static_cast<int>(12 * dpiScale);
  int choiceMinHeight = static_cast<int>(50 * dpiScale);

  const QVariantList &choices = m_gameEngine->choices();
  for (int i = 0; i < choices.size(); ++i) {
    QVariantMap choiceData = choices[i].toMap();
    QString choiceText = choiceData["text"].toString();

    QPushButton *choiceButton = new QPushButton(choiceText, this);

    bool wasPreviouslySelected = m_gameEngine->isChoicePreviouslySelected(
        m_gameEngine->currentNodeId(), i);

    if (wasPreviouslySelected) {
      choiceButton->setStyleSheet(QString("QPushButton {"
                                          "  background-color: #1a3a2a;"
                                          "  color: #90EE90;"
                                          "  border: 2px solid #2a5a4a;"
                                          "  border-radius: 5px;"
                                          "  padding: %1px;"
                                          "  font-size: %2px;"
                                          "  text-align: left;"
                                          "}"
                                          "QPushButton:hover {"
                                          "  background-color: #2a4a3a;"
                                          "}"
                                          "QPushButton:pressed {"
                                          "  background-color: #3a5a4a;"
                                          "}")
                                      .arg(choicePadding)
                                      .arg(choiceFontSize));
    } else {
      choiceButton->setStyleSheet(QString("QPushButton {"
                                          "  background-color: #2c4563;"
                                          "  color: #ffffff;"
                                          "  border: 2px solid #1a2a3a;"
                                          "  border-radius: 5px;"
                                          "  padding: %1px;"
                                          "  font-size: %2px;"
                                          "  text-align: left;"
                                          "}"
                                          "QPushButton:hover {"
                                          "  background-color: #3d5a80;"
                                          "}"
                                          "QPushButton:pressed {"
                                          "  background-color: #4a6a90;"
                                          "}")
                                      .arg(choicePadding)
                                      .arg(choiceFontSize));
    }
    choiceButton->setMinimumHeight(choiceMinHeight);
    choiceButton->setWindowOpacity(0.0);

    choiceButton->setProperty("choiceIndex", i);
    connect(choiceButton, &QPushButton::clicked, this,
            &MainWindow::onChoiceClicked);

    m_choicesLayout->addWidget(choiceButton);

    QPropertyAnimation *buttonFade =
        new QPropertyAnimation(choiceButton, "windowOpacity");
    buttonFade->setDuration(300);
    buttonFade->setStartValue(0.0);
    buttonFade->setEndValue(1.0);
    buttonFade->start(QAbstractAnimation::DeleteWhenStopped);
  }

  m_choicesLayout->addStretch();

  highlightSelectedChoice();
}

void MainWindow::onCanGoBackChanged() {
  m_backButton->setEnabled(m_gameEngine->canGoBack());
}

void MainWindow::onChoiceClicked() {
  QPushButton *button = qobject_cast<QPushButton *>(sender());
  if (button) {
    int choiceIndex = button->property("choiceIndex").toInt();
    m_gameEngine->makeChoice(choiceIndex);
    setFocus();
  }
}

void MainWindow::onGameEnded(const QString &endingText) {
  Q_UNUSED(endingText);
}

void MainWindow::onErrorOccurred(const QString &error) {
  QMessageBox::critical(this, "Story Error", error);
}

void MainWindow::onBackClicked() {
  m_gameEngine->goBack();
  setFocus();
}

void MainWindow::onRestartClicked() {
  m_endingLabel->setVisible(false);
  m_gameEngine->restart();
  setFocus();
}

void MainWindow::clearChoiceButtons() {
  while (QLayoutItem *item = m_choicesLayout->takeAt(0)) {
    if (QPushButton *button = qobject_cast<QPushButton *>(item->widget())) {
      delete button;
    }
    delete item;
  }
}

void MainWindow::onStatsChanged() {
  if (!m_statsLabel)
    return;

  int health = m_gameEngine->health();
  int strength = m_gameEngine->strength();
  int intelligence = m_gameEngine->intelligence();
  int wisdom = m_gameEngine->wisdom();

  if (m_lastHealth > 0 && health <= 0) {
    m_wasHealthZero = true;
  } else if (m_wasHealthZero && health > 0) {
    m_wasHealthZero = false;
  }
  m_lastHealth = health;

  m_statsLabel->setText(QString("Qi Vitality: %1 | Spiritual Power: %2 | "
                                "Comprehension: %3 | Fortune: %4")
                            .arg(health)
                            .arg(strength)
                            .arg(intelligence)
                            .arg(wisdom));
}

void MainWindow::onProgressChanged() {
  if (!m_progressLabel && !m_achievementsLabel)
    return;

  int choicesMade = m_gameEngine->choicesMade();
  int nodesVisited = m_gameEngine->nodesVisited();
  int playTimeSeconds = m_gameEngine->playTimeSeconds();
  int minutes = playTimeSeconds / 60;
  int seconds = playTimeSeconds % 60;

  if (m_progressLabel) {
    m_progressLabel->setText(QString("Choices: %1 | Nodes: %2 | Time: %3:%4")
                                 .arg(choicesMade)
                                 .arg(nodesVisited)
                                 .arg(minutes)
                                 .arg(seconds, 2, 10, QChar('0')));
  }

  if (m_achievementsLabel) {
    int endingsFound = m_gameEngine->endingsFound().size();
    m_achievementsLabel->setText(QString("Endings: %1").arg(endingsFound));
  }
}

void MainWindow::onInventoryChanged() {
  if (!m_inventoryLabel)
    return;

  QStringList inventory = m_gameEngine->inventory();
  if (inventory.isEmpty()) {
    m_inventoryLabel->setText("Items: none");
  } else {
    QString itemsText = "Items: ";
    QString currentLine = "";

    for (int i = 0; i < inventory.size(); ++i) {
      QString item = inventory[i];
      QString separator = (i < inventory.size() - 1) ? ", " : "";
      QString testLine =
          currentLine.isEmpty() ? item : currentLine + ", " + item;

      if (testLine.length() > 80 && !currentLine.isEmpty()) {
        itemsText += currentLine + "\n         ";
        currentLine = item;
      } else {
        currentLine = testLine;
      }
    }

    if (!currentLine.isEmpty()) {
      itemsText += currentLine;
    }

    m_inventoryLabel->setText(itemsText);
  }
}

void MainWindow::onGameOver(const QString &reason) {
  m_endingLabel->setText("GAME OVER\n\n" + reason +
                         "\n\nClick Restart to begin a new journey.");

  QScreen *screen = QGuiApplication::primaryScreen();
  qreal dpiScale = screen->logicalDotsPerInch() / 96.0;
  int gameOverFontSize = static_cast<int>(16 * dpiScale);
  int gameOverPadding = static_cast<int>(20 * dpiScale);

  m_endingLabel->setStyleSheet(QString("QLabel {"
                                       "  color: #FF0000;"
                                       "  font-weight: bold;"
                                       "  font-size: %1px;"
                                       "  padding: %2px;"
                                       "}")
                                   .arg(gameOverFontSize)
                                   .arg(gameOverPadding));
  m_endingLabel->setVisible(true);
  m_backButton->setEnabled(false);
}

void MainWindow::animateStoryText() {
  if (m_storyFadeAnimation) {
    if (m_storyFadeAnimation->state() == QAbstractAnimation::Running) {
      m_storyFadeAnimation->stop();
    }
    delete m_storyFadeAnimation;
  }

  m_storyFadeAnimation =
      new QPropertyAnimation(m_storyDisplay, "windowOpacity");
  m_storyFadeAnimation->setDuration(500);
  m_storyFadeAnimation->setStartValue(0.0);
  m_storyFadeAnimation->setEndValue(1.0);

  m_storyDisplay->setWindowOpacity(0.0);
  m_storyFadeAnimation->start();
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Up) {
    if (m_selectedChoiceIndex > 0) {
      m_selectedChoiceIndex--;
      highlightSelectedChoice();
    }
    event->accept();
  } else if (event->key() == Qt::Key_Down) {
    int numChoices = m_gameEngine->choices().size();
    if (m_selectedChoiceIndex < numChoices - 1) {
      m_selectedChoiceIndex++;
      highlightSelectedChoice();
    }
    event->accept();
  } else if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
    selectChoice(m_selectedChoiceIndex);
    event->accept();
  } else if (event->key() == Qt::Key_Left) {
    onBackClicked();
    event->accept();
  } else {
    QMainWindow::keyPressEvent(event);
  }
}

void MainWindow::selectChoice(int index) {
  if (index >= 0 && index < m_gameEngine->choices().size()) {
    m_gameEngine->makeChoice(index);
    setFocus();
  }
}

void MainWindow::highlightSelectedChoice() {
  QLayoutItem *item;
  int buttonIndex = 0;

  while ((item = m_choicesLayout->itemAt(buttonIndex)) != nullptr) {
    QWidget *widget = item->widget();
    if (!widget) {
      buttonIndex++;
      continue;
    }

    QPushButton *button = qobject_cast<QPushButton *>(widget);
    if (!button) {
      buttonIndex++;
      continue;
    }

    QScreen *screen = QGuiApplication::primaryScreen();
    qreal dpiScale = screen->logicalDotsPerInch() / 96.0;
    int choicePadding = static_cast<int>(12 * dpiScale);
    int choiceFontSize = static_cast<int>(16 * dpiScale);

    bool wasPreviouslySelected = m_gameEngine->isChoicePreviouslySelected(
        m_gameEngine->currentNodeId(), buttonIndex);

    if (buttonIndex == m_selectedChoiceIndex) {
      if (wasPreviouslySelected) {
        button->setStyleSheet(QString("QPushButton {"
                                      "  background-color: #00CED1;"
                                      "  color: #000000;"
                                      "  border: 3px solid #20B2AA;"
                                      "  border-radius: 5px;"
                                      "  padding: %1px;"
                                      "  font-size: %2px;"
                                      "  font-weight: bold;"
                                      "  text-align: left;"
                                      "}"
                                      "QPushButton:hover {"
                                      "  background-color: #00FFFF;"
                                      "}"
                                      "QPushButton:pressed {"
                                      "  background-color: #00E5E5;"
                                      "}")
                                  .arg(choicePadding)
                                  .arg(choiceFontSize));
      } else {
        button->setStyleSheet(QString("QPushButton {"
                                      "  background-color: #FFD700;"
                                      "  color: #000000;"
                                      "  border: 3px solid #FFA500;"
                                      "  border-radius: 5px;"
                                      "  padding: %1px;"
                                      "  font-size: %2px;"
                                      "  font-weight: bold;"
                                      "  text-align: left;"
                                      "}"
                                      "QPushButton:hover {"
                                      "  background-color: #FFE600;"
                                      "}"
                                      "QPushButton:pressed {"
                                      "  background-color: #FFC900;"
                                      "}")
                                  .arg(choicePadding)
                                  .arg(choiceFontSize));
      }
    } else {
      if (wasPreviouslySelected) {
        button->setStyleSheet(QString("QPushButton {"
                                      "  background-color: #1a3a2a;"
                                      "  color: #90EE90;"
                                      "  border: 2px solid #2a5a4a;"
                                      "  border-radius: 5px;"
                                      "  padding: %1px;"
                                      "  font-size: %2px;"
                                      "  text-align: left;"
                                      "}"
                                      "QPushButton:hover {"
                                      "  background-color: #2a4a3a;"
                                      "}"
                                      "QPushButton:pressed {"
                                      "  background-color: #3a5a4a;"
                                      "}")
                                  .arg(choicePadding)
                                  .arg(choiceFontSize));
      } else {
        button->setStyleSheet(QString("QPushButton {"
                                      "  background-color: #2c4563;"
                                      "  color: #ffffff;"
                                      "  border: 2px solid #1a2a3a;"
                                      "  border-radius: 5px;"
                                      "  padding: %1px;"
                                      "  font-size: %2px;"
                                      "  text-align: left;"
                                      "}"
                                      "QPushButton:hover {"
                                      "  background-color: #3d5a80;"
                                      "}"
                                      "QPushButton:pressed {"
                                      "  background-color: #4a6a90;"
                                      "}")
                                  .arg(choicePadding)
                                  .arg(choiceFontSize));
      }
    }

    buttonIndex++;
  }
}
