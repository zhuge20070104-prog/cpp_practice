#ifndef _FREDRIC_CV_UTIL_H_
#define _FREDRIC_CV_UTIL_H_

#include <QtGui/QPixmap>
#include <opencv2/core/core.hpp>
 
class util
{
public:
    static QPixmap matToPixmap(const QSize & size,const cv::Mat & mat);//Mat转QPixmap
    static void readImage(const QString & filePath,cv::Mat & mat);//打开一张图片
 
private:
    util();
};

#endif