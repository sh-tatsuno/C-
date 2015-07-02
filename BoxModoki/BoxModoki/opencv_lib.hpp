#pragma once

#define CV_VER  CVAUX_STR(CV_MAJOR_VERSION) CVAUX_STR(CV_MINOR_VERSION) CVAUX_STR(CV_SUBMINOR_VERSION)

#if _DEBUG
#define CV_EXT "d.lib"
#else
#define CV_EXT ".lib"
#endif

#pragma comment(lib, "opencv_calib3d"    CV_VER CV_EXT)
#pragma comment(lib, "opencv_contrib"    CV_VER CV_EXT)
#pragma comment(lib, "opencv_core"       CV_VER CV_EXT)
#pragma comment(lib, "opencv_features2d" CV_VER CV_EXT)
#pragma comment(lib, "opencv_flann"      CV_VER CV_EXT)
//#pragma comment(lib, "opencv_gpu"        CV_VER CV_EXT)
#pragma comment(lib, "opencv_highgui"    CV_VER CV_EXT)
#pragma comment(lib, "opencv_imgproc"    CV_VER CV_EXT)
//#pragma comment(lib, "opencv_imgcodecs"  CV_VER CV_EXT)
#pragma comment(lib, "opencv_legacy"     CV_VER CV_EXT)
#pragma comment(lib, "opencv_ml"         CV_VER  CV_EXT)
#pragma comment(lib, "opencv_nonfree"    CV_VER CV_EXT)
#pragma comment(lib, "opencv_objdetect"  CV_VER CV_EXT)
#pragma comment(lib, "opencv_ocl"        CV_VER CV_EXT)
#pragma comment(lib, "opencv_photo"      CV_VER CV_EXT)
#pragma comment(lib, "opencv_stitching"  CV_VER CV_EXT)
#pragma comment(lib, "opencv_superres"   CV_VER CV_EXT)
#pragma comment(lib, "opencv_ts"         CV_VER CV_EXT)
#pragma comment(lib, "opencv_video"      CV_VER CV_EXT)
//#pragma comment(lib, "opencv_videoio"    CV_VER CV_EXT)
#pragma comment(lib, "opencv_videostab"  CV_VER CV_EXT)
