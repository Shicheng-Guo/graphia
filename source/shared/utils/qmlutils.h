#ifndef QMLUTILS_H
#define QMLUTILS_H

#include "shared/utils/thread.h"
#include "utils.h"

#include <QObject>
#include <QUrl>
#include <QDebug>
#include <QFileInfo>
#include <QCollator>

class QQmlEngine;
class QJSEngine;

class QmlUtils : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QmlUtils)

public:
    QmlUtils() = default;

    Q_INVOKABLE QString baseFileNameForUrl(const QUrl& url) const { return url.fileName(); }
    Q_INVOKABLE QString baseFileNameForUrlNoExtension(const QUrl& url) const
    {
        auto fi = QFileInfo(url.toLocalFile());
        return fi.baseName();
    }

    Q_INVOKABLE QString fileNameForUrl(const QUrl& url) const { return url.toLocalFile(); }
    Q_INVOKABLE QUrl urlForFileName(const QString& fileName) const { return QUrl::fromLocalFile(fileName); }
    Q_INVOKABLE QUrl urlForUserInput(const QString& userInput) const { return QUrl::fromUserInput(userInput); }
    Q_INVOKABLE bool fileExists(const QString& fileName) const { return QFileInfo::exists(fileName); }
    Q_INVOKABLE bool fileUrlExists(const QUrl& url) const { return QFileInfo::exists(url.toLocalFile()); }

    Q_INVOKABLE QUrl replaceExtension(const QUrl& url, const QString& extension) const
    {
        auto fi = QFileInfo(url.toLocalFile());
        auto replaced = QFileInfo(QStringLiteral("%1/%2.%3")
                                  .arg(fi.path(),
                                       fi.baseName(),
                                       extension));

        return QUrl::fromLocalFile(replaced.filePath());
    }

    Q_INVOKABLE QString currentThreadName() const { return u::currentThreadName(); }

    Q_INVOKABLE bool urlIsValid(const QString& urlString) const
    {
        QUrl url = QUrl::fromUserInput(urlString);
        return url.isValid();
    }

    // QML JS comparelocale doesn't include numeric implementation...
    Q_INVOKABLE int localeCompareStrings(const QString& left, const QString& right, bool numeric = true)
    {
        m_collator.setNumericMode(numeric);
        return m_collator.compare(left, right);
    }

    static QObject* qmlInstance(QQmlEngine*, QJSEngine*)
    {
        return new QmlUtils;
    }

    Q_INVOKABLE QString formatForDisplay(double value)
    {
        return u::formatNumberForDisplay(value);
    }
private:
    QCollator m_collator;
};

#endif // QMLUTILS_H
