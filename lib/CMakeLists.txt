# local
set(DYNAMIC_LIBRARY "${PROJECT_NAME}-lib")
set(LIBRARY_INCLUDE_PATH "${CMAKE_CURRENT_LIST_DIR}/include")

# export
set(DYNAMIC_LIBRARY ${DYNAMIC_LIBRARY} PARENT_SCOPE)
set(LIBRARY_INCLUDE_PATH "${LIBRARY_INCLUDE_PATH}" PARENT_SCOPE)


add_library(${DYNAMIC_LIBRARY} SHARED
    "src/Test.cpp"
)

target_compile_features(${DYNAMIC_LIBRARY} PRIVATE cxx_std_20)
target_include_directories(${DYNAMIC_LIBRARY} PRIVATE 
    ${LIBRARY_INCLUDE_PATH}
)

# set up tests
include("test.cmake")
