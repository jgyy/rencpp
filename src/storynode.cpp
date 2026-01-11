#include "storynode.h"

StoryNode::StoryNode(const QString &id, const QString &text)
    : m_id(id), m_text(text)
{
}

StoryNode::~StoryNode()
{
    qDeleteAll(m_choices);
    m_choices.clear();
}

QString StoryNode::id() const
{
    return m_id;
}

QString StoryNode::text() const
{
    return m_text;
}

QList<Choice*> StoryNode::choices() const
{
    return m_choices;
}

bool StoryNode::isEndNode() const
{
    return m_choices.isEmpty();
}

void StoryNode::addChoice(Choice *choice)
{
    if (choice) {
        m_choices.append(choice);
    }
}

void StoryNode::setText(const QString &text)
{
    m_text = text;
}
