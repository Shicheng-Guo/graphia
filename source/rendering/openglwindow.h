#ifndef OPENGLWINDOW_H
#define OPENGLWINDOW_H

#include <QWindow>
#include <QTime>

#include <memory>

class Scene;
class Interactor;
class QOpenGLDebugMessage;

class OpenGLWindow : public QWindow
{
    Q_OBJECT

public:
    explicit OpenGLWindow(QScreen* parent = nullptr);
    ~OpenGLWindow();

    const QOpenGLContext& context() const { return *_context; }

    void setScene(Scene* scene);
    const Scene& scene() const { return *_scene; }
    void enableSceneUpdate() { _sceneUpdateEnabled = true; }
    void disableSceneUpdate() { _sceneUpdateEnabled = false; }

    void setInteractor(Interactor* interactor) { _interactor = interactor; }
    const Interactor& interactor() const { return *_interactor; }
    void enableInteraction();
    void disableInteraction();

    void update();
    
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
    void resizeEvent(QResizeEvent* e);

    void messageLogged(const QOpenGLDebugMessage &message);

private:
    void makeContextCurrent();

    std::shared_ptr<QOpenGLContext> _context;
    Scene* _scene;
    Interactor* _interactor;
    bool _sceneUpdateEnabled;
    bool _interactionEnabled;
    int _debugLevel;
    
    QTime _time;
};

#endif // OPENGLWINDOW_H
