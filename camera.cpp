#include "camera.h"
#include <QPainter>

#ifdef USE_OPENGL_WIDGET
Camera::Camera(QWidget *parent) : QOpenGLWidget(parent)
#else
Camera::Camera(QWidget *parent) : QWidget(parent)
#endif
{
    QObject::connect(&mTimer,&QTimer::timeout,this,[this](){update();});
    mTimer.start(1000/40);
}

void Camera::setFramesPerSecond(quint32 fps)
{
    if(fps>1){
        mTimer.start(1000/fps);
    }else{
        mTimer.start(1000/1);
    }
}

void Camera::updateData(QImage &image)
{
    mMutex.lock();
    mImage = image;
    mMutex.unlock();
}

#ifdef USE_OPENGL_WIDGET
void Camera::initializeGL()
{
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void Camera::resizeGL(int w, int h)
{
    Q_UNUSED(w)
    Q_UNUSED(h)
}

void Camera::paintGL()
{
    QPainter painter(this);

    mMutex.lock();
    QImage image = mImage.scaled(width(),height(),Qt::KeepAspectRatio);
    mMutex.unlock();
    qint32 w = image.width();
    qint32 h = image.height();
    qint32 x = (width() - w) / 2;
    qint32 y = (height() - h) / 2;

    painter.drawImage(QRect{x,y,w,h},image,QRect{0,0,w,h});
}

#else
void Camera::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    mMutex.lock();
    QImage image = mImage.scaled(width(),height(),Qt::KeepAspectRatio);
    mMutex.unlock();
    qint32 w = image.width();
    qint32 h = image.height();
    qint32 x = (width() - w) / 2;
    qint32 y = (height() - h) / 2;

    painter.drawImage(QRect{x,y,w,h},image,QRect{0,0,w,h});
}
#endif
