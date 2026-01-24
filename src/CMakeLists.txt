set (BOTS2D_SOURCE_FILES
    renderer/Renderer.cpp
    renderer/Camera.cpp
    renderer/Scalebar.cpp
    renderer/GLError.cpp
    renderer/AssetsHelper.cpp
    renderer/VertexBuffer.cpp
    renderer/IndexBuffer.cpp
    renderer/VertexArray.cpp
    renderer/Shader.cpp
    renderer/ImGuiOverlay.cpp
    renderer/Texture.cpp
    renderer/components/RectComponent.cpp
    renderer/components/QuadComponent.cpp
    renderer/SpriteAnimation.cpp
    renderer/stb_image.cpp
    renderer/ImGuiMenu.cpp
    physics/PhysicsWorld.cpp
    physics/ContactListener.cpp
    physics/components/Body2D.cpp
    physics/components/RangeSensor.cpp
    physics/components/LineDetector.cpp
    controllers/components/Microcontroller.cpp
    controllers/components/CMicrocontroller.cpp
    controllers/components/microcontroller_c_bindings.c
    core/Application.cpp
    core/Event.cpp
    scene/SceneObject.cpp
    scene/Scene.cpp
    scene/SceneMenu.cpp
    ${EXTERNAL_SOURCE_FILES}
)

set(BOTS2D_HEADER_FILES
    ../include/bots2d/renderer/Renderer.h
    ../include/bots2d/renderer/Camera.h
    ../include/bots2d/renderer/Scalebar.h
    ../include/bots2d/renderer/GLError.h
    ../include/bots2d/renderer/AssetsHelper.h
    ../include/bots2d/renderer/VertexBuffer.h
    ../include/bots2d/renderer/IndexBuffer.h
    ../include/bots2d/renderer/VertexArray.h
    ../include/bots2d/renderer/Shader.h
    ../include/bots2d/renderer/ImGuiOverlay.h
    ../include/bots2d/renderer/Texture.h
    ../include/bots2d/renderer/components/RectComponent.h
    ../include/bots2d/renderer/components/QuadComponent.h
    ../include/bots2d/renderer/SpriteAnimation.h
    ../include/bots2d/renderer/ImGuiMenu.h
    ../include/bots2d/physics/PhysicsWorld.h
    ../include/bots2d/physics/ContactListener.h
    ../include/bots2d/physics/components/Body2D.h
    ../include/bots2d/physics/components/RangeSensor.h
    ../include/bots2d/physics/components/LineDetector.h
    ../include/bots2d/controllers/Microcontroller.h
    ../include/bots2d/controllers/CMicrocontroller.h
    ../include/bots2d/core/Application.h
    ../include/bots2d/core/Event.h
    ../include/bots2d/scene/SceneObject.h
    ../include/bots2d/scene/Scene.h
    ../include/bots2d/scene/SceneMenu.h
)

set(EXTERNAL_SOURCE_FILES
    ../external/glfw/deps/glad_gl.c
    ../external/imgui/imgui.cpp
    ../external/imgui/imgui_draw.cpp
    ../external/imgui/imgui_widgets.cpp
    ../external/imgui/backends/imgui_impl_opengl3.cpp
    ../external/imgui/backends/imgui_impl_glfw.cpp
)

add_library(bots2d STATIC
    ${BOTS2D_SOURCE_FILES}
    ${BOTS2D_HEADER_FILES}
    ${EXTERNAL_SOURCE_FILES}
)

target_include_directories(bots2d PRIVATE transforms)
target_include_directories(bots2d PRIVATE scene)
target_include_directories(bots2d PRIVATE ../external/glfw/deps)
target_include_directories(bots2d PRIVATE ../external/stb)
target_include_directories(bots2d PRIVATE ../external/glm)
target_include_directories(bots2d PRIVATE ../external/imgui)

target_include_directories(bots2d
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/bots2d
)

# Build box2d and glfw  as static libraries
add_subdirectory(../external/glfw glfw_build)
add_subdirectory(../external/box2D/src box2d_build)

# Link box2d and glfw to bots2d
target_link_libraries(bots2d PRIVATE box2d glfw)

# Make Dear ImGui use GLAD2
add_definitions( -DIMGUI_IMPL_OPENGL_LOADER_GLAD2 )

set_target_properties(bots2d PROPERTIES
	CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

# Make Dear ImGui use GLAD2
add_definitions( -DIMGUI_IMPL_OPENGL_LOADER_GLAD2 )

set_target_properties(bots2d PROPERTIES
	CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

if(MSVC)
  target_compile_options(bots2d PRIVATE /W4 /WX)
else()
  target_compile_options(bots2d PRIVATE -Wall -Wextra -pedantic -Werror)
  # Ignore compile flags to keep the external repo intact
  set_source_files_properties(renderer/stb_image.cpp PROPERTIES COMPILE_FLAGS "-Wno-sign-compare -Wno-unused-but-set-variable")
endif()