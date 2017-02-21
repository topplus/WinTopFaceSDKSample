#pragma once
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>

	
	extern class TopFaceSDK_;

	namespace voomeSDK
	{
		class WinTopFaceSDK
		{
		public:

			TopFaceSDK_* faceSDK;

			WinTopFaceSDK(void);
			~WinTopFaceSDK(void);

			void setLicense(std::string clientID,std::string clientSecret);

			int initWithFocus(std::string model_path, float focus_length);
			bool dynamicDetect(unsigned char* grayscale_image,int width,int height, std::vector<float> & faceInfo);

			void GetVersionInfo(std::string& version,int& versionNumber);
		};
	}





