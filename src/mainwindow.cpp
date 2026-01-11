#include "mainwindow.h"
#include <QWidget>
#include <QScrollArea>
#include <QScrollBar>
#include <QMessageBox>
#include <QApplication>

MainWindow::MainWindow(GameEngine *gameEngine, QWidget *parent)
    : QMainWindow(parent), m_gameEngine(gameEngine), m_statsLabel(nullptr), m_progressLabel(nullptr),
      m_inventoryLabel(nullptr), m_achievementsLabel(nullptr), m_animationGroup(nullptr),
      m_storyFadeAnimation(nullptr)
{
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setSpacing(10);
    mainLayout->setContentsMargins(15, 15, 15, 15);

    QHBoxLayout *statsLayout = new QHBoxLayout();
    statsLayout->setSpacing(20);
    statsLayout->setContentsMargins(10, 5, 10, 5);

    m_statsLabel = new QLabel("Qi Vitality: 100 | Spiritual Power: 10 | Comprehension: 10 | Fortune: 10", this);
    m_statsLabel->setStyleSheet(
        "QLabel {"
        "  color: #FFD700;"
        "  font-weight: bold;"
        "  font-size: 12px;"
        "}"
    );
    statsLayout->addWidget(m_statsLabel);

    m_progressLabel = new QLabel("Choices: 0 | Nodes: 1 | Time: 0:00", this);
    m_progressLabel->setStyleSheet(
        "QLabel {"
        "  color: #87CEEB;"
        "  font-weight: bold;"
        "  font-size: 12px;"
        "}"
    );
    statsLayout->addWidget(m_progressLabel);

    m_inventoryLabel = new QLabel("Items: none", this);
    m_inventoryLabel->setWordWrap(true);
    m_inventoryLabel->setStyleSheet(
        "QLabel {"
        "  color: #90EE90;"
        "  font-weight: bold;"
        "  font-size: 12px;"
        "}"
    );
    statsLayout->addWidget(m_inventoryLabel);

    m_achievementsLabel = new QLabel("Endings: 0", this);
    m_achievementsLabel->setStyleSheet(
        "QLabel {"
        "  color: #FF69B4;"
        "  font-weight: bold;"
        "  font-size: 12px;"
        "}"
    );
    statsLayout->addWidget(m_achievementsLabel);

    QFrame *statsFrame = new QFrame(this);
    statsFrame->setLayout(statsLayout);
    statsFrame->setStyleSheet(
        "QFrame {"
        "  background-color: #0a1420;"
        "  border: 1px solid #3d5a80;"
        "  border-radius: 3px;"
        "}"
    );
    mainLayout->addWidget(statsFrame, 0);

    m_titleLabel = new QLabel(this);
    m_titleLabel->setStyleSheet(
        "QLabel {"
        "  color: #ffffff;"
        "  font-size: 24px;"
        "  font-weight: bold;"
        "  padding: 10px;"
        "}"
    );
    mainLayout->addWidget(m_titleLabel);

    m_storyDisplay = new QTextEdit(this);
    m_storyDisplay->setReadOnly(true);
    m_storyDisplay->setStyleSheet(
        "QTextEdit {"
        "  background-color: #1a2a3a;"
        "  color: #e8e8e8;"
        "  border: 2px solid #3d5a80;"
        "  border-radius: 5px;"
        "  padding: 10px;"
        "  font-family: Georgia;"
        "  font-size: 14px;"
        "}"
    );
    mainLayout->addWidget(m_storyDisplay, 1);

    m_choicesContainer = new QWidget(this);
    m_choicesLayout = new QVBoxLayout(m_choicesContainer);
    m_choicesLayout->setSpacing(8);

    QScrollArea *choicesScroll = new QScrollArea(this);
    choicesScroll->setWidget(m_choicesContainer);
    choicesScroll->setWidgetResizable(true);
    choicesScroll->setStyleSheet(
        "QScrollArea {"
        "  background-color: #0f1a25;"
        "  border: 1px solid #3d5a80;"
        "  border-radius: 5px;"
        "}"
    );
    mainLayout->addWidget(choicesScroll, 0);

    QHBoxLayout *controlLayout = new QHBoxLayout();
    controlLayout->setSpacing(10);

    m_backButton = new QPushButton("Back", this);
    m_backButton->setStyleSheet(
        "QPushButton {"
        "  background-color: #3d5a80;"
        "  color: #ffffff;"
        "  border: 1px solid #1a2a3a;"
        "  border-radius: 3px;"
        "  padding: 8px 15px;"
        "  font-size: 12px;"
        "}"
        "QPushButton:hover:enabled {"
        "  background-color: #4a6a90;"
        "}"
        "QPushButton:disabled {"
        "  background-color: #1a2a3a;"
        "  color: #666666;"
        "}"
    );
    connect(m_backButton, &QPushButton::clicked, this, &MainWindow::onBackClicked);
    controlLayout->addWidget(m_backButton);

    m_restartButton = new QPushButton("Restart", this);
    m_restartButton->setStyleSheet(
        "QPushButton {"
        "  background-color: #3d5a80;"
        "  color: #ffffff;"
        "  border: 1px solid #1a2a3a;"
        "  border-radius: 3px;"
        "  padding: 8px 15px;"
        "  font-size: 12px;"
        "}"
        "QPushButton:hover {"
        "  background-color: #4a6a90;"
        "}"
    );
    connect(m_restartButton, &QPushButton::clicked, this, &MainWindow::onRestartClicked);
    controlLayout->addWidget(m_restartButton);

    controlLayout->addStretch();

    mainLayout->addLayout(controlLayout);

    m_endingLabel = new QLabel("", this);
    m_endingLabel->setStyleSheet(
        "QLabel {"
        "  color: #90EE90;"
        "  font-weight: bold;"
        "  padding: 10px;"
        "}"
    );
    m_endingLabel->setVisible(false);
    mainLayout->addWidget(m_endingLabel);

    setWindowTitle("Text Adventure - The Mysterious Room");
    setGeometry(100, 100, 900, 700);
    setStyleSheet(
        "QMainWindow {"
        "  background-color: #0f1a25;"
        "}"
    );

    connect(m_gameEngine, &GameEngine::currentTextChanged,
            this, &MainWindow::onStoryTextChanged);
    connect(m_gameEngine, &GameEngine::choicesChanged,
            this, &MainWindow::onChoicesChanged);
    connect(m_gameEngine, &GameEngine::canGoBackChanged,
            this, &MainWindow::onCanGoBackChanged);
    connect(m_gameEngine, &GameEngine::gameEnded,
            this, &MainWindow::onGameEnded);
    connect(m_gameEngine, &GameEngine::gameOver,
            this, &MainWindow::onGameOver);
    connect(m_gameEngine, &GameEngine::errorOccurred,
            this, &MainWindow::onErrorOccurred);

    connect(m_gameEngine, &GameEngine::healthChanged,
            this, &MainWindow::onStatsChanged);
    connect(m_gameEngine, &GameEngine::strengthChanged,
            this, &MainWindow::onStatsChanged);
    connect(m_gameEngine, &GameEngine::intelligenceChanged,
            this, &MainWindow::onStatsChanged);
    connect(m_gameEngine, &GameEngine::wisdomChanged,
            this, &MainWindow::onStatsChanged);
    connect(m_gameEngine, &GameEngine::choicesMadeChanged,
            this, &MainWindow::onProgressChanged);
    connect(m_gameEngine, &GameEngine::nodesVisitedChanged,
            this, &MainWindow::onProgressChanged);
    connect(m_gameEngine, &GameEngine::playTimeChanged,
            this, &MainWindow::onProgressChanged);
    connect(m_gameEngine, &GameEngine::inventoryChanged,
            this, &MainWindow::onInventoryChanged);
    connect(m_gameEngine, &GameEngine::endingsFoundChanged,
            this, &MainWindow::onProgressChanged);

    m_gameEngine->loadStory(":/stories/story.json");
    m_titleLabel->setText(m_gameEngine->storyTitle());
}

MainWindow::~MainWindow()
{
}

void MainWindow::onStoryTextChanged()
{
    m_storyDisplay->setText(m_gameEngine->currentText());
    m_storyDisplay->verticalScrollBar()->setValue(0);
    animateStoryText();
}

void MainWindow::onChoicesChanged()
{
    clearChoiceButtons();

    const QVariantList &choices = m_gameEngine->choices();
    for (int i = 0; i < choices.size(); ++i) {
        QVariantMap choiceData = choices[i].toMap();
        QString choiceText = choiceData["text"].toString();

        QPushButton *choiceButton = new QPushButton(choiceText, this);

        bool wasPreviouslySelected = m_gameEngine->isChoicePreviouslySelected(m_gameEngine->currentNodeId(), i);

        if (wasPreviouslySelected) {
            choiceButton->setStyleSheet(
                "QPushButton {"
                "  background-color: #1a3a2a;"
                "  color: #90EE90;"
                "  border: 2px solid #2a5a4a;"
                "  border-radius: 5px;"
                "  padding: 12px;"
                "  font-size: 14px;"
                "  text-align: left;"
                "}"
                "QPushButton:hover {"
                "  background-color: #2a4a3a;"
                "}"
                "QPushButton:pressed {"
                "  background-color: #3a5a4a;"
                "}"
            );
        } else {
            choiceButton->setStyleSheet(
                "QPushButton {"
                "  background-color: #2c4563;"
                "  color: #ffffff;"
                "  border: 2px solid #1a2a3a;"
                "  border-radius: 5px;"
                "  padding: 12px;"
                "  font-size: 14px;"
                "  text-align: left;"
                "}"
                "QPushButton:hover {"
                "  background-color: #3d5a80;"
                "}"
                "QPushButton:pressed {"
                "  background-color: #4a6a90;"
                "}"
            );
        }
        choiceButton->setMinimumHeight(50);
        choiceButton->setWindowOpacity(0.0);

        choiceButton->setProperty("choiceIndex", i);
        connect(choiceButton, &QPushButton::clicked, this, &MainWindow::onChoiceClicked);

        m_choicesLayout->addWidget(choiceButton);

        QPropertyAnimation *buttonFade = new QPropertyAnimation(choiceButton, "windowOpacity");
        buttonFade->setDuration(300);
        buttonFade->setStartValue(0.0);
        buttonFade->setEndValue(1.0);
        buttonFade->start(QAbstractAnimation::DeleteWhenStopped);
    }

    m_choicesLayout->addStretch();
}

void MainWindow::onCanGoBackChanged()
{
    m_backButton->setEnabled(m_gameEngine->canGoBack());
}

void MainWindow::onChoiceClicked()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (button) {
        int choiceIndex = button->property("choiceIndex").toInt();
        m_gameEngine->makeChoice(choiceIndex);
    }
}

void MainWindow::onGameEnded(const QString &endingText)
{
    m_endingLabel->setText("This story has ended. Click Restart to play again.");
    m_endingLabel->setVisible(true);
}

void MainWindow::onErrorOccurred(const QString &error)
{
    QMessageBox::critical(this, "Error", error);
}

void MainWindow::onBackClicked()
{
    m_gameEngine->goBack();
}

void MainWindow::onRestartClicked()
{
    m_endingLabel->setVisible(false);
    m_gameEngine->restart();
}

void MainWindow::clearChoiceButtons()
{
    while (QLayoutItem *item = m_choicesLayout->takeAt(0)) {
        if (QPushButton *button = qobject_cast<QPushButton *>(item->widget())) {
            delete button;
        }
        delete item;
    }
}

void MainWindow::onStatsChanged()
{
    if (!m_statsLabel) return;

    int health = m_gameEngine->health();
    int strength = m_gameEngine->strength();
    int intelligence = m_gameEngine->intelligence();
    int wisdom = m_gameEngine->wisdom();

    m_statsLabel->setText(QString("Qi Vitality: %1 | Spiritual Power: %2 | Comprehension: %3 | Fortune: %4")
                         .arg(health)
                         .arg(strength)
                         .arg(intelligence)
                         .arg(wisdom));
}

void MainWindow::onProgressChanged()
{
    if (!m_progressLabel && !m_achievementsLabel) return;

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
        m_achievementsLabel->setText(QString("Endings: %1/1").arg(endingsFound));
    }
}

void MainWindow::onInventoryChanged()
{
    if (!m_inventoryLabel) return;

    QStringList inventory = m_gameEngine->inventory();
    if (inventory.isEmpty()) {
        m_inventoryLabel->setText("Items: none");
    } else {
        QString itemsText = "Items: ";
        QString currentLine = "";

        for (int i = 0; i < inventory.size(); ++i) {
            QString item = inventory[i];
            QString separator = (i < inventory.size() - 1) ? ", " : "";
            QString testLine = currentLine.isEmpty() ? item : currentLine + ", " + item;

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

void MainWindow::onGameOver(const QString &reason)
{
    m_endingLabel->setText("GAME OVER\n\n" + reason + "\n\nClick Restart to begin a new journey.");
    m_endingLabel->setStyleSheet(
        "QLabel {"
        "  color: #FF0000;"
        "  font-weight: bold;"
        "  font-size: 16px;"
        "  padding: 20px;"
        "}"
    );
    m_endingLabel->setVisible(true);
    m_backButton->setEnabled(false);
}

void MainWindow::animateStoryText()
{
    if (m_storyFadeAnimation) {
        if (m_storyFadeAnimation->state() == QAbstractAnimation::Running) {
            m_storyFadeAnimation->stop();
        }
        delete m_storyFadeAnimation;
    }

    m_storyFadeAnimation = new QPropertyAnimation(m_storyDisplay, "windowOpacity");
    m_storyFadeAnimation->setDuration(500);
    m_storyFadeAnimation->setStartValue(0.0);
    m_storyFadeAnimation->setEndValue(1.0);

    m_storyDisplay->setWindowOpacity(0.0);
    m_storyFadeAnimation->start();
}
