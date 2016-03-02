#ifndef VISOR_H
#define VISOR_H

#include <QWidget>
#include <opencv/cv.h>
#include <QImage>
#include <QTimer>
#include "cameraprocessor.hpp"

#define CORRECCION_BOCA_ABIERTA 1.2
#define CORRECCION_LINEA_SUPERIOR_BOCA 1.1
#define COMPONENTE 0
#define COMPONENTE_A 1


namespace Ui {
class Visor;
}

class Visor : public QWidget
{
    Q_OBJECT

public:
    explicit Visor(QWidget *parent = 0);
    ~Visor();
    void setCameraProcessor(CameraProcessor * cameraProcessor);
    cv::Mat getFrame();

protected:
    void paintEvent(QPaintEvent *);

private:
    Ui::Visor *ui;
    cv::Mat frame;
    QTimer * timer;
    CameraProcessor * cameraProcessor;

private slots:
    void slot_dibujarFrame();
};

#endif // VISOR_H
