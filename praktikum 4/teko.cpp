#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

double rotAngle = 10;
double rotAngle1 = 10;

void init()
{
    glClearColor(0.9, 0.9, 0.9, 1.0); 
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
    
  
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};
    GLfloat light_ambient[] = {0.3, 0.3, 0.3, 1.0};
    GLfloat light_diffuse[] = {0.8, 0.8, 0.8, 1.0};
    GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};
    
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1, 1, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
        0.0, 0.0, 5.0,
        0.0, 0.0, 0.0,
        0.0, 1.0, 0.0);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glPushMatrix();
        glRotated(rotAngle, 0, 1, 0);
        glRotated(rotAngle1, 1, 0, 0);
        
       
        GLfloat mat_ambient[] = {0.4, 0.2, 0.1, 1.0};
        GLfloat mat_diffuse[] = {0.7, 0.3, 0.2, 1.0}; 
        GLfloat mat_specular[] = {0.8, 0.6, 0.4, 1.0};
        GLfloat mat_shininess[] = {50.0};
        
        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
        
     
        glutSolidTeapot(1.5);
        
    glPopMatrix();
    
    glFlush();
    glutSwapBuffers();
}

void keyboard(unsigned char k, int x, int y)
{
    switch (k)
    {
        case 'a':
            rotAngle += 5;
            break;
        case 'y':
            rotAngle1 += 5;
            break;
        case 'b':
            rotAngle1 -= 5;
            break;
        case 'l':
            rotAngle -= 5;
            break;
        case 'q':
            exit(0);
    }
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("GLUT Brown Teapot Example");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    init();
    glutMainLoop();
    return 0;
}
