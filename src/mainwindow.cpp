#include "mainwindow.h"
#include <QWidget>
#include <QScrollArea>
#include <QScrollBar>
#include <QMessageBox>
#include <QApplication>

MainWindow::MainWindow(GameEngine *gameEngine, QWidget *parent)
    : QMainWindow(parent), m_gameEngine(gameEngine)
{
    // Create central widget
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Main layout
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setSpacing(10);
    mainLayout->setContentsMargins(15, 15, 15, 15);

    // Title
    QLabel *titleLabel = new QLabel("The Mysterious Room", this);
    titleLabel->setStyleSheet(
        "QLabel {"
        "  color: #ffffff;"
        "  font-size: 24px;"
        "  font-weight: bold;"
        "  padding: 10px;"
        "}"
    );
    mainLayout->addWidget(titleLabel);

    // Story display
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

    // Choices container with scroll
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

    // Control buttons layout
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

    // Ending label
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

    // Set window properties
    setWindowTitle("Text Adventure - The Mysterious Room");
    setGeometry(100, 100, 900, 700);
    setStyleSheet(
        "QMainWindow {"
        "  background-color: #0f1a25;"
        "}"
    );

    // Connect signals from game engine
    connect(m_gameEngine, &GameEngine::currentTextChanged,
            this, &MainWindow::onStoryTextChanged);
    connect(m_gameEngine, &GameEngine::choicesChanged,
            this, &MainWindow::onChoicesChanged);
    connect(m_gameEngine, &GameEngine::canGoBackChanged,
            this, &MainWindow::onCanGoBackChanged);
    connect(m_gameEngine, &GameEngine::gameEnded,
            this, &MainWindow::onGameEnded);
    connect(m_gameEngine, &GameEngine::errorOccurred,
            this, &MainWindow::onErrorOccurred);

    // Load initial story
    m_gameEngine->loadStory(":/stories/sample_story.json");
}

MainWindow::~MainWindow()
{
}

void MainWindow::onStoryTextChanged()
{
    m_storyDisplay->setText(m_gameEngine->currentText());
    m_storyDisplay->verticalScrollBar()->setValue(0);
}

void MainWindow::onChoicesChanged()
{
    clearChoiceButtons();

    const QVariantList &choices = m_gameEngine->choices();
    for (int i = 0; i < choices.size(); ++i) {
        QVariantMap choiceData = choices[i].toMap();
        QString choiceText = choiceData["text"].toString();

        QPushButton *choiceButton = new QPushButton(choiceText, this);
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
        choiceButton->setMinimumHeight(50);
        choiceButton->setWordWrap(true);

        // Store choice index as property
        choiceButton->setProperty("choiceIndex", i);
        connect(choiceButton, &QPushButton::clicked, this, &MainWindow::onChoiceClicked);

        m_choicesLayout->addWidget(choiceButton);
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
