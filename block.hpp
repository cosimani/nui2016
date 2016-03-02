#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <QWidget>
#include <QLabel>
#include <QPalette>
#include "image.hpp"

class Block : public QWidget
{
    Q_OBJECT

private:

    QLabel *name;
    Image *icon;
    bool active;

public:

    explicit Block( int w, int h, QString string, QString uri,
                    int fontSize = 30, bool horizontal = true, QWidget *parent = 0 ) : QWidget( parent ),
                                                                                       name( new QLabel( string, this ) ),
                                                                                       icon( new Image( uri, this ) ),
                                                                                       active( false )
    {
        this->setFixedSize( w, h );
        name->setFont( QFont( "Segoe UI Light", fontSize ) );

        if( horizontal )
        {
            icon->setGeometry( height() / 2 - icon->height() / 2,
                               height() / 2 - icon->height() / 2,
                               icon->width(), icon->height() );

            name->setGeometry( height() / 2 - icon->height() / 2 + icon->width() + height() / 2 - icon->height() / 2,
                               height() / 2 - name->sizeHint().height() / 2,
                               name->sizeHint().width(), name->sizeHint().height() );
        }
        else
        {
            icon->setGeometry( width() / 2 - icon->width() / 2,
                               width() / 2 - icon->width() / 2,
                               icon->width(), icon->height() );

            name->setGeometry( width() / 2 - name->sizeHint().width() / 2,
                               width() / 2 - icon->width() / 2 + icon->height() +  width() / 2 - icon->width() / 2,
                               name->sizeHint().width(), name->sizeHint().height() );
        }

        QPalette style;
        style.setColor( QPalette::WindowText, QColor( 255, 255, 255, 255 ) );
        style.setColor( QPalette::Background, QColor( 0, 0, 0, 75 ) );
        this->setPalette( style );

        this->setAutoFillBackground( true );
    }

    void activate()
    {
        QPalette style = this->palette();
        style.setColor( QPalette::Background, QColor( 255, 0, 0, 128 ) );
        this->setPalette( style );
        active = true;
    }

    void deactivate()
    {
        QPalette style = this->palette();
        style.setColor( QPalette::Background, QColor( 0, 0, 0, 75 ) );
        this->setPalette( style );
        active = false;
    }

    bool isBlockActive()
    {
        return active;
    }
};

#endif // BLOCK_HPP

