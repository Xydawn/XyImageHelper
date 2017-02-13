//
//  DownloaderMangerHelp.cpp
//  DQPoker
//
//  Created by dawn on 16/11/15.
//
//
#include "baseheader.h"
#include "DownloaderMangerHelp.hpp"
#include "GetImageData.hpp"
#include <pthread.h>
#include "md5.h"
DownloaderMangerHelp* DownloaderMangerHelp::createDownloader(){
    
    DownloaderMangerHelp *loaer = new DownloaderMangerHelp;

    
    return loaer;
    
}

void DownloaderMangerHelp::loadChaseInThread(){
    
    Image *img = GetImageData::getDataWithPath(this->downloadURL);
    
    if (img == nullptr) {
        _success(nullptr);
        return;
    }

    
    Director::getInstance()->getScheduler()->performFunctionInCocosThread([=](){
    
        Texture2D* texture = new Texture2D();
        
        if (false == texture->initWithImage(img))
        {
            return;
        }
        
        
        
        if (_success != NULL) {
            _success(texture);
            
        }
        
        texture->autorelease();
        
        img->autorelease();

        autorelease();
        
    });
    
    
   
   

    
}

void  DownloaderMangerHelp::createDownLoader(Ref *creator,std::string url,std::function<void(int , int)> progress,std::function<void(Texture2D*)> success,std::function<void(void)> errorblock)
{
    this->downloadURL = url;
    
    
    if (creator) {
        
        this->_creator = creator;
        
        this->_creator->retain();
        
        
    }
    
    if (success) {
        this->_success = success;
    }
    
    if (url.length() == 0) {
        this->_success(nullptr);
        return;
    }
    
    //如果缓存 存在 则直接读取缓存
    if (GetImageData::imageIsInTheDict(this->downloadURL)) {
#if 0
        std::thread t1(&DownloaderMangerHelp::loadChaseInThread,this);

        t1.detach();
        
        
#else
     

        
//        this->_success(TextureCache::getInstance()->addImage(GetImageData::getTheFilePath(MD5(this->downloadURL).toStr())));
        
        TextureCache::getInstance()->addImageAsync(GetImageData::getTheFilePath(MD5(this->downloadURL).toStr()), [=](Texture2D *text){
            this->_success(text);
            this->release();
//            text->autorelease();
        });
     
        
        
#endif
        return;
    }
    
    if (this->_loader) {
        this->_loader->createDownloadDataTask(url);
    }else{
        return;
    }
    
    if (progress) {
        this->_progress = progress;
    }

    if (errorblock) {
        this->_error = errorblock;
    }
    
    loaderError();
    
    loaderSuccess();
    
    loaderProgress();
    
    
    
}

void DownloaderMangerHelp::createDownloaderData(Ref *creator,std::string url, std::function<void (int, int)> progress, std::function<void(std::vector<unsigned char>&)>data, std::function<void (void)> error){
    
    this->downloadURL = url;
    
    if (creator) {
        this->_creator = creator;
        
        this->_creator->retain();
    }
    
    if (this->_loader)
    {
        this->_loader->createDownloadDataTask(url);
    }else{
        return;
    }
    
    
    this->_progress = progress;
    
    this->_error = error;
    
    this->_dataSuccess = data;
    
    loaderProgress();
    
    loaderDataSuccess();
    
    loaderError();
    
    
 

}

void DownloaderMangerHelp::loaderSuccess(){
    

    
    _loader->onDataTaskSuccess = [this](const cocos2d::network::DownloadTask& task,
                                        std::vector<unsigned char>& data)
    {
        // create texture from data
        Texture2D* texture = nullptr;
        do{
            Image img;
            
            if (false == img.initWithImageData(data.data(), data.size()))
            {
                break;
            }
            
            GetImageData::saveImageDataWithPath(this->downloadURL, &img);
            
            texture = new Texture2D();
            
            if (false == texture->initWithImage(&img))
            {
                break;
            }
        
            
            if (this->_success != NULL) {
                this->_success(texture);

            }
        } while (0);
        CC_SAFE_RELEASE(texture);
        this->autorelease();
    };
}

void DownloaderMangerHelp::loaderProgress(){
    
    _loader->onTaskProgress = [this](const network::DownloadTask& task,
                                     int64_t bytesReceived,
                                     int64_t totalBytesReceived,
                                     int64_t totalBytesExpected)
    {
        float percent = float(totalBytesReceived * 100) / totalBytesExpected;
        char buf[32];
        sprintf(buf, "%.1f%%[total %d KB]", percent, int(totalBytesExpected/1024));
        CCLOG("------下载进度%s",buf);
        if (this->_progress != NULL) {
            this->_progress(percent,int(totalBytesExpected/1024));
        }
        
    };
    

}


void DownloaderMangerHelp::loaderError(){
    
    _loader->onTaskError = [this](const cocos2d::network::DownloadTask& task,
                                  int errorCode,
                                  int errorCodeInternal,
                                  const std::string& errorStr)
    {
        CCLOG("Failed to download : %s, identifier(%s) error code(%d), internal error code(%d) desc(%s)"
            , task.requestURL.c_str()
            , task.identifier.c_str()
            , errorCode
            , errorCodeInternal
            , errorStr.c_str());
        
        if (this->_error != NULL) {
            this->_error();
        }
       this->autorelease(); 
    };
}

void DownloaderMangerHelp::loaderDataSuccess(){
    
    _loader->onDataTaskSuccess = [this](const cocos2d::network::DownloadTask& task,
                                        std::vector<unsigned char>& data)
    {
        if (this->_dataSuccess) {
            this->_dataSuccess(data);
        }
       this->autorelease();
    };

    
}
