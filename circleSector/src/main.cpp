#include <osgViewer/Viewer>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Vec3>
#include <iostream>
#include <list>
#include <vector>

// Careful with fidelity!!! 4 is a damn good circle, 5 is cleannnnn. above that your asking for performance trouble.
// Vec one, and two have to be in local coordinate space or this sector algorithm will not be oriented correctly.
std::list<osg::Vec3> PointsOnUnitSphereGreaterCircle(osg::Vec3 start, osg::Vec3 termination, int fidelityIterations = 1)
{
    std::list<osg::Vec3> verts{}; // list for performant insertion,
    start.normalize(); // MUST NORMALIZE, its correct in 3d space because of the unit sphere!!.
    termination.normalize();// MUST NORMALIZE, its correct in 3d space because of the unit sphere!!.
    verts.push_back(start);
    verts.push_back(termination);

    for(int i =0; i <fidelityIterations; i++)
    {
       std::vector<std::pair<std::list<osg::Vec3>::iterator,osg::Vec3>> insertionPositions{};
       for(std::list<osg::Vec3>::iterator currentPostion = verts.begin(); currentPostion != --verts.end(); /*iter increas in body*/)
       {
           osg::Vec3 left = *(currentPostion);
           osg::Vec3 right = *(++currentPostion);
           osg::Vec3 mid = (left + right) / 2;
           mid.normalize(); // MUST NORMALIZE, its correct in 3d space because of the unit sphere!!.
           insertionPositions.push_back(std::make_pair(currentPostion, mid)); // add the midpoint AFTER left vertex of the calculation.
       }
       // add new verts to list at correct positions.
       for(auto pair : insertionPositions)
       {
           verts.insert(pair.first, pair.second);
       }
       // you must clear the verts that have been added, the new round will calculate again with the new points.
       insertionPositions.clear();
    }
    return verts;
}

int main()
{
    osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array{};
    //triangle plane
    osg::Vec3 origin = osg::Vec3(0,0,0);
    osg::Vec3 start = osg::Vec3(-1,0,0.0001);
    osg::Vec3 termination = osg::Vec3(1,0,0);
    vertices->push_back(origin);

    auto verts = PointsOnUnitSphereGreaterCircle(start, termination, 4);

    for(auto vert:verts )
    {
        vertices->push_back(vert);
    }

    float angle = std::acos((start * termination) / (termination.length() * start.length())) * 180 / 3.14;
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
