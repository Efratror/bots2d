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
    renderer/Renderer.h
    renderer/Camera.h
    renderer/Scalebar.h
    renderer/GLError.h
    renderer/AssetsHelper.h
    renderer/VertexBuffer.h
    renderer/IndexBuffer.h
    renderer/VertexArray.h
    renderer/Shader.h
    renderer/ImGuiOverlay.h
    renderer/Texture.h
    renderer/components/RectComponent.h
    renderer/components/QuadComponent.h
    renderer/SpriteAnimation.h
    renderer/ImGuiMenu.h
    physics/PhysicsWorld.h
    physics/ContactListener.h
    physics/components/Body2D.h
    physics/components/RangeSensor.h
    physics/components/LineDetector.h
    controllers/components/Microcontroller.h
    controllers/components/CMicrocontroller.h
    core/Application.h
    core/Event.h
    scene/SceneObject.h
    scene/Scene.h
    scene/SceneMenu.h
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

target_include_directories(bots2d PRIVATE core)
target_include_directories(bots2d PRIVATE renderer)
target_include_directories(bots2d PRIVATE transforms)
target_include_directories(bots2d PRIVATE physics)
target_include_directories(bots2d PRIVATE controllers)
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