#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include "gameengine.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(GameEngine *gameEngine, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onStoryTextChanged();
    void onChoicesChanged();
    void onCanGoBackChanged();
    void onChoiceClicked();
    void onGameEnded(const QString &endingText);
    void onGameOver(const QString &reason);
    void onErrorOccurred(const QString &error);
    void onBackClicked();
    void onRestartClicked();
    void onStatsChanged();
    void onInventoryChanged();
    void onProgressChanged();
    void animateStoryText();

private:
    void updateUI();
    void clearChoiceButtons();

    GameEngine *m_gameEngine;
    QTextEdit *m_storyDisplay;
    QVBoxLayout *m_choicesLayout;
    QWidget *m_choicesContainer;
    QPushButton *m_backButton;
    QPushButton *m_restartButton;
    QLabel *m_endingLabel;
    QLabel *m_titleLabel;

    QLabel *m_statsLabel;
    QLabel *m_progressLabel;
    QLabel *m_inventoryLabel;
    QLabel *m_achievementsLabel;

    QSequentialAnimationGroup *m_animationGroup;
    QPropertyAnimation *m_storyFadeAnimation;
};

#endif
