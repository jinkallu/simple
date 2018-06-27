#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(), parent)
{
    num_steps = 0;
}

GLWidget::~GLWidget(){

}

QSize GLWidget::sizeHint() const{
    return QSize(640, 480);
}

void GLWidget::initializeGL(){
    qglClearColor((QColor(Qt::black)));
}

void GLWidget::resizeGL(int w, int h){
    if (h == 0) {
        h = 1;
    }
    pMatrix.setToIdentity();
    pMatrix.perspective(60.0, (float) w / (float) h, 0.001, 1000);
    glViewport(0, 0, w, h);
}

void GLWidget::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    paint_genetic();
    glFlush();
}

void GLWidget::paint_genetic(){
    // The following code displays the steps as points.
    glPointSize(5.0);
    glColor3f(1.0, 1.0, 1.0);

    if(num_steps > 0){
        glBegin(GL_LINES);
        glVertex3f(-0.5, -0.5, 0.);
        glVertex3f(0.75, -0.5, 0.);

        glVertex3f(-0.5, -0.5, 0.);
        glVertex3f(-0.5, 0.75, 0.);
        glEnd();
    }

    glColor3f(0.0, 1.0, 1.0);
    if(num_steps > 0){
        glBegin(GL_LINE_STRIP);

        float dx_step = 1./(float)num_steps;
        float dy_step = 0.5 / step_vals[0];
        for(int i = 0; i < num_steps; i++){
            glVertex3f(dx_step * i - 0.5, step_vals[i] * dy_step, 0.);
        }

        glEnd();
    }
}

void GLWidget::setValues(int *st, float *val){
    num_steps = st[0];
    step_vals = val;
    this->repaint();
}
