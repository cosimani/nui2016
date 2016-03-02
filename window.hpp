#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <QWidget>
#include <QVector>

#include "cameraprocessor.hpp"
#include "welcome.hpp"
#include "university.hpp"
#include "news.hpp"
#include "queries.hpp"

class Window : public QWidget
{
    Q_OBJECT

private:

    QVector< Container* > *containers;
    int active;

    void activateContainer( int index )
    {
        active = index;
        containers->at( active )->setActive( true );

        for( int i = 0; i < containers->size(); i++ )
        {
            if( i != active )
            {
                containers->at( i )->setActive( false );
            }
        }
    }

    void focusLeft()
    {
        for( int i = 0; i < containers->size(); i++ )
        {
            containers->at( i )->right();
        }
    }

    void focusRight()
    {
        for( int i = 0; i < containers->size(); i++ )
        {
            containers->at( i )->left();
        }
    }

    void focusUp()
    {
        for( int i = 0; i < containers->size(); i++ )
        {
            containers->at( i )->down();
        }
    }

    void focusDown()
    {
        for( int i = 0; i < containers->size(); i++ )
        {
            containers->at( i )->up();
        }
    }

public:

    explicit Window( QWidget *parent = 0 ) : QWidget( parent ),
                                             containers( new QVector< Container * >() )
    {
        this->setFixedSize( 800, 600 );

        containers->append( new Welcome( this ) ); // 0 - Welcome
        containers->at( 0 )->setGeometry( 0, 0, 800, 600 );
        connect( containers->at( 0 ), SIGNAL( start() ), SLOT( slot_start() ) );

        containers->append( new University( this ) ); // 1 - University
        containers->at( 1 )->setGeometry( 800, 0, 800, 600 );
        connect( containers->at( 1 ), SIGNAL( showNews() ), SLOT( slot_news() ) );
        connect( containers->at( 1 ), SIGNAL( showQueries() ), SLOT( slot_queries() ) );

        containers->append( new News( this ) ); // 2 - News
        containers->at( 2 )->setGeometry( 1600, 0, 800, 600 );

        containers->append( new Queries( this ) ); // 3 - Queries
        containers->at( 3 )->setGeometry( 800, 600, 800, 600 );

        this->activateContainer( 0 );
        connect( CameraProcessor::getInstance(), SIGNAL( noFace() ), SLOT( slot_noFace() ) );
    }

private slots:

    void slot_noFace()
    {
        qDebug() << "NO FACE";
        this->activateContainer( 0 );
        containers->at( 0 )->setGeometry( 0, 0, 800, 600 );
        containers->at( 1 )->setGeometry( 800, 0, 800, 600 );
        containers->at( 2 )->setGeometry( 1600, 0, 800, 600 );
        containers->at( 3 )->setGeometry( 800, 600, 800, 600 );
        ( ( Welcome * )containers->at( 0 ) )->showWelcomeForce();
    }

    void slot_start()
    {
        qDebug() << "START";
        this->activateContainer( 1 );
        this->focusRight();
    }

    void slot_news()
    {
        qDebug() << "NEWS";
        this->activateContainer( 2 );
        this->focusRight();
    }

    void slot_queries()
    {
        qDebug() << "QUERIES";
        this->activateContainer( 3 );
        this->focusDown();
    }
};

#endif // WINDOW_HPP

