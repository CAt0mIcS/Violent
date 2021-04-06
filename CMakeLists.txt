cmake_minimum_required(VERSION 3.16)

project("Violent")

set(SRC
	"include/Violent/VLoglevel.h"
	"include/Violent/Violent.h"
	"include/Violent/Loggers/VBaseLogger.h"
	"include/Violent/Loggers/VFileLogger.h"
	"include/Violent/Loggers/VConsoleLogger.h"
	"include/Violent/Formatters/VBracketFormatter.h"
	"include/Violent/Formatters/VDateTimeFormatter.h"
	"include/Violent/Formatters/VFormatter.h"
	"include/Violent/Formatters/VLogLevelFormatter.h"
	"include/Violent/Formatters/VNullTerminatorFormatter.h"

	"include/Violent/Utils/VUtils.h"
	"include/Violent/Utils/VSerialize.h"
)

option(VIOLENT_BUILD_TESTS "Add Violent tests to CMake" ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library("Violent" INTERFACE "${SRC}")

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