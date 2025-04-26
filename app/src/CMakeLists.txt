add_executable(${PROJECT_NAME}
    "main.cpp"
    "App/AppInit.cpp"
    "App/AppRun.cpp"
    "App/App.cpp"
)

target_precompile_headers(${PROJECT_NAME} PRIVATE "pch.h")
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR} 
    ${LIBRARY_INCLUDE_PATH}
    ${SFML_INCLUDE_DIR} ${IMGUI_DIR} ${OPENGL_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME} PRIVATE 
    ${DYNAMIC_LIBRARY}
    ImGui-SFML::ImGui-SFML
    sfml-system sfml-window sfml-graphics
)

target_compile_definitions(${PROJECT_NAME} PRIVATE 
    PROJECT_NAME="${PROJECT_NAME}"
)
