#WinTopFaceSDKSample使用说明
<br>
[官网](http://www.voome.cn)
<br>
##开发环境说明
使用vs2012进行开发 .
<br>
##支持平台说明
支持win7操作系统;支持x86平台。
<br>
##接入流程
###依赖库导入
依赖TopFaceSDK,路径:工程文件同级的WinTopFaceSDK_lib文件夹. 库文件为:WinTopFaceSDK.lib(release版本), WinTopFaceSDKd.lib(debug版本).
<br>
###授权认证
首先调用WinTopFaceSDK的setLicense(string clientID,string clientSecret)进行授权认证。
说明：申请 client_id 和 client_secret 后调用此函数获得授权。不调用认证函数无法使用人脸检测功能，正常调用认证函数即可正常使用。

<br>
<br>
[获取License](http://www.voome.cn/register/index.shtml)
<br>
###SDK初始化
在检测之前调用WinTopFaceSDK的initWithFocus(string model_path, float focus_length)进行初始化。
<br>
##接口定义和使用说明

/**<br> 
* 授权认证, 首先调用的函数<br> 
* @param clientID<br>
* @param clientSecret<br>
* @return 无返回值<br>
*/<br>
void setLicense(std::string clientID,std::string clientSecret);

/**<br> 
* 初始化TopFace<br> 
* @param model_path 资源文件路径<br>
* @param focus_length 等效焦距<br>
* @return 返回码，-1表示初始化失败，0表示初始化成功<br>
*/<br> 
int initWithFocus(std::string model_path, float focus_length);

/**<br>
 * 检测人脸<br>
 * @param grayscale_image 图像数据，单通道灰度图格式<br>
 * @param width  图像宽度<br>
 * @param height 图像高度<br>
 * @ param faceInfo长度为151的数组，第0~135位表示68个人脸特征点二维像素坐标，原点是传入图像的左上角，特征点代表意义参考示意图；第136~138位表示人脸鼻尖处在相机坐标系下的位置数据，坐标系定义：x轴正方向向右,y轴正方向向下,z轴正方向向前；第139~141位表示人脸相对相机的姿态数据，单位是弧度，依次定义为：pitch俯仰角、roll翻滚角、yaw偏航角；第142位表示置信度.<br>
 */<br>
bool dynamicDetect(unsigned char* grayscale_image,int width,int height, std::vector<float> & faceInfo);

/**<br> 
* 获取版本信息<br> 
* @param version<br>
* @param versionNumber<br>
* @return 无返回值<br>
*/<br>
void GetVersionInfo(std::string& version,int& versionNumber);



<br>
##68个人脸特征点二维像素坐标图
![](https://github.com/topplus/WinTopFaceSDKSample/raw/master/images/feature.jpg)
##开源协议
[LICENSE](https://github.com/topplus/WinTopFaceSDKSample/raw/master/LICENSE)
##开发者微信群
![](https://github.com/topplus/WinTopFaceSDKSample/raw/master/images/voomeGroup.png)
##联系我们
<br>
商务合作sales@topplusvision.com
<br>
媒体合作pr@topplusvision.com
<br>
技术支持support@topplusvision.com