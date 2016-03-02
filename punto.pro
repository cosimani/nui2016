# Interfaz de interaccion natural para ubp

QT += widgets multimedia

unix:LIBS += "/usr/lib/x86_64-linux-gnu/libopencv_core.so"        # OpenCV
unix:LIBS += "/usr/lib/x86_64-linux-gnu/libopencv_highgui.so"     # OpenCV
unix:LIBS += "/usr/lib/x86_64-linux-gnu/libopencv_imgproc.so"     # OpenCV
unix:LIBS += "/usr/lib/x86_64-linux-gnu/libopencv_objdetect.so"   # OpenCV

SOURCES += \
    main.cpp \
    cameraprocessor.cpp \
    visor.cpp

HEADERS += \
    window.hpp \
    container.hpp \
    welcome.hpp \
    image.hpp \
    cameraprocessor.hpp \
    university.hpp \
    block.hpp \
    news.hpp \
    queries.hpp \
    visor.h

RESOURCES += \
    resources.qrc

FORMS += \
    visor.ui
