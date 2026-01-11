#ifndef CHOICE_H
#define CHOICE_H

#include <QString>
#include <QMap>
#include <QStringList>

class Choice
{
public:
    Choice(const QString &text, const QString &targetNodeId,
           const QMap<QString, int> &statChanges = QMap<QString, int>(),
           const QStringList &itemsGained = QStringList());

    QString text() const;
    QString targetNodeId() const;
    QMap<QString, int> statChanges() const;
    QStringList itemsGained() const;

private:
    QString m_text;
    QString m_targetNodeId;
    QMap<QString, int> m_statChanges;
    QStringList m_itemsGained;
};

#endif
