#include <GL/glut.h>
#include <cmath>
void Display(void)
{
	//��ʾ������������꣬��뾶 R=0.2
	const double PI = acos(0.) * 2;
	double L1 = 0.2*cos(36 * PI / 180);
	double L2 = 0.2*sin(36 * PI / 180);
	double L3 = 0.2*cos(72 * PI / 180);
	double L4 = 0.2*sin(72 * PI / 180);
	double L5 = L2*tan(72 * PI / 180);
	double L6 = L2 / cos(72 * PI / 180);
	double L7 = L6*sin(54 * PI / 180);
	double L8 = L6*cos(54 * PI / 180) + 0.2;
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//���Ʊ�
	//glBegin(GL_POLYGON); 
	//glColor3f(0.0f, 0.0f, 0.0f);
	//glVertex2f(0.0f, 0.0f);
	//glVertex2f(0.0f, L5 + L1);//1
	//glVertex2f(L2, L1);//2
	//glVertex2f(L2 + L6, L1);//3
	//glVertex2f(L4, -L3);//4
	//glVertex2f(L7, -L8);//5
	//glVertex2f(0.0f, -0.2f);//6
	//glVertex2f(-L7, -L8);//7
	//glVertex2f(-L4, -L3);//8
	//glVertex2f(-L2 - L6, L1);//9
	//glVertex2f(-L2, L1);//10
	//glVertex2f(0.0f, L5 + L1);
	//glEnd();

	glEnable(GL_POINT_SMOOTH);//���õ�Ĵ�С�����ΪԲ��

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPointSize(8.0f);
	glBegin(GL_POINTS); //���ƶ���
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0.0f, L5 + L1);//1
	glVertex2f(L2 + L6, L1);//3
	glVertex2f(L7, -L8);//5
	glVertex2f(-L7, -L8);//7
	glVertex2f(-L2 - L6, L1);//9
	glVertex2f(0.0f, L5 + L1);
	glEnd();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);//���
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex2f(L2, L1);//2
	glVertex2f(L4, -L3);//4
	glVertex2f(0.0f, -0.2f);//6
	glVertex2f(-L4, -L3);//8
	glVertex2f(-L2, L1);//10
	glEnd();

	glEnable(GL_LINE_SMOOTH);
	glLineWidth(3.0f);//����
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0.0f, L5 + L1);//1
	glVertex2f(L7, -L8);//5
	glVertex2f(-L2 - L6, L1);//9
	glVertex2f(L2 + L6, L1);//3
	glVertex2f(-L7, -L8);//7
	glVertex2f(0.0f, L5 + L1);//1
	glEnd();

	glFlush();
}
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(700, 700);
	glutCreateWindow("Star");
	glutDisplayFunc(Display);
	glutMainLoop();
	return 0;
}
