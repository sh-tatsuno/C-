#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

#include "Header.h"
#include <math.h>
#include <iostream>
#include <direct.h>
#include <GL/glut.h>
using namespace std;

int WindowPositionX = 200;  //��������E�B���h�E�ʒu��X���W
int WindowPositionY = 200;  //��������E�B���h�E�ʒu��Y���W
int WindowWidth = 1024;  //��������E�B���h�E�̕�
int WindowHeight = 1024;  //��������E�B���h�E�̍���
char WindowTitle[] = "BoxModoki";

//----------------------------------------------------
// �֐��v���g�^�C�v�i��ɌĂяo���֐����ƈ����̐錾�j
//----------------------------------------------------
void Initialize(void);
void Display(void);
void Idle();

//----------------------------------------------------
// �`��֐�
//----------------------------------------------------
void thread_glut() {
	glutInitWindowPosition(WindowPositionX, WindowPositionY);//�E�B���h�E�̈ʒu�̎w��
	glutInitWindowSize(WindowWidth, WindowHeight); //�E�B���h�E�T�C�Y�̎w��
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);//�f�B�X�v���C���[�h�̎w��
	glutCreateWindow(WindowTitle);  //�E�B���h�E�̍쐬
	glutDisplayFunc(Display);
	glutIdleFunc(Idle);       //�v���O�����A�C�h����Ԏ��ɌĂяo�����֐�
	Initialize(); //�����ݒ�̊֐����Ăяo��
	glutMainLoop();
}