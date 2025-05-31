# local
set(DYNAMIC_LIBRARY "${PROJECT_NAME}-lib")
set(LIBRARY_INCLUDE_PATH "${CMAKE_CURRENT_LIST_DIR}/include")

# export
set(DYNAMIC_LIBRARY ${DYNAMIC_LIBRARY} PARENT_SCOPE)
set(LIBRARY_INCLUDE_PATH "${LIBRARY_INCLUDE_PATH}" PARENT_SCOPE)


add_library(${DYNAMIC_LIBRARY} SHARED
    "src/BoardList.cpp"    
    "src/Board.cpp"
    "src/Card.cpp"
    "src/List.cpp"
)

target_compile_features(${DYNAMIC_LIBRARY} PRIVATE cxx_std_20)
target_compile_definitions(${DYNAMIC_LIBRARY} PRIVATE _BUILD)
target_include_directories(${DYNAMIC_LIBRARY} PRIVATE 
    ${LIBRARY_INCLUDE_PATH}
)

target_link_libraries(${DYNAMIC_LIBRARY} PRIVATE 
    nlohmann_json::nlohmann_json
)

# set up tests
add_subdirectory("test")
