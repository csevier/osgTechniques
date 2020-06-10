#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Vec3>
#include <osgUtil/SmoothingVisitor>
#include <stdlib.h>

#include "logfilehandler.hpp"

osg::Vec3Array* SierpinskiGasket()
{
    osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array{};

    //triangle plane
    vertices->push_back(osg::Vec3(-1,0,-1));
    vertices->push_back(osg::Vec3(0,0,1));
    vertices->push_back(osg::Vec3(1,0,-1));


    //random start
    vertices->push_back(osg::Vec3(0.25,0,0.5));
    //gasket
    for(int i =4; i < 5004; i++)
    {
        int j = rand() % 3;
        osg::Vec3 lastpoint = (*vertices)[i-1];
        osg::Vec3 randomTrianglePoint = (*vertices)[j];
        osg::Vec3 midpont = (lastpoint + randomTrianglePoint) /2;
        vertices->push_back(midpont);
    }
    return vertices.release();
}

int main()
{
    osg::setNotifyLevel(osg::INFO);
    osg::setNotifyHandler(new LogFileHandler("osgLog.txt"));
    osg::ref_ptr<osg::Vec3Array> vertices  = SierpinskiGasket();
    osg::ref_ptr<osg::Vec4Array> color = new osg::Vec4Array{};
    osg::ref_ptr<osg::Vec3Array> norms = new osg::Vec3Array{};
    norms->push_back(osg::Vec3(0,-1,0));
    color->push_back(osg::Vec4(1,0,0,1));
    osg::ref_ptr<osg::Geometry> geom = new osg::Geometry{};

    geom->setVertexArray(vertices.get());
    geom->setColorArray(color.get());
    geom->setNormalArray(norms.get());
    geom->setNormalBinding(osg::Geometry::BIND_OVERALL);
    geom->setColorBinding(osg::Geometry::BIND_OVERALL);
    geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::POINTS,0,vertices->size()));


    osg::ref_ptr<osg::Geode> root = new osg::Geode{};
    root->addDrawable(geom.get());
    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());
    return viewer.run();
}
