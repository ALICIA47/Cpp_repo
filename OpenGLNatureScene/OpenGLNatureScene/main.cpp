#include <GL/glut.h>
#include <GL/glu.h>
#include <math.h>
#include <stdlib.h>

// Camera orbit (time‑based)
float rotationAngle = 0.0f;
int   prevTime = 0;
const float ANGLE_PER_SECOND = 6.0f;   // 6°/s → 60 s per circle

// Train animation
float trainT = 0.0f;
const float TRAIN_SPEED = 0.08f;       // one full lap per ~12.5 seconds

const float PI = 3.1415926535f;
const float cameraRadius = 5.5f;
const float cameraHeight = 2.0f;
const float centerX = 0.0f, centerY = -1.2f, centerZ = -5.0f;

// Room boundaries
const float roomLeft = -8.0f;
const float roomRight = 8.0f;
const float roomBack = -12.0f;
const float roomFront = 2.0f;
const float roomBottom = -2.25f;
const float roomTop = 2.0f;

// Elliptical track
const float trackCenterX = 0.0f;
const float trackCenterZ = -5.0f;
const float trackRadiusX = 2.5f;
const float trackRadiusZ = 1.5f;
const float trackY = roomBottom + 0.02f;

// ------------------------------------------------------------
void init(void) {
    glClearColor(0.53f, 0.81f, 0.98f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat lightAmbient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat lightDiffuse[] = { 0.9f, 0.9f, 0.9f, 1.0f };
    GLfloat lightPosition[] = { 5.0f, 10.0f, 5.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    prevTime = glutGet(GLUT_ELAPSED_TIME);
}

// ------------------------------------------------------------
void drawBox(float w, float h, float d) {
    float x = w * 0.5f, y = h * 0.5f, z = d * 0.5f;
    glBegin(GL_TRIANGLES);
    glNormal3f(0, 0, 1);  glVertex3f(-x, -y, z); glVertex3f(x, -y, z); glVertex3f(x, y, z);
    glVertex3f(-x, -y, z); glVertex3f(x, y, z); glVertex3f(-x, y, z);
    glNormal3f(0, 0, -1); glVertex3f(x, -y, -z); glVertex3f(-x, -y, -z); glVertex3f(-x, y, -z);
    glVertex3f(x, -y, -z); glVertex3f(-x, y, -z); glVertex3f(x, y, -z);
    glNormal3f(1, 0, 0);  glVertex3f(x, -y, z); glVertex3f(x, -y, -z); glVertex3f(x, y, -z);
    glVertex3f(x, -y, z); glVertex3f(x, y, -z); glVertex3f(x, y, z);
    glNormal3f(-1, 0, 0); glVertex3f(-x, -y, -z); glVertex3f(-x, -y, z); glVertex3f(-x, y, z);
    glVertex3f(-x, -y, -z); glVertex3f(-x, y, z); glVertex3f(-x, y, -z);
    glNormal3f(0, 1, 0);  glVertex3f(-x, y, z); glVertex3f(x, y, z); glVertex3f(x, y, -z);
    glVertex3f(-x, y, z); glVertex3f(x, y, -z); glVertex3f(-x, y, -z);
    glNormal3f(0, -1, 0); glVertex3f(-x, -y, -z); glVertex3f(x, -y, -z); glVertex3f(x, -y, z);
    glVertex3f(-x, -y, -z); glVertex3f(x, -y, z); glVertex3f(-x, -y, z);
    glEnd();
}

// ------------------------------------------------------------
void drawLegoBrick(float x, float y, float z, float rotY,
    float r, float g, float b,
    float w, float h, float d,
    int studRows, int studCols)
{
    glPushMatrix();
    glColor3f(r, g, b);
    glTranslatef(x, y, z);
    glRotatef(rotY, 0, 1, 0);
    drawBox(w, h, d);

    glColor3f(r * 0.9f, g * 0.9f, b * 0.9f);
    float studR = fmin(w, d) * 0.15f;
    float studH = h * 0.3f;
    float startX = -(w / 2.0f) + (w / (studRows + 1));
    float startZ = -(d / 2.0f) + (d / (studCols + 1));
    float stepX = w / (studRows + 1);
    float stepZ = d / (studCols + 1);

    GLUquadric* quad = gluNewQuadric();
    for (int i = 0; i < studRows; ++i) {
        for (int j = 0; j < studCols; ++j) {
            float sx = startX + i * stepX;
            float sz = startZ + j * stepZ;
            glPushMatrix();
            glTranslatef(sx, h / 2.0f, sz);
            gluCylinder(quad, studR, studR, studH, 8, 1);
            glTranslatef(0, 0, studH);
            gluDisk(quad, 0, studR, 8, 1);
            glPopMatrix();
        }
    }
    gluDeleteQuadric(quad);
    glPopMatrix();
}

// ------------------------------------------------------------
void drawAllBricks() {
    drawLegoBrick(-3.2f, roomBottom + 0.01f, -5.2f, 0.0f,
        1.0f, 0.2f, 0.2f, 0.3f, 0.15f, 0.6f, 2, 4);
    drawLegoBrick(-3.2f, roomBottom + 0.16f, -5.2f, 0.0f,
        0.2f, 0.3f, 1.0f, 0.3f, 0.15f, 0.3f, 2, 2);
    drawLegoBrick(3.5f, roomBottom + 0.01f, -5.0f, 45.0f,
        0.2f, 0.8f, 0.3f, 0.3f, 0.15f, 0.45f, 2, 3);
    drawLegoBrick(3.0f, roomBottom + 0.01f, -4.5f, -20.0f,
        1.0f, 0.9f, 0.1f, 0.15f, 0.15f, 0.3f, 1, 2);
    drawLegoBrick(0.0f, roomBottom + 0.01f, -7.2f, 12.0f,
        0.6f, 0.2f, 0.6f, 0.3f, 0.15f, 0.6f, 2, 4);
    drawLegoBrick(-1.5f, roomBottom + 0.01f, -2.8f, 30.0f,
        1.0f, 0.5f, 0.1f, 0.3f, 0.15f, 0.3f, 2, 2);
    drawLegoBrick(5.0f, roomBottom + 0.01f, -3.0f, -15.0f,
        0.1f, 0.7f, 0.7f, 0.3f, 0.15f, 0.6f, 2, 4);
    drawLegoBrick(-5.0f, roomBottom + 0.01f, -5.5f, 0.0f,
        1.0f, 1.0f, 1.0f, 0.3f, 0.15f, 0.3f, 2, 2);
    drawLegoBrick(-5.0f, roomBottom + 0.16f, -5.5f, 0.0f,
        0.1f, 0.1f, 0.1f, 0.3f, 0.15f, 0.3f, 2, 2);
}

// ------------------------------------------------------------
// Plush toys (bigger, thrown casually)
// ------------------------------------------------------------
void drawBigTeddy(float x, float y, float z, float rotY, float rotX, float rotZ) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(rotY, 0, 1, 0);
    glRotatef(rotX, 1, 0, 0);
    glRotatef(rotZ, 0, 0, 1);
    glColor3f(0.6f, 0.35f, 0.2f);
    glutSolidSphere(0.55, 16, 16);
    glPushMatrix();
    glTranslatef(0.0f, 0.55f, 0.0f);
    glutSolidSphere(0.4, 16, 16);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.25f, 0.85f, 0.0f);
    glutSolidSphere(0.15, 10, 10);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-0.25f, 0.85f, 0.0f);
    glutSolidSphere(0.15, 10, 10);
    glPopMatrix();
    glColor3f(0.85f, 0.7f, 0.55f);
    glPushMatrix();
    glTranslatef(0.0f, 0.5f, 0.35f);
    glutSolidSphere(0.12, 8, 8);
    glPopMatrix();
    glPopMatrix();
}

void drawBigBunny(float x, float y, float z, float rotY, float rotX, float rotZ) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(rotY, 0, 1, 0);
    glRotatef(rotX, 1, 0, 0);
    glRotatef(rotZ, 0, 0, 1);
    glColor3f(0.9f, 0.8f, 0.75f);
    glutSolidSphere(0.5, 16, 16);
    glPushMatrix();
    glTranslatef(0.0f, 0.5f, 0.0f);
    glutSolidSphere(0.35, 16, 16);
    glPopMatrix();
    glColor3f(0.95f, 0.85f, 0.8f);
    GLUquadric* quadEars = gluNewQuadric();
    glPushMatrix();
    glTranslatef(0.15f, 0.75f, 0.0f);
    glRotatef(-15, 0, 0, 1);
    gluCylinder(quadEars, 0.06, 0.06, 0.3, 8, 1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-0.15f, 0.75f, 0.0f);
    glRotatef(15, 0, 0, 1);
    gluCylinder(quadEars, 0.06, 0.06, 0.3, 8, 1);
    glPopMatrix();
    gluDeleteQuadric(quadEars);
    glPopMatrix();
}

void drawPlushToys() {
    drawBigTeddy(-6.5f, roomBottom + 0.01f, -4.0f, 15.0f, 10.0f, -5.0f);
    drawBigBunny(6.5f, roomBottom + 0.01f, -7.5f, -45.0f, 20.0f, 120.0f);
}

// ------------------------------------------------------------
// Bed (2x bigger, 1.5m wide visually)
// ------------------------------------------------------------
void drawBed() {
    float bedCX = -6.4f;
    float bedCZ = -9.9f;
    float bedY = roomBottom + 0.4f;

    glColor3f(0.55f, 0.40f, 0.25f);
    glPushMatrix();
    glTranslatef(bedCX, bedY, bedCZ);
    drawBox(3.2f, 0.7f, 4.2f);
    glPopMatrix();

    glColor3f(0.95f, 0.95f, 0.92f);
    glPushMatrix();
    glTranslatef(bedCX, bedY + 0.5f, bedCZ);
    drawBox(3.0f, 0.3f, 4.0f);
    glPopMatrix();

    glColor3f(0.95f, 0.8f, 0.85f);
    glPushMatrix();
    glTranslatef(bedCX, bedY + 0.6f, bedCZ + 1.2f);
    drawBox(1.2f, 0.2f, 0.8f);
    glPopMatrix();

    glColor3f(0.4f, 0.6f, 0.9f);
    glPushMatrix();
    glTranslatef(bedCX, bedY + 0.55f, bedCZ - 1.2f);
    drawBox(2.8f, 0.16f, 1.4f);
    glPopMatrix();

    glColor3f(0.55f, 0.40f, 0.25f);
    glPushMatrix();
    glTranslatef(bedCX - 1.5f, bedY + 0.8f, bedCZ);
    drawBox(0.16f, 1.2f, 4.2f);
    glPopMatrix();
}

// ------------------------------------------------------------
// Wardrobe (2x bigger, double-door)
// ------------------------------------------------------------
void drawWardrobe() {
    float wbX = 7.1f;
    float wbZ = -11.4f;
    float wbY = roomBottom + 1.8f;
    float wbWidth = 1.8f;
    float wbDepth = 1.2f;
    float wbHeight = 3.6f;

    glColor3f(0.6f, 0.45f, 0.3f);
    glPushMatrix();
    glTranslatef(wbX, wbY, wbZ);
    drawBox(wbWidth, wbHeight, wbDepth);
    glPopMatrix();

    glColor3f(0.7f, 0.55f, 0.4f);
    glPushMatrix();
    glTranslatef(wbX - wbWidth * 0.25f, wbY, wbZ + wbDepth / 2 + 0.04f);
    drawBox(wbWidth * 0.45f, wbHeight - 0.15f, 0.06f);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(wbX + wbWidth * 0.25f, wbY, wbZ + wbDepth / 2 + 0.04f);
    drawBox(wbWidth * 0.45f, wbHeight - 0.15f, 0.06f);
    glPopMatrix();

    glColor3f(0.9f, 0.9f, 0.8f);
    glPushMatrix();
    glTranslatef(wbX - wbWidth * 0.25f, wbY + 0.2f, wbZ + wbDepth / 2 + 0.1f);
    glutSolidSphere(0.06, 6, 6);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(wbX + wbWidth * 0.25f, wbY + 0.2f, wbZ + wbDepth / 2 + 0.1f);
    glutSolidSphere(0.06, 6, 6);
    glPopMatrix();
}

// ------------------------------------------------------------
// Door (right‑front corner, closed)
// ------------------------------------------------------------
void drawDoor() {
    // Door placed against the right wall (X = roomRight), near front wall (Z = roomFront)
    float doorWidth = 1.2f;    // width along Z
    float doorHeight = 2.2f;
    float doorThick = 0.08f;   // depth along X
    float doorBottom = roomBottom + 0.02f;
    float doorCenterZ = roomFront - 0.9f;  // center of door in Z (leave some space)
    float doorCenterX = roomRight - doorThick / 2 - 0.01f; // slightly in front of right wall

    // Door frame (4 thin bars)
    glColor3f(0.5f, 0.35f, 0.2f);
    // top bar
    glPushMatrix();
    glTranslatef(doorCenterX, doorBottom + doorHeight, doorCenterZ);
    drawBox(doorThick + 0.1f, 0.1f, doorWidth + 0.2f);
    glPopMatrix();
    // bottom bar
    glPushMatrix();
    glTranslatef(doorCenterX, doorBottom, doorCenterZ);
    drawBox(doorThick + 0.1f, 0.1f, doorWidth + 0.2f);
    glPopMatrix();
    // left bar
    glPushMatrix();
    glTranslatef(doorCenterX, doorBottom + doorHeight / 2, doorCenterZ - doorWidth / 2 - 0.05f);
    drawBox(doorThick + 0.1f, doorHeight, 0.1f);
    glPopMatrix();
    // right bar
    glPushMatrix();
    glTranslatef(doorCenterX, doorBottom + doorHeight / 2, doorCenterZ + doorWidth / 2 + 0.05f);
    drawBox(doorThick + 0.1f, doorHeight, 0.1f);
    glPopMatrix();

    // Door panel
    glColor3f(0.65f, 0.5f, 0.3f);
    glPushMatrix();
    glTranslatef(doorCenterX, doorBottom + doorHeight / 2, doorCenterZ);
    drawBox(doorThick, doorHeight, doorWidth);
    glPopMatrix();

    // Doorknob (sphere)
    glColor3f(0.9f, 0.9f, 0.8f);
    glPushMatrix();
    glTranslatef(doorCenterX - doorThick / 2 - 0.02f, doorBottom + doorHeight / 2, doorCenterZ - 0.15f);
    glutSolidSphere(0.06, 8, 8);
    glPopMatrix();
}

// ------------------------------------------------------------
void drawWoodFloor() {
    const float plankLengthZ = 2.0f;
    const float plankWidthX = 0.3f;
    const int numPlanksX = (int)((roomRight - roomLeft) / plankWidthX) + 2;
    const int numPlanksZ = (int)((roomFront - roomBack) / plankLengthZ) + 2;

    for (int ix = 0; ix < numPlanksX; ++ix) {
        for (int iz = 0; iz < numPlanksZ; ++iz) {
            float x0 = roomLeft + ix * plankWidthX;
            float z0 = roomBack + iz * plankLengthZ;
            float x1 = x0 + plankWidthX; if (x1 > roomRight) x1 = roomRight;
            float z1 = z0 + plankLengthZ; if (z1 > roomFront) z1 = roomFront;
            if (x0 >= roomRight || z0 >= roomFront) continue;
            float shade = 0.45f + 0.15f * ((ix * 13 + iz * 7) % 19) / 18.0f;
            glColor3f(0.65f * shade, 0.45f * shade, 0.25f * shade);
            glBegin(GL_QUADS);
            glNormal3f(0, 1, 0);
            glVertex3f(x0, roomBottom + 0.002f, z0);
            glVertex3f(x1, roomBottom + 0.002f, z0);
            glVertex3f(x1, roomBottom + 0.002f, z1);
            glVertex3f(x0, roomBottom + 0.002f, z1);
            glEnd();
        }
    }
}

void drawRoom() {
    glColor3f(0.70f, 0.85f, 0.95f);
    // Left
    glBegin(GL_QUADS);
    glNormal3f(1, 0, 0);
    glVertex3f(roomLeft, roomBottom, roomFront);
    glVertex3f(roomLeft, roomBottom, roomBack);
    glVertex3f(roomLeft, roomTop, roomBack);
    glVertex3f(roomLeft, roomTop, roomFront);
    glEnd();
    // Right
    glBegin(GL_QUADS);
    glNormal3f(-1, 0, 0);
    glVertex3f(roomRight, roomBottom, roomBack);
    glVertex3f(roomRight, roomBottom, roomFront);
    glVertex3f(roomRight, roomTop, roomFront);
    glVertex3f(roomRight, roomTop, roomBack);
    glEnd();
    // Back
    glBegin(GL_QUADS);
    glNormal3f(0, 0, 1);
    glVertex3f(roomRight, roomBottom, roomBack);
    glVertex3f(roomLeft, roomBottom, roomBack);
    glVertex3f(roomLeft, roomTop, roomBack);
    glVertex3f(roomRight, roomTop, roomBack);
    glEnd();
    // Front
    glBegin(GL_QUADS);
    glNormal3f(0, 0, -1);
    glVertex3f(roomLeft, roomBottom, roomFront);
    glVertex3f(roomRight, roomBottom, roomFront);
    glVertex3f(roomRight, roomTop, roomFront);
    glVertex3f(roomLeft, roomTop, roomFront);
    glEnd();

    drawWoodFloor();
}

// ------------------------------------------------------------
void drawTrack() {
    const int numSleepers = 120;
    const float sleeperWidth = 0.08f;
    const float sleeperLength = 0.25f;
    const float sleeperHeight = 0.01f;

    glColor3f(0.4f, 0.25f, 0.15f);
    for (int i = 0; i < numSleepers; ++i) {
        float angle = (i / (float)numSleepers) * 2.0f * PI;
        float x = trackCenterX + trackRadiusX * cosf(angle);
        float z = trackCenterZ + trackRadiusZ * sinf(angle);
        float dx = -trackRadiusX * sinf(angle);
        float dz = trackRadiusZ * cosf(angle);
        float len = sqrtf(dx * dx + dz * dz);
        dx /= len; dz /= len;
        float angleY = atan2f(dx, dz) * 180.0f / PI;
        glPushMatrix();
        glTranslatef(x, trackY, z);
        glRotatef(angleY, 0, 1, 0);
        drawBox(sleeperWidth, sleeperHeight, sleeperLength);
        glPopMatrix();
    }

    glDisable(GL_LIGHTING);
    glLineWidth(2.0f);
    glColor3f(0.7f, 0.7f, 0.75f);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i <= 360; ++i) {
        float angle = i * PI / 180.0f;
        float x = trackCenterX + (trackRadiusX + 0.08f) * cosf(angle);
        float z = trackCenterZ + (trackRadiusZ + 0.08f) * sinf(angle);
        glVertex3f(x, trackY + 0.015f, z);
    }
    glEnd();
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i <= 360; ++i) {
        float angle = i * PI / 180.0f;
        float x = trackCenterX + (trackRadiusX - 0.08f) * cosf(angle);
        float z = trackCenterZ + (trackRadiusZ - 0.08f) * sinf(angle);
        glVertex3f(x, trackY + 0.015f, z);
    }
    glEnd();
    glLineWidth(1.0f);
    glEnable(GL_LIGHTING);
}

// ------------------------------------------------------------
void drawTrain(float t) {
    float angle = t * 2.0f * PI;
    float x = trackCenterX + trackRadiusX * cosf(angle);
    float z = trackCenterZ + trackRadiusZ * sinf(angle);
    float dx = -trackRadiusX * sinf(angle);
    float dz = trackRadiusZ * cosf(angle);
    float len = sqrtf(dx * dx + dz * dz);
    dx /= len; dz /= len;
    float facingAngle = atan2f(dx, dz) * 180.0f / PI;
    float trainY = trackY + 0.04f;

    glPushMatrix();
    glColor3f(0.9f, 0.2f, 0.2f);
    glTranslatef(x, trainY, z);
    glRotatef(facingAngle, 0, 1, 0);
    drawBox(0.25f, 0.12f, 0.4f);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.1f, 0.1f, 0.1f);
    glTranslatef(x, trainY + 0.12f, z);
    glRotatef(facingAngle, 0, 1, 0);
    glTranslatef(0.0f, 0.0f, 0.15f);
    GLUquadric* q = gluNewQuadric();
    gluCylinder(q, 0.03, 0.03, 0.08, 10, 1);
    gluDeleteQuadric(q);
    glPopMatrix();

    float wagonOffset = 0.3f;
    float wx = x - wagonOffset * dx;
    float wz = z - wagonOffset * dz;
    glPushMatrix();
    glColor3f(0.2f, 0.8f, 0.3f);
    glTranslatef(wx, trainY, wz);
    glRotatef(facingAngle, 0, 1, 0);
    drawBox(0.2f, 0.1f, 0.3f);
    glPopMatrix();
}

// ------------------------------------------------------------
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    float rad = rotationAngle * PI / 180.0f;
    float ex = centerX + cameraRadius * sin(rad);
    float ez = centerZ + cameraRadius * cos(rad);
    float ey = centerY + cameraHeight;

    gluLookAt(ex, ey, ez, centerX, centerY, centerZ, 0.0, 1.0, 0.0);

    drawRoom();
    drawBed();
    drawWardrobe();
    drawDoor();
    drawTrack();
    drawAllBricks();
    drawPlushToys();
    drawTrain(trainT);

    glutSwapBuffers();
}

// ------------------------------------------------------------
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// ------------------------------------------------------------
void idle(void) {
    int cur = glutGet(GLUT_ELAPSED_TIME);
    float dt = (cur - prevTime) / 1000.0f;
    prevTime = cur;

    rotationAngle += ANGLE_PER_SECOND * dt;
    if (rotationAngle > 360.0f) rotationAngle -= 360.0f;

    trainT += TRAIN_SPEED * dt;
    if (trainT > 1.0f) trainT -= 1.0f;

    glutPostRedisplay();
}

// ------------------------------------------------------------
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Playroom with bed, wardrobe and door");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}