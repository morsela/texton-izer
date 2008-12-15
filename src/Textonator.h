#ifndef _H_SEGMENTATOR_H_
#define _H_SEGMENTATOR_H_

#include <vector>

#include <cv.h>
#include <highgui.h>

#include "fe/FeatureExtraction.h"
#include "Texton.h"

using std::vector;

#define FIRST_TEXTON_NUM	5
#define UNCLUSTERED_DATA	0
#define OUT_OF_SEGMENT_DATA	4
#define BORDER_DATA			1

#define EDGE_DATA			255

#define UNDEFINED			-1

class Textonator
{
public:
	Textonator(IplImage * Img, int nClusters, int nMinTextonSize);
	virtual ~Textonator();

	void	Textonize(vector<Texton*>& textonList);

private:
	
	void	ColorWindow(int x, int y, int sizeX, int sizeY);
	void	RecolorPixel(uchar * pData, int y, int x, int step, CvScalar * pColor);

	void	Segment();
	void	Cluster(CFeatureExtraction *pFeatureExtractor);

    void	colorCluster(int nCluster);
	void	blurImage();
	void	cannyEdgeDetect();
	void	extractTextons(int nCluster, vector<Texton*>& textonList);

	int		scanForTextons(int nCluster, int * pTextonMap);
	void	colorTextonMap(uchar *pBorderData,int * pTextonMap,int nCluster);
	void	assignTextons(int x, int y, uchar * pData, int * pTextonMap, int nClust);
	void	retrieveTextons(int nTexton, int nCluster, int * pTextonMap, vector<Texton*>& textonList);
	
	void	assignRemainingData(int * pTextonMap);
	void	assignStrayPixels(int ** ppTextonMap, int nSize);

	void	extractTexton(int minX, int maxX, int minY, int maxY, uchar * pImageData, IplImage* pTexton);

private:

	IplImage*	m_pImg;
	IplImage*	m_pOutImg;
	IplImage*	m_pSegmentBoundaries;

	CvMat *		m_pClusters;

	int			m_nClusters;
	int			m_nMinTextonSize;
	int			m_nCurTextonSize;

	CvScalar	m_bgColor;
	
};

#endif	//_H_SEGMENTATOR_H_