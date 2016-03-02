#ifndef NEWS_HPP
#define NEWS_HPP

#include "cameraprocessor.hpp"
#include "container.hpp"
#include "image.hpp"
#include "block.hpp"

#include <QLabel>

class News : public Container
{
    Q_OBJECT

private:

    QLabel *title;
    Image *smallLogo;

    QVector< Block * > *news;

public:

    explicit News( QWidget *parent = 0 ) : Container( parent ),
                                           title( new QLabel( "<div style=\"color:#555555; font-size:35px;\">> Novedades</div>", this ) ),
                                           smallLogo( new Image( ":/smallLogo.png", this ) ),
                                           news( new QVector< Block * >() )
    {
        title->setGeometry( 10, 125 / 2 - title->sizeHint().height() / 2, 800, title->sizeHint().height() );
        smallLogo->setGeometry( width() - smallLogo->width() - 10, height() - smallLogo->height() - 10, smallLogo->width(), smallLogo->height() );

        news->append( new Block( 780, 80, "Ya se encuentran abiertas las inscripciones 2016", ":/academic.png", 18, true, this ) );
        news->last()->setGeometry( 10, 125, news->last()->width(), news->last()->height() );

        news->append( new Block( 780, 80, "La UBP festeja sus 25 años!", ":/chat.png", 18, true, this ) );
        news->last()->setGeometry( 10, 215, news->last()->width(), news->last()->height() );

        news->append( new Block( 780, 80, "El CED de San Luis se renueva con entusiasmo y experiencia", ":/chat.png", 18, true, this ) );
        news->last()->setGeometry( 10, 305, news->last()->width(), news->last()->height() );

        news->append( new Block( 780, 80, "La UBP promueve proyectos de innovación", ":/academic.png", 18, true, this ) );
        news->last()->setGeometry( 10, 395, news->last()->width(), news->last()->height() );

        connect( CameraProcessor::getInstance(), SIGNAL( activeBlockChanged( int, int ) ), SLOT( slot_activateBlock( int, int ) ) );
    }

private slots:

    void slot_activateBlock( int, int y )
    {
        if( !this->getActive() ) return;

        for( int i = 0; i < news->size(); i++ )
        {
            if( i != y ) news->at( i )->deactivate();
        }

        news->at( y )->activate();
    }
};

#endif // NEWS_HPP

