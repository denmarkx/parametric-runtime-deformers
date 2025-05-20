cmake_minimum_required(VERSION 3.12.0 FATAL_ERROR)
project(surface_deformers)

# Either Python or CXX build:
# Python will use interrogate, CXX will build everything from main.
option(COMPILE_PYTHON_LIB "Compile as a library using interrogate." OFF)

# CXX Lib:
option(COMPILE_CXX_LIB "Compile as a C++ library." OFF)

# Python:
if (COMPILE_PYTHON_LIB)
    find_package(Python COMPONENTS Interpreter Development REQUIRED)
endif()

# Panda3D:
set(PANDA "C:\\panda3d-engine" CACHE STRING "Panda3D Root Directory")
set(P3D_LIBS
    ${PANDA}/lib/libp3framework.lib
    ${PANDA}/lib/libpanda.lib
    ${PANDA}/lib/libpandafx.lib
    ${PANDA}/lib/libpandaexpress.lib
    ${PANDA}/lib/libp3dtool.lib
    ${PANDA}/lib/libp3dtoolconfig.lib
)

# Common sources from Interrogate Lib and full C++ program.
set(SOURCES
    deformers/config_deformer.cxx
    deformers/config_deformer.h
    deformers/deformer.cxx
    deformers/deformer.h
    deformers/deformer.I
    deformers/bendDeformer.cxx
    deformers/bendDeformer.h
    deformers/sineDeformer.cxx
    deformers/sineDeformer.h
    deformers/twistDeformer.cxx
    deformers/twistDeformer.h
    deformers/expandDeformer.cxx
    deformers/expandDeformer.h
)

if (NOT COMPILE_PYTHON_LIB AND NOT COMPILE_CXX_LIB)
    # IMGui Files:
    set (IMGUI_FILES
        imgui/imconfig.h
        imgui/imgui.cpp
        imgui/imgui.h
        imgui/imgui_demo.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_internal.h
        imgui/imgui_tables.cpp
        imgui/imgui_widgets.cpp
        imgui/imstb_rectpack.h
        imgui/imstb_textedit.h
        imgui/imstb_truetype.h
        imgui/panda3d_imgui.cpp
        imgui/panda3d_imgui.hpp
        imgui/panda3d_imgui_main.cxx
    )
endif()


include_directories(deformers)
include_directories(${PANDA}/include)
include_directories(${PANDA}/lib)

if (COMPILE_PYTHON_LIB)
    include_directories(${Python_INCLUDE_DIRS})
elseif(COMPILE_CXX_LIB)
    include_directories(imgui)
endif()

if(MSVC)
    add_definitions(/DYY_NO_UNISTD_H)
endif()



if (COMPILE_PYTHON_LIB)
    add_library(surface_deformers SHARED ${SOURCES})

    # Interrogate:
    execute_process(
        COMMAND interrogate
            -D__inline
            -DCPPPARSER
            -DINTERROGATE
            -DP3_INTERROGATE=1
            -D__STDC__=1
            -D__cplusplus
            -D_X86
            -DWIN32_VC
            -D_WIN32
            -DWIN32
            -DWIN64_VC
            -DWIN64
            -D_WIN64
            -fnames
            -string
            -refcount
            -assert
            -python-native
            -S${PANDA}/include/parser-inc
            -S${PANDA}/include
            -I${PANDA}/include
            -Ideformers/
            -srcdir .
            -oc surface_deformers_igate.cxx
            -od surface_deformers.in
            -module surface_deformers
            -library surface_deformers
            -nomangle
            -D"__declspec(param)="
            -D__cdecl
            -D_near
            -D_far
            -D__near
            -D__far
            -D__stdcall
            ${SOURCES}
    )

    # Interrogate Module:
    execute_process(
        COMMAND interrogate_module
            -python-native
            -oc surface_deformers_module.cxx
            -library surface_deformers
            -module surface_deformers
            surface_deformers.in
    )

    # Set module and igate file after we run interrogate:
    set (INTERROGATE_FILES 
        surface_deformers_igate.cxx
        surface_deformers_module.cxx
    )

    target_sources(surface_deformers PUBLIC ${INTERROGATE_FILES})
    set_target_properties(surface_deformers PROPERTIES SUFFIX ".pyd")
    target_link_libraries(surface_deformers ${P3D_LIBS} ${Python_LIBRARIES})
elseif(COMPILE_CXX_LIB)
    add_library(surface_deformers SHARED ${SOURCES})
    target_link_libraries(surface_deformers ${P3D_LIBS})
else()
    # C++ Program
    add_executable(surface_deformers main.cxx ${SOURCES} ${IMGUI_FILES})
    target_link_libraries(surface_deformers ${P3D_LIBS})
endif()
