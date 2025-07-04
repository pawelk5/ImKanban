FetchContent_Declare(
    imgui
    URL "https://github.com/ocornut/imgui/archive/v1.91.9b.zip"
)
FetchContent_MakeAvailable(imgui)
FetchContent_GetProperties(imgui SOURCE_DIR IMGUI_DIR)

FetchContent_Declare(
    imgui-sfml
    GIT_REPOSITORY "https://github.com/SFML/imgui-sfml.git"
    GIT_TAG     v3.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM
)
set(IMGUI_SFML_FIND_SFML OFF)
FetchContent_MakeAvailable(imgui-sfml)