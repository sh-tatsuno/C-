#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
#include <GL/glut.h>
#include "Header.h"
#include <opencv2/opencv.hpp>
#include "opencv_lib.hpp"
#include <math.h>
#include <iostream>
#include <thread>
using namespace std;

// �O���[�o���ϐ�
cv::Rect box;
bool drawing_box = false;
double width = 640;
double height = 480;
double X = width / 2;
double Y = height / 2;



void thread_glut();
void my_mouse_callback(int event, int x, int y, int flags, void* param);
//void draw_box(cv::Mat* img, cv::Rect rect); //�T���̈����������֐�

int main(int argc, char *argv[]){
	int f = 0;
	cv::VideoCapture cap1(0);
	//cv::VideoCapture cap2(1);
	cv::namedWindow("�J�����P", CV_WINDOW_AUTOSIZE);
	//cv::namedWindow("�J�����Q", CV_WINDOW_AUTOSIZE);
	cv::Mat cam1image;
	//cv::Mat cam2image;
	std::vector<cv::Point2d>container;
	cv::Point2d center;
	

	// �R�[���o�b�N��ݒ�
	cv::setMouseCallback("�J�����P", my_mouse_callback, (void *)& cam1image);
	//if (!cap2.isOpened())cout << "AA" << endl;

	glutInit(&argc, argv); //���̏�����
	std::thread th(thread_glut); //�X���b�h�𗧂Ă�

	while (1)
	{
		auto start = std::chrono::system_clock::now();
		cap1 >> cam1image; // �J�����P(�����̃J�����̉摜�H)
		cv::cvtColor(cam1image, cam1image, CV_RGB2GRAY);
		cv::threshold(cam1image, cam1image, 240, 255, cv::THRESH_BINARY);
		//do{
			//cap2 >> cam2image;		//�L���v�`��
		//} while (cam2image.empty());	//�������L���v�`�������܂ő҂�
		//cap2 >> cam2image; //�J�����Q(�E���̃J�����̉摜)
		if (drawing_box) {
			//draw_box(&cam1image, box);
			center = cv::Point2d(X, Y);
			f = 1;
		}
		if (f == 1){
			container.clear();
			for (int dy = center.y - 50; dy < center.y + 50; dy++){
				if (dy >= 0 && dy < cam1image.rows){
					for (int dx = center.x - 50; dx < center.x + 50; dx++){
						if (dx >= 0 && dx < cam1image.cols){
							if (cam1image.data[dy * cam1image.step + dx * cam1image.elemSize()] > 100)container.push_back(cv::Point2d(dx, dy));
						}
					}
				}
			}
			center = cv::Point2d(0, 0);
			vector<cv::Point2d>::iterator k;
			//���marker�Q�̍��W�̑��a�����߂�
			for (k = container.begin(); k != container.end(); ++k){
				center.x += k->x;
				center.y += k->y;

			}
			//���a�𑍐��Ŋ���A�d�S�����Z�o
			center.x = center.x / container.size();
			center.y = center.y / container.size();
			X = center.x;
			Y = center.y;
			//cout << center.x << " " << center.y << endl;
		}
		cv::circle(cam1image, cvPoint(center.x, center.y), 3, cv::Scalar(0, 200, 0), 3, 4);

		cv::imshow("�J�����P", cam1image);
		//cv::imshow("�J�����Q", cam2image);

		int key = cv::waitKey(1);
		if (key == 27 || key == 's'){
			th.detach();
			break; // ESC�ŏI��
		}
	}
	return 0;
}

//void draw_box(cv::Mat* img, cv::Rect rect){
//	cv::rectangle(*img, cv::Point2d(box.x, box.y), cv::Point2d(box.x + box.width, box.y + box.height),
//		cv::Scalar(0xff, 0x00, 0x00));
//}

//�R�[���o�b�N�֐�
void my_mouse_callback(int event, int x, int y, int flags, void* param){
	cv::Mat* image = static_cast<cv::Mat*>(param);

	switch (event){
		/*
		case cv::EVENT_MOUSEMOVE:
		if (drawing_box){
		box.width = x - box.x;
		box.height = y - box.y;
		}
		break;
		*/
	case cv::EVENT_LBUTTONDOWN:
		drawing_box = true;
		box = cv::Rect(x, y, 0, 0);
		//cout << x << " " << y << endl;
		X = x;
		Y = y;
		break;
	case cv::EVENT_LBUTTONUP:
		drawing_box = false;
		/*
		if (box.width < 0){
		box.x += box.width;
		box.width *= -1;
		}
		if (box.height < 0){
		box.y += box.height;
		box.height *= -1;
		}
		draw_box(image, box);
		*/
		break;
	}

}
