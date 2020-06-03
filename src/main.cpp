#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

int main()
{

    osg::ref_ptr<osg::Node> root = osgDB::readNodeFile("/home/csevier/source/osgTechniques/resources/cow.osg");
    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());
    return viewer.run();
}
