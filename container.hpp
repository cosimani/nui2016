#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <QFont>
#include <QTimer>
#include <QImage>
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QPropertyAnimation>

#include "cameraprocessor.hpp"

class Container : public QWidget
{
    Q_OBJECT

private:

    QPropertyAnimation *animation;
    QImage background;
    bool active;
    QTimer *sleepActive;

public:

    explicit Container( QWidget *parent = 0 ) : QWidget( parent ),
                                                animation( new QPropertyAnimation( this, "pos", this ) ),
                                                active( false ),
                                                sleepActive( new QTimer( this ) )
    {
        background.load( ":/background.jpg" );

        this->resize( 800, 600 );

        animation->setStartValue( this->pos() );
        animation->setDuration( 500 );
        animation->setEasingCurve( QEasingCurve::OutCubic );
        connect( animation, SIGNAL( finished() ), SLOT( slot_continueCameraProcess() ) );

        this->setFont( QFont( "Segoe UI Light", 20 ) );

        this->repaint();

        connect( sleepActive, SIGNAL( timeout() ), SLOT( slot_sleepTimeout() ) );
    }

    void left()
    {
        CameraProcessor::pause();
        animation->setStartValue( this->pos() );
        animation->setEndValue( QPoint( this->x() - this->width(), this->y() ) );
        animation->start();
    }

    void right()
    {
        CameraProcessor::pause();
        animation->setStartValue( this->pos() );
        animation->setEndValue( QPoint( this->x() + this->width(), this->y() ) );
        animation->start();
    }

    void up()
    {
        CameraProcessor::pause();
        animation->setStartValue( this->pos() );
        animation->setEndValue( QPoint( this->x(), this->y() - this->height() ) );
        animation->start();
    }

    void down()
    {
        CameraProcessor::pause();
        animation->setStartValue( this->pos() );
        animation->setEndValue( QPoint( this->x(), this->y() + this->height() ) );
        animation->start();
    }

    void setActive( bool value )
    {
        if( value )
        {
            sleepActive->start( 500 );
        }
        else
        {
            active = false;
        }
    }

    bool getActive()
    {
        return active;
    }

protected:

    void paintEvent( QPaintEvent * )
    {
        QPainter painter( this );
        painter.drawImage( width() / 2 - background.width() / 2,
                           height() / 2 - background.height() / 2,
                           background );
    }

private slots:

    void slot_continueCameraProcess()
    {
        CameraProcessor::unpause();
    }

    void slot_sleepTimeout()
    {
        active = true;
        sleepActive->stop();
    }
};


#endif // CONTAINER_HPP

