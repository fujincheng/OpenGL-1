#include <GL/glut.h>
#include <cmath>
#include <iostream>

float angle = 0.0;
bool auto_rotate = false;


void display(void)
{

	//��ʾ������������꣬��뾶 
	double R = 0.3;
	const double PI = acos(0.) * 2;
	double L1 = R*cos(36 * PI / 180);
	double L2 = R*sin(36 * PI / 180);
	double L3 = R*cos(72 * PI / 180);
	double L4 = R*sin(72 * PI / 180);
	double L5 = L2*tan(72 * PI / 180);
	double L6 = L2 / cos(72 * PI / 180);
	double L7 = L6*sin(54 * PI / 180);
	double L8 = L6*cos(54 * PI / 180) + R;

	//���浱ǰģ����ͼ����
	glPushMatrix();
	
	
	//ƽ�Ƶ����Ͻ�
	glTranslatef(-L2 - L6, L1, 0);
	//��ת
	glRotatef(angle, 0.0, 0.0, 1);
	//ƽ�ƻص�ԭ��
	glTranslatef(L2 + L6, -L1, 0);

	glClearColor(1.0, 1.0, 1.0, 0.0);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT);

	//���õ�Ĵ�С���Լ�����alpha blend�Լ���������������Ի�Բ�εĵ�,���СӦ�÷���begin��end֮��
	glEnable(GL_POINT_SMOOTH);
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
	glVertex2f(0.0f, -R);//6
	glVertex2f(-L4, -L3);//8
	glVertex2f(-L2, L1);//10
	glEnd();

	//������
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

	// ������ջ
	glPopMatrix();
	// ����������
	glutSwapBuffers();
	
}

void reshape(int w, int h) {

	//��ֹ�������߶�Ϊ0
	if (h == 0)
		h = 1;
	float ratio = 1.0* w / h;
	//��λ��ͶӰ����
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//�����ӿڴ�СΪ�������ڴ�С
	glViewport(0, 0, w, h);
	//������ȷ��ͶӰ����
	gluPerspective(45, ratio, 1, 1000);
	//����ģ����ͼ����
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, -1.0, 0.0f, 1.0f, 0.0f);
}


void keyboard(unsigned char key, int x, int y) {
	switch (key)
	{
	case 27:
		exit(0);
		break;
	case ' ':
		auto_rotate = !auto_rotate;
		break;
	default:
		break;
	}
}

//�����ֶ���ת,(UP)��ʱ��,(DOWN)˳ʱ��
void specialkey(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		if (auto_rotate) break;
		std::cout << "UP" << std::endl;
		angle = angle + 2;
		angle = angle > 360 ? angle - 360 : angle;
		glutPostRedisplay();//ˢ����ʾ
		break;
	case GLUT_KEY_DOWN:
		if (auto_rotate) break;
		std::cout << "DOWN" << std::endl;
		angle = angle - 2;
		angle = angle < 0 ? angle + 360 : angle;
		glutPostRedisplay();//ˢ����ʾ
		break;
	default:
		break;
	}
}

//���ö�ʱ��,ÿ��10ms����Ƿ���Ҫ�Զ���ת
void timer(int iTimerIndex) {
	if (auto_rotate) {
		Sleep(10);
		// ��angle�Զ����ӡ�
		angle=angle+2;
		angle = angle > 360 ? angle - 360 : angle;
		glutPostRedisplay();//ˢ����ʾ
	}
	glutTimerFunc(10, timer, 0);
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(700, 500);
	glutCreateWindow("Star Rotate");
	glutDisplayFunc(display);
	//glutIdleFunc(display);
	glutReshapeFunc(reshape);

	//���ö�ʱ��,ÿ��10ms����Ƿ���Ҫ�Զ���ת
	glutTimerFunc(10, timer, 0);

	//����(ESC)�˳�,��(Space)�����Զ���ת
	glutKeyboardFunc(keyboard);
	
	//�����ֶ���ת,(UP)��ʱ��,(DOWN)˳ʱ��
	glutSpecialFunc(specialkey);

	//������Ȳ���
	//glEnable(GL_DEPTH_TEST);
	glutMainLoop();
	return 0;
}