//
//  GetImageData.cpp
//  DJPoker
//
//  Created by dawn on 17/1/11.
//
//
#include "baseheader.h"
#include "GetImageData.hpp"
#include "md5.h"

//不用改变  因为 传进来 已经是  全路径
 Data GetImageData::getImageDataWithPath(std::string imagePath){
    
     std::string filepath = FileUtils::getInstance()->fullPathForFilename(imagePath);
     
     //读取的内容
     return FileUtils::getInstance()->getDataFromFile(filepath.c_str());
     
}


bool GetImageData::imageIsInTheDict(std::string urlPath){
    
    std::string path = getTheFilePath(MD5(urlPath).toStr());

    
    return FileUtils::getInstance()->isFileExist(path);
}



Image * GetImageData::getDataWithPath(std::string imagePath){
    
    
    std::string path = getTheFilePath(MD5(imagePath).toStr());
    
    if (FileUtils::getInstance()->isFileExist(path)) {
        
        Image * image = new Image;
        
        image->initWithImageFile(path);
        
        return image;
        
    }else{
        
        return nullptr;
        
    }
    
    
}

std::string GetImageData::saveDataWithPath(std::string filePath){
    
     std::string path = getTheFilePath(MD5(filePath).toStr());
//    FileUtils::getInstance()->writeDataToFile(, )
    
    return path;
    
}

std::string GetImageData::saveImageDataWithPath(std::string imagePath, cocos2d::Image *image){
    
    std::string path = getTheFilePath(MD5(imagePath).toStr());
    
    image->saveToFile(path);
    
    return path;

}

void GetImageData::deleteTheRootDom(){
    
    int oldTime = UserDefault::getInstance()->getIntegerForKey("rootDom");
    
    if (oldTime>0) {
        
        time_t nowTime = time(0);
        
        nowTime = nowTime / K_TIME;
        
        if (nowTime != oldTime) {
            
            std::string rootDow = UserDefault::getInstance()->getStringForKey("path");
            
            
            if (FileUtils::getInstance()->isFileExist(rootDow)) {
                
                FileUtils::getInstance()->removeDirectory(rootDow);
                
    
                UserDefault::getInstance()->deleteValueForKey("path");
            }
            
        }
        
    }
    
}

std::string GetImageData::getTheFilePath(std::string path){
    
//    std::string rootPath = __String::createWithFormat("%s/%s",creatTheRootDom().c_str(),path.c_str())->getCString();
    
    std::string rootPath = creatTheRootDom() +"/"+ path;
    
    return rootPath;
    
}

std::string GetImageData::creatTheRootDom(){
    
    time_t nowTime = time(0);
    
    nowTime = nowTime / K_TIME;
    
    std::string rootDow = std::to_string(nowTime);
    
    std::string path = FileUtils::getInstance()->fullPathFromRelativeFile(rootDow,FileUtils::getInstance()->getWritablePath());
    
    UserDefault::getInstance()->setStringForKey("path", path);
    
    if (!FileUtils::getInstance()->isFileExist(path)) {
        
        deleteTheRootDom();
        
        UserDefault::getInstance()->setIntegerForKey("rootDom", (int)nowTime);
        
        FileUtils::getInstance()->createDirectory(path);
        
    }
    
    return path;
    
}
