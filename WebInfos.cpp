#include <QString>
#include <QStringList>
#include <QDebug>

#include "WebInfos.h"

#include "WebContents.h"

WebInfos::WebInfos(QString identifier, QString sdkVersion, QString installedVersion) {
    m_wc = new WebContents;
    m_identifier = identifier;
    m_sdk_version = sdkVersion;
    m_installedVersion = installedVersion;
}

void WebInfos::fetch() {
    connect(m_wc, SIGNAL(stringAvailable(QString)), SLOT(infosArrived(QString)));
    m_wc->fetch("http://schrell.de/AfterShotPro/WebTools/PlugInfo.php?sdk=" + m_sdk_version + "&id=" + m_identifier);
}

void WebInfos::fetchAll() {
    connect(m_wc, SIGNAL(stringAvailable(QString)), SLOT(allInfosArrived(QString)));
    m_wc->fetch("http://schrell.de/AfterShotPro/WebTools/PlugInfo.php?sdk=" + m_sdk_version + "&id=%");
}

void WebInfos::infosArrived(QString str) {
    QRegExp re("(\\s|')");
    str.remove(re);
    QStringList webFields = str.split(";");
    if (webFields.size() < 4) return;
    m_name = webFields.at(0);
    m_webVersion = webFields.at(2);
    m_link = webFields.at(3);
    emit ready();
}

void WebInfos::allInfosArrived(QString str) {
    QStringList strList = str.split("\n");
    QList<WebInfos*> wiList;
    QStringListIterator i(strList);
    while (i.hasNext()) {
        QString singleStr = i.next();
        QRegExp re("(\\s|')");
        singleStr.remove(re);
        QStringList webFields = singleStr.split(";");
        if (webFields.size() < 4) continue;
        WebInfos *wi = new WebInfos(webFields.at(0), m_sdk_version, NULL);
        wi->m_identifier = webFields.at(1);
        wi->m_webVersion = webFields.at(2);
        wi->m_name = webFields.at(0);
        wi->m_link = webFields.at(3);
        wiList.append(wi);
    }
    emit readyAll(wiList);
}

bool WebInfos::isWebNewer() {
    return formatVersion(m_webVersion) > formatVersion(m_installedVersion);
}

QString WebInfos::formatVersion(QString versionString) {
    QStringList vList = versionString.split(".");
    QString result("");
    QStringListIterator i(vList);
    while (i.hasNext()) {
        result.append(QString("%1.").arg(i.next(),5,'0'));
    }
    return result;
}

QString WebInfos::name() {
    return m_name;
}

QString WebInfos::identifier() {
    return m_identifier;
}

QString WebInfos::installedVersion() {
    return m_installedVersion;
}

QString WebInfos::webVersion() {
    return m_webVersion;
}

QString WebInfos::sdk_version() {
    return m_sdk_version;
}

QString WebInfos::link() {
    return m_link;
}
