#ifndef CAMERA_H
#define CAMERA_H

#define USE_OPENGL_WIDGET
#ifdef USE_OPENGL_WIDGET
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#else
#include <QWidget>
#endif
#include <QImage>
#include <QTimer>
#include <QMutex>

#ifdef USE_OPENGL_WIDGET
#else
#endif

#ifdef USE_OPENGL_WIDGET
class Camera : public QOpenGLWidget
#else
class Camera : public QWidget
#endif
{
    Q_OBJECT
public:
    explicit Camera(QWidget *parent = nullptr);
    void setFramesPerSecond(quint32 fps);
signals:

public slots:
    void updateData(QImage &image);
protected:
#ifdef USE_OPENGL_WIDGET
    virtual void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
#else
    virtual void paintEvent(QPaintEvent *e) override;
#endif

private:
    QTimer mTimer;
    QImage mImage;
    QMutex mMutex;
};

#endif // CAMERA_H
