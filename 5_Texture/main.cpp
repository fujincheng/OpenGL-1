#include<GL\glut.h>
#include<glm\glm.hpp>
#include<glm\ext.hpp>
#include<windows.h>       //for exit() and Sleep()  
#include<cmath>

//double p1[3]{ 0,0,0 };
//double p2[3]{ 0,1,0 };
double angle = 0;
double angle_cube = -45;
GLubyte image[64 * 64 * 3];
GLubyte surround[64 * 64 * 3];

bool isFirst = true;
bool cube_rotate = false;

void draw_teapot(double size) {
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glPushMatrix();
	
	glColor3f(1.0f, 0.0f, 0.0f);
	if(!isFirst)
		glTranslatef(3, 0, 0);
	if (isFirst) {
		glRotatef(90, 0, 1.0, 0);
	}
	glRotatef(angle, 0, 1.0, 0);
	angle += 2;
	if (angle >= 360) angle = angle - 360;
	glutSolidTeapot(size);
	
	if (isFirst) {
		//glColor3f(1.0f, 1.0f, 1.0f);
		glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 0, 0, 700, 500, 0);
	}
	glPopMatrix();
}

void draw_cube(double size)
{
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(-3, 0, 0);
	glRotatef(angle_cube, 0, 1.0, 0);
	if(cube_rotate)
		angle_cube+=2;
	/*if(isFirst)
		angle += 2;
	if (angle >= 360) angle = angle - 360;*/

	double beg, end;
	beg = isFirst ? 0.25 : 0;
	end = isFirst ? 0.75 : 1.0;

	glBegin(GL_QUADS);
	if (!isFirst) {
		glColor3f(1.0, 1.0, 1.0);//��
		glTexCoord2f(end, end); glVertex3f(size / 2, size / 2, -size / 2);
		glTexCoord2f(end, beg); glVertex3f(-size / 2, size / 2, -size / 2);
		glTexCoord2f(beg, beg); glVertex3f(-size / 2, size / 2, size / 2);
		glTexCoord2f(beg, end); glVertex3f(size / 2, size / 2, size / 2);
		//glColor3f(0.0, 1.0, 0.0);//��
		glTexCoord2f(beg, end); glVertex3f(size / 2, -size / 2, size / 2);
		glTexCoord2f(end, end); glVertex3f(-size / 2, -size / 2, size / 2);
		glTexCoord2f(end, beg); glVertex3f(-size / 2, -size / 2, -size / 2);
		glTexCoord2f(beg, beg); glVertex3f(size / 2, -size / 2, -size / 2);
	}
	//glColor3f(0.0, 0.0, 1.0);//ǰ
	if (!isFirst) {
		glTexCoord2f(beg, end);glVertex3f(size / 2, size / 2, size / 2);
		glTexCoord2f(end, end);glVertex3f(-size / 2, size / 2, size / 2);
		glTexCoord2f(end, beg);glVertex3f(-size / 2, -size / 2, size / 2);
		glTexCoord2f(beg, beg);glVertex3f(size / 2, -size / 2, size / 2);
	}

	//glColor3f(1.0, 1.0, 0.0);//��
	if (!isFirst) {
		glTexCoord2f(end, beg); glVertex3f(size / 2, -size / 2, -size / 2);
		glTexCoord2f(beg, beg); glVertex3f(-size / 2, -size / 2, -size / 2);
		glTexCoord2f(beg, end); glVertex3f(-size / 2, size / 2, -size / 2);
		glTexCoord2f(end, end); glVertex3f(size / 2, size / 2, -size / 2);
	}
	//glColor3f(1.0, 0.0, 1.0);//��
	if (!isFirst) {
		glTexCoord2f(end, end); glVertex3f(-size / 2, size / 2, size / 2);
		glTexCoord2f(beg, end); glVertex3f(-size / 2, size / 2, -size / 2);
		glTexCoord2f(beg, beg); glVertex3f(-size / 2, -size / 2, -size / 2);
		glTexCoord2f(end, beg); glVertex3f(-size / 2, -size / 2, size / 2);
	}
	//glColor3f(0.0, 1.0, 1.0);//��
	if (isFirst) {
		glTexCoord2f(beg, end); glVertex3f(size / 2, size / 2, -size / 2);
		glTexCoord2f(end, end); glVertex3f(size / 2, size / 2, size / 2);
		glTexCoord2f(end, beg); glVertex3f(size / 2, -size / 2, size / 2);
		glTexCoord2f(beg, beg); glVertex3f(size / 2, -size / 2, -size / 2);
	}
	Sleep(10);
	glEnd();
	glPopMatrix();
}

void display(void)
{
	glm::mat4 transform_camera(1.0f); // �������λ�úͶ��򣬼����������������ϵ��λ��
	transform_camera = glm::affineInverse(glm::lookAt(glm::vec3(0, 5, 10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)));
	glm::mat4 model_view_matrix = glm::affineInverse(transform_camera);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(&model_view_matrix[0][0]);
	isFirst = true;
	draw_teapot(2);
	//glCopyTexImage2D(GL_TEXTURE_2D,0,GL_RGB,0,0,500);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	draw_cube(2);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 64, 64, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	isFirst = false;
	draw_cube(2);
	draw_teapot(2);

	glFlush();
	glutSwapBuffers();

	Sleep(20);
}

void reshape(int w, int h)
{
	if (h == 0) h = 1;
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);

}
void init(int width, int height)
{
	if (height == 0) height = 1;

	//glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

	glClearColor(0.0, 0.0, 0.0, 1.0);
	//���ù���  
	const GLfloat light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };//����ǿ��
	const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };//����ǿ��

	const GLfloat white_light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };//ɢ��ǿ��
	//const GLfloat red_light_diffuse[] = { 1.0f, 0.0f, 0.0f, 1.0f };//ɢ��ǿ��

	//const GLfloat red_light_position[] = { 5.0f, 5.0f, 3.0f, 0.0f };
	const GLfloat white_light_position[] = { -5.0f, 5.0f, 3.0f, 0.0f };

	const GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	const GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	const GLfloat mat_diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	const GLfloat high_shininess[] = { 50.0f };

	/*glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);*/

	glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHT1);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light_diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, white_light_position);

	/*glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, red_light_diffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, red_light_position);*/

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);


	glDepthFunc(GL_LEQUAL);
	
	int i, j, c;
	for (i = 0; i<64; i++)
	{
		for (j = 0; j<64; j++)
		{
			c = ((((i & 0x8) == 0) ^ ((j & 0x8)) == 0)) * 255;
			image[i*64*3+j*3+0] = (GLubyte)c;
			image[i*64*3+j*3+1] = (GLubyte)c;
			image[i*64*3+j*3+2] = (GLubyte)c;
		}
	}

	glTexImage2D(GL_TEXTURE_2D, 0, 3, 64, 64, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

void keyboard(unsigned char key, int x, int y) {
	switch (key)
	{
	case 27:
		exit(0);
		break;
	case ' ':
		cube_rotate = !cube_rotate;
		break;
	default:
		break;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(400, 100);
	glutInitWindowSize(700, 500);
	glutCreateWindow("Cube");

	glutDisplayFunc(display);
	glutIdleFunc(display);

	//����(ESC)�˳�,��(Space)�����Զ���ת
	glutKeyboardFunc(keyboard);

	glutReshapeFunc(reshape);
	init(640, 480);
	glutMainLoop();
	return 0;
}