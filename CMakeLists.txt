cmake_minimum_required (VERSION 3.8)
project ("Hydra")

# Setting some useful variables
set(HYDRA_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(HYDRA_VENDOR_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vendor")
set(HYDRA_VENDOR_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/vendor-builds")


# Globbing all the sources together into one HYDRA_SOURCES variable
file(GLOB HYDRA_SOURCES CONFIGURE_DEPENDS
	"${HYDRA_SOURCE_DIR}/*.cpp"
	"${HYDRA_SOURCE_DIR}/Core/*.cpp"
)

# Add Hydra sources to be compiled
add_executable (Hydra ${HYDRA_SOURCES})

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

# ---------------------------------------------------------------------------