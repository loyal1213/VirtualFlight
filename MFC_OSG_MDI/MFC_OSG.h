#pragma once

#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgViewer/api/win32/GraphicsWindowWin32>
#include <osgGA/TrackballManipulator>
#include <osgGA/KeySwitchMatrixManipulator>
#include <osgGA/FlightManipulator>
#include <osgGA/DriveManipulator>
#include <osgGA/TerrainManipulator>
#include <osgDB/DatabasePager>
#include <osgDB/Registry>
#include <osgDB/ReadFile>
#include <osgUtil/Optimizer>
#include <string>

class cOSG
{
public:
	cOSG(HWND hWnd);
	~cOSG();

	void InitOSG(std::string filename);
	void InitManipulators(void);
	void InitSceneGraph(void);
	void InitCameraConfig(void);
	void SetupWindow(void);
	void SetupCamera(void);
	void PreFrameUpdate(void);
	void PostFrameUpdate(void);
	void Done(bool value) { mDone = value; }
	bool Done(void) { return mDone; }
	//static void Render(void* ptr);

	osgViewer::Viewer* getViewer() { return mViewer; }

private:
	bool mDone;
	std::string m_ModelName;
	HWND m_hWnd;
	osgViewer::Viewer* mViewer;
	osg::ref_ptr<osg::Group> mRoot; // ���������
	osg::ref_ptr<osg::Node> mModel; // ����ģ���ļ� 
	osg::ref_ptr<osgGA::TrackballManipulator> trackball;  // trackball ������
	osg::ref_ptr<osgGA::KeySwitchMatrixManipulator> keyswitchManipulator; //����KeySwitchѡ�������
};

class CRenderingThread : public OpenThreads::Thread
{
public:
	CRenderingThread(cOSG* ptr);
	virtual ~CRenderingThread();

	virtual void run();

protected:
	cOSG* _ptr;
	bool _done;
};
