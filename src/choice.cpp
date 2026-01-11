#include "choice.h"

Choice::Choice(const QString &text, const QString &targetNodeId)
    : m_text(text), m_targetNodeId(targetNodeId)
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
