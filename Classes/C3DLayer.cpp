#include "C3DLayer.h"

//构造
C3DLayer::C3DLayer()
{
	m_pShape_Points = NULL ;
	m_pShape_Lines  = NULL ;
	m_pShape_Triangles = NULL ;
}
//析构
C3DLayer::~C3DLayer()
{
	CC_SAFE_DELETE(m_pShape_Points);
	CC_SAFE_DELETE(m_pShape_Lines);
	CC_SAFE_DELETE(m_pShape_Triangles);
}

//初始化
bool C3DLayer::init()
{
//	m_pShape_Points = new C3DShape();
//	m_pShape_Points->CreatePoints();
    
    m_pShape_Lines = new C3DShape();
    m_pShape_Lines->CreateLines();
    
//    m_pShape_Triangles = new C3DShape();
//    m_pShape_Triangles->CreateTriangles();
    
	return true;
}
//绘制
void C3DLayer::draw(Renderer *renderer, const Mat4& transform, uint32_t flags)
{
	//开启深度测试
	CCDirector::sharedDirector()->setDepthTest(true);
    
	//投影和观察矩阵压栈
	kmGLMatrixMode(KM_GL_PROJECTION);
	kmGLPushMatrix();
	kmGLMatrixMode(KM_GL_MODELVIEW);
	kmGLPushMatrix();
	//设置一下观察与投影矩阵
	UpdateViewProjMatrix();
    
	//绘制3D物体
	Render3DWorld();
    
	//投影和观察矩阵出栈
	kmGLMatrixMode(KM_GL_PROJECTION);
	kmGLPopMatrix();
	kmGLMatrixMode(KM_GL_MODELVIEW);
	kmGLPopMatrix();
    
	//关闭深度测试
	CCDirector::sharedDirector()->setDepthTest(false);
}

//设置一下观察与投影矩阵
void	C3DLayer::UpdateViewProjMatrix()
{
	//观察矩阵的设置
	kmVec3 tEyeResult = kmVec3(0,0,-2);
	kmVec3 tLookAtResult = kmVec3(0,0,0);
	kmVec3 tUpResult = kmVec3(0,1,0);
	kmMat4 tViewMatrix;
	kmMat4LookAt(&tViewMatrix, &tEyeResult, &tLookAtResult, &tUpResult);
    
	kmGLMatrixMode(KM_GL_MODELVIEW);
	kmGLLoadIdentity();
	kmGLMultMatrix(&tViewMatrix);
    
	//投影矩阵的设置
	kmMat4 matrixPerspective;
	kmGLMatrixMode(KM_GL_PROJECTION);
	kmGLLoadIdentity();
	CCSize size =  CCDirector::sharedDirector()->getVisibleSize();
	kmMat4PerspectiveProjection( &matrixPerspective, 60, (GLfloat)size.width/size.height, 0.1f, 500.0f);
	kmGLMultMatrix(&matrixPerspective);
	
}
//绘制3D物体
void	C3DLayer::Render3DWorld()
{
	//渲染
	if(m_pShape_Points)
	{
		m_pShape_Points->Render();
	}
    
    if (m_pShape_Lines) {
        m_pShape_Lines->Render();
    }
    
    if (m_pShape_Triangles) {
        m_pShape_Triangles->Render();
    }
    
}