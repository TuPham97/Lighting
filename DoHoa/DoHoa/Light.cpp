
#include "pch.h"
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include "Dependencies/glew/glew.h"
#include "Dependencies/freeglut/freeglut.h"

#define TORUS 0
#define TEAPOT 1
#define DOD 2
#define TET 3
#define ISO 4
#define QUIT 5


int shade_model = GL_SMOOTH;
char *left_light, *right_light;
char *ico_material, *teapot_material, *torus_material;

static int spin = 0;
static int obj = TORUS;
static int begin;


void output(GLfloat x, GLfloat y, char *format, ...)
{
	va_list args;
	char buffer[200], *p;

	va_start(args, format);
	vsprintf_s(buffer, format, args);
	va_end(args);
	glPushMatrix();
	glTranslatef(x, y, 0);
	for (p = buffer; *p; p++)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, *p);
	glPopMatrix();
}

void menu_select(int item)
{
	if (item == QUIT)
		exit(0);
	obj = item;
	glutPostRedisplay();
}


void movelight(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		begin = x;
	}
}

void motion(int x, int y)
{
	spin = (spin + (x - begin)) % 360;
	begin = x;
	glutPostRedisplay();
}

void myinit(void)
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
}


void display(void)
{


	GLfloat position[] ={ 0.0, 0.0, 1.5, 1.0 };

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glClearColor(1.0, 1.0, 1.0, 0.0); 

	glMatrixMode(GL_MODELVIEW);


	glPushMatrix();
	glTranslatef(0.0, 0.0, -5.0);

	glPushMatrix();
	glRotated((GLdouble)spin, 0.0, 1.0, 0.0);
	/*glRotated(1.0, 0.0, 1.0, 0.0);*/

	//GLfloat light_ambient[] = { 1.0,0.0,0.0,0.0 };
	GLfloat light_diffuse[] = { 0.0,1.0,0.0,0.0 };
	//GLfloat light_specular[] = { 1.0,0.0,0.0,0.0 };
	//GLfloat light_shinii[] = { 1.0,1.0,1.0,1.0 }; 

	glLightfv(GL_LIGHT0, GL_POSITION, position);
	//máu ánh sáng
	//glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse); 
	//glLightfv(GL_LIGHT0, GL_SHININESS, light_shinii);

	//glMaterialfv(GL_LIGHT0, GL_POSITION, position);
	//glMaterialfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	//glMaterialfv(GL_LIGHT1, GL_POSITION, position);
	//glMaterialfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
	//glMaterialfv(GL_LIGHT1, GL_POSITION, position);
	//glMaterialfv(GL_LIGHT1, GL_SPECULAR, light_specular);

	glTranslated(0.0, 0.0, 1.5);
	glDisable(GL_LIGHTING);
	glColor3f(0.0, 1.0, 1.0);

	glutWireCube(0.1);
	glEnable(GL_LIGHTING);

	glPopMatrix();

	//thiết lập màu cho khói cube
	// Tạo ánh sáng môi trường
	//GLfloat ambient[] = { 0.0, 0.8, 0.0, 1.0 };
	//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	////khuếch tán
	GLfloat diffuse[] = { 0.0, 0.8, 0.0, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	////phản xạ
	//GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	//glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	////cường độ
	//GLfloat shininess = 30.0f; //độ phản xạ ánh sáng
	//glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

	glutSolidTeapot(1.0);

	/*glTranslatef(1, 1.8, 0.0);
	glutSolidTeapot(0.5);*/

	glPopMatrix(); // vị trí ban đầu 


	/*switch (obj) {
	case TORUS:
	glutSolidTorus(0.275, 0.85, 20, 20);
	break;
	case TEAPOT:
	glutSolidTeapot(1.0);
	break;
	case DOD:
	glPushMatrix();
	glScalef(.5, .5, .5);
	glutSolidDodecahedron();
	glPopMatrix();
	break;
	case TET:
	glutSolidTetrahedron();
	break;
	case ISO:
	glutSolidIcosahedron();
	break;
	}*/

	glPushAttrib(GL_ENABLE_BIT);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	gluOrtho2D(0, 3000, 0, 3000);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	//output(80, 250, "Left light: %s", left_light);
	//output(1700, 250, "Right light: %s", right_light);

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glPopAttrib();
	glutSwapBuffers();
}


void myReshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
}
//
//void tmotion(int x, int y)
//{
//	printf("Tablet motion x = %d, y = %d\n", x, y);
//}
//
//void tbutton(int b, int s, int x, int y)
//{
//	printf("b = %d, s = %d, x = %d, y = %d\n", b, s, x, y);
//}
//
//void smotion(int x, int y, int z)
//{
//	fprintf(stderr, "Spaceball motion %d %d %d\n", x, y, z);
//}
//
//void rmotion(int x, int y, int z)
//{
//	fprintf(stderr, "Spaceball rotate %d %d %d\n", x, y, z);
//}
//
//void sbutton(int button, int state)
//{
//	fprintf(stderr, "Spaceball button %d is %s\n",
//		button, state == GLUT_UP ? "up" : "down");
//}
//
//void dials(int dial, int value)
//{
//	fprintf(stderr, "Dial %d is %d\n", dial, value);
//	spin = value % 360;
//	glutPostRedisplay();
//}
//
//void buttons(int button, int state)
//{
//	fprintf(stderr, "Button %d is %s\n", button,
//		state == GLUT_UP ? "up" : "down");
//}


int main(int argc, char **argv)
{
	int left_light_m, right_light_m;
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1280, 720);
	glutCreateWindow(argv[0]);
	myinit();
	glutMouseFunc(movelight);
	glutMotionFunc(motion);
	glutReshapeFunc(myReshape);
	glutDisplayFunc(display);


	//glutTabletMotionFunc(tmotion);
	//glutTabletButtonFunc(tbutton);
	//glutSpaceballMotionFunc(smotion);
	//glutSpaceballRotateFunc(rmotion);
	//glutSpaceballButtonFunc(sbutton);
	//glutDialsFunc(dials);
	//glutButtonBoxFunc(buttons);
	//glutCreateMenu(menu_select);
	//
	//glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
	return 0;             /* ANSI C requires main to return int. */
}