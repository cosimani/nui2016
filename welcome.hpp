#ifndef WELCOME_HPP
#define WELCOME_HPP

#include <QLabel>
#include <QSound>
#include <QPropertyAnimation>

#include "cameraprocessor.hpp"
#include "container.hpp"
#include "image.hpp"

class Welcome : public Container
{
    Q_OBJECT

private:

    QLabel *title;
    Image *logo;
    QLabel *text;

    QPropertyAnimation *titleAnimation;
    QPropertyAnimation *logoAnimation;

    int state;

public:

    explicit Welcome( QWidget *parent = 0 ) : Container( parent ),
                                              title( new QLabel( "<h2 align=center>Sistema de interacción natural</h2>" , this ) ),
                                              logo( new Image( ":/logo.png", this ) ),
                                              text( new QLabel( "<div align=center>Colóquese al frente de la cámara</div>", this ) ),
                                              titleAnimation( new QPropertyAnimation( title, "pos", this ) ),
                                              logoAnimation( new QPropertyAnimation( logo, "pos", this ) ),
                                              state( 0 )
    {
        title->setGeometry( 0, this->height() / 4 - title->sizeHint().height() / 2,
                            800, title->sizeHint().height() );

        logo->setGeometry( this->width() / 2 - logo->width() / 2,
                           this->height() / 2 - logo->height() / 2,
                           logo->width(), logo->height() );

        text->setGeometry( 0, this->height() / 4 * 3 - text->sizeHint().height() / 2,
                           800, text->sizeHint().height() );


        titleAnimation->setDuration( 500 );

        logoAnimation->setDuration( 1000 );
        logoAnimation->setEasingCurve( QEasingCurve::OutBack );

        connect( CameraProcessor::getInstance(), SIGNAL( face() ), SLOT( slot_showInstruction() ) );
        connect( CameraProcessor::getInstance(), SIGNAL( noFace() ), SLOT( slot_showWelcome() ) );
        connect( CameraProcessor::getInstance(), SIGNAL( smile() ), SLOT( slot_smile() ) );

        connect( logoAnimation, SIGNAL( finished() ), SLOT( slot_continueCameraProcess() ) );

        this->slot_showWelcome();
    }

    void showWelcomeForce()
    {
        if( state == 0 ) return;

        CameraProcessor::pause();

        text->setText( "<div align=center>Colóquese al frente de la cámara</div>" );

        titleAnimation->setStartValue( QPoint( 0, -title->sizeHint().height() ) );
        titleAnimation->setEndValue( QPoint( 0, height() / 4 - title->sizeHint().height() / 2 ) );

        logoAnimation->setStartValue( QPoint( width() / 2 - logo->width() / 2, height() / 4 - logo->height() / 2 ) );
        logoAnimation->setEndValue( QPoint( width() / 2 - logo->width() / 2, height() / 2 - logo->height() / 2 ) );

        titleAnimation->start();
        logoAnimation->start();
        state = 0;
    }

public slots:

    void slot_showWelcome()
    {
        if( !this->getActive() ) return;
        this->showWelcomeForce();
    }

    void slot_showInstruction()
    {
        if( !this->getActive() ) return;

        if( state == 1 ) return;

        CameraProcessor::pause();

        text->setText( "<div align=center>Bienvenido, sonría para comenzar</div>" );

        logoAnimation->setStartValue( QPoint( width() / 2 - logo->width() / 2, height() / 2 - logo->height() / 2 ) );
        logoAnimation->setEndValue( QPoint( width() / 2 - logo->width() / 2, height() / 4 - logo->height() / 2 ) );

        titleAnimation->setStartValue( QPoint( 0, height() / 4 - title->sizeHint().height() / 2 ) );
        titleAnimation->setEndValue( QPoint( 0, -title->sizeHint().height() ) );

        titleAnimation->start();
        logoAnimation->start();

        QSound::play( ":/welcome.wav" );

        state = 1;
    }

    void slot_smile()
    {
        if( !this->getActive() ) return;

        CameraProcessor::calibrate();

        emit start();
    }

signals:

    void start();
};

#endif // WELCOME_HPP

