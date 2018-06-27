#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QMatrix4x4>

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);
    ~GLWidget();
    QSize sizeHint() const;

    void paint_genetic();
    void setValues(int *st, float * val);

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

private:
    QMatrix4x4 pMatrix;
    int num_steps;
    float *step_vals;
};

#endif // GLWIDGET_H
