#ifndef OPENGLWINDOW_H
#define OPENGLWINDOW_H

#include <QWindow>
#include <QTime>

class Scene;
class GraphView;
class QOpenGLDebugMessage;

class OpenGLWindow : public QWindow
{
    Q_OBJECT

public:
    explicit OpenGLWindow(const QSurfaceFormat& format,
                          GraphView* graphView,
                          QScreen* parent = 0);
    //FIXME destructor to delete things

    QOpenGLContext* context() const { return _context; }

    void setScene(Scene* scene);
    Scene* scene() const { return _scene; }
    
protected:
    virtual void initialise();
    virtual void resize();
    virtual void render();

    virtual void keyPressEvent(QKeyEvent* e);
    virtual void keyReleaseEvent(QKeyEvent* e);
    virtual void mousePressEvent(QMouseEvent* e);
    virtual void mouseReleaseEvent(QMouseEvent* e);
    virtual void mouseMoveEvent(QMouseEvent* e);
    virtual void mouseDoubleClickEvent(QMouseEvent* e);
    virtual void wheelEvent(QWheelEvent* e);

protected slots:
    virtual void updateScene();

    void resizeEvent(QResizeEvent* e);

    void messageLogged(const QOpenGLDebugMessage &message);

private:
    QOpenGLContext* _context;
    Scene* _scene;
    GraphView* _graphView;
    int _debugLevel;
    
    QTime _time;
};

#endif // OPENGLWINDOW_H
