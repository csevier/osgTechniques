#include <osgViewer/Viewer>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Vec3>
#include <iostream>


osg::Vec3 MidPointDivide(osg::Vec3 one, osg::Vec3 two)
{
    one.normalize();
    two.normalize();
    osg::Vec3 mid = (one + two) / 2;
    mid.normalize();
    return mid;
}

int main()
{
    osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array{};
    //triangle plane
    osg::Vec3 origin = osg::Vec3(0,0,0);


    osg::Vec3 right = osg::Vec3(0,0,-1);
    right.normalize(); // now on the unit sphere.

    osg::Vec3 left = osg::Vec3(1,0,0);
    left.normalize(); // now on the unit sphere.

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

    float angle = std::acos((left * right) / (right.length() * left.length())) * 180 / 3.14;
    std::cout << angle;

    osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array{};
    normals->push_back(osg::Vec3(0,-1,0));

    osg::ref_ptr<osg::Vec4Array> color = new osg::Vec4Array{};
    color->push_back(osg::Vec4(1,0,0,1));

    osg::ref_ptr<osg::Geode> root = new osg::Geode{};
    osg::ref_ptr<osg::Geometry> geom = new osg::Geometry{};

    geom->setVertexArray(vertices.get());
    geom->setNormalArray(normals.get());
    geom->setNormalBinding(osg::Geometry::BIND_OVERALL);
    geom->setColorArray(color.get());
    geom->setColorBinding(osg::Geometry::BIND_OVERALL);
    geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::TRIANGLE_FAN,0,vertices->size()));
    root->addDrawable(geom.get());
    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());
    return viewer.run();
}
