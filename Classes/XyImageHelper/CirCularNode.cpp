//
//  CirCularNode.cpp
//  NewDemo
//
//  Created by dawn on 16/12/15.
//
//
#include "baseheader.h"
#include "CirCularNode.hpp"
USING_NS_CC;

CirCularNode::CirCularNode()
:m_clipNode(nullptr)
{
    
}

CirCularNode::~CirCularNode()
{
    CC_SAFE_RELEASE_NULL(m_clipNode);
}

CirCularNode* CirCularNode::create(float radius)
{
    auto pClipNode = new CirCularNode();
    if (pClipNode && pClipNode->init(radius))
    {
        pClipNode->autorelease();
    }
    else
    {
        delete pClipNode;
        pClipNode = nullptr;
    }
    return pClipNode;
}

bool CirCularNode::init(float radius)
{
    if (!ClippingNode::init())
    {
        CCLOG("CirCularNode parent init failed!");
        return false;
    }
    
    //使用drawNode画圆形
    auto circleNode = DrawNode::create();
    
    //顶点坐标个数，在需要画大圆的时候，这个值就要相应变大一点
    const int maxTrangle = 360;
    
    //顶点数组
    Vec2 circleVec2[maxTrangle];
    //计算圆上面的各个点的坐标
    for (int i = 0; i < maxTrangle; i ++)
    {
        float x = cosf( i * (M_PI/180.f)) * radius;
        float y = sinf( i * (M_PI/180.f)) * radius;
        circleVec2[i] = Vec2(x, y);
    }
    
    //颜色
    auto circleColor = Color4F(0, 1, 0, 1);
    
    circleNode->drawPolygon(circleVec2, maxTrangle, circleColor, 1, circleColor);
    
    //设置clippingNode的模板类
    setStencil(circleNode);
    
    return true;
}

CirCularNode* CirCularNode::create(float radius, Node* pNode)
{
    auto clipNode = CirCularNode::create(radius);
    if (clipNode)
    {
        clipNode->setClipNode(pNode);
    }
    
    return clipNode;
}

void CirCularNode::setClipNode(Node* pNode)
{
    CC_SAFE_RELEASE_NULL(m_clipNode);
    m_clipNode = pNode;
    CC_SAFE_RETAIN(m_clipNode);
    
    addChild(pNode);
}

Node* CirCularNode::getClipNode()
{
    return m_clipNode;
}
