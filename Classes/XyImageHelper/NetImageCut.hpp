//
//  NetImageCut.hpp
//  DQPoker
//
//  Created by dawn on 16/12/17.
//
// cocos studio手动创建的图片 不能直接用clipnode来实现圆形  只好用了这个方法  感觉不太好  不如直接手写

#ifndef NetImageCut_hpp
#define NetImageCut_hpp

USING_NS_CC;

using namespace ui;

class NetImageCut :  public cocos2d::Ref
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static void cutImage(Sprite *imageView,Texture2D *image);
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    
    
    
    // implement the "static create()" method manually
    
    
private:
    
    NetImageCut(){
        
    };
    
    ~NetImageCut(){
        
    }
    
    
};


#endif /* NetImageCut_hpp */
