#ifndef QUERIES_HPP
#define QUERIES_HPP

#include "cameraprocessor.hpp"
#include "container.hpp"
#include "image.hpp"
#include "block.hpp"

#include <QLabel>

class Queries : public Container
{
    Q_OBJECT

private:

    QLabel *title;
    Image *smallLogo;

    QVector< Block * > *queries;

public:

    explicit Queries( QWidget *parent = 0 ) : Container( parent ),
                                           title( new QLabel( "<div style=\"color:#555555; font-size:35px;\">> Consultas</div>", this ) ),
                                           smallLogo( new Image( ":/smallLogo.png", this ) ),
                                           queries( new QVector< Block * >() )
    {
        title->setGeometry( 10, 125 / 2 - title->sizeHint().height() / 2, 800, title->sizeHint().height() );
        smallLogo->setGeometry( width() - smallLogo->width() - 10, height() - smallLogo->height() - 10, smallLogo->width(), smallLogo->height() );

        queries->append( new Block( 385, 180, "Planes", ":/academic.png", 18, true, this ) );
        queries->last()->setGeometry( 10, 125, queries->last()->width(), queries->last()->height() );

        queries->append( new Block( 385, 180, "Directivos", ":/academic.png", 18, true, this ) );
        queries->last()->setGeometry( 405, 125, queries->last()->width(), queries->last()->height() );

        queries->append( new Block( 385, 180, "Instalaciones", ":/bars.png", 18, true, this ) );
        queries->last()->setGeometry( 10, 315, queries->last()->width(), queries->last()->height() );

        queries->append( new Block( 385, 180, "Servicios", ":/bars.png", 18, true, this ) );
        queries->last()->setGeometry( 405, 315, queries->last()->width(), queries->last()->height() );

        connect( CameraProcessor::getInstance(), SIGNAL( activeBlockChanged( int, int ) ), SLOT( slot_activateBlock( int, int ) ) );
    }

private slots:

    void slot_activateBlock( int x, int y )
    {
        if( !this->getActive() ) return;

        if( x <= 1 && y <= 1 )
        {
            queries->at( 0 )->activate();
            queries->at( 1 )->deactivate();
            queries->at( 2 )->deactivate();
            queries->at( 3 )->deactivate();
        }
        if( x >= 2 && y <= 1 )
        {
            queries->at( 0 )->deactivate();
            queries->at( 1 )->activate();
            queries->at( 2 )->deactivate();
            queries->at( 3 )->deactivate();
        }
        if( x <= 1 && y >= 2 )
        {
            queries->at( 0 )->deactivate();
            queries->at( 1 )->deactivate();
            queries->at( 2 )->activate();
            queries->at( 3 )->deactivate();
        }
        if( x >= 2 && y >= 2 )
        {
            queries->at( 0 )->deactivate();
            queries->at( 1 )->deactivate();
            queries->at( 2 )->deactivate();
            queries->at( 3 )->activate();
        }
    }
};

#endif // QUERIES_HPP

