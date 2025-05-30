#include <GL/glut.h>
#include <cstdlib>

static int shoulderAngle = 0;
static int elbowAngle = 0;
static int palmAngle = 0;
static int fingerAngles[5] = {0, 0, 0, 0, 0};

void init() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glShadeModel(GL_SMOOTH);
}

void drawFinger(int rotationAngle) {
    glPushMatrix();
        glRotatef((GLfloat)rotationAngle, 0.0f, 0.0f, 1.0f);
        glTranslatef(0.3f, 0.0f, 0.0f);
        glPushMatrix();
            glScalef(0.6f, 0.15f, 0.15f);
            glutWireCube(1.0);
        glPopMatrix();
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, -7.0f);

    glPushMatrix();
        glTranslatef(-1.5f, 0.0f, 0.0f);
        glRotatef((GLfloat)shoulderAngle, 0.0f, 0.0f, 1.0f);
        glTranslatef(1.0f, 0.0f, 0.0f);

        glPushMatrix();
            glScalef(2.0f, 0.4f, 1.0f);
            glutWireCube(1.0);
        glPopMatrix();

        glTranslatef(1.0f, 0.0f, 0.0f);
        glRotatef((GLfloat)elbowAngle, 0.0f, 0.0f, 1.0f);
        glTranslatef(1.0f, 0.0f, 0.0f);

        glPushMatrix();
            glScalef(2.0f, 0.4f, 1.0f);
            glutWireCube(1.0);
        glPopMatrix();

        glTranslatef(1.0f, 0.0f, 0.0f);
        glRotatef((GLfloat)palmAngle, 0.0f, 0.0f, 1.0f);
        glTranslatef(0.5f, 0.0f, 0.0f);

        glPushMatrix();
            glScalef(1.0f, 0.5f, 0.5f);
            glutWireCube(1.0);
        glPopMatrix();

        for (int i = 0; i < 5; i++) {
            glPushMatrix();
                glTranslatef(0.5f, 0.3f - i * 0.15f, 0.0f);
                drawFinger(fingerAngles[i]);
            glPopMatrix();
        }
    glPopMatrix();

    glutSwapBuffers();
}

void setGestureTwo() {
    fingerAngles[0] = 45;  // ibu jari agak terbuka
    fingerAngles[1] = 0;   // jari telunjuk lurus
    fingerAngles[2] = 90;  // jari tengah ditekuk
    fingerAngles[3] = 90;  // jari manis ditekuk
    fingerAngles[4] = 90;  // kelingking ditekuk
}

void resetFingers() {
    for (int i = 0; i < 5; i++) {
        fingerAngles[i] = 0;
    }
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 's': shoulderAngle = (shoulderAngle + 5) % 360; break;
        case 'S': shoulderAngle = (shoulderAngle - 5) % 360; break;
        case 'e': elbowAngle = (elbowAngle + 5) % 360; break;
        case 'E': elbowAngle = (elbowAngle - 5) % 360; break;
        case 'p': palmAngle = (palmAngle + 5) % 360; break;
        case 'P': palmAngle = (palmAngle - 5) % 360; break;
        case '1': fingerAngles[0] = (fingerAngles[0] + 5) % 360; break;
        case '2': fingerAngles[1] = (fingerAngles[1] + 5) % 360; break;
        case '3': fingerAngles[2] = (fingerAngles[2] + 5) % 360; break;
        case '4': fingerAngles[3] = (fingerAngles[3] + 5) % 360; break;
        case '5': fingerAngles[4] = (fingerAngles[4] + 5) % 360; break;
        case 't': // tombol t untuk gesture angka 2
            setGestureTwo();
            break;
        case 'r': // tombol r untuk reset posisi jari
            resetFingers();
            break;
        case 27: exit(0); break;
        default: break;
    }
    glutPostRedisplay();
}

void reshape(int w, int h) {
    if (h == 0) h = 1;
    float aspect = (float)w / (float)h;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(60.0f, aspect, 1.0f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("3D Articulated Arm with Gesture");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glEnable(GL_DEPTH_TEST);

    glutMainLoop();
    return 0;
}

