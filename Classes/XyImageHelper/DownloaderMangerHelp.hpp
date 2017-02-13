//
//  DownloaderMangerHelp.hpp
//  DQPoker
//
//  Created by dawn on 16/11/15.
//
//

#ifndef DownloaderMangerHelp_hpp
#define DownloaderMangerHelp_hpp

//#include "network/CCDownloader.h"

//下载文件   刚开始学c++时候写的 不大好   有空了好好改改

USING_NS_CC;


using namespace ui;

class DownloaderMangerHelp : public cocos2d::Ref
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointe

    static DownloaderMangerHelp*createDownloader();
    
    //下载图片
    void createDownLoader(Ref * creator,std::string url,std::function<void(int , int)> progress,std::function<void(Texture2D*)> success,std::function<void(void)> error);
 
    void createDownLoader(Ref * creator,std::string url,std::function<void(Texture2D*)> success){
          createDownLoader(creator,url, NULL, success, NULL);
    };
    void createDownLoader(Ref * creator,std::string url,std::function<void(Texture2D*)> success,std::function<void(void)> error){
         createDownLoader(creator,url, NULL, success, error);
    };
    //下载2进制数据
    void createDownloaderData(Ref * creator,std::string url,std::function<void(int , int)> progress,std::function<void(std::vector<unsigned char>&)> success,std::function<void(void)> error);
    
    void createDownloaderData(Ref * creator,std::string url,std::function<void(std::vector<unsigned char>&)> success){
          createDownloaderData(creator,url, NULL, success, NULL);
    };
    
    std::string downloadURL;
    
    std::function<void(int , int)> _progress;
    
    std::function<void(Texture2D*)> _success;
    
    std::function<void(void)> _error;
    
    std::function<void(std::vector<unsigned char>&)> _dataSuccess;
    
private:
    
    std::unique_ptr<network::Downloader> _loader;
    
    void loaderSuccess();
    
    void loaderProgress();
    
    void loaderError();
    
    void loaderDataSuccess();
    
    void loadChaseInThread();
    
    Ref *_creator;
    
    DownloaderMangerHelp(){
        _loader.reset(new network::Downloader());
        downloadURL = "";
        _progress = NULL;
        _success = NULL;
        _error = NULL;
        _dataSuccess = NULL;
        _creator = NULL;
    };
    ~DownloaderMangerHelp(){
        if (_creator) {
            _creator->release();
        }
        
    };
    
};


#endif /* DownloaderMangerHelp_hpp */
