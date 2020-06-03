# set the minimum required version across the board
cmake_minimum_required(VERSION 3.1.0)

project(osgTechniques)
find_package(OpenSceneGraph 3.3.4 REQUIRED osgDB osgViewer osgText osgGA osgParticle osgUtil osgFX osgShadow)
file(GLOB SOURCES "src/*.cpp"
    "src/*.hpp")

add_executable(osgTechniques ${SOURCES})
if (OpenSceneGraph_FOUND)
    include_directories(SYSTEM ${OPENSCENEGRAPH_INCLUDE_DIRS})
    link_libraries(${OPENSCENEGRAPH_LIBRARIES})
    target_link_libraries(osgTechniques ${OPENSCENEGRAPH_LIBRARIES})
    message("found osg")
endif()
set(USED_OSG_PLUGINS
                    osgdb_bmp
                    osgdb_dds
                    osgdb_freetype
                    osgdb_jpeg
                    osgdb_osg
                    osgdb_png
                    osgdb_serializers_osg
                    osgdb_tga
                  )


