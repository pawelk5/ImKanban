add_executable(${PROJECT_NAME}
    "src/main.cpp"
    "src/App/AppInit.cpp"
    "src/App/AppRun.cpp"
    "src/App/App.cpp"
    "src/Board/BoardView.cpp"
    "src/Board/ListPrompt/ListPrompt.cpp"
    "src/Board/CardPrompt/CardPrompt.cpp"
)

target_precompile_headers(${PROJECT_NAME} PRIVATE "src/pch.h")
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

target_include_directories(${PROJECT_NAME} PRIVATE
    "${CMAKE_CURRENT_LIST_DIR}/src" 
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

file(COPY "assets"
    DESTINATION "${EXECUTABLE_OUTPUT_PATH}")