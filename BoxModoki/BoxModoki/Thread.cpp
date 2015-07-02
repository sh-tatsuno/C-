#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

#include "Header.h"
#include <math.h>
#include <iostream>
#include <direct.h>
#include <GL/glut.h>
using namespace std;

int WindowPositionX = 200;  //生成するウィンドウ位置のX座標
int WindowPositionY = 200;  //生成するウィンドウ位置のY座標
int WindowWidth = 1024;  //生成するウィンドウの幅
int WindowHeight = 1024;  //生成するウィンドウの高さ
char WindowTitle[] = "BoxModoki";

//----------------------------------------------------
// 関数プロトタイプ（後に呼び出す関数名と引数の宣言）
//----------------------------------------------------
void Initialize(void);
void Display(void);
void Idle();

//----------------------------------------------------
// 描画関数
//----------------------------------------------------
void thread_glut() {
	glutInitWindowPosition(WindowPositionX, WindowPositionY);//ウィンドウの位置の指定
	glutInitWindowSize(WindowWidth, WindowHeight); //ウィンドウサイズの指定
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);//ディスプレイモードの指定
	glutCreateWindow(WindowTitle);  //ウィンドウの作成
	glutDisplayFunc(Display);
	glutIdleFunc(Idle);       //プログラムアイドル状態時に呼び出される関数
	Initialize(); //初期設定の関数を呼び出す
	glutMainLoop();
}