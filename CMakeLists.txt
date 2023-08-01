cmake_minimum_required (VERSION 3.8)
project ("Hydra")

# Setting some useful variables
set(HYDRA_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

# Globbing all the sources together into one HYDRA_SOURCES variable
file(GLOB HYDRA_SOURCES CONFIGURE_DEPENDS
	"${HYDRA_SOURCE_DIR}/*.cpp"
	"${HYDRA_SOURCE_DIR}/Core/*.cpp"
)

# Add Hydra sources to be compiled
add_executable (Hydra ${HYDRA_SOURCES})

