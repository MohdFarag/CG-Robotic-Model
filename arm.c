// Robotic Arm
// Mohamed Ahmed Abdullah
// Ismail Tawfik

#include <stdlib.h>
#include <GL/glut.h>


static int shoulder = 0, elbow = 0, fingerBasePhalange = 0, fingerUpPhalange = 0;
static int fingerBase = 0, fingerUp = 0;
int moving, startx, starty;


GLfloat angle = 0.0;   /* in degrees */
GLfloat angle2 = 0.0;   /* in degrees */


void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();

    //Mouse movements
    glRotatef(angle2, 1.0, 0.0, 0.0);
    glRotatef(angle, 0.0, 1.0, 0.0);
    glTranslatef(-1.0, 0.0, 0.0);

    //Shoulder
    glRotatef((GLfloat)shoulder, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);
    glPushMatrix();
    glScalef(2.0, 0.6, 1.0);
    glutWireCube(1.0);
    glPopMatrix();

    //Elbow
    glTranslatef(1.0, 0.0, 0.0);
    glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);
    glPushMatrix();
    glScalef(2.0, 0.6, 1.0);
    glutWireCube(1.0);
    glPopMatrix();

    // FINGERS

    // Finger 1 Up 
    glPushMatrix();
    glTranslatef(1.0, -0.25, 0.0);
    glRotatef((GLfloat)fingerBasePhalange, 0.0, 0.0, 1.0);
    glTranslatef(0.15, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.3, 0.1, 0.15);
    glutWireCube(1);
    glPopMatrix();

    ////Finger 2 Base
    glTranslatef(0.15, 0.0, 0.0);
    glRotatef((GLfloat)fingerUpPhalange, 0.0, 0.0, 1.0);
    glTranslatef(0.15, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.3, 0.1, 0.15);
    glutWireCube(1);
    glPopMatrix();
    glPopMatrix();

    //Finger 2 Base
    glPushMatrix();
    glTranslatef(1.0, 0.25, 0.0);
    glRotatef((GLfloat)fingerBase, 0.0, 0.0, 1.0);
    glTranslatef(0.15, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.3, 0.1, 0.15);
    glutWireCube(1);
    glPopMatrix();

    //Finger 2 Up
    glTranslatef(0.15, 0.0, 0.0);
    glRotatef((GLfloat)fingerUp, 0.0, 0.0, 1.0);
    glTranslatef(0.15, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.3, 0.1, 0.15);
    glutWireCube(1);
    glPopMatrix();
    glPopMatrix();

    //Finger RIGHT 3 Base
    glPushMatrix();
    glTranslatef(1.0, 0.25, 0.25);
    glRotatef((GLfloat)fingerBase, 0.0, 0.0, 1.0);
    glTranslatef(0.15, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.3, 0.1, 0.15);
    glutWireCube(1);
    glPopMatrix();

    //Finger RIGHT 3 Up 
    glTranslatef(0.15, 0.0, 0.0);
    glRotatef((GLfloat)fingerUp, 0.0, 0.0, 1.0);
    glTranslatef(0.15, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.3, 0.1, 0.15);
    glutWireCube(1);
    glPopMatrix();
    glPopMatrix();

    //Finger LEFT 4 Base
    glPushMatrix();
    glTranslatef(1.0, 0.25, -0.25);
    glRotatef((GLfloat)fingerBase, 0.0, 0.0, 1.0);
    glTranslatef(0.15, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.3, 0.1, 0.15);
    glutWireCube(1);
    glPopMatrix();

    //Finger 4 Up
    glTranslatef(0.15, 0.0, 0.0);
    glRotatef((GLfloat)fingerUp, 0.0, 0.0, 1.0);
    glTranslatef(0.15, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.3, 0.1, 0.15);
    glutWireCube(1);
    glPopMatrix();
    glPopMatrix();

    glPopMatrix();
    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(85.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -5.0);
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 's':
        if (shoulder > -90)
        {
            shoulder = (shoulder - 5) % 360;
        }
        glutPostRedisplay();
        break;
    case 'S':
        if (shoulder < 0)
        {
            shoulder = (shoulder + 5) % 360;
        }
        glutPostRedisplay();
        break;
    case 'e':
        if (elbow < 120) {
            elbow = (elbow + 5) % 360;
        }
        glutPostRedisplay();
        break;
    case 'E':
        if (elbow > 0)
        {
            elbow = (elbow - 5) % 360;
        }
        glutPostRedisplay();
        break;
    case 'f':
        if (fingerBasePhalange < 15)
        {
            fingerBasePhalange = (fingerBasePhalange + 5) % 360;
        }
        if (fingerBase > -45)
        {
            fingerBase = (fingerBase - 5) % 360;
        }
        glutPostRedisplay();
        break;
    case 'F':
        if (fingerBasePhalange > -10)
        {
            fingerBasePhalange = (fingerBasePhalange - 5) % 360;
        }
        if (fingerBase < 0)
        {
            fingerBase = (fingerBase + 5) % 360;

        }
        glutPostRedisplay();
        break;
    case 'p':
        if (fingerUpPhalange < 45)
        {
            fingerUpPhalange = (fingerUpPhalange + 5) % 360;
        }
        if (fingerUp > -45)
        {
            fingerUp = (fingerUp - 5) % 360;

        }
        glutPostRedisplay();
        break;
    case 'P':
        if (fingerUpPhalange > 0)
        {
            fingerUpPhalange = (fingerUpPhalange - 5) % 360;
        }
        if (fingerUp < 0) {
            fingerUp = (fingerUp + 5) % 360;
        }
        glutPostRedisplay();
        break;

    case 27:
        exit(0);
        break;
    default:
        break;
    }
}

static void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            moving = 1;
            startx = x;
            starty = y;
        }
        if (state == GLUT_UP) {
            moving = 0;
        }
    }
}


static void motion(int x, int y)
{
    if (moving) {
        angle = angle + (x - startx);
        angle2 = angle2 + (y - starty);
        startx = x;
        starty = y;
        glutPostRedisplay();
    }
}



int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
