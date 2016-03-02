#ifndef CAMERAPROCESSOR_HPP
#define CAMERAPROCESSOR_HPP

#include <QObject>
#include <QTimer>
#include <QDebug>
#include <QSound>
#include <vector>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>

using namespace cv;
using namespace std;

class CameraProcessor : public QObject
{
    Q_OBJECT

private:

    static CameraProcessor* instance;

    VideoCapture *videoCapture;
    static QTimer *updateTimer;
    Mat cameraFrame;
    CascadeClassifier faceClassifier;
    CascadeClassifier smileClassifier;

    int nofacesCounter;
    bool faces;

    int nosmilesCounter;
    bool smiles;

    Rect firstFace;
    static bool needCalibrate;
    int activeBlockX, activeBlockY;

    void process();

public:

    static CameraProcessor *getInstance();

    explicit CameraProcessor( QObject *parent = 0 );

    static void pause();
    static void unpause();
    static void calibrate();

    Mat getCameraFrame() const;
    void setCameraFrame(const Mat &value);

private slots:

    void slot_updateMat();

signals:

    void face();
    void noFace();
    void smile();
    void noSmile();
    void activeBlockChanged( int x, int y );
};

#endif // CAMERAPROCESSOR_HPP

