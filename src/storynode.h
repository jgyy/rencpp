#ifndef STORYNODE_H
#define STORYNODE_H

#include <QString>
#include <QList>
#include "choice.h"

class StoryNode
{
public:
    StoryNode(const QString &id, const QString &text);
    ~StoryNode();

    QString id() const;
    QString text() const;
    QList<Choice*> choices() const;
    bool isEndNode() const;

    void addChoice(Choice *choice);
    void setText(const QString &text);

private:
    QString m_id;
    QString m_text;
    QList<Choice*> m_choices;
};

#endif
