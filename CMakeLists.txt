# This CMake script is mainly designed for CLion IDE and QTCreator projects on Windows
# It should find bundled binary dependencies automatically when using MinGW
# On Linux and Mac the dependencies (glm, glew, glfw) need to be installed manually

cmake_minimum_required ( VERSION 3.1 )
project( Pokemon3D CXX )

#
# CONFIGURATION
#

# Basic CMake settings
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/_install)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Warnings for Debug mode
option(USE_STRICT_COMPILE_WARNINGS "Use strict compilation warnings in debug mode." ON)
if (USE_STRICT_COMPILE_WARNINGS)
    # Assuming Clang and GCC
    set(STRICT_COMPILE_WARNINGS "-Wpedantic -Wall -Wfloat-equal -Wextra -Wsign-promo -Wsign-compare -Wconversion -Wno-sign-conversion -Wno-unused-parameter")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${STRICT_COMPILE_WARNINGS}")
endif ()

# Make sure GLM uses radians
add_definitions ( -DGLM_FORCE_RADIANS )

# Add custom target for installation in CLion
add_custom_target(run_install COMMAND ${CMAKE_MAKE_PROGRAM} install)

# Use generate_shader function to vonvert .glsl sources to C++ headers
include(shaders)

#
# DEPENDENCIES
#

# Set up external dependencies for Wwindows users
if ( MINGW )
    set ( CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "${CMAKE_SOURCE_DIR}/dependencies/mingw/include/" )
    set ( CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${CMAKE_SOURCE_DIR}/dependencies/mingw/lib/" )
endif ()

# Find dependencies
find_package ( GLFW3 REQUIRED )
find_package ( GLEW REQUIRED )
find_package ( GLM REQUIRED )
find_package ( OpenGL REQUIRED )

# Set default installation destination
if (NOT CMAKE_INSTALL_PREFIX)
    set(CMAKE_INSTALL_PREFIX "../_install")
endif ()

file(GLOB pokemon_main "src/*.cpp")
file(GLOB pokemon_camera "src/camera/*.cpp")
file(GLOB pokemon_loaders "src/loaders/*.cpp")
file(GLOB pokemon_objects "src/objects/*.cpp")
file(GLOB pokemon_shaders "src/shaders/*.cpp")
file(GLOB pokemon_engine "src/engine/*.cpp")
file(GLOB pokemon_textures "src/textures/*.cpp")
file(GLOB pokemon_models "src/models/*.cpp")
file(GLOB pokemon_wrappers "src/wrappers/*.cpp")
file(GLOB pokemon_extensions "src/extensions/*.cpp")
file(GLOB pokemon_managers "src/managers/*.cpp")
file(GLOB pokemon_gui "src/gui/*.cpp")
file(GLOB pokemon_shaders_programs "src/shaders/*.glsl")

# Include header directories
include_directories (
        src/
        ${GLFW_INCLUDE_DIRS}
        ${GLEW_INCLUDE_DIRS}
        ${GLM_INCLUDE_DIRS}
        ${OPENGL_INCLUDE_DIRS}
        ${CMAKE_SOURCE_DIR}
        ${CMAKE_CURRENT_BINARY_DIR} )

# Prepare libraries for linking
set ( LIBRARIES
        ${OPENGL_LIBRARIES}
        ${GLFW_LIBRARIES}
        ${GLEW_LIBRARIES}
        libpokemon3d)

# Pokemon3D library
add_library(libpokemon3d STATIC
        ${pokemon_camera}
        ${pokemon_loaders}
        ${pokemon_objects}
        ${pokemon_shaders}
        ${pokemon_engine}
        ${pokemon_textures}
        ${pokemon_models}
        ${pokemon_wrappers}
        ${pokemon_extensions}
        ${pokemon_managers}
        ${pokemon_gui})

target_link_libraries(libpokemon3d ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${GLFW_LIBRARIES})


#
# TARGETS
#

# gl_pokemon
set ( POKEMON3D_SRC
        src/gl_pokemon.cpp
        ${pokemon_camera}
        ${pokemon_loaders}
        ${pokemon_objects}
        ${pokemon_shaders}
        ${pokemon_engine}
        ${pokemon_textures}
        ${pokemon_models}
        ${pokemon_wrappers}
        ${pokemon_extensions}
        ${pokemon_managers}
        ${pokemon_gui} )
generate_shaders( POKEMON3D_SHADERS
        src/shaders/frag_ground.glsl
        src/shaders/vert_ground.glsl
        src/shaders/frag_pokemon.glsl
        src/shaders/vert_pokemon.glsl
        src/shaders/frag_texture.glsl
        src/shaders/vert_texture.glsl
        src/shaders/vert_gui.glsl
        src/shaders/frag_gui.glsl)

add_executable ( Pokemon3D ${POKEMON3D_SRC} ${POKEMON3D_SHADERS})

target_link_libraries( Pokemon3D ${LIBRARIES} )

install ( TARGETS Pokemon3D DESTINATION . )
#install ( FILES shaders/gl_pokemon.vert shaders/gl_pokemon.frag models/objects/Pokecenter.obj models/objects/Trainer.rgb cursor.obj DESTINATION . )

# ADD YOUR PROJECT HERE
#add_executable( my_project my_project.cpp my_project_other.cpp )
#target_link_libraries( my_project ${LIBRARIES} )

#install ( TARGETS my_project DESTINATION . )
#install ( FILES my_project.file my_project.vert my_project.frag DESTINATION . )

#
# INSTALLATION
#

install(DIRECTORY models DESTINATION .)

# Install dlls to destination when on Windows
if ( MINGW )
    install ( FILES ${GLFW_LIBRARIES} ${GLEW_LIBRARIES} DESTINATION . )
    # Install dlls into binary dir for development and debugging
    file ( COPY ${GLFW_LIBRARIES} ${GLEW_LIBRARIES} DESTINATION ${CMAKE_BINARY_DIR} )
endif ()
