#ifndef MONGOEVENTS_H
#define MONGOEVENTS_H

#include <QString>
#include <QStringList>
#include <QEvent>
#include "Core.h"
#include "mongo/client/dbclient.h"
#include <engine/Result.h>
#include "domain/MongoShellResult.h"
#include "Events.h"

namespace Robomongo
{
    /**
     * @brief Init Request & Response
     */

    class InitRequest : public Event
    {
        R_MESSAGE

        InitRequest(QObject *sender) :
            Event(sender) {}
    };

    class InitResponse : public Event
    {
        R_MESSAGE

        InitResponse(QObject *sender) :
            Event(sender) {}

        InitResponse(QObject *sender, Error error) :
            Event(sender, error) {}
    };

    /**
     * @brief Init Request & Response
     */

    class FinalizeRequest : public Event
    {
        R_MESSAGE

        FinalizeRequest(QObject *sender) :
            Event(sender) {}
    };

    class FinalizeResponse : public Event
    {
        R_MESSAGE

        FinalizeResponse(QObject *sender) :
            Event(sender) {}

        FinalizeResponse(QObject *sender, Error error) :
            Event(sender, error) {}
    };


    /**
     * @brief EstablishConnection
     */

    class EstablishConnectionRequest : public Event
    {
        R_MESSAGE

        EstablishConnectionRequest(QObject *sender, const QString &databaseName,
                                   const QString &userName, const QString &userPassword) :
            Event(sender),
            databaseName(databaseName),
            userName(userName),
            userPassword(userPassword) {}

        QString databaseName;
        QString userName;
        QString userPassword;
    };

    class EstablishConnectionResponse : public Event
    {
        R_MESSAGE

        EstablishConnectionResponse(QObject *sender, const QString &address) :
            Event(sender),
            address(address) {}

        EstablishConnectionResponse(QObject *sender, const Error &error) :
            Event(sender, error) {}

        QString address;
    };


    /**
     * @brief LoadDatabaseNames
     */

    class LoadDatabaseNamesRequest : public Event
    {
        R_MESSAGE

        LoadDatabaseNamesRequest(QObject *sender) :
            Event(sender) {}
    };

    class LoadDatabaseNamesResponse : public Event
    {
        R_MESSAGE

        LoadDatabaseNamesResponse(QObject *sender, const QStringList &databaseNames) :
            Event(sender),
            databaseNames(databaseNames) {}

        LoadDatabaseNamesResponse(QObject *sender, const Error &error) :
            Event(sender, error) {}

        QStringList databaseNames;
    };


    /**
     * @brief LoadCollectionNames
     */

    class LoadCollectionNamesRequest : public Event
    {
        R_MESSAGE

        LoadCollectionNamesRequest(QObject *sender, const QString &databaseName) :
            Event(sender),
            databaseName(databaseName) {}

        QString databaseName;
    };

    class LoadCollectionNamesResponse : public Event
    {
        R_MESSAGE

        LoadCollectionNamesResponse(QObject *sender, const QString &databaseName,
                                    const QStringList &collectionNames) :
            Event(sender),
            databaseName(databaseName),
            collectionNames(collectionNames) { }

        LoadCollectionNamesResponse(QObject *sender, Error error) :
            Event(sender, error) {}

        QString databaseName;
        QStringList collectionNames;
    };


    /**
     * @brief Query Mongodb
     */

    class ExecuteQueryRequest : public Event
    {
        R_MESSAGE

        ExecuteQueryRequest(QObject *sender, const QString &nspace, int take = 0, int skip = 0) :
            Event(sender),
            nspace(nspace),
            take(take),
            skip(skip) {}

        QString nspace; //namespace of object (i.e. "database_name.collection_name")
        int take; //
        int skip;
    };

    class ExecuteQueryResponse : public Event
    {
        R_MESSAGE

        ExecuteQueryResponse(QObject *sender, const QList<mongo::BSONObj> &documents) :
            Event(sender),
            documents(documents) { }

        ExecuteQueryResponse(QObject *sender, const Error &error) :
            Event(sender, error) {}

        QList<mongo::BSONObj> documents;
    };


    /**
     * @brief ExecuteScript
     */

    class ExecuteScriptRequest : public Event
    {
        R_MESSAGE

        ExecuteScriptRequest(QObject *sender, const QString &script, const QString &dbName, int take = 0, int skip = 0) :
            Event(sender),
            script(script),
            databaseName(dbName),
            take(take),
            skip(skip) {}

        QString script;
        QString databaseName;
        int take; //
        int skip;
    };

    class ExecuteScriptResponse : public Event
    {
        R_MESSAGE

        ExecuteScriptResponse(QObject *sender, const QList<Result> &results) :
            Event(sender),
            results(results) { }

        ExecuteScriptResponse(QObject *sender, const Error &error) :
            Event(sender, error) {}

        QList<Result> results;
    };



    class SomethingHappened : public Event
    {
        R_MESSAGE

        SomethingHappened(QObject *sender, const QString &something) :
            Event(sender),
            something(something) { }

        QString something;
    };

    class ConnectingEvent : public Event
    {
        R_MESSAGE

        ConnectingEvent(QObject *sender, const MongoServerPtr &server) :
            Event(sender),
            server(server) { }

        MongoServerPtr server;
    };

    class OpeningShellEvent : public Event
    {
        R_MESSAGE

        OpeningShellEvent(QObject *sender, const MongoShellPtr &shell, const QString &initialScript) :
            Event(sender),
            shell(shell),
            initialScript(initialScript) { }

        MongoShellPtr shell;
        QString initialScript;
    };

    class ConnectionFailedEvent : public Event
    {
        R_MESSAGE

        ConnectionFailedEvent(QObject *sender, const MongoServerPtr &server) :
            Event(sender),
            server(server) { }

        MongoServerPtr server;
    };

    class ConnectionEstablishedEvent : public Event
    {
        R_MESSAGE

        ConnectionEstablishedEvent(QObject *sender, const MongoServerPtr &server) :
            Event(sender),
            server(server) { }

        ~ConnectionEstablishedEvent() {
            int a = 56;
        }

        MongoServerPtr server;
    };

    class DatabaseListLoadedEvent : public Event
    {
        R_MESSAGE

        DatabaseListLoadedEvent(QObject *sender, const QList<MongoDatabasePtr> &list) :
            Event(sender),
            list(list) { }

        QList<MongoDatabasePtr> list;
    };

    class DocumentListLoadedEvent : public Event
    {
        R_MESSAGE

        DocumentListLoadedEvent(QObject *sender, const QString &query, const QList<MongoDocumentPtr> &list) :
            Event(sender),
            query(query),
            list(list) { }

        QList<MongoDocumentPtr> list;
        QString query;
    };

    class ScriptExecutedEvent : public Event
    {
        R_MESSAGE

        ScriptExecutedEvent(QObject *sender, const QList<MongoShellResult> &list) :
            Event(sender),
            results(list) { }

        QList<MongoShellResult> results;
    };

}

#endif // MONGOEVENTS_H
