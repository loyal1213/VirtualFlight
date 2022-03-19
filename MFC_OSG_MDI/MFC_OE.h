#pragma once

#include <osgEarth/MapNode>
#include <osgEarth/EarthManipulator>
#include <osgEarth/ExampleResources>
#include <osgEarth/ImageOverlay>
#include <osgEarth/CircleNode>
#include <osgEarth/RectangleNode>
#include <osgEarth/EllipseNode>
#include <osgEarth/PlaceNode>
#include <osgEarth/LabelNode>
#include <osgEarth/LocalGeometryNode>
#include <osgEarth/FeatureNode>
#include <osgEarth/ModelNode>
#include <osgEarth/ImageOverlayEditor>
#include <osgEarth/GeometryFactory>
#include <osgViewer/Viewer>

using namespace osgEarth;
using namespace osgEarth::Util;

class cOsgEarth
{
public:
	cOsgEarth(HWND hWnd);
	~cOsgEarth();

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
	osg::ref_ptr<osg::Group> mRoot; // 场景根结点
	osg::ref_ptr<osg::Node> mModel; // 场景模型文件 
};
