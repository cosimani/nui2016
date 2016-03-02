#include "cameraprocessor.hpp"

CameraProcessor* CameraProcessor::instance = 0;
QTimer *CameraProcessor::updateTimer = new QTimer;
bool CameraProcessor::needCalibrate = false;


CameraProcessor::CameraProcessor( QObject *parent ) : QObject( parent ),
                                                      videoCapture( new VideoCapture( 0 ) ),
                                                      //updateTimer( new QTimer( this ) ),
                                                      nofacesCounter( 0 ),
                                                      faces( false ),
                                                      smiles( false ),
                                                      activeBlockX( -1 ),
                                                      activeBlockY( -1 )
                                                      //needCalibrate( false )
{
    qDebug() << "face.xml cargado" << faceClassifier.load( "../punto/face.xml" );
    qDebug() << "smile.xml cargado" << smileClassifier.load( "../punto/smile.xml" );

    firstFace = Rect( 0, 0, 0, 0 );

    connect( updateTimer, SIGNAL( timeout() ), SLOT( slot_updateMat() ) );
    updateTimer->start( 10 );
}

void CameraProcessor::pause()
{
    updateTimer->stop();
}

void CameraProcessor::unpause()
{
    updateTimer->start( 10 );
}

void CameraProcessor::calibrate()
{
    needCalibrate = true;
}


Mat CameraProcessor::getCameraFrame() const
{
    return cameraFrame;
}

void CameraProcessor::setCameraFrame(const Mat &value)
{
    cameraFrame = value;
}
void CameraProcessor::process()
{
    vector< Rect > detectedFaces;
    detectedFaces.clear();

    faceClassifier.detectMultiScale( cameraFrame, detectedFaces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size( 150, 150 ) );

    // caras

    if( detectedFaces.size() > 0 )
    {
        nofacesCounter = 0;
        if( !faces )
        {
            emit face();
            faces = true;
        }



        // posicion

        int xFaceCenter = detectedFaces.at( 0 ).x + detectedFaces.at( 0 ).width / 2;
        int yFaceCenter = detectedFaces.at( 0 ).y + detectedFaces.at( 0 ).height / 2;

        if( xFaceCenter > firstFace.x &&
            xFaceCenter < firstFace.x + firstFace.width &&
            yFaceCenter > firstFace.y &&
            yFaceCenter < firstFace.y + firstFace.height &&
            firstFace.width != 0 &&
            firstFace.height != 0 )
        {

            int xIndex = 3 - ( xFaceCenter - firstFace.x ) / ( firstFace.width / 4 );
            int yIndex = ( yFaceCenter - firstFace.y ) / ( firstFace.height / 4 );

            if( xIndex < 0 ) xIndex = 0;
            if( xIndex > 3 ) xIndex = 3;
            if( yIndex < 0 ) yIndex = 0;
            if( yIndex > 3 ) yIndex = 3;


            if( xIndex != activeBlockX || yIndex != activeBlockY )
            {
                activeBlockX = xIndex;
                activeBlockY = yIndex;

                emit activeBlockChanged( xIndex, yIndex );
            }
        }


        // sonrisa

        vector< Rect > detectedSmiles;
        detectedSmiles.clear();

        detectedFaces.operator []( 0 ).width -= detectedFaces.operator []( 0 ).width % 3;

        Mat face( cameraFrame, detectedFaces.at( 0 ) );

        smileClassifier.detectMultiScale( face, detectedSmiles, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size( 50, 50 ) );

        if( detectedSmiles.size() > 0 )
        {
            // calibracion

            if( needCalibrate )
            {
                Rect newFirstFace = detectedFaces.at( 0 );
                newFirstFace.x += newFirstFace.width / 4;
                newFirstFace.y += newFirstFace.height / 4;
                newFirstFace.width /= 2;
                newFirstFace.height /= 2;

                firstFace = newFirstFace;
                //firstFace = detectedFaces.at( 0 );
                needCalibrate = false;
            }

            nosmilesCounter = 0;
            if( !smiles )
            {
                emit smile();
                QSound::play( ":/selected.wav" );
                smiles = true;
            }
        }

        else
        {
            nosmilesCounter++;
            if( nosmilesCounter >= 1 )
            {
                if( smiles ) emit noSmile();
                smiles = false;
            }
        }


    }
    else
    {
        nofacesCounter++;

        if( nofacesCounter >= 10 )
        {
            if( faces ) emit noFace();
            faces = false;
        }
    }
}

CameraProcessor *CameraProcessor::getInstance()
{
    if( instance == NULL )
    {
        instance = new CameraProcessor;
    }

    return instance;
}

void CameraProcessor::slot_updateMat()
{
    videoCapture->operator >>( cameraFrame );
    process();
}
