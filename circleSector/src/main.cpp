#include <osgViewer/Viewer>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Vec3>
#include <osgUtil/Tessellator>
#include <cmath>

#include "logfilehandler.hpp"

int main()
{
    osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array{};
    //triangle plane
    osg::Vec3 origin = osg::Vec3(0,0,0);


    osg::Vec3 right = osg::Vec3(-4,0,0.5);
    right.normalize(); // now on the unit sphere.

    osg::Vec3 left = osg::Vec3(1,0,0);
    left.normalize(); // now on the unit sphere.

    osg::Vec3 normalForCirclePlane = right ^ left; // cross product.
    normalForCirclePlane.normalize();

    osg::Vec3 mid = (right + left) /2;
    mid.normalize();

    osg::Vec3 mid1 = (left + mid) /2;
    mid1.normalize();

    osg::Vec3 mid2 = (right + mid) /2;
    mid2.normalize();

    vertices->push_back(origin);
    vertices->push_back(left);
    vertices->push_back(mid1);
    vertices->push_back(mid);
    vertices->push_back(mid2);
    vertices->push_back(right); // finish


    // circle equation
    //float x = x0 + radius * (std::cos(phi)*std::cos(theta));
    //float y = y0 + radius * (std::cos(phi)*std::sin(theta));
    //float z = z0 + radius * std::sin(phi);

    // generalize
    //normalForCirclePlane.x()

//    vertices->push_back(left);
    float angle = std::acos((left * right) / (right.length() * left.length())) * 180 / 3.14;
    std::cout << angle;
//    float increment = 5;
//    float startAngle = increment; // angles for points.
//    float radius = 1;
//    while(startAngle < angle)
//    {
//        float x = radius * std::cos(startAngle * 3.14/180);
//        float y = radius * std::sin(startAngle* 3.14/180);
//        osg::Vec3 point = osg::Vec3(x, 0, y);
//        vertices->push_back(point);
//        startAngle += increment;
//    }


    osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array{};
    normals->push_back(osg::Vec3(0,-1,0));
    //color->push_back(osg::Vec4(1,0,0,1));

    osg::ref_ptr<osg::Vec4Array> color = new osg::Vec4Array{};
    color->push_back(osg::Vec4(1,0,0,1));
    color->push_back(osg::Vec4(0,1,0,1));
    color->push_back(osg::Vec4(1,1,1,1));
    color->push_back(osg::Vec4(1,1,1,1));
    color->push_back(osg::Vec4(1,1,1,1));
    color->push_back(osg::Vec4(0,0,1,1));

    osg::ref_ptr<osg::Geode> root = new osg::Geode{};
    osg::ref_ptr<osg::Geometry> geom = new osg::Geometry{};

    geom->setVertexArray(vertices.get());
    geom->setNormalArray(normals.get());
    geom->setNormalBinding(osg::Geometry::BIND_OVERALL);
    geom->setColorArray(color.get());
    geom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
    geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::TRIANGLE_FAN,0,vertices->size()));
    root->addDrawable(geom.get());
    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());
    return viewer.run();
}
