#ifndef ENGINE_HPP
#define ENGINE_HPP
#include <QObject>
#include <QString>
#include <QMap>
#include <QSqlDatabase>
#include <QPrinter>
#include "converters/convertertoqwidget.hpp"
#include "parser.hpp"
#include "processeddb.hpp"

namespace qtreports {
    using namespace detail;

    class Engine : public QObject {
        Q_OBJECT

    public:
        Engine( QObject * parent = 0 );
        ~Engine();

        bool    compile( const QString & path );
        bool    setParameters( const QMap< QString, QString > & map );
        bool    setConnection( const QSqlDatabase & connection );

        void    addQuery( const QString &queryName, const QString & query );
        void    addScript( const QString & script );

        bool                createPDF( const QString & path );
        bool                createHTML( const QString & path );//etc.
        const QWidgetPtr	createWidget();
        bool                print();
        
        bool        	    isCompiled() const;
        const QString       getLastError() const;

    private:
        bool                        m_isCompiled;
        QString                     m_lastError, m_compiledPath;
        ReportPtr                   m_report;
        QWidgetPtr                  m_widget;
        QMap< QString, QString >    m_dbQueries;
        QVector< QString >          m_scripts;
        QSqlDatabase                m_dbConnection;
        ProcessedDB                 m_processedDB;

        void                drawPreview( QPrinter * printer );
        void                prepareDB();
        QSqlQueryModelPtr   executeQuery( const QString & query );

    };

}
#endif // ENGINE_HPP
