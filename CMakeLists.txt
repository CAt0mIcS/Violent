cmake_minimum_required(VERSION 3.16)

project("Violent")

set(SRC
	"include/Violent/Violent.h"
	"include/Violent/VConfigure.h"
	"include/Violent/VLoglevel.h"
	"include/Violent/Loggers/VBaseLogger.h"
	"include/Violent/Loggers/VFileLogger.h"
	"include/Violent/Loggers/VConsoleLogger.h"
	"include/Violent/Utils/VSerialize.h"
	"include/Violent/Utils/VFormatDescriptor.h"
	"include/Violent/Utils/VTimes.h"
	"include/Violent/Utils/VColorFormatDescriptor.h"
	"src/CMakeStatic.cpp"
)

option(VIOLENT_BUILD_TESTS "Add Violent tests to CMake" ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library("Violent" STATIC "${SRC}")

# Preserves directory structure by creating Visual Studio filters for folders
foreach(source IN ITEMS ${SRC})
    get_filename_component(sourcePath "${source}" PATH)
    if(IS_ABSOLUTE source)
        file(RELATIVE_PATH relSourcePath "${_src_root_path}" "${sourcePath}")
    else()
        set(relSourcePath "${sourcePath}")
    endif()

    string(REPLACE "/" "\\" groupPath "${relSourcePath}")
    source_group("${groupPath}" FILES "${source}")
endforeach()

if(VIOLENT_BUILD_TESTS)
	add_subdirectory("tests")
endif()