set(SRC
	"main.cpp"
)

add_executable("DefaultTest" "${SRC}")
target_include_directories("DefaultTest" PRIVATE "${CMAKE_SOURCE_DIR}/include")