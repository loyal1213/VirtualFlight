#include "pch.h"
#include "COSGObject.h"

COSGObject::COSGObject(HWND hWnd):m_hWnd(hWnd)
{
	// osgEarth::initialize();
}


COSGObject::~COSGObject(void)
{
	mViewer->setDone(true);
	Sleep(1000);
	mViewer->stopThreading();

	delete mViewer;
}

void COSGObject::InitOSG(std::string filename)
{

	// Store the name of the model to load
	m_ModelName = filename;

	InitSceneGraph();
	InitCameraConfig();
	InitOsgEarth();

}

void COSGObject::InitSceneGraph()
{
	mRoot = new osg::Group;
	// osg::ref_ptr<osg::Node> mp 
	mModel = osgDB::readNodeFile(m_ModelName.c_str());//"../x86/oe32-src/tests/arcgisonline.earth");//"arcgisonline.earth");
	mRoot->addChild(mModel);
	mapNode = dynamic_cast<osgEarth::MapNode*>(mModel.get());
	//mRoot->addChild(osgDB::readNodeFile("H:/002.OpenSceneGraph/019.Earth/003.第三讲-VPB用法详解与常见问题处理/vpbtest/TestCommon10/output.ive"));

}

void COSGObject::InitCameraConfig()
{
	RECT rect;
	mViewer = new osgViewer::Viewer;
	::GetWindowRect(m_hWnd, &rect);
	osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
	osg::ref_ptr<osg::Referenced> windata = new osgViewer::GraphicsWindowWin32::WindowData(m_hWnd);
	traits->x = 0;
	traits->y = 0;
	traits->width = rect.right - rect.left;
	traits->height = rect.bottom - rect.top;
	traits->windowDecoration = false;
	traits->doubleBuffer = true;
	traits->sharedContext = 0;
	traits->setInheritedWindowPixelFormat = true;
	traits->inheritedWindowData = windata;
	osg::GraphicsContext* gc = osg::GraphicsContext::createGraphicsContext(traits);

	osg::ref_ptr<osg::Camera> camera = new osg::Camera;
	camera->setGraphicsContext(gc);
	camera->setViewport(new osg::Viewport(traits->x, traits->y, traits->width, traits->height));
	camera->setProjectionMatrixAsPerspective(30.0f, static_cast<double>(traits->width) / static_cast<double>(traits->height), 1.0, 1000.0);

	mViewer->setCamera(camera);
	//mViewer->setCameraManipulator(new osgGA::TrackballManipulator);
	mViewer->setSceneData(mRoot);
	mViewer->realize();
	mViewer->getCamera()->setComputeNearFarMode(osg::CullSettings::COMPUTE_NEAR_FAR_USING_PRIMITIVES);
	mViewer->getCamera()->setNearFarRatio(0.000003f);
}

void COSGObject::PreFrameUpdate()
{

}

void COSGObject::PostFrameUpdate()
{

}


osgViewer::Viewer* COSGObject::getViewer()
{
	return mViewer;
}

void COSGObject::InitOsgEarth()
{
	em = new osgEarth::Util::EarthManipulator;
	if (mapNode.valid())
	{
		em->setNode(mapNode);
	}
	em->getSettings()->setArcViewpointTransitions(true);
	mViewer->setCameraManipulator(em);


	//osgEarth::Config skyConf;
	//double hours = skyConf.value("hours", 12.0);
	//osg::ref_ptr<osgEarth::Util::SkyNode> sky_node = new osgEarth::Util::SkyNode(mapNode->getMap());
	//sky_node->setDateTime(2012, 1, 27, hours);
	//sky_node->attach(mViewer, 1);
	//sky_node->setAmbientBrightness(1.0, mViewer);
	//mRoot->addChild(sky_node);

}
