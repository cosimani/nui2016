#include "visor.h"
#include "ui_visor.h"
#include <QPainter>

Visor::Visor(QWidget *parent) : QWidget(parent), ui(new Ui::Visor)  {
    ui->setupUi(this);

    timer = new QTimer(this);
    timer->start(50);

    connect(timer, SIGNAL(timeout()), this, SLOT(slot_dibujarFrame()));
}

Visor::~Visor()  {
    delete ui;
}

void Visor::setCameraProcessor(CameraProcessor *cameraProcessor)  {
    this->cameraProcessor = cameraProcessor;
}

Mat Visor::getFrame()  {
    return this->frame.clone();
}

void Visor::paintEvent(QPaintEvent *)  {
    QPainter painter(this);

    QImage image( frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888 );
    image = image.rgbSwapped();  // Convierte de BGR a RGB

    painter.drawImage(0, 0, image);
}

/**
 * @brief Visor::slot_dibujarFrame Aca se pueden hacer las pruebas de procesamiento.
 */
void Visor::slot_dibujarFrame()  {
    this->frame = CameraProcessor::getInstance()->getCameraFrame().clone();
//    this->frame = this->cameraProcessor->getCameraTexture().clone();

    this->repaint();
}
