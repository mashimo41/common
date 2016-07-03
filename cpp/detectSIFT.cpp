#include <opencv2/opencv.hpp>
#include <opencv2/nonfree/nonfree.hpp> // SIFT・SURFモジュール用
//#include <opencv2/nonfree/features2d.hpp>

void FeatureMatching(
		     const std::string& filename1,// 画像１のファイル名
		     const std::string& filename2,// 画像２のファイル名
		     const std::string& featureDetectorName,
		     const std::string& descriptorExtractorName,
		     const std::string& descriptorMatcherName,
		     bool crossCheck);

int main(int argc, char *argv[]) {


  //    FeatureMatching("p1_photo1.jpg","p1_photo2.jpg", "ORB", "ORB", "BruteForce-Hamming",true);
  //FeatureMatching("image3.JPG","itokawa3.JPG", "SURF", "SURF", "BruteForce",false);
  FeatureMatching(argv[1], argv[2], "SIFT", "SIFT", "BruteForce",false);
  //SIFTだとおもすぎてフリーズするかも
  return 0;

}


void FeatureMatching(
		     const std::string& filename1,// 画像１のファイル名
		     const std::string& filename2,// 画像２のファイル名
		     const std::string& featureDetectorName,// detectorType
		     const std::string& descriptorExtractorName,// descriptorExtractorType
		     const std::string& descriptorMatcherName,// descriptorMatcherType
		     bool crossCheck)// マッチング結果をクロスチェックするかどうか
{
  // 画像の読み込み
  cv::Mat img1 = cv::imread(filename1);
  cv::Mat img2 = cv::imread(filename2);

  cv::resize(img1, img1, cv::Size(640, 480));

  // SIFT・SURFモジュールの初期化
  cv::initModule_nonfree();

  // 特徴点抽出(vector配列に保存)
  //  cv::Ptr<cv::FeatureDetector> detector = cv::FeatureDetector::create(featureDetectorName);
  //  cv::Ptr<cv::FeatureDetector> detector(new cv::DynamicAdaptedFeatureDetector(new cv::SurfAdjuster(), 600, 1000, 5));
  //cv::SiftFeatureDetector detector(0.04, 10);
  cv::SurfFeatureDetector detector(500);
  std::vector<cv::KeyPoint> keypoint1, keypoint2;
  detector.detect(img1, keypoint1);
  detector.detect(img2, keypoint2);


  // 特徴記述(vector配列の特徴点を???上に記述)
  cv::Ptr<cv::DescriptorExtractor> extractor = cv::DescriptorExtractor::create(descriptorExtractorName);
  cv::Mat descriptor1, descriptor2;
  extractor->compute(img1, keypoint1, descriptor1);
  extractor->compute(img2, keypoint2, descriptor2);

    
  // マッチング
  cv::Mat mask = cv::imread("mask.bmp");
  cv::Ptr<cv::DescriptorMatcher> matcher = cv::DescriptorMatcher::create(descriptorMatcherName);
  std::vector<cv::DMatch> dmatch;
  if (crossCheck)
    {
      // クロスチェックする場合
      std::vector<cv::DMatch> match12, match21;
      matcher->match(descriptor1, descriptor2, match12, mask);
      matcher->match(descriptor2, descriptor1, match21, mask);
      for (size_t i = 0; i < match12.size(); i++)
	{
	  cv::DMatch forward = match12[i];
	  cv::DMatch backward = match21[forward.trainIdx];
	  if (backward.trainIdx == forward.queryIdx)
	    dmatch.push_back(forward);
	}
    }
  else
    {
      // クロスチェックしない場合
      matcher->match(descriptor1, descriptor2, dmatch);
      double vmax = 0;
      for (size_t i = 0; i < dmatch.size(); ++i) 
      {
	vmax = vmax < dmatch[i].distance ? dmatch[i].distance: vmax;
      }
      std::cout << vmax << std::endl;
      for (size_t i = 0; i < dmatch.size(); ++i)
	{
          if (vmax / 2.6 < dmatch[i].distance || dmatch[i].distance == 0)
	    {
	    dmatch[i].queryIdx=0;
	  dmatch[i].trainIdx=0;
	    }
	}
    }
  
    
  // マッチング結果の表示
  cv::Mat out;
  cv::drawMatches(img1, keypoint1, img2, keypoint2, dmatch, out);
  cv::namedWindow("matching", CV_WINDOW_NORMAL);
  cv::imshow("matching", out);


  cv::Mat featureImage1, featureImage2;
  cv::drawKeypoints(img1, keypoint1, featureImage1, cv::Scalar(255, 255, 255), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
  cv::drawKeypoints(img2, keypoint2, featureImage2, cv::Scalar(255, 255, 255), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

  cv::namedWindow("image1", CV_WINDOW_NORMAL);
  cv::namedWindow("image2", CV_WINDOW_NORMAL);
  cv::imshow("image1", featureImage1);
  cv::imshow("image2", featureImage2);

  while (cv::waitKey(1) == -1);
  

  //特徴点の描画、SIFT・SURFの切り替え、マッチングの有無、入力画像
}
