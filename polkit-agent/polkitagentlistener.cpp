#include "polkitagentlistener.h"
#include "dialog.h"

PolKitAgentListener::PolKitAgentListener(QObject *parent)
    : PolkitQt1::Agent::Listener(parent)
    , m_dialog(nullptr)
{

}

void PolKitAgentListener::initiateAuthentication(const QString &actionId,
                                                 const QString &message,
                                                 const QString &iconName,
                                                 const PolkitQt1::Details &details,
                                                 const QString &cookie,
                                                 const PolkitQt1::Identity::List &identities,
                                                 PolkitQt1::Agent::AsyncResult *result)
{
    Q_UNUSED(iconName);
    Q_UNUSED(details);

    if (m_dialog) {
        m_dialog->deleteLater();
        m_dialog = nullptr;
    }

    m_dialog = new Dialog(actionId, message, cookie, identities.first().toString(), result);

    for (const PolkitQt1::Identity &i : identities) {
        PolkitQt1::Agent::Session *session;
        session = new PolkitQt1::Agent::Session(i, cookie, result);
        Q_ASSERT(session);
        m_sessionIdentity[session] = i;
        connect(session, &PolkitQt1::Agent::Session::request, this, &PolKitAgentListener::request);
        connect(session, &PolkitQt1::Agent::Session::completed, this, &PolKitAgentListener::completed);
        session->initiate();
    }
}

void PolKitAgentListener::request(const QString &request, bool echo)
{
    Q_UNUSED(request);
    Q_UNUSED(echo);

    PolkitQt1::Agent::Session *session = qobject_cast<PolkitQt1::Agent::Session *>(sender());
    Q_ASSERT(session);
    Q_ASSERT(m_dialog);

    PolkitQt1::Identity identity = m_sessionIdentity[session];

    connect(m_dialog, &Dialog::finished, this, [=] {
        if (m_dialog->identity() == m_sessionIdentity[session].toString() && !m_dialog->password().isEmpty()) {
            session->setResponse(m_dialog->password());
        } else {
            session->cancel();
        }
    });

    m_dialog->show();
}

void PolKitAgentListener::completed(bool gainedAuthorization)
{
    Q_UNUSED(gainedAuthorization);

    PolkitQt1::Agent::Session *session = qobject_cast<PolkitQt1::Agent::Session *>(sender());
    Q_ASSERT(session);
    Q_ASSERT(m_dialog);

    if (m_dialog->identity() == m_sessionIdentity[session].toString()) {
        session->result()->setCompleted();

        m_dialog->deleteLater();
        m_dialog = nullptr;
    }

    session->deleteLater();
}
