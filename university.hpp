#ifndef UNIVERSITY_HPP
#define UNIVERSITY_HPP

#include "cameraprocessor.hpp"
#include "container.hpp"
#include "image.hpp"
#include "block.hpp"

#include <QLabel>

class University : public Container
{
    Q_OBJECT

private:

    QLabel *title;
    Image *smallLogo;
    Block *news;
    Block *queries;
    Block *diary;

public:

    explicit University( QWidget *parent = 0 ) : Container( parent ),
                                                 title( new QLabel( "<div style=\"color:#555555; font-size:35px;\">> Universidad</div>", this ) ),
                                                 smallLogo( new Image( ":/smallLogo.png", this ) ),
                                                 news( new Block( 520, 175, "Novedades", ":/world.png", 30, true, this ) ),
                                                 queries( new Block( 520, 175, "Consultas", ":/info.png", 30,  true, this ) ),
                                                 diary( new Block( 250, 360, "Agenda", ":/diary.png", 30,  false, this ) )
    {
        title->setGeometry( 10, 125 / 2 - title->sizeHint().height() / 2, 800, title->sizeHint().height() );
        smallLogo->setGeometry( width() - smallLogo->width() - 10, height() - smallLogo->height() - 10, smallLogo->width(), smallLogo->height() );
        news->setGeometry( 10, 125, news->width(), news->height() );
        queries->setGeometry( 10, 310, news->width(), news->height() );
        diary->setGeometry( 540, 125, diary->width(), diary->height() );

        connect( CameraProcessor::getInstance(), SIGNAL( activeBlockChanged( int, int ) ), SLOT( slot_activateBlock( int, int ) ) );
        connect( CameraProcessor::getInstance(), SIGNAL( smile() ), SLOT( slot_smile() ) );
    }

private slots:

    void slot_activateBlock( int x, int y )
    {
        if( !this->getActive() ) return;

        if( y <= 1 && x <= 2 )
        {
            queries->deactivate();
            diary->deactivate();
            news->activate();
        }
        if( y >= 2 && x <= 2 )
        {
            news->deactivate();
            diary->deactivate();
            queries->activate();
        }
        if( x >= 2 )
        {
            news->deactivate();
            queries->deactivate();
            diary->activate();
        }
    }

    void slot_smile()
    {
        if( !this->getActive() ) return;

        if( news->isBlockActive() ) emit showNews();
        if( queries->isBlockActive() ) emit showQueries();
        if( diary->isBlockActive() ) emit showDiary();
    }

signals:

    void showNews();
    void showQueries();
    void showDiary();
};

#endif // UNIVERSITY_HPP

