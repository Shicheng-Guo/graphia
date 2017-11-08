include(${CMAKE_CURRENT_SOURCE_DIR}/../common.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/../thirdparty/thirdparty.cmake)

add_definitions(-DPRODUCT_NAME="${PROJECT_NAME}")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

list(APPEND HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/application.h 
    ${CMAKE_CURRENT_LIST_DIR}/attributes/attribute.h 
    ${CMAKE_CURRENT_LIST_DIR}/attributes/availableattributesmodel.h 
    ${CMAKE_CURRENT_LIST_DIR}/attributes/conditionfncreator.h 
    ${CMAKE_CURRENT_LIST_DIR}/attributes/condtionfnops.h 
    ${CMAKE_CURRENT_LIST_DIR}/auth/auth.h 
    ${CMAKE_CURRENT_LIST_DIR}/commands/applytransformscommand.h 
    ${CMAKE_CURRENT_LIST_DIR}/commands/applyvisualisationscommand.h 
    ${CMAKE_CURRENT_LIST_DIR}/commands/commandmanager.h 
    ${CMAKE_CURRENT_LIST_DIR}/commands/selectnodescommand.h 
    ${CMAKE_CURRENT_LIST_DIR}/crashtype.h 
    ${CMAKE_CURRENT_LIST_DIR}/graph/componentmanager.h 
    ${CMAKE_CURRENT_LIST_DIR}/graph/elementiddistinctsetcollection.h 
    ${CMAKE_CURRENT_LIST_DIR}/graph/graphcomponent.h 
    ${CMAKE_CURRENT_LIST_DIR}/graph/graphconsistencychecker.h 
    ${CMAKE_CURRENT_LIST_DIR}/graph/graph.h 
    ${CMAKE_CURRENT_LIST_DIR}/graph/graphmodel.h 
    ${CMAKE_CURRENT_LIST_DIR}/graph/mutablegraph.h 
    ${CMAKE_CURRENT_LIST_DIR}/graph/qmlelementid.h 
    ${CMAKE_CURRENT_LIST_DIR}/layout/barneshuttree.h 
    ${CMAKE_CURRENT_LIST_DIR}/layout/centreinglayout.h 
    ${CMAKE_CURRENT_LIST_DIR}/layout/circlepackcomponentlayout.h 
    ${CMAKE_CURRENT_LIST_DIR}/layout/collision.h 
    ${CMAKE_CURRENT_LIST_DIR}/layout/componentlayout.h 
    ${CMAKE_CURRENT_LIST_DIR}/layout/fastinitiallayout.h 
    ${CMAKE_CURRENT_LIST_DIR}/layout/forcedirectedlayout.h 
    ${CMAKE_CURRENT_LIST_DIR}/layout/layout.h 
    ${CMAKE_CURRENT_LIST_DIR}/layout/layoutsettings.h 
    ${CMAKE_CURRENT_LIST_DIR}/layout/nodepositions.h 
    ${CMAKE_CURRENT_LIST_DIR}/layout/octree.h 
    ${CMAKE_CURRENT_LIST_DIR}/layout/powerof2gridcomponentlayout.h 
    ${CMAKE_CURRENT_LIST_DIR}/layout/randomlayout.h 
    ${CMAKE_CURRENT_LIST_DIR}/layout/scalinglayout.h 
    ${CMAKE_CURRENT_LIST_DIR}/layout/sequencelayout.h 
    ${CMAKE_CURRENT_LIST_DIR}/loading/parserthread.h 
    ${CMAKE_CURRENT_LIST_DIR}/maths/boundingbox.h 
    ${CMAKE_CURRENT_LIST_DIR}/maths/boundingsphere.h 
    ${CMAKE_CURRENT_LIST_DIR}/maths/circle.h 
    ${CMAKE_CURRENT_LIST_DIR}/maths/conicalfrustum.h 
    ${CMAKE_CURRENT_LIST_DIR}/maths/constants.h 
    ${CMAKE_CURRENT_LIST_DIR}/maths/frustum.h 
    ${CMAKE_CURRENT_LIST_DIR}/maths/interpolation.h 
    ${CMAKE_CURRENT_LIST_DIR}/maths/line.h 
    ${CMAKE_CURRENT_LIST_DIR}/maths/plane.h 
    ${CMAKE_CURRENT_LIST_DIR}/maths/ray.h 
    ${CMAKE_CURRENT_LIST_DIR}/rendering/camera.h 
    ${CMAKE_CURRENT_LIST_DIR}/rendering/compute/gpucomputejob.h 
    ${CMAKE_CURRENT_LIST_DIR}/rendering/compute/gpucomputethread.h 
    ${CMAKE_CURRENT_LIST_DIR}/rendering/compute/sdfcomputejob.h 
    ${CMAKE_CURRENT_LIST_DIR}/rendering/glyphmap.h 
    ${CMAKE_CURRENT_LIST_DIR}/rendering/graphcomponentrenderer.h 
    ${CMAKE_CURRENT_LIST_DIR}/rendering/graphcomponentscene.h 
    ${CMAKE_CURRENT_LIST_DIR}/rendering/graphoverviewscene.h 
    ${CMAKE_CURRENT_LIST_DIR}/rendering/graphrenderer.h 
    ${CMAKE_CURRENT_LIST_DIR}/rendering/opengldebuglogger.h 
    ${CMAKE_CURRENT_LIST_DIR}/rendering/openglfunctions.h 
    ${CMAKE_CURRENT_LIST_DIR}/rendering/primitives/arrow.h 
    ${CMAKE_CURRENT_LIST_DIR}/rendering/primitives/rectangle.h 
    ${CMAKE_CURRENT_LIST_DIR}/rendering/primitives/sphere.h 
    ${CMAKE_CURRENT_LIST_DIR}/rendering/scene.h 
    ${CMAKE_CURRENT_LIST_DIR}/rendering/shadertools.h 
    ${CMAKE_CURRENT_LIST_DIR}/rendering/transition.h 
    ${CMAKE_CURRENT_LIST_DIR}/transform/graphtransformconfig.h 
    ${CMAKE_CURRENT_LIST_DIR}/transform/graphtransformconfigparser.h 
    ${CMAKE_CURRENT_LIST_DIR}/transform/graphtransform.h 
    ${CMAKE_CURRENT_LIST_DIR}/transform/graphtransformparameter.h 
    ${CMAKE_CURRENT_LIST_DIR}/transform/transformcache.h 
    ${CMAKE_CURRENT_LIST_DIR}/transform/transformedgraph.h 
    ${CMAKE_CURRENT_LIST_DIR}/transform/transforminfo.h 
    ${CMAKE_CURRENT_LIST_DIR}/transform/transforms/eccentricitytransform.h 
    ${CMAKE_CURRENT_LIST_DIR}/transform/transforms/edgecontractiontransform.h 
    ${CMAKE_CURRENT_LIST_DIR}/transform/transforms/filtertransform.h 
    ${CMAKE_CURRENT_LIST_DIR}/transform/transforms/mcltransform.h 
    ${CMAKE_CURRENT_LIST_DIR}/transform/transforms/pageranktransform.h 
    ${CMAKE_CURRENT_LIST_DIR}/ui/alert.h 
    ${CMAKE_CURRENT_LIST_DIR}/ui/document.h 
    ${CMAKE_CURRENT_LIST_DIR}/ui/graphcommoninteractor.h 
    ${CMAKE_CURRENT_LIST_DIR}/ui/graphcomponentinteractor.h 
    ${CMAKE_CURRENT_LIST_DIR}/ui/graphoverviewinteractor.h 
    ${CMAKE_CURRENT_LIST_DIR}/ui/graphquickitem.h 
    ${CMAKE_CURRENT_LIST_DIR}/ui/interactor.h 
    ${CMAKE_CURRENT_LIST_DIR}/ui/searchmanager.h 
    ${CMAKE_CURRENT_LIST_DIR}/ui/selectionmanager.h 
    ${CMAKE_CURRENT_LIST_DIR}/ui/visualisations/colorgradient.h 
    ${CMAKE_CURRENT_LIST_DIR}/ui/visualisations/colorvisualisationchannel.h 
    ${CMAKE_CURRENT_LIST_DIR}/ui/visualisations/defaultgradients.h 
    ${CMAKE_CURRENT_LIST_DIR}/ui/visualisations/elementvisual.h 
    ${CMAKE_CURRENT_LIST_DIR}/ui/visualisations/sizevisualisationchannel.h 
    ${CMAKE_CURRENT_LIST_DIR}/ui/visualisations/textvisualisationchannel.h 
    ${CMAKE_CURRENT_LIST_DIR}/ui/visualisations/visualisationbuilder.h 
    ${CMAKE_CURRENT_LIST_DIR}/ui/visualisations/visualisationchannel.h 
    ${CMAKE_CURRENT_LIST_DIR}/ui/visualisations/visualisationconfig.h 
    ${CMAKE_CURRENT_LIST_DIR}/ui/visualisations/visualisationconfigparser.h 
    ${CMAKE_CURRENT_LIST_DIR}/ui/visualisations/visualisationinfo.h 
    ${CMAKE_CURRENT_LIST_DIR}/transform/availabletransformsmodel.h 
    ${CMAKE_CURRENT_LIST_DIR}/loading/saver.h 
    ${CMAKE_CURRENT_LIST_DIR}/loading/loader.h 
    ${CMAKE_CURRENT_LIST_DIR}/commands/deletenodescommand.h 
    ${CMAKE_CURRENT_LIST_DIR}/ui/hovermousepassthrough.h 
    ${CMAKE_CURRENT_LIST_DIR}/graph/elementiddistinctsetcollection_debug.h 
    ${CMAKE_CURRENT_LIST_DIR}/graph/graphfilter.h
)

list(APPEND SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/application.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/attributes/attribute.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/attributes/availableattributesmodel.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/attributes/conditionfncreator.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/auth/auth.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/commands/applytransformscommand.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/commands/applyvisualisationscommand.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/commands/commandmanager.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/commands/deletenodescommand.cpp
    ${CMAKE_CURRENT_LIST_DIR}/graph/componentmanager.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/graph/graphconsistencychecker.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/graph/graph.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/graph/graphmodel.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/graph/mutablegraph.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/layout/barneshuttree.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/layout/centreinglayout.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/layout/circlepackcomponentlayout.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/layout/collision.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/layout/componentlayout.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/layout/fastinitiallayout.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/layout/forcedirectedlayout.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/layout/layout.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/layout/layoutsettings.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/layout/nodepositions.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/layout/powerof2gridcomponentlayout.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/layout/randomlayout.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/layout/scalinglayout.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/loading/loader.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/loading/parserthread.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/loading/saver.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/main.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/maths/boundingbox.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/maths/boundingsphere.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/maths/conicalfrustum.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/maths/frustum.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/maths/plane.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/maths/ray.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/rendering/camera.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/rendering/compute/gpucomputethread.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/rendering/compute/sdfcomputejob.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/rendering/glyphmap.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/rendering/graphcomponentrenderer.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/rendering/graphcomponentscene.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/rendering/graphoverviewscene.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/rendering/graphrenderer.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/rendering/opengldebuglogger.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/rendering/openglfunctions.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/rendering/primitives/arrow.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/rendering/primitives/rectangle.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/rendering/primitives/sphere.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/rendering/transition.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/transform/availabletransformsmodel.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/transform/graphtransformconfig.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/transform/graphtransformconfigparser.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/transform/graphtransform.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/transform/transformcache.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/transform/transformedgraph.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/transform/transforms/eccentricitytransform.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/transform/transforms/edgecontractiontransform.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/transform/transforms/filtertransform.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/transform/transforms/mcltransform.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/transform/transforms/pageranktransform.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/ui/document.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/ui/graphcommoninteractor.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/ui/graphcomponentinteractor.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/ui/graphoverviewinteractor.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/ui/graphquickitem.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/ui/searchmanager.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/ui/selectionmanager.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/ui/visualisations/colorgradient.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/ui/visualisations/colorvisualisationchannel.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/ui/visualisations/sizevisualisationchannel.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/ui/visualisations/textvisualisationchannel.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/ui/visualisations/visualisationconfig.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/ui/visualisations/visualisationconfigparser.cpp 
)

list(APPEND RESOURCES
    ${CMAKE_CURRENT_LIST_DIR}/icon/mainicon.qrc
    ${CMAKE_CURRENT_LIST_DIR}/icon-themes/icons.qrc
    ${CMAKE_CURRENT_LIST_DIR}/auth/keys.qrc
    ${CMAKE_CURRENT_LIST_DIR}/rendering/shaders.qrc
    ${CMAKE_CURRENT_LIST_DIR}/ui/qml.qrc
    ${CMAKE_CURRENT_LIST_DIR}/ui/imagery.qrc
)

if(MSVC)
    list(APPEND RESOURCES ${CMAKE_CURRENT_LIST_DIR}/icon/Icon.rc)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

if(APPLE)
    set(MACOSX_FRAMEWORK_ICON_FILE ${CMAKE_CURRENT_LIST_DIR}/icon/Icon.icns)
    set(MACOSX_FRAMEWORK_IDENTIFIER com.kajeka.${PROJECT_NAME})
    add_executable(${PROJECT_NAME} MACOSX_BUNDLE ${SOURCES} ${HEADERS} ${RESOURCES})
else()
    add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${RESOURCES})
endif()

target_link_libraries(${PROJECT_NAME} thirdparty shared)

find_package(Qt5 COMPONENTS Core Qml Quick OpenGL OpenGLExtensions PrintSupport Widgets Xml REQUIRED)
target_link_libraries(${PROJECT_NAME}
    Qt5::Core
    Qt5::Qml
    Qt5::Quick
    Qt5::OpenGL
    Qt5::OpenGLExtensions
    Qt5::PrintSupport
    Qt5::Widgets
    Qt5::Xml
)

find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} ${OPENGL_gl_LIBRARY})

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} Threads::Threads)

if(APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework CoreFoundation")
endif()