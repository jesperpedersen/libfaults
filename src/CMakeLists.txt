#
# Add files for libfaults
#
FILE(GLOB SOURCE_FILES "libfaults/*.c")
FILE(GLOB HEADER_FILES "include/*.h")

set(SOURCES ${SOURCE_FILES} ${HEADER_FILES})

#
# Include directories
#
include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

#
# Library directories
#
link_libraries(
  ${CMAKE_DL_LIBS}
)

#
# Compile options
#
add_compile_options(-g)
add_compile_options(-Wall)
add_compile_options(-D_GNU_SOURCE)

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0 -fno-omit-frame-pointer -DDEBUG")

if (CMAKE_BUILD_TYPE MATCHES Release)
  add_compile_options(-O2)
endif (CMAKE_BUILD_TYPE MATCHES Release)

#
# Build libfaults
#
add_library(faults SHARED ${SOURCES})
set_target_properties(faults PROPERTIES LINKER_LANGUAGE C VERSION ${VERSION_STRING}
                               SOVERSION ${VERSION_MAJOR})
target_link_libraries(faults PUBLIC)

install(TARGETS faults DESTINATION ${CMAKE_INSTALL_LIBDIR}/)

#
# Install documentation
#
install(DIRECTORY ../doc/ DESTINATION share/doc/libfaults FILES_MATCHING PATTERN "*")
