find_package(HDF5 REQUIRED)

include_directories(${HDF5_INCLUDE_DIRS})

link_libraries(${HDF5_LIBRARIES})
