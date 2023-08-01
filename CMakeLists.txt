cmake_minimum_required (VERSION 3.8)
project ("Hydra")

# Setting some useful variables
set(HYDRA_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(HYDRA_VENDOR_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vendor")


# Globbing all the sources together into one HYDRA_SOURCES variable
file(GLOB HYDRA_SOURCES CONFIGURE_DEPENDS
	"${HYDRA_SOURCE_DIR}/*.cpp"
	"${HYDRA_SOURCE_DIR}/Core/*.cpp"
)

# Add Hydra sources to be compiled
add_executable (Hydra ${HYDRA_SOURCES})

# ----------------- SETTING UP THIRD PARTY LIBRARIES ------------------------
# GLFW
set(GLFW_DIR "${HYDRA_VENDOR_DIR}/glfw")
add_subdirectory("${GLFW_DIR}")
target_link_libraries(Hydra PRIVATE glfw)
target_include_directories(Hydra PUBLIC "${GLFW_DIR}/include")

# ---------------------------------------------------------------------------