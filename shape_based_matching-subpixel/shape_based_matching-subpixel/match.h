#ifndef MATCH_H
#define MATCH_H

#include <vector>
#include <opencv2/opencv.hpp>


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

}sRect;

class CmatchBase
{
public:
	CmatchBase() {}
	virtual ~CmatchBase() {}

	virtual int creatModel(cv::Mat &src, cv::Mat &mask = cv::Mat()) = 0;

	virtual int detect(cv::Mat &src, cv::Mat &mask = cv::Mat()) = 0;

protected:

	sModeObj m_sModeObj;//���ɵ�ģ��
	std::vector<sRect> m_sRectVec;//ƥ������

};

class CmatchX :public CmatchBase
{
public:
	CmatchX() {}
	~CmatchX() {}

	int creatModel(cv::Mat &src, cv::Mat &mask = cv::Mat()) = 0;
	int detect(cv::Mat &src, cv::Mat &mask = cv::Mat()) = 0;

	//����
	int a;
	int b;

};

//
#endif
