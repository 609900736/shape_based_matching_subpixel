#ifndef DJ_DETECTOR_H
#define DJ_DETECTOR_H
#include<fstream>
#include <string>
#include <opencv2\opencv.hpp>
#include <vector>
#include<map>
#include <omp.h>

#define EXPORT _declspec(dllexport)

using std::string;

enum UpLoadDefectType{ PanelBroken = 1, PanelUnfilledCorner, PanelUnfilledEdge, PanelFlange, LeadScratch, PanelScratch, TFTSidePimple };
enum DefectType1{ DzBreak = 1, CornerBreak, DzOtherBreak, NoDzBreak, CutBreak, Five, Crack, VisionDefect };
static cv::Scalar NoDzColor = cv::Scalar(199, 21, 133);
static cv::Scalar DzColor = cv::Scalar(220, 20, 60);
static cv::Scalar DzOtherColor = cv::Scalar(178, 34, 34);
static cv::Scalar CornerColor = cv::Scalar(255, 191, 0);
static cv::Scalar CutColor = cv::Scalar(34, 139, 34);
static cv::Scalar VisionColor = cv::Scalar(0, 128, 0);
static cv::Scalar FiveColor = cv::Scalar(0, 0, 128);
static cv::Scalar CrackColor = cv::Scalar(148, 0, 211);
static cv::Scalar ShellColor = cv::Scalar(100, 0, 0);
static cv::Scalar OtherColor = cv::Scalar(0, 100, 0);

struct EXPORT Segment
{
	//��ʾ����Mask
	cv::Rect						visionRect;
	cv::Mat							visionMask;
	std::vector<cv::Point>			visionPts;

	//��Ե����
	cv::Mat							edgeMask;
	cv::Mat							edgeMask1;
	cv::Mat							cornerMask;
	cv::Mat							cornerLengthMask;
	cv::Mat							dzEdgeValidMask;
	cv::Rect						upperRoi;
	cv::Rect						bottomRoi;
	cv::Rect						leftRoi;
	cv::Rect						rightRoi;
	cv::Rect						dzUpperRoi;
	cv::Rect						dzMidRoi;
	cv::Rect						dzBottomRoi;

	std::vector<cv::Point>			vecUpperPt;
	std::vector<cv::Point>			vecBottomPt;
	std::vector<cv::Point>			vecLeftPt;
	std::vector<cv::Point>			vecRightPt;
	std::vector<cv::Point>			vecUpperFivePt;
	std::vector<cv::Point>			vecRightFivePt;

	cv::Mat							edgeLineMask;
	cv::Mat							testMask;
	cv::Mat							glueOutMask;
	cv::Mat							glueMask;
	cv::Mat							dzOtherMask;
	cv::Mat							edgeErodeMask;

	cv::Mat							debugImg;
	cv::Mat							edgeImg;
	cv::Mat							dzEdgeImg;
	cv::Mat							gradImg;

	cv::Point pt1, pt2, pt3, pt4, pt5, pt6, pt7, pt8, pt9, pt10, pt1_, pt2_, pt5_;
};

struct EXPORT aContour
{
	int defectType;
	float width;
	float height;
	cv::Point2f center;
	cv::Rect2f rect;
	cv::Rect2f defectRoi;
};

class EXPORT Detector
{

	//////****************ͨ��ͷ�ļ�����***************///////////
public:
	Detector(std::string modelName);
	~Detector();
	int preparatory(cv::Mat& src);//Ԥ���������ڶ�����棬����Ҫһ�������ȴ�����ǶȾ������ȼ������ת�Ƕȣ��������л����ڲ��м���
	void setIDstring(std::string IDstring);                 //���ò�ƷID
	void setParameters(int flag_save, std::string dir);      //�����Ƿ��ͼ
	int calibration(cv::Mat& src, cv::Mat& dst, std::string name);  //�궨����
	bool loadParameters(std::map<std::string, std::map<std::string, double>> &parameters);         //�����㷨���� 
	int loadRoiParm();
	int Detect_main(cv::Mat &src, cv::Mat &dst, std::string name, std::vector<aContour>& contourVec, std::vector<aContour>& contourVec1);

private:
	string												m_id;
	string												m_dir;
	int													m_save_flag;
	int													m_drawExp;
	float												m_xRatio;
	float												m_yRatio;

	int													m_bContinue;
	bool												m_bFirst;
	cv::Mat												m_firstImg;
	cv::Rect											m_templRect;
	cv::Rect											m_roiRect;
	string												m_modelType;
	int													m_margin;
	int													m_grayVal;

	//Common
	int													m_debug;
	int													m_okImg;
	int													m_originImg;
	int													m_resultImg;


	std::map<std::string, std::map<std::string, double>> m_parameters;


};

#endif