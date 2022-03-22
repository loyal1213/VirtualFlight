#include "pch.h"
#include "COSGObject.h"
#include <osgGA/FlightManipulator>
#include <osgGA/DriveManipulator>
#include <osgGA/TerrainManipulator>
#include <osgGA/StateSetManipulator>

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

	InitManipulators();
	InitSceneGraph();
	InitCameraConfig();
	InitOsgEarth();

}

void COSGObject::InitManipulators(void)
{
	// Create a trackball manipulator
	trackball = new osgGA::TrackballManipulator();

	// Create a Manipulator Switcher
	keyswitchManipulator = new osgGA::KeySwitchMatrixManipulator;

	// Add our trackball manipulator to the switcher
	keyswitchManipulator->addMatrixManipulator('1', "Trackball", trackball.get());
	keyswitchManipulator->addMatrixManipulator('2', "Flight", new osgGA::FlightManipulator());
	keyswitchManipulator->addMatrixManipulator('3', "Drive", new osgGA::DriveManipulator());
	keyswitchManipulator->addMatrixManipulator('4', "Terrain", new osgGA::TerrainManipulator());

	// Init the switcher to the first manipulator (in this case the only manipulator)
	keyswitchManipulator->selectMatrixManipulator(0);  // Zero based index Value
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

	// Create the viewer for this window
	mViewer = new osgViewer::Viewer();

	// Add a Stats Handler to the viewer
	mViewer->addEventHandler(new osgViewer::StatsHandler);

	//添加状态事件
	mViewer->addEventHandler(new osgGA::StateSetManipulator(mViewer->getCamera()->getOrCreateStateSet()));
	mViewer->addEventHandler(new osgViewer::ThreadingHandler);
	//窗口大小变化事件
	mViewer->addEventHandler(new osgViewer::WindowSizeHandler);
	//添加一些常用状态设置
	mViewer->addEventHandler(new osgViewer::StatsHandler);
	// mViewer->addEventHandler(new osgViewer::HelpHandler(arguments.getApplicationUsage()));
	mViewer->addEventHandler(new osgViewer::RecordCameraPathHandler);


	// Get the current window size
	::GetWindowRect(m_hWnd, &rect);

	// Init the GraphicsContext Traits
	osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;

	// Init the Windata Variable that holds the handle for the Window to display OSG in.
	osg::ref_ptr<osg::Referenced> windata = new osgViewer::GraphicsWindowWin32::WindowData(m_hWnd);

	// Setup the traits parameters
	traits->x = 0;
	traits->y = 0;
	traits->width = rect.right - rect.left;
	traits->height = rect.bottom - rect.top;
	traits->windowDecoration = false;
	traits->doubleBuffer = true;
	traits->sharedContext = 0;
	traits->setInheritedWindowPixelFormat = true;
	traits->inheritedWindowData = windata;


	// Create the Graphics Context
	osg::GraphicsContext* gc = osg::GraphicsContext::createGraphicsContext(traits.get());

	// Init Master Camera for this View
	osg::ref_ptr<osg::Camera> camera = mViewer->getCamera();

	// Assign Graphics Context to the Camera
	camera->setGraphicsContext(gc);

	// Set the viewport for the Camera
	camera->setViewport(new osg::Viewport(0, 0, traits->width, traits->height));

	// set the draw and read buffers up for a double buffered window with rendering going to back buffer
	camera->setDrawBuffer(GL_BACK);
	camera->setReadBuffer(GL_BACK);

	// Set projection matrix and camera attribtues
	camera->setClearMask(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	camera->setClearColor(osg::Vec4f(0.2f, 0.2f, 0.4f, 1.0f));
	camera->setProjectionMatrixAsPerspective(
		30.0f, static_cast<double>(traits->width) / static_cast<double>(traits->height), 1.0, 1000.0);


	// Add the Camera to the Viewer
	// mViewer->addSlave(camera);
	mViewer->setCamera(camera);

	// Add the Camera Manipulator to the Viewer
	mViewer->setCameraManipulator(keyswitchManipulator);

	// Set the Scene Data
	mViewer->setSceneData(mRoot);

	// Realize the Viewer
	mViewer->realize();

	//mViewer->setCameraManipulator(new osgGA::TrackballManipulator);
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
