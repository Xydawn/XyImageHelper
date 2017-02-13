//
//  CirCularNode.hpp
//  NewDemo
//
//  Created by dawn on 16/12/15.
//
//

#ifndef __CirCularNode__
#define __CirCularNode__

#include <stdio.h>
#include "cocos2d.h"
#include "extensions/cocos-ext.h"

class CirCularNode:public cocos2d::ClippingNode
{
public:
    CirCularNode();
    virtual ~CirCularNode();
    /**
     *  创建一个圆形clippingNode
     *
     *  @param radius 创建的圆形半径
     *
     *  @return 返回一个剪切node
     */
    static CirCularNode* create(float radius);
    
    void setClipNode(Node *node);
    
    Node *getClipNode();
    /**
     *  创建一个圆形的clippingNode
     *
     *  @param radius 创建的圆形半径
     *  @param sprite 需要切呈圆形的精灵
     *
     *  @return 返回一个剪切node
     */
    static CirCularNode* create(float radius, cocos2d::Node* pNode);
    
    virtual bool init(float radius);
    
    cocos2d::Node  * m_clipNode;
//    CC_PROPERTY(cocos2d::Node*, m_clipNode, ClipNode);
};
#endif
