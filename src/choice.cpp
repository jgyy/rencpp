#include "choice.h"

Choice::Choice(const QString &text, const QString &targetNodeId,
               const QMap<QString, int> &statChanges, const QStringList &itemsGained)
    : m_text(text), m_targetNodeId(targetNodeId), m_statChanges(statChanges), m_itemsGained(itemsGained)
{
}

QString Choice::text() const
{
    return m_text;
}

QString Choice::targetNodeId() const
{
    return m_targetNodeId;
}

QMap<QString, int> Choice::statChanges() const
{
    return m_statChanges;
}

QStringList Choice::itemsGained() const
{
    return m_itemsGained;
}
