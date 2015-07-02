#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

#include <opencv2/opencv.hpp>
#include "opencv_lib.hpp"
#include "Header.h"
#include <math.h>
#include <iostream>
#include <direct.h>
#include <GL/glut.h>
#include <chrono>
using namespace std;

//double PI = acos(-1.0);
//double ViewPointX = X;
//double ViewPointY = -200.0;
//double ViewPointZ = Y;

bool _Bitmap = true;
//int tn = 0;
//double t = 0;
//double dt = 0.1;
//double omega = 2.0 * PI / 10.0;
//gl_screenshot gs; //bmp�t�@�C���̏o��
void Ground(void);  //��n�̕`��Keyboard

//----------------------------------------------------
// �����̂̒�`
//----------------------------------------------------
GLdouble vertex[][3] = {
	{ 0.0, 0.0, 0.0 },
	{ 2.0, 0.0, 0.0 },
	{ 2.0, 2.0, 0.0 },
	{ 0.0, 2.0, 0.0 },
	{ 0.0, 0.0, 30.0 },
	{ 2.0, 0.0, 30.0 },
	{ 2.0, 2.0, 30.0 },
	{ 0.0, 2.0, 30.0 }
};
int face[][4] = {//�ʂ̒�`
	{ 0, 1, 2, 3 },
	{ 1, 5, 6, 2 },
	{ 5, 4, 7, 6 },
	{ 4, 0, 3, 7 },
	{ 4, 5, 1, 0 },
	{ 3, 2, 6, 7 }
};
GLdouble normal[][3] = {//�ʂ̖@���x�N�g��
	{ 0.0, 0.0, -1.0 },
	{ 1.0, 0.0, 0.0 },
	{ 0.0, 0.0, 1.0 },
	{ -1.0, 0.0, 0.0 },
	{ 0.0, -1.0, 0.0 },
	{ 0.0, 1.0, 0.0 }
};
//----------------------------------------------------
// ���������̒�`
//----------------------------------------------------
struct MaterialStruct {
	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];
	GLfloat shininess;
};
//jade(�Ő�)
MaterialStruct ms_jade = {
	{ 0.135, 0.2225, 0.1575, 1.0 },
	{ 0.54, 0.89, 0.63, 1.0 },
	{ 0.316228, 0.316228, 0.316228, 1.0 },
	12.8 };
//ruby(���r�[)
MaterialStruct ms_ruby = {
	{ 0.1745, 0.01175, 0.01175, 1.0 },
	{ 0.61424, 0.04136, 0.04136, 1.0 },
	{ 0.727811, 0.626959, 0.626959, 1.0 },
	76.8 };
//----------------------------------------------------
// �F�̒�`�̒�`
//----------------------------------------------------
GLfloat red[] = { 0.8, 0.2, 0.2, 1.0 }; //�ԐF
GLfloat green[] = { 0.2, 0.8, 0.2, 1.0 };//�ΐF
GLfloat blue[] = { 0.2, 0.2, 0.8, 1.0 };//�F
GLfloat yellow[] = { 0.8, 0.8, 0.2, 1.0 };//���F
GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };//���F
GLfloat shininess = 40.0;//����̋���
//-----------------------------------------

//----------------------------------------------------
// �����ݒ�̊֐�
//----------------------------------------------------
void Initialize(void){
	glClearColor(1.0, 1.0, 1.0, 1.0); //�w�i�F
	glEnable(GL_DEPTH_TEST);//�f�v�X�o�b�t�@���g�p�FglutInitDisplayMode() �� GLUT_DEPTH ���w�肷��

	//�����̐ݒ�--------------------------------------
	GLfloat light_position0[] = { 0.0, -50.0, 0.0, 1.0 }; //����0�̍��W
	glLightfv(GL_LIGHT0, GL_POSITION, light_position0); //����0��

}
//----------------------------------------------------
// �`��̊֐�
//----------------------------------------------------
void Display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //�o�b�t�@�̏���

	//t = dt * tn;
	//ViewPointX = 20.0 * sin(omega * t / 100);
	//ViewPointY = -100.0 * sin(omega * t/200);
	//ViewPointZ = 20.0 * cos(omega * t / 100);
	//ViewPointX = 0;
	//ViewPointY = -100.0;

	/*
	x = 100 * cos(phi) * sin(theta);
	y = 100 * cos(phi) * cos(theta);
	z = 100 * sin(phi);
	*/
	//if (int(t) % 4 == 0) ViewPointX += 1 * 100 * t;
	//if (int(t) % 4 == 1) ViewPointZ += 1 * 100 * t;
	//if (int(t) % 4 == 2) ViewPointX += -1 * 100 * t;
	//if (int(t) % 4 == 3) ViewPointZ += -1 * 100 * t;

	//�����ϊ��s��̐ݒ�------------------------------
	glMatrixMode(GL_PROJECTION);//�s�񃂁[�h�̐ݒ�iGL_PROJECTION : �����ϊ��s��̐ݒ�AGL_MODELVIEW�F���f���r���[�ϊ��s��j
	glLoadIdentity();//�s��̏�����
	gluPerspective(30.0, (double)WindowWidth / (double)WindowHeight, 0.1, 1000.0); //�������e�@�̎��̐�gluPerspactive(th, w/h, near, far);

	//���_�̐ݒ�------------------------------
	gluLookAt(
		//ViewPointX, ViewPointY, ViewPointZ, // ���_�̈ʒux,y,z;
		-(X / width - 0.5) * WindowWidth / 2, -200, -(Y / height - 0.5) * WindowHeight / 2, // ���E�̒��S�ʒu�̎Q�Ɠ_���Wx,y,z
		0.0, 100.0, 0.0,
		0.0, 0.0, 1.0);     //���E�̏�����̃x�N�g��x,y,z
	//----------------------------------------

	//���f���r���[�ϊ��s��̐ݒ�--------------------------
	glMatrixMode(GL_MODELVIEW);//�s�񃂁[�h�̐ݒ�iGL_PROJECTION : �����ϊ��s��̐ݒ�AGL_MODELVIEW�F���f���r���[�ϊ��s��j
	glLoadIdentity();//�s��̏�����
	glViewport(0, 0, WindowWidth, WindowHeight);
	//----------------------------------------------

	//�A�eON-----------------------------
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);//����0�𗘗p
	//-----------------------------------

	//��
	for (int i = -10; i < 150; i += 10){
		glPushMatrix();
		glMaterialfv(GL_FRONT, GL_AMBIENT, ms_ruby.ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, ms_ruby.diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, ms_ruby.specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, &ms_ruby.shininess);
		glTranslated(0.0, i, 0.0);//���s�ړ��l�̐ݒ�
		glutSolidSphere(4.0, 20, 20);//�����F(���a, Z���܂��̕�����, Z���ɉ�����������)
		glPopMatrix();
		glPushMatrix();
		glMaterialfv(GL_FRONT, GL_AMBIENT, ms_jade.ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, ms_jade.diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, ms_jade.specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, &ms_jade.shininess);
		glTranslated(-20, i, 0.0);//���s�ړ��l�̐ݒ�
		glutSolidSphere(4.0, 20, 20);//�����F(���a, Z���܂��̕�����, Z���ɉ�����������)
		glPopMatrix();
	}

	/*
	//������
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, green);
	glTranslated(-10.0, -20.0, 0.0);//���s�ړ��l�̐ݒ�
	glutSolidCube(10.0);//�����F(��ӂ̒���)
	glPopMatrix();
	*/

	//�~��
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, blue);
	glTranslated(20.0, 30.0, 0.0);//���s�ړ��l�̐ݒ�
	glutSolidCone(5.0, 10.0, 20, 20);//�����F(���a, ����, Z���܂��̕�����, Z���ɉ�����������)
	glPopMatrix();

	/*
	//������
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, ms_jade.ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, ms_jade.diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, ms_jade.specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &ms_jade.shininess);
	glTranslated(30.0, 40.0, 0.0);//���s�ړ��l�̐ݒ�
	glBegin(GL_QUADS);
	for (int j = 0; j < 6; ++j) {
		glNormal3dv(normal[j]); //�@���x�N�g���̎w��
		for (int i = 0; i < 4; ++i) {
			glVertex3dv(vertex[face[j][i]]);
		}
	}
	glEnd();
	glPopMatrix();
	*/

	//�A�eOFF-----------------------------
	glDisable(GL_LIGHTING);
	//-----------------------------------

	Ground();

	/*
	if (_Bitmap){
	ostringstream fname;
	int tt = tn + 10000;
	fname << "bitmap/" << tt << ".bmp";//�o�̓t�@�C����
	string name = fname.str();
	gs.screenshot(name.c_str(), 24);
	}
	tn++;
	*/

	glutSwapBuffers(); //glutInitDisplayMode(GLUT_DOUBLE)�Ń_�u���o�b�t�@�����O�𗘗p��
}
//----------------------------------------------------
// �A�C�h�����ɌĂяo�����֐�
//----------------------------------------------------
void Idle(){
	glutPostRedisplay(); //glutDisplayFunc()���P����s����
}

//----------------------------------------------------
// ��n�̕`��
//----------------------------------------------------
double coe(double x, double y, double n, double ly){
	return x / n*(1 + (n - 1)*(y - ly) / (2 * y));
}


void Ground(void){
	double ground_max_x = 200.0;
	double ground_max_y = 300.0;
	double ground_max_z = 200.0;
	double n = 16;
	glColor3d(0.8, 0.8, 0.8);  // ��n�̐F
	glBegin(GL_LINES);

	//�㉺����
	for (double ly = -ground_max_y; ly <= ground_max_y; ly += 10.0){
		glVertex3d(-coe(ground_max_x, ground_max_y, n, ly), ly, -coe(ground_max_z, ground_max_y, n, ly));
		glVertex3d(coe(ground_max_x, ground_max_y, n, ly), ly, -coe(ground_max_z, ground_max_y, n, ly));
		glVertex3d(-coe(ground_max_x, ground_max_y, n, ly), ly, coe(ground_max_z, ground_max_y, n, ly));
		glVertex3d(coe(ground_max_x, ground_max_y, n, ly), ly, coe(ground_max_z, ground_max_y, n, ly));
	}
	for (double lx = -ground_max_x; lx <= ground_max_x; lx += 10.0){
		glVertex3d(lx, -ground_max_y, -ground_max_z);
		glVertex3d(lx / n, ground_max_y, -ground_max_z / n);
		glVertex3d(lx, -ground_max_y, ground_max_z);
		glVertex3d(lx / n, ground_max_y, ground_max_z / n);

	}
	//���̕���
	for (double lx = -ground_max_x; lx <= ground_max_x; lx += 10.0){
		glVertex3d(lx / n, ground_max_y, -ground_max_z / n);
		glVertex3d(lx / n, ground_max_y, ground_max_z / n);
	}
	for (double lz = -ground_max_z; lz <= ground_max_z; lz += 10.0){
		glVertex3d(-ground_max_x / n, ground_max_y, lz / n);
		glVertex3d(ground_max_x / n, ground_max_y, lz / n);
	}
	//���E����
	for (double lz = -ground_max_z; lz <= ground_max_z; lz += 10.0){
		glVertex3d(ground_max_x, -ground_max_y, lz);
		glVertex3d(ground_max_x / n, ground_max_y, lz / n);
		glVertex3d(-ground_max_x, -ground_max_y, lz);
		glVertex3d(-ground_max_x / n, ground_max_y, lz / n);
	}
	for (double ly = -ground_max_y; ly <= ground_max_y; ly += 10.0){
		glVertex3d(coe(ground_max_x, ground_max_y, n, ly), ly, -coe(ground_max_z, ground_max_y, n, ly));
		glVertex3d(coe(ground_max_x, ground_max_y, n, ly), ly, coe(ground_max_z, ground_max_y, n, ly));
		glVertex3d(-coe(ground_max_x, ground_max_y, n, ly), ly, -coe(ground_max_z, ground_max_y, n, ly));
		glVertex3d(-coe(ground_max_x, ground_max_y, n, ly), ly, coe(ground_max_z, ground_max_y, n, ly));
	}


	glEnd();
}