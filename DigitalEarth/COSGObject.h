#pragma once
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgViewer/api/win32/GraphicsWindowWin32>
#include <osgGA/TrackballManipulator>
#include <osgGA/KeySwitchMatrixManipulator>
#include <osgDB/DatabasePager>
#include <osgDB/Registry>
#include <osgDB/ReadFile>
#include <osgUtil/Optimizer>
#include <osgEarth/MapNode>
#include <osgEarth/EarthManipulator>
#include <string>
//#include <osgEarthUtil/SkyNode>

class COSGObject
{
public:
	COSGObject(HWND hWnd);
	~COSGObject(void);

	void InitOSG(std::string filename);
	void InitManipulators(void);
	void InitSceneGraph();
	void InitCameraConfig();
	void PreFrameUpdate();
	void PostFrameUpdate();

	void InitOsgEarth();

	osgViewer::Viewer* getViewer();
private:
	std::string m_ModelName;
	HWND m_hWnd;
	osg::ref_ptr<osgGA::TrackballManipulator> trackball;
	osg::ref_ptr<osgGA::KeySwitchMatrixManipulator> keyswitchManipulator;
	osg::ref_ptr<osg::Node> mModel;
	osgViewer::Viewer* mViewer;
	osg::ref_ptr<osg::Group> mRoot;
	osg::ref_ptr<osgEarth::MapNode> mapNode;
	osg::ref_ptr<osgEarth::Util::EarthManipulator> em;
};


