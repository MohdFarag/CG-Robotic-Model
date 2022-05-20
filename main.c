// Full Body Movements //

// Mohamed Ahmed Abdullah 1190388
// Ismail Tawfik 1190264

// Includes
#include "glm.h"
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include "imageloader.h"


//Body variables
static int body = 0; int run = 0;

//Right Shoulder variables
static int shoulder1 = 0, shoulder1R = 0, shoulder1V = 0, elbow1 = 0, elbow1RF = 0, fingerBasePhalange = 0, fingerUpPhalange = 0;
static int fingerBase = 0, fingerUp = 0;

//Left Shoulder variables
static int shoulder2 = 0, shoulder2L = 0, shoulder2V = 0, elbow2 = 0, elbow2RF = 0, shoulder = 0;

//Right Leg variables
static int legDown1 = 0, legR = 0, legBase1 = 0, foot1 = 0;

//Left Leg variables
static int legDown2 = 0, legBase2 = 0, legL = 0, foot2 = 0;

int moving, startx, starty;

double eye[] = { 0 , 0, -10 };
double center[] = { 0, 0, 10 };
double up[] = { 0, 1, 0 };
double perpendicularAxis[] = { 0, 0, 0 };
GLfloat Znear = 100.0;

int windowWidth;
int windowHeight;

GLfloat angle = 0.0;   /* in degrees */
GLfloat angle2 = 0.0;   /* in degrees */
GLfloat zDistance = 10.0;

/* Path of the external objects used in the application */
char objectPathBed[] = "data/Bed.obj";
char objectPathBook[] = "data/book.obj";
char objectPathDrawer[] = "data/drawer.obj";
char objectPathOffice[] = "data/office_desk.obj";
char objectPathScreen[] = "data/monitorLCD.obj";
char objectPathLamp[] = "data/deskLamp1.obj";
char objectPathlargeCouch[] = "data/plaidChair.obj";


GLMmodel* Bed = glmReadOBJ(objectPathBed);
GLMmodel* Books = glmReadOBJ(objectPathBook);
GLMmodel* Drawer = glmReadOBJ(objectPathDrawer);
GLMmodel* Office = glmReadOBJ(objectPathOffice);
GLMmodel* Screen = glmReadOBJ(objectPathScreen);
GLMmodel* Lamp = glmReadOBJ(objectPathLamp);
GLMmodel* largeCouch = glmReadOBJ(objectPathlargeCouch);


/* lighting parameters */
GLfloat light_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat light_diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_position[] = { 0.5, 5.0, 0.0, 1.0 };
GLfloat lightPos1[] = { -0.5, -5.0, -2.0, 1.0 };

/* material parameters */
GLfloat mat_amb_diff[] = { 0.643, 0.753, 0.934, 1.0 };
GLfloat mat_specular[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat shininess[] = { 100.0 };

GLfloat mat_amb_diff_2[] = { 0.2, 0.2, 0.2, 1.0 };
GLfloat mat_specular_2[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat shininess_2[] = { 30.0 };

GLuint _textureId; //The id of the texture

/**************************************************************
FUNCTION: to draw the external object and scale it in the world space
INPUT:    pointer to the object
***************************************************************/
void drawmodel(GLMmodel* object)
{
    glmUnitize(object);
    glmFacetNormals(object);
    glmVertexNormals(object, 90.0);
    glmScale(object, .05);
    glmDraw(object, GLM_SMOOTH | GLM_MATERIAL);
}
/**************************************************************
FUNCTION: convert the image into a texture
INPUT:    pointer to the image
RETURN:   id of the texture
***************************************************************/
GLuint loadTexture(Image* image)
{
    GLuint textureId;
    glGenTextures(1, &textureId);			 //Make room for our texture
    glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
    //Map the image to the texture
    glTexImage2D(GL_TEXTURE_2D,				  //Always GL_TEXTURE_2D
        0,							  //0 for now
        GL_RGB,					  //Format OpenGL uses for image
        image->width, image->height, //Width and height
        0,							  //The border of the image
        GL_RGB,					  //GL_RGB, because pixels are stored in RGB format
        GL_UNSIGNED_BYTE,			  //GL_UNSIGNED_BYTE, because pixels are stored
                                     //as unsigned numbers
        image->pixels);			  //The actual pixel data
    return textureId;						  //Returns the id of the texture
}


//////////////////////////////


// Camera Movments
void rotatePoint(double a[], double theta, double p[])
{
    double temp[3];
    temp[0] = p[0];
    temp[1] = p[1];
    temp[2] = p[2];
    temp[0] = -a[2] * p[1] + a[1] * p[2];
    temp[1] = a[2] * p[0] - a[0] * p[2];
    temp[2] = -a[1] * p[0] + a[0] * p[1];
    temp[0] *= sin(theta);
    temp[1] *= sin(theta);
    temp[2] *= sin(theta);
    temp[0] += (1 - cos(theta)) * (a[0] * a[0] * p[0] + a[0] * a[1] * p[1] + a[0] * a[2] * p[2]);
    temp[1] += (1 - cos(theta)) * (a[0] * a[1] * p[0] + a[1] * a[1] * p[1] + a[1] * a[2] * p[2]);
    temp[2] += (1 - cos(theta)) * (a[0] * a[2] * p[0] + a[1] * a[2] * p[1] + a[2] * a[2] * p[2]);
    temp[0] += cos(theta) * p[0];
    temp[1] += cos(theta) * p[1];
    temp[2] += cos(theta) * p[2];
    p[0] = temp[0];
    p[1] = temp[1];
    p[2] = temp[2];
}

void crossProduct(double a[], double b[], double c[])
{
    c[0] = a[1] * b[2] - a[2] * b[1];
    c[1] = a[2] * b[0] - a[0] * b[2];
    c[2] = a[0] * b[1] - a[1] * b[0];
}

void normalize(double a[])
{
    double norm;
    norm = a[0] * a[0] + a[1] * a[1] + a[2] * a[2];
    norm = sqrt(norm);
    a[0] /= norm;
    a[1] /= norm;
    a[2] /= norm;
}


/////////////////////////////////


void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}


void drawFinger(char rightOrLeft, int num, bool isPhalange) {

    static int fingerBaseRotate = 0, fingerUpRotate;

    float type = 0;
    if (isPhalange)
    {
        fingerBaseRotate = (GLfloat)fingerBasePhalange;
        fingerUpRotate = (GLfloat)fingerUpPhalange;
        type = -0.25;
    }
    else {
        fingerBaseRotate = (GLfloat)fingerBase;
        fingerUpRotate = (GLfloat)fingerUp;
        type = 0.25;
    }

    float dir = 0;
    switch (rightOrLeft)
    {
    case 'R':
        dir = 1;
        break;
    case 'L':
        dir = -1.6;
        break;
    default:
        dir = 0;
        break;
    }

    float pos = 0;
    switch (num)
    {
    case 1:
        pos = 0;
        break;
    case 2:
        pos = 0.25;
        break;
    case 3:
        pos = -0.25;
        break;
    default:
        num = 0;
        break;
    }

    // Finger 1 Up
    glPushMatrix();
    glTranslatef(dir, type, pos);
    glRotatef(fingerBaseRotate, 0.0, 0.0, 1.0);
    glTranslatef(0.15, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.3, 0.1, 0.15);
    glutWireCube(1);
    glPopMatrix();

    ////Finger 2 Base
    glTranslatef(0.15, 0.0, 0.0);
    glRotatef(fingerUpRotate, 0.0, 0.0, 1.0);
    glTranslatef(0.15, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.3, 0.1, 0.15);
    glutWireCube(1);
    glPopMatrix();
    glPopMatrix();
}

void drawArm(char rightOrLeft) {
    int shoulder = 0, shoulderR = 0, shoulderV = 0, elbowRF = 0;

    if (rightOrLeft == 'R')
    {
        shoulder = shoulder;
        shoulderR = shoulder1R;
        shoulderV = shoulder1V;
        elbowRF = elbow1RF;
    }
    else {
        shoulder = -shoulder;
        shoulderR = shoulder2L;
        shoulderV = shoulder2V;
        elbowRF = elbow2RF;
    }

    // Shoulder                   
    glPushMatrix();
    glTranslatef(1.2, 1.2, 0.0);
    glRotatef((GLfloat)shoulder1, 0.0, 0.0, 1.0);
    glRotatef((GLfloat)shoulder, 0.0, 0.0, 1.0);
    glRotatef((GLfloat)-90, 0.0, 0.0, 1.0);

    glRotatef((GLfloat)shoulderR, 0.0, 1.0, 0.0);
    glRotatef((GLfloat)shoulderV, 1.0, 0.0, 0.0);

    glTranslatef(1.0, 0.0, 0.0);
    glPushMatrix();
    glScalef(2.0, 0.6, 1.0);
    glutWireCube(1.0);
    glPopMatrix();

    // Elbow (elbow)
    glTranslatef(1.0, 0.0, 0.0);
    glRotatef((GLfloat)elbow1, 0.0, 0.0, 1.0);
    glRotatef((GLfloat)elbowRF, 0.0, 1.0, 0.0);
    glTranslatef(1.0, 0.0, 0.0);
    glPushMatrix();
    glScalef(2.0, 0.6, 1.0);
    glutWireCube(1.0);
    glPopMatrix();


    // FINGERS
    drawFinger('R', 1, true);
    drawFinger('R', 1, false);
    drawFinger('R', 2, false);
    drawFinger('R', 3, false);
    glPopMatrix();

}

void drawLeg(char rightOrLeft) {

    int legBase = 0;
    int legDown = 0;
    int leg = 0;

    switch (rightOrLeft)
    {
    case 'R':
        legBase = -legBase1;
        legDown = -legDown1;
        leg = legR;
        break;
    case 'L':
        legBase = -legBase2;
        legDown = -legDown2;
        leg = legL;
        break;
    default:
        break;
    }

    // Leg 
    glPushMatrix();
    glTranslatef(1.0, -1.35, 0.0);
    glRotatef((GLfloat)legBase, 1.0, 0.0, 0.0);
    glRotatef((GLfloat)leg, 0.0, 0.0, 1.0);

    glTranslatef(-0.35, -1.2, 0.0);
    glPushMatrix();
    glScalef(0.7, 2.0, 1.0);
    glutWireCube(1.0);
    glPopMatrix();


    // KNEE                      
    glPushMatrix();
    glTranslatef(1.0, -1.35, 0.0);
    glRotatef((GLfloat)legDown, 1.0, 0.0, 0.0);
    glTranslatef(-1, -0.7, 0.0);
    glPushMatrix();
    glScalef(0.7, 2.0, 1.0);
    glutWireCube(1.0);
    glPopMatrix();
    glTranslatef(0.0, -1.3, 0.0);
    glScalef(0.8, 0.7, 2.0);
    glutSolidCube(1.0);         // Right ankle 
    glPopMatrix();
    glPopMatrix();

}


void display(void)
{
    glPushMatrix();
    /////////////////
    glScalef(0.9, 0.9, 0.9);

    //Mouse movements
    glTranslatef(-9.0, 0.0, 3.0);
    glRotatef(-90, 0.0, 1.0, 0.0);
    glTranslatef(0.0, 0.0, zDistance);

    // Head
    glPushMatrix();
    glTranslatef(1.0, 2.4, 0.0);
    glScalef(1, 1, 1);
    glutWireSphere(0.6, 8, 20); /* draw head */
    glPopMatrix();

    ////////////////////////////////////////////////

    //Body
    glRotatef((GLfloat)body, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);
    glPushMatrix();
    glScalef(2.0, 2.9, 1.0);
    glutWireCube(1.0);
    glPopMatrix();

    //////////////////

    // Right Arm
    drawArm('R');

    ////////////////////////////////////////////////

    // Left Arm
    glRotatef(180, 0, 1, 0);
    drawArm('L');

    /////////////////////////////////////////////////////////////////
    // Right Leg
    drawLeg('R');
    ////////////////////////////////////////////////////////////

    // Left Leg
    glTranslatef(-1.30, 0.0, 0.0);
    drawLeg('L');

    glPopMatrix();
    glutSwapBuffers();

}

void displayEnvironment(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glRotatef(angle2, 1.0, 0.0, 0.0);
    glRotatef(angle, 0.0, 1.0, 0.0);

    gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], up[0], up[1], up[2]);
    /*********************************************************************
                                        CARPET
    **********************************************************************/
    glPushMatrix();
    glScalef(5.1, 5.1, 10.1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBegin(GL_QUADS);
    glNormal3f(0.0, 1.0, 0.0);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0, -0.2, 0.0);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0, -0.2, 0.0);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0, -0.2, -1.0);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0, -0.2, -1.0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();


    /**************************************************************
                                    EXTERNAL OBJECTS
    ***************************************************************/

    glPushMatrix();
    glTranslatef(0.075, 0.0, -9.86);
    glRotatef(180.0, 0.0, 1.0, 0.0);
    drawmodel(Bed);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.02, 0.0, -9.975);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glScalef(0.1, 0.1, 0.1);
    drawmodel(largeCouch);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.01, -0.02, -9.78);
    glScalef(1.2, 1.2, 1.2);
    drawmodel(Office);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.04, 0.023, -9.78);
    glRotatef(-90.0, 0.0, 1.0, 0.0);
    glScalef(0.29, 0.29, 0.29);
    drawmodel(Lamp);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.01, 0.025, -9.78);
    glScalef(0.45, 0.45, 0.45);
    glRotatef(180, 0.0, 1.0, 0.0);
    drawmodel(Screen);
    glPopMatrix();


    display();
}

void reshape(int w, int h)
{
    windowWidth = w;
    windowHeight = h;
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(Znear, (GLfloat)w / (GLfloat)h, 0.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -5.0);
}


//////////////////////////

// Motion of Robot
void motion(int x, int y)
{
    if (moving) {
        int dx = x - startx;
        int dy = y - starty;
        rotatePoint(up, -(dx % 360) * 0.01, center);
        crossProduct(up, center, perpendicularAxis);
        normalize(perpendicularAxis);
        rotatePoint(perpendicularAxis, -dy * 0.01, center);
        rotatePoint(perpendicularAxis, -dy * 0.01, up);
        startx = x;
        starty = y;
        glutPostRedisplay();
    }
}

/* angle positions for 8 different frames to be used in animation (timer functions) */
int anglePositions[8][8] = { 
                  {-10,  30, -20, -30,   20, -20,  10,   -10},
                  {-40,  70, -50, -70,   40, -40,  25,  -25},
                  {-10,  30, -20, -30,   20, -20,  10,   -10},
                  {0,     0,   0,   0,    0,   0,   0,  0},
                  {10,   30,  20, -30,  -20,  20,  10, -10},
                  {40,   70,  50, -70,  -40,  40,  25, -25},
                  {10,   30,  20, -30,  -20,  20,  10, -10},
                  {0,     0,   0,   0,    0,   0,   0,  0}
};

void setAnglePositions(int frameNum)
{
    shoulder1R = anglePositions[frameNum][0];
    elbow1RF = anglePositions[frameNum][1];

    shoulder2L = anglePositions[frameNum][2];
    elbow2RF = anglePositions[frameNum][3];

    legBase1 = anglePositions[frameNum][4];
    legBase2 = anglePositions[frameNum][5];

    legDown1 = anglePositions[frameNum][6];
    legDown2 = anglePositions[frameNum][7];
}

// Timer Function
static int f = 0;
void timer(int value) {
    if (run == 1) {
        f = f % 8;
        setAnglePositions(f);
        f++;
        if (zDistance <= eye[2])
        {
            zDistance = 10.0;
        }
        else
        {
            zDistance -= 0.2;
        }
        glutPostRedisplay();
        glutTimerFunc(150, timer, 0);
    }
}

////////////////////////////

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        //Timer Function Movments  

    case 'w':
        run = 1;
        timer(0);
        glutPostRedisplay();
        break;

    case 'W':
        run = 0;
        glutPostRedisplay();
        break;

        /////////////////////////

        //Camera Movments

        ////////////////////////
        
        // Camera Top
    case '8':
        crossProduct(up, center, perpendicularAxis);
        normalize(perpendicularAxis);
        rotatePoint(perpendicularAxis, 0.05, center);
        rotatePoint(perpendicularAxis, 0.05, up);
        glutPostRedisplay();
        break;

        //Camera Down
    case '2':
        crossProduct(up, center, perpendicularAxis);
        normalize(perpendicularAxis);
        rotatePoint(perpendicularAxis, -0.05, center);
        rotatePoint(perpendicularAxis, -0.05, up);
        glutPostRedisplay();
        break;

        // Camera Right
    case '6':
        rotatePoint(up, -0.05, center);
        glutPostRedisplay();
        break;

        //Camera Left
    case '4':
        rotatePoint(up, 0.05, center);
        glutPostRedisplay();
        break;
        ///////////////////////////////////////

        // Move Camera Forward	'R'
    case 'R':

        if (Znear > 120)
        {
            Znear = 120;
        }
        else if (Znear <= 60)
        {
            Znear = 60;
        }
        else
        {
            Znear -= 1.0;
        }

        reshape(windowWidth, windowHeight);

        glutPostRedisplay();
        break;

        // Move Camera Backward  'B'
    case 'B':

        if (Znear >= 120)
        {
            Znear = 120;
        }
        else if (Znear < 60)
        {
            Znear = 60;
        }
        else
        {
            Znear += 1.0;
        }
        reshape(windowWidth, windowHeight);

        glutPostRedisplay();
        break;

        ////////////////////////

        // Arms movments 

        ///////////////////////

        //Shoulder Rotations 's','S' 
    case 's':
        if (shoulder1 < 180)
        {
            shoulder1 = (shoulder1 + 5) % 360;
        }

        if (shoulder2 > -180)
        {

            shoulder2 = (shoulder2 - 5) % 360;

        }

        glutPostRedisplay();
        break;

    case 'S':

        if (shoulder1 > 0)
        {
            shoulder1 = (shoulder1 - 5) % 360;
        }

        if (shoulder2 < 0)
        {
            shoulder2 = (shoulder2 + 5) % 360;
        }

        glutPostRedisplay();
        break;

        ///////////////////////////////////////////

        // Right Arm Rotation  Z 'z','Z'
    case 'z':

        if (shoulder2L > -180)

        {
            shoulder2L = (shoulder2L - 5) % 360;
        }

        glutPostRedisplay();
        break;

    case 'Z':

        if (shoulder2L < 15)

        {
            shoulder2L = (shoulder2L + 5);
        }

        glutPostRedisplay();
        break;


        // Left Arm Rotation Z 'x','X'
    case 'x':

        if (shoulder1R < 180)

        {
            shoulder1R = (shoulder1R + 5);
        }

        glutPostRedisplay();
        break;


    case 'X':

        if (shoulder1R > -15)

        {
            shoulder1R = (shoulder1R - 5);
        }

        glutPostRedisplay();
        break;

        // Arm Rotation X
    case 'l':
        if (shoulder1V < 90)
        {
            shoulder1V = (shoulder1V + 5) % 360;
        }

        if (shoulder2V > -90)
        {
            shoulder2V = (shoulder2V - 5) % 360;
        }

        glutPostRedisplay();
        break;

    case 'L':

        if (shoulder1V > -90)
        {
            shoulder1V = (shoulder1V - 5) % 360;
        }

        if (shoulder2V < 90)
        {
            shoulder2V = (shoulder2V + 5) % 360;
        }

        glutPostRedisplay();
        break;

        //Elbowes Movment
    case 'e':

        if (elbow1 < 150)
        {
            elbow1 = (elbow1 + 5) % 360;
        }

        if (elbow2 > -150)
        {
            elbow2 = (elbow2 - 5) % 360;
        }

        glutPostRedisplay();
        break;

    case 'E':

        if (elbow1 > 0)
        {
            elbow1 = (elbow1 - 5) % 360;
        }

        if (elbow2 < 0)
        {
            elbow2 = (elbow2 + 5) % 360;
        }

        glutPostRedisplay();
        break;

        //Fingers Movment
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


        // Phalange movments
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

        /////////////////////////

        // Legs Movements

        /////////////////////////


        //Right Leg

        //Right lge Rotation 'h' , 'H'
        //Right Knee 'k','K'
        //Right leg Z 'o','O'

    case 'h':

        if (legBase2 < 90)
        {
            legBase2 = (legBase2 + 5) % 360;

        }

        glutPostRedisplay();
        break;

    case 'H':

        if (legBase2 > -15)
        {
            legBase2 = (legBase2 - 5) % 360;

        }

        glutPostRedisplay();
        break;


        //Right knee Rotationn
    case 'k':
        if (legDown2 > -90)
        {
            legDown2 = (legDown2 - 5) % 360;

        }
        glutPostRedisplay();
        break;

    case 'K':

        if (legDown2 < 0)
        {
            legDown2 = (legDown2 + 5) % 360;

        }

        glutPostRedisplay();
        break;

        // Right Hip Z
    case 'o':
        if (legL > -75)

        {
            legL = (legL - 5);
        }


        glutPostRedisplay();
        break;


    case 'O':
        if (legL < 30)
        {
            legL = (legL + 5);

        }
        glutPostRedisplay();
        break;

    //////////////////////////////////////

    // Left Leg
    // Left Leg Rotations 'i','I'
    //Left Knee 'n','N'
    //left Leg Z 'j','J'

     //// Left Leg Rotations
    case 'i':
        if (legBase1 < 90)
        {
            legBase1 = (legBase1 + 5) % 360;

        }
        glutPostRedisplay();
        break;

    case 'I':

        if (legBase1 > -15)
        {
            legBase1 = (legBase1 - 5) % 360;

        }

        glutPostRedisplay();
        break;


        //Left knee Rotation
    case 'n':
        if (legDown1 > -90)
        {
            legDown1 = (legDown1 - 5) % 360;

        }

        glutPostRedisplay();
        break;

    case 'N':

        if (legDown1 < 0)
        {
            legDown1 = (legDown1 + 5) % 360;

        }

        glutPostRedisplay();
        break;

    case 'j':

        if (legR < 75)
        {
            legR = (legR + 5);

        }

        glutPostRedisplay();
        break;

    case 'J':

        if (legR > -30)

        {
            legR = (legR - 5);
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

void screan_menu(int m)
{
    glutPostRedisplay();
    if (m == 1) {
        Image* image = loadBMP("images/Texture1.bmp");
        _textureId = loadTexture(image);
        delete image;
    }
    else if (m == 2)
    {
        Image* image = loadBMP("images/Texture2.bmp");
        _textureId = loadTexture(image);
        delete image;
    }
    else if (m == 3)
    {
        Image* image = loadBMP("images/Texture3.bmp");
        _textureId = loadTexture(image);
        delete image;
    }
    else if (m == 4)
    {
        Image* image = loadBMP("images/Texture4.bmp");
        _textureId = loadTexture(image);
        delete image;
    }
    else {

    }
}

void initCarpet(void) {
    Image* image = loadBMP("images/Texture1.bmp");
    _textureId = loadTexture(image);
    delete image;
}

void attachMenu() {
    glutCreateMenu(screan_menu);
    glutAddMenuEntry("carpet Menu", 0);
    glutAddMenuEntry("Texture 1", 1);
    glutAddMenuEntry("Texture 2", 2);
    glutAddMenuEntry("Texture 3", 3);
    glutAddMenuEntry("Texture 4", 4);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void initRendering()
{
    initCarpet();
    // Turn on the power
    glEnable(GL_LIGHTING);
    // Flip light switch
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    // assign light parameters
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
    // Material Properties
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, mat_amb_diff);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
    GLfloat lightColor1[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor1);
    glEnable(GL_NORMALIZE);
    //Enable smooth shading
    glShadeModel(GL_SMOOTH);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    initRendering();
    glMatrixMode(GL_PROJECTION);
    gluPerspective(100, 3.0, -3.9, 7);
    attachMenu();
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutDisplayFunc(displayEnvironment);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}