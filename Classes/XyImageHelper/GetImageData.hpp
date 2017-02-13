//
//  GetImageData.hpp
//  DJPoker
//
//  Created by dawn on 17/1/11.
//
//

#ifndef GetImageData_hpp
#define GetImageData_hpp

//图片存储 以及 提取

//文件创建时间为2天
#define K_TIME (60*60*24*2)
USING_NS_CC;

using namespace ui;

class GetImageData : Ref  {
    
public:
    
    static Data getImageDataWithPath(std::string imagePath);
    //MARK: image需要释放
    static Image * getDataWithPath(std::string imagePath);
    //MARK: 文件存在
    static bool imageIsInTheDict(std::string urlPath);
    
    static std::string saveDataWithPath(std::string filePath);
    
    static std::string saveImageDataWithPath(std::string imagePath,Image * image);
    
    static void deleteTheRootDom();
    
    static std::string creatTheRootDom();
    
    static std::string getTheFilePath(std::string path);
    
private:

    GetImageData(){
        
    };
    
    ~GetImageData(){
        
    };
    
};

#endif /* GetImageData_hpp */
