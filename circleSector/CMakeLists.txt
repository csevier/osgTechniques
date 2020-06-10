file(GLOB SOURCES "src/*.cpp"
    "src/*.hpp")
find_package(OpenSceneGraph 3.3.4 REQUIRED osgDB osgViewer osgText osgGA osgParticle osgUtil osgFX osgShadow)
add_executable(circleSector ${SOURCES})
if (OpenSceneGraph_FOUND)
    include_directories(SYSTEM ${OPENSCENEGRAPH_INCLUDE_DIRS})
    link_libraries(${OPENSCENEGRAPH_LIBRARIES})
    target_link_libraries(circleSector ${OPENSCENEGRAPH_LIBRARIES})
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
