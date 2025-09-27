find_package(HDF5 REQUIRED)
if(NOT HDF5_FOUND)
    message(FATAL_ERROR "HDF5 library is required but not found")
endif()

include_directories(${HDF5_INCLUDE_DIRS})

link_libraries(${HDF5_LIBRARIES})
