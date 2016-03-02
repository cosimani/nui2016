#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <QWidget>
#include <QImage>
#include <QPainter>
#include <QPaintEvent>

class Image : public QWidget
{
    Q_OBJECT

private:

    QImage image;

public:

    explicit Image( QString imageUri = "", QWidget *parent = 0 ) : QWidget( parent )
    {
        image.load( imageUri );

        if( !image.isNull() )
        {
            this->setFixedSize( image.size() );
        }

        this->repaint();
    }

protected:

    void paintEvent( QPaintEvent * )
    {
        QPainter painter( this );

        if( !image.isNull() )
        {
            painter.drawImage( 0, 0, image );
        }
    }
};

#endif // IMAGE_HPP

