// Full Body Movements //

// Mohamed Ahmed Abdullah 1190388
// Ismail Tawfik 1190264
// Abdulrahman Elshahed

// Includes
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <GL/glut.h>

//Body variables
static int body = 0; int run = 0;

//Right Shoulder variables
static int shoulder1 = 0, shoulder1R = 0, shoulder1V=0, elbow1 = 0, fingerBasePhalange = 0, fingerUpPhalange = 0;
static int fingerBase = 0, fingerUp = 0;

//Left Shoulder variables
static int shoulder2 = 0 , shoulder2L=0 , shoulder2V=0 , elbow2 = 0, shoulder=0;

int moving, startx, starty;


//Right Leg variables
static int legDown1 = 0,legR=0, legBase1 = 0, foot1 = 0;

//Left Leg variables
static int legDown2 = 0, legBase2 = 0,legL=0, foot2 = 0;

double eye[] = { 0 , 0, -5 };
double center[] = { 0, 0, 5 };
double up[] = { 0, 1, 0 };
double perpendicularAxis[] = { 0, 0, 0 };
GLfloat Znear = 100.0;
int windowWidth;
int windowHeight;


GLfloat angle = 0.0;   /* in degrees */
GLfloat angle2 = 0.0;   /* in degrees */

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

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    /////////////////
    gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], up[0], up[1], up[2]);
    glScalef(0.7, 0.7, 0.7);
    glRotatef(angle2, 1.0, 0.0, 0.0);
    glRotatef(angle, 0.0, 1.0, 0.0);

    //Mouse movements
    glRotatef(angle2, 1.0, 0.0, 0.0);
    glRotatef(angle, 0.0, 1.0, 0.0);
    glTranslatef(-1.0, 0.0, 0.0);

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

     //Right  Shoulder                   
    glPushMatrix();
    glTranslatef(1.2, 1.2, 0.0);
    glRotatef((GLfloat)shoulder1, 0.0, 0.0, 1.0);
    glRotatef((GLfloat)shoulder, 0.0, 0.0, 1.0);
    glTranslatef(0.0, 0.0, 0.0);
    glRotatef((GLfloat)shoulder1R, 0.0, 1.0, 0.0);
    glRotatef((GLfloat)shoulder1V, 1.0, 0.0, 0.0);

    glTranslatef(1.0, 0.0, 0.0);
    glPushMatrix();
    glScalef(2.0, 0.6, 1.0);
    glutWireCube(1.0);
    glPopMatrix();

    //elbow1
    glTranslatef(1.0, 0.0, 0.0);
    glRotatef((GLfloat)elbow1, 0.0, 0.0, 1.0);
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

    ////////////////////////////////////////////////

    // Left Arm

    //Left shoulder
    glPushMatrix();
    glTranslatef(-1.3, 1.2, 0.0);
    glRotatef((GLfloat)shoulder2, 0.0, 0.0, 1.0);
    glRotatef((GLfloat)-shoulder, 0.0, 0.0, 1.0);

    glTranslatef(0.0, 0.0, 0.0);
    glRotatef((GLfloat)shoulder2L, 0.0, 1.0, 0.0);
    glRotatef((GLfloat)shoulder2V, 1.0, 0.0, 0.0);

    glTranslatef(-1.0, 0.0, 0.0);
    glPushMatrix();
    glScalef(2.0, 0.6, 1.0);
    glutWireCube(1.0);
    glPopMatrix();

    //ELBOW 2                      
    glTranslatef(-1.0, 0.0, 0.0);
    glRotatef((GLfloat)elbow2, 0.0, 0.0, 1.0);
    glTranslatef(-1.0, 0.0, 0.0);
    glPushMatrix();
    glScalef(2.0, 0.6, 1.0);
    glutWireCube(1.0);
    glPopMatrix();


    // FINGERS

    // Finger 1 Up 
    glPushMatrix();
    glTranslatef(-1.6, -0.25, 0.0);
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
    glTranslatef(-1.6, 0.25, 0.0);
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
    glTranslatef(-1.6, 0.25, 0.25);
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
    glTranslatef(-1.6, 0.25, -0.25);
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



    /////////////////////////////////////////////////////////////////


    // Right  Leg 
    glPushMatrix();
    glTranslatef(1.0, -1.35, 0.0);
    glRotatef((GLfloat)legBase1, 1.0, 0.0, 0.0);
    glRotatef((GLfloat)legR, 0.0, 0.0, 1.0);

    glTranslatef(-0.35, -1.2, 0.0);
    glPushMatrix();
    glScalef(0.7, 2.0, 1.0);
    glutWireCube(1.0);
    glPopMatrix();


    // KNEE 1                       
    glPushMatrix();             
    glTranslatef(1.0, -1.35, 0.0);
    glRotatef((GLfloat)legDown1, 1.0, 0.0, 0.0);
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

    ////////////////////////////////////////////////////////////

    //Left Leg

    glPushMatrix();
    glTranslatef(1.0, -1.35, 0.0);
    glRotatef((GLfloat)legBase2, 1.0, 0.0, 0.0);  
    glTranslatef(-1.2, -0.0, 0.0);
    glRotatef((GLfloat)legL, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);
    glTranslatef(-1.53, -1.2, 0.0);
    glPushMatrix();
    glScalef(0.7, 2.0, 1.0);
    glutWireCube(1.0);
    glPopMatrix();


    //KNEE 2       
    glPushMatrix();
    glTranslatef(1.0, -1.35, 0.0);
    glRotatef((GLfloat)legDown2, 1.0, 0.0, 0.0);
    glTranslatef(-1, -0.7, 0.0);
    glPushMatrix();
    glScalef(0.7, 2.0, 1.0);
    glutWireCube(1.0);
    glPopMatrix();
    glTranslatef(0.0, -1.3, 0.0);
    glScalef(0.8, 0.7, 2.0);
    glutSolidCube(1.0);         //Left ankle 
    glPopMatrix();
    glPopMatrix();


    glPopMatrix();
    glutSwapBuffers();
}

void reshape(int w, int h)
{
    windowWidth = w;
    windowHeight = h;
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    printf("\n%f", Znear);
    gluPerspective(Znear, (GLfloat)w / (GLfloat)h, 0.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -5.0);
}


//////////////////////////

// Timer function
void timer(int t)
{
    if (run == 1) {
        glutTimerFunc(500, timer, 0);

        if (shoulder < 180)
        {
            shoulder = (shoulder + 5) % 360;
        }
        else
        {
            if (shoulder2 < 180)
            {
                shoulder2 = (shoulder2 + 5) % 360;
            }

            if (shoulder1 > -180)
            {
                shoulder1 = (shoulder1 - 5) % 360;
            }
        }
        if (shoulder == 180 && shoulder2 == 180 && shoulder1 == -180)
        {
            shoulder = 0;
            shoulder1 = 0;
            shoulder2 = 0;
        }

        glutPostRedisplay();
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
        timer(shoulder);
        glutPostRedisplay();
        break;

    case 'W':
        run = 0;
        glutPostRedisplay();
        break;

     /////////////////////////

     //Camera Movments
      
     ////////////////////////

          
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
        if (shoulder1 < 90)
        {
            shoulder1 = (shoulder1 + 5) % 360;
        }

        if (shoulder2 > -90)
        {

            shoulder2 = (shoulder2 - 5) % 360;

        }

        glutPostRedisplay();
        break;

    case 'S':

        if (shoulder1 > -90)
        {
            shoulder1 = (shoulder1 - 5) % 360;
        }

        if (shoulder2 < 90)
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
            shoulder2L = (shoulder2L - 5) %360 ;
        }

        glutPostRedisplay();
        break;

        /////////////

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

        if (shoulder2V > - 90)
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
   


        /////////////////////
        
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

        if (legBase1 >-15)
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


        //////////////////////
       
  
/////////////////////////////
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
