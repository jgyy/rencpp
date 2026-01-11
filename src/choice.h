#ifndef CHOICE_H
#define CHOICE_H

#include <QString>

class Choice
{
public:
    Choice(const QString &text, const QString &targetNodeId);

    QString text() const;
    QString targetNodeId() const;

private:
    QString m_text;
    QString m_targetNodeId;
};

#endif
