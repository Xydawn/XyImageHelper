//
//  NetImageCut.cpp
//  DQPoker
//
//  Created by dawn on 16/12/17.
//
//
#include "baseheader.h"
#include "NetImageCut.hpp"
#include "CirCularNode.hpp"


void NetImageCut::cutImage(cocos2d::Sprite *imageView, cocos2d::Texture2D *image){

        if (imageView == nullptr) {
            return;
        }
        
        imageView->removeAllChildren();
        
        if (image == nullptr) {
            return;
        }
        
        float r = imageView->getContentSize().width/2.0;
        
        CirCularNode *cnode = CirCularNode::create(r);
        
        cnode->setPosition(imageView->getContentSize()/2.0);
        
        Sprite *kimage = Sprite::createWithTexture(image);
        
        float k_scale = image->getContentSize().width;
        
        if (k_scale > image->getContentSize().height) {
            k_scale = image->getContentSize().height;
        }
        
        kimage->setScale((r*2.0)/k_scale);
        
        cnode->addChild(kimage);
        
        imageView->addChild(cnode);
   
    
}
