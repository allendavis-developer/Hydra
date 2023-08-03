cmake_minimum_required (VERSION 3.8)
project ("Hydra")
set(CMAKE_CXX_STANDARD 17)

# Setting some useful variables
set(HYDRA_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(HYDRA_VENDOR_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vendor")
set(HYDRA_VENDOR_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/vendor-builds")


# Globbing all the sources together into one HYDRA_SOURCES variable
file(GLOB HYDRA_SOURCES CONFIGURE_DEPENDS
	"${HYDRA_SOURCE_DIR}/*.cpp"
	"${HYDRA_SOURCE_DIR}/Core/*.cpp"
	"${HYDRA_SOURCE_DIR}/Renderer/*.cpp"
	"${HYDRA_SOURCE_DIR}/Renderer/Shaders/*.cpp"
)



# Add Hydra sources to be compiled
add_executable (Hydra ${HYDRA_SOURCES})

# Making sure Hydra is built in a seperate folder
set_target_properties(Hydra 
	PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/Hydra"
	VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
)

# Setting include directories for Hydra from Hydra
target_include_directories(Hydra PUBLIC "${HYDRA_SOURCE_DIR}")

# ----------------- SETTING UP THIRD PARTY LIBRARIES ------------------------

# glfw
set(GLFW_DIR "${HYDRA_VENDOR_DIR}/glfw")
add_subdirectory("${GLFW_DIR}" "${HYDRA_VENDOR_BUILD_DIR}/glfw")

target_link_libraries(Hydra PRIVATE glfw)
target_include_directories(Hydra PUBLIC "${GLFW_DIR}/include")

# spdlog
set(SPDLOG_DIR "${HYDRA_VENDOR_DIR}/spdlog")
add_subdirectory("${SPDLOG_DIR}" "${HYDRA_VENDOR_BUILD_DIR}/spdlog")

target_link_libraries(Hydra PRIVATE spdlog)
target_include_directories(Hydra PUBLIC "${SPDLOG_DIR}/include")

# glad
set(GLAD_DIR "${HYDRA_VENDOR_DIR}/glad")
add_library(glad "${GLAD_DIR}/src/glad.c")
# Making sure glad is built into vendor-builds
set_target_properties(glad PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/vendor-builds/glad"
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/vendor-builds/glad"
	LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/vendor-builds/glad")
target_include_directories(glad PUBLIC "${GLAD_DIR}/include")

target_link_libraries(Hydra PRIVATE glad)
target_include_directories(Hydra PUBLIC "${GLAD_DIR}/include")

# stb_image
set(STB_IMAGE_DIR "${HYDRA_VENDOR_DIR}/stb_image")
add_library(stb_image "${STB_IMAGE_DIR}/stb_image_implementation.cpp")
# Making sure stb_image is built into vendor-builds
set_target_properties(stb_image PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/vendor-builds/stb_image"
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/vendor-builds/stb_image"
	LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/vendor-builds/stb_image")
target_include_directories(stb_image PUBLIC "${STB_IMAGE_DIR}")

target_link_libraries(Hydra PRIVATE stb_image)
target_include_directories(Hydra PUBLIC "${HYDRA_VENDOR_DIR}/stb_image")


# ---------------------------------------------------------------------------
