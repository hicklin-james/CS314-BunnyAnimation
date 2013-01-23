#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <iostream.h>

// Jumpcut variable
bool isJumpcutOn = true;

// Front right leg animation variables
GLfloat FRLegAngle = 0;
bool isFRLegUp = false;

// Front left leg animation variables
GLfloat FLLegAngle = 0;
bool isFLLegUp = false;

// Back right leg animation variables
GLfloat BRLegAngle = 0;
bool isBRLegUp = false;

// Back left leg animation variables
GLfloat BLLegAngle = 0;
bool isBLLegUp = false;

// Right ear animation variables
GLfloat REAngle = 0;
bool isREdown = false;

// Left ear animation variables
GLfloat LEAngle = 0;
bool isLEdown = false;

// Head nod animation variables
GLfloat headAngle = 0;
bool isHeadDown = false;

// Body Curl Animation variables
GLfloat curlAngle = 0;
bool isCurled = false;

// Jump Animation variables
GLfloat jumpHeight = 0;
GLfloat jumpAngle = 0;
bool isJumpUp = false;

// Rear Animation variables
GLfloat rearAngle = 0;
bool isReared = false;

// Animation frames count
GLfloat frames = 0;

int dumpPPM(int frameNum);
void drawAxis();
void drawFloor();
GLfloat jumpcutValue(bool isOn, GLfloat value, float max, float min);
GLfloat startAnimation(bool isOn, GLfloat value, int max, float incr);

unsigned char camera = 'r';

int iCount = 0;       // used for numbering the PPM image files
int Width = 400;      // window width (pixels)
int Height = 400;     // window height (pixels)
bool Dump=false;      // flag set to true when dumping animation frames

void idle() {
    if (frames != 200) {
        
        // Check for jump animation
        jumpAngle = startAnimation(isJumpUp, jumpAngle, 40, 0.2);
        jumpHeight = startAnimation(isJumpUp, jumpHeight, 1, 0.005);
        
        // Check for rear animation
        rearAngle = startAnimation(isReared, rearAngle, 90, 0.45);
        
        // Check for body curl animation
        curlAngle = startAnimation(isCurled, curlAngle, 40, 0.2);
        
        // Check for front right leg animation
        FRLegAngle = startAnimation(isFRLegUp, FRLegAngle, 70, 0.35);
        
        // Check for front left leg animation
        FLLegAngle = startAnimation(isFLLegUp, FLLegAngle, 70, 0.35);
        
        // Check for head nod animation
        headAngle = startAnimation(isHeadDown, headAngle, 12, 0.06);
        
        // Check for right ear wiggle animation
        REAngle = startAnimation(isREdown, REAngle, 140, 0.7);
        
        // Check for left ear wiggle animation
        LEAngle = startAnimation(isLEdown, LEAngle, 140, 0.7);
        
        // Check for back right leg animation
        BRLegAngle = startAnimation(isBRLegUp, BRLegAngle, 70, 0.35);
        
        // Check for back left leg animation
        BLLegAngle = startAnimation(isBLLegUp, BLLegAngle, 70, 0.35);
        
        frames++;
        glutPostRedisplay();
    }
    
    else {
        glutIdleFunc(NULL);
        frames = 0;
    }
}

void keyboardCallback(unsigned char c, int x, int y) {
    frames = 0;
    switch (c) {
        case 'q':
            exit (0);
            break;
        case 'p':
            camera = 'p';
            break;
        case 'f':
            camera = 'f';
            break;
        case 'b':
            camera = 'b';
            break;
        case 'a':
            camera = 'a';
            break;
        case 'u':
            camera = 'u';
            break;
        case 'r':
            camera = 'r';
            break;
        case 'i':
            dumpPPM(iCount);
            iCount++;
            break;
        case 'd':               // dump animation PPM frames
            iCount = 0;         // image file count
            Dump = !Dump;
            break;
        case 'j':
            isJumpUp = !isJumpUp;
            if (!isJumpcutOn)
                glutIdleFunc(idle);
            else {
                jumpAngle = jumpcutValue(isJumpUp, jumpAngle, 40, 0);
                jumpHeight = jumpcutValue(isJumpUp, jumpHeight, 1, 0);
            }
            break;
        case 'm':
            isFRLegUp = !isFRLegUp;
            if (!isJumpcutOn)
                glutIdleFunc(idle);
            else
                FRLegAngle = jumpcutValue(isFRLegUp, FRLegAngle, 70, 0);
            break;
        case 'l':
            isFLLegUp = !isFLLegUp;
            if (!isJumpcutOn)
                glutIdleFunc(idle);
            else
                FLLegAngle = jumpcutValue(isFLLegUp, FLLegAngle, 70, 0);
            break;
        case 'h':
            isHeadDown = !isHeadDown;
            if (!isJumpcutOn)
                glutIdleFunc(idle);
            else
                headAngle = jumpcutValue(isHeadDown, headAngle, 12, 0);
            break;
        case 'e':
            isREdown = !isREdown;
            if (!isJumpcutOn)
                glutIdleFunc(idle);
            else
                REAngle = jumpcutValue(isREdown, REAngle, 140, 0);
            break;
        case 'w':
            isLEdown = !isLEdown;
            if (!isJumpcutOn)
                glutIdleFunc(idle);
            else
                LEAngle = jumpcutValue(isLEdown, LEAngle, 140, 0);
            break;
        case 'c':
            isCurled = !isCurled;
            if (!isJumpcutOn)
                glutIdleFunc(idle);
            else
                curlAngle = jumpcutValue(isCurled, curlAngle, 40, 0);
            break;
        case 'o':
            isBRLegUp = !isBRLegUp;
            if (!isJumpcutOn)
                glutIdleFunc(idle);
            else
                BRLegAngle = jumpcutValue(isBRLegUp, BRLegAngle, 70, 0);
            break;
        case 'n':
            isBLLegUp = !isBLLegUp;
            if (!isJumpcutOn)
                glutIdleFunc(idle);
            else
                BLLegAngle = jumpcutValue(isBLLegUp, BLLegAngle, 70, 0);
            break;
        case 't':
            isReared = !isReared;
            if (!isJumpcutOn)
                glutIdleFunc(idle);
            else
                rearAngle = jumpcutValue(isReared, rearAngle, 90, 0);
            break;
        case ' ':
            isJumpcutOn = !isJumpcutOn;
            break;
            
    }
    
    glutPostRedisplay();
    
}

GLfloat jumpcutValue(bool isOn, GLfloat value, float max, float min) {
    if (isOn)
        return max;
    else
        return min;
}

void reshapeCallback(int w, int h)
{
    Width = w;
    Height = h;
    glViewport(0, 0, w, h);
}

void displayCallback()
{
    // clear the color buffer
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    
    // set up camera
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( 45, 1.0, 0.1, 200.0 );
    
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glTranslatef( 0.0, 0.0, -10.0 );
    switch (camera) {
        case 'p':
            glRotatef( 180, 0.0, 1.0, 0.0 );
            break;
        case 'f':
            glRotatef( -90, 0.0, 1.0, 0.0 );
            break;
        case 'b':
            glRotatef( 90, 0.0, 1.0, 0.0 );
            break;
        case 'a':
            glRotatef( 90, 1.0, 0.0, 0.0 );
            break;
        case 'u':
            glRotatef( -90, 1.0, 0.0, 0.0 );
            break;
        case 'r':
            break;
            
    }
    
    
    drawAxis();
    
    // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
    // Draw your rabbit here
    // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
    
    // Always start the hierarchy from the middle body block
    
    glPushMatrix(); // Save camera matrix
    glColor3f(1,1,1); // Make rabbit white
    
    // Draw middle body block
    glTranslatef(0,jumpHeight+1,0);
    glTranslatef(0,0.1,0);
    glRotatef(rearAngle,0,0,1);
    glTranslatef(0,-0.1,0);
    glutSolidCube(1.3);
    
    // Build front body block
    glPushMatrix();
    glTranslatef(0.8,-0.05,0);
    glRotatef(jumpAngle*0.7,0,0,1);
    glRotatef(-curlAngle*0.4,0,0,1);
    glScaled(0.4,1,1);
    glutSolidCube(1.3);
    glScaled(1/0.4,1,1);
    
    // Build front right leg
    glPushMatrix();
    glTranslatef(0.15,-0.35,0.25);
    glRotated(FRLegAngle+30,0,0,1);
    glTranslatef(-0.11,-0.35,0.25);
    glScalef(0.4,1,0.4);
    glutSolidCube(0.5);
    
    // Build front right paw
    glPushMatrix();
    glScalef(1/0.4,1,1/0.4);
    glTranslatef(0.05,-0.25,0);
    glRotated(-FRLegAngle*0.85-30,0,0,1);
    glScalef(0.6,0.2,0.5);
    glutSolidCube(0.5);
    glPopMatrix();
    glPopMatrix();
    
    // Build front left leg
    glPushMatrix();
    glTranslatef(0.15,-0.35,-0.25);
    glRotated(FLLegAngle+30,0,0,1);
    glTranslatef(-0.11,-0.35,-0.25);
    glScalef(0.4,1,0.4);
    glutSolidCube(0.5);
    
    // Build front left paw
    glPushMatrix();
    glScalef(1/0.4,1,1/0.4);
    glTranslatef(0.05,-0.25,0);
    glRotated(-FLLegAngle*0.85-30,0,0,1);
    glScalef(0.6,0.2,0.5);
    glutSolidCube(0.5);
    glPopMatrix();
    glPopMatrix();
    
    // Build neck
    glPushMatrix();
    glRotatef(-headAngle+15,0,0,1);
    glTranslatef(0.3,0.5,0);
    glScalef(1.5,0.5,0.5);
    glutSolidCube(1);
    glScalef(1/1.5,2,2);
    
    // Build Head
    glTranslatef(0.5,0,0);
    glRotatef(-headAngle*1.8,0,0,1);
    glRotatef(-rearAngle,0,0,1);
    glScalef(0.8,0.8,0.8);
    glutSolidCube(1);
    glScalef(1/0.8,1/0.8,1/0.8);
    
    // Build right eye
    glPushMatrix();
    glTranslatef(0.355,0.07,0.17);
    glScalef(0.1,0.1,0.1);
    glColor3f(1,0,0); // Make the rabbit evil!
    glutSolidCube(1);
    glPopMatrix();
    
    // Build left eye
    glPushMatrix();
    glTranslatef(0.355,0.07,-0.17);
    glScalef(0.1,0.1,0.1);
    glutSolidCube(1);
    glColor3f(1,1,1);
    glPopMatrix();
    
    // Build the right ear
    glPushMatrix();
    glTranslatef(0.2,0,0.42);
    glTranslatef(0,0.3,0);
    glRotatef(-155+REAngle,1,0,0);
    glTranslatef(0,-0.3,0);
    glScalef(0.2,0.7,0.07);
    glutSolidCube(1);
    glPopMatrix();
    
    // Build the left ear
    glPushMatrix();
    glTranslatef(0.2,0,-0.42);
    glTranslatef(0,0.3,0);
    glRotatef(155-LEAngle,1,0,0);
    glTranslatef(0,-0.3,0);
    glScalef(0.2,0.7,0.07);
    glutSolidCube(1);
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
    
    // Build back body block
    glTranslatef(-0.9,-0.1,0);
    glRotatef(-jumpAngle+22, 0, 0, 1);
    glTranslatef(0.5,0.5,0);
    glRotatef(curlAngle*0.8,0,0,1);
    glTranslatef(-0.5,-0.5,0);
    glScaled(0.95,1,1);
    glutSolidCube(1.2);
    glScaled(1/0.95,1,1);
    
    // Build the right back leg
    glPushMatrix();
    glTranslatef(-0.1,-0.25,0.75);
    glTranslatef(0,0.3,0);
    glRotatef(BRLegAngle*0.8,0,0,1);
    glTranslatef(0,-0.3,0);
    glScalef(0.8,1,0.2);
    glutSolidCube(1);
    glScalef(1/0.8,1,1/0.2);
    
    // Build right back paw
    glPushMatrix();
    glTranslatef(-0.2,-0.46,0);
    glTranslatef(-0.13,0,0);
    glRotatef(-22-BRLegAngle*0.7,0,0,1);
    glRotatef(-rearAngle,0,0,1);
    glTranslatef(0.18,0,0);
    glScalef(0.5,0.2,0.3);
    glutSolidCube(1);
    glPopMatrix();
    glPopMatrix();
    
    // Build the back left leg
    glPushMatrix();
    glTranslatef(-0.1,-0.25,-0.75);
    glTranslatef(0,0.3,0);
    glRotatef(BLLegAngle*0.8,0,0,1);
    glTranslatef(0,-0.3,0);
    glScalef(0.8,1,0.2);
    glutSolidCube(1);
    glScalef(1/0.8,1,1/0.2);
    
    // Build left back paw
    glPushMatrix();
    glTranslatef(-0.2,-0.46,0);
    glTranslatef(-0.13,0,0);
    glRotatef(-22-BLLegAngle*0.7,0,0,1);
    glRotatef(-rearAngle,0,0,1);
    glTranslatef(0.18,0,0);
    glScalef(0.5,0.2,0.3);
    glutSolidCube(1);
    glPopMatrix();
    glPopMatrix();
    
    // Build tail
    glTranslatef(-0.6,0.2,0);
    glScalef(0.5,0.5,0.5);
    glutSolidCube(1);
    glPopMatrix();
    
    
    //    cout << "jumpHeight " << jumpHeight << "\n";
    //    cout << "JumpAngle " << jumpAngle << "\n";
    //    cout << "headAngle " << headAngle << "\n";
    //    cout << "FLLegAngle " << FLLegAngle << "\n";
    //    cout << "FRLegAngle " << FRLegAngle << "\n";
    //    cout << "count:" << frames << "\n";
    //    cout << "REangle " << REAngle << isREdown << "  " << "\n";
    //    cout << "LEangle " << LEAngle << isLEdown << "  " << "\n";
    
    // draw after the opaque objects, since it is translucent
    drawFloor();
    
    // draw the buffer to the screen
    glutSwapBuffers();
    
    if (Dump) {               // save images to file
        dumpPPM(iCount);
        iCount++;
    }
    
    GLenum error = glGetError();
    if(error != GL_NO_ERROR)
        printf("ERROR: %s\n", gluErrorString(error));
    
}


//---------------------------------------------------------------

// Function that takes as input a boolean that determines whether the animation
// is on or off, the value to be modified in the animation, the maximum value
// it will reach, and the amount at which the value must be modified. It returns
// the new value. This is the function that actually makes the rabbit to move.
GLfloat startAnimation(bool isOn, GLfloat value, int max, float incr) {
    if (isOn && value < max)
        return value + incr;
    else if (!isOn && value > 0)
        return value - incr;
    else
        return value;
}

// Draw a set of coloured cones representing the current local coord system.
// X -> red, Y -> green, Z -> blue.

void drawAxis() {
    float axisHeight = 0.75; // TODO
    float axisBase = 0.075;
    glColor3f(0, 0, 1);
    glutSolidCone(axisBase, axisHeight, 8, 2);
    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glColor3f(1, 0, 0);
    glutSolidCone(axisBase, axisHeight, 8, 2);
    glPopMatrix();
    glPushMatrix();
    glRotatef(-90, 1, 0, 0);
    glColor3f(0, 1, 0);
    glutSolidCone(axisBase, axisHeight, 8, 2);
    glPopMatrix();
}

void drawFloor() {
    // Draw a floor. Since it is transparent, we need to do it AFTER all of
    // the opaque objects.
    for (int x = -5; x < 5; x++) {
        for (int y = -5; y < 5; y++) {
            glColor4f(1, 1, 1, (x + y) % 2 ? 0.75 : 0.5);
            glNormal3f(0, 1, 0);
            glBegin(GL_POLYGON);
            glVertex3f(x    , 0, y    );
            glVertex3f(x + 1, 0, y    );
            glVertex3f(x + 1, 0, y + 1);
            glVertex3f(x    , 0, y + 1);
            glEnd();
        }
    }
    // visible from initial side angle
    glBegin(GL_POLYGON);
    glVertex3f(-5,    0, 0);
    glVertex3f(-5, -.05, 0);
    glVertex3f( 5, -.05, 0);
    glVertex3f( 5,    0, 0);
    glEnd();
    
    // visible from front angle
    glBegin(GL_POLYGON);
    glVertex3f(0,    0, -5);
    glVertex3f(0, -.05, -5);
    glVertex3f(0, -.05, 5);
    glVertex3f(0,    0, 5);
    glEnd();
}

int dumpPPM(int frameNum)
{
    FILE *fp;
    const int maxVal=255;
    register int y;
    unsigned char *pixels;
    
    glReadBuffer( GL_FRONT );
    char fname[100];
    sprintf(fname,"/Users/jameshicklin/Documents/img%03d.ppm",frameNum);
    fp = fopen(fname,"wb");
    if (!fp) {
        printf("Unable to open file '%s'\n",fname);
        return 1;
    }
    printf("Saving image `%s`\n",fname);
    fprintf(fp, "P6 ");
    fprintf(fp, "%d %d ", Width, Height);
    fprintf(fp, "%d", maxVal);
    putc(13,fp);
    pixels = new unsigned char [3*Width];
    
    y = 0;
    glReadPixels(0,Height-1,Width,1,GL_RGB,GL_UNSIGNED_BYTE, (GLvoid *) pixels);
    
    for ( y = Height-1; y >=0; y-- ) {
        glReadPixels(0,y,Width,1,GL_RGB,GL_UNSIGNED_BYTE, (GLvoid *) pixels);
        for (int n=0; n<3*Width; n++) {
            putc(pixels[n],fp);
        }
    }
    fclose(fp);
    delete [] pixels;
    return 0;
    
}

//---------------------------------------------------------------

int main(int argc, char **argv)
{
    // create window and rendering context
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_DEPTH | GLUT_RGB | GLUT_DOUBLE );
    glutInitWindowSize( Width, Height );
    glutCreateWindow( "Evil Rabbit" );
    
    // register display callback
    glutDisplayFunc( displayCallback );
    glutKeyboardFunc( keyboardCallback );
    
    glViewport( 0, 0, Width, Height );
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_NORMALIZE );
    
    // Turn on blending (for floor).
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    
    // lighting stuff
    GLfloat ambient[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat diffuse[] = {0.9, 0.9, 0.9, 1.0};
    GLfloat specular[] = {0.4, 0.4, 0.4, 1.0};
    GLfloat position0[] = {1.0, 1.0, 1.0, 0.0};
    glLightfv( GL_LIGHT0, GL_POSITION, position0 );
    glLightfv( GL_LIGHT0, GL_AMBIENT, ambient );
    glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuse );
    glLightfv( GL_LIGHT0, GL_SPECULAR, specular );
    GLfloat position1[] = {-1.0, -1.0, -1.0, 0.0};
    glLightfv( GL_LIGHT1, GL_POSITION, position1 );
    glLightfv( GL_LIGHT1, GL_AMBIENT, ambient );
    glLightfv( GL_LIGHT1, GL_DIFFUSE, diffuse );
    glLightfv( GL_LIGHT1, GL_SPECULAR, specular );
    
    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );
    glEnable( GL_LIGHT1 );
    glEnable( GL_COLOR_MATERIAL );
    
    // pass control over to GLUT
    glutMainLoop();
    
    return 0;       // never reached
}

