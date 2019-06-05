#ifndef MATCH_H
#define MATCH_H

#include <vector>
#include <opencv2/opencv.hpp>
#include <string>
#include ".\\match\\line2Dup.h"

//ģ�ͽṹ
typedef struct
{

}sModex;

//ģ�ͼ���
typedef struct
{
	std::vector<sModex> objVec;
}sModeObj;

//ƥ����
typedef struct
{
	std::string classID;//Ŀ�����
	cv::Rect rect;//Ŀ��λ��
	float similarity;//Ŀ�����ƶ�


}sRect;

class CmatchBase
{
public:
	CmatchBase() {};
	virtual ~CmatchBase() {};

	virtual int creatModel(cv::Mat &src, cv::Mat &mask = cv::Mat(), std::string classID = "") = 0;

	virtual int detect(cv::Mat &src, cv::Mat &mask = cv::Mat(), std::string classID = "") = 0;

protected:

	sModeObj m_sModeObj;//���ɵ�ģ��
	std::vector<sRect> m_sRectVec;//ƥ������

};

class CmatchHL :public CmatchBase
{
public:
	CmatchHL();
	~CmatchHL();

	int creatModel(cv::Mat &src, cv::Mat &mask = cv::Mat(), std::string classID = "");
	int loadModel(std::string classID = "");
	int detect(cv::Mat &src, cv::Mat &dst, std::string classID = "");
	int	setParmeter(float startAngle, float endAngle, float stepAngle, float startScale, float endScale, float stepScale, int numFeatures);

	//����
	float	m_similarity;
	float	m_startAngle;
	float	m_endAngle;
	float	m_stepAngle;
	float	m_startScale;
	float	m_endScale;
	float	m_stepScale;
	int		m_numFeatures;
	line2Dup::Detector m_detector;
	std::vector<std::string> m_ids;
	std::vector<shape_based_matching::shapeInfo_producer::Info>  m_infos;

};

//
#endif
