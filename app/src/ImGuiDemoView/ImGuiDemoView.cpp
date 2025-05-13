#include "pch.h"
#include "ImGuiDemoView.hpp"
#include "imgui_demo.cpp"


ImGuiDemoView::ImGuiDemoView() 
    :m_goToMainView(false)
{
    ;
}

/// NOTE: copied from imgui_demo.cpp
void ImGuiDemoView::DrawContent(sf::RenderTarget& target) {
    // Exceptionally add an extra assert here for people confused about initial Dear ImGui setup
    // Most functions would normally just assert/crash if the context is missing.
    IM_ASSERT(ImGui::GetCurrentContext() != NULL && "Missing Dear ImGui context. Refer to examples app!");

    // Verify ABI compatibility between caller code and compiled version of Dear ImGui. This helps detects some build issues.
    IMGUI_CHECKVERSION();

    // Stored data
    static ImGuiDemoWindowData demo_data;

    // Examples Apps (accessible from the "Examples" menu)
    if (demo_data.ShowMainMenuBar)          { ShowExampleAppMainMenuBar(); }
    if (demo_data.ShowAppDocuments)         { ShowExampleAppDocuments(&demo_data.ShowAppDocuments); }
    if (demo_data.ShowAppAssetsBrowser)     { ShowExampleAppAssetsBrowser(&demo_data.ShowAppAssetsBrowser); }
    if (demo_data.ShowAppConsole)           { ShowExampleAppConsole(&demo_data.ShowAppConsole); }
    if (demo_data.ShowAppCustomRendering)   { ShowExampleAppCustomRendering(&demo_data.ShowAppCustomRendering); }
    if (demo_data.ShowAppLog)               { ShowExampleAppLog(&demo_data.ShowAppLog); }
    if (demo_data.ShowAppLayout)            { ShowExampleAppLayout(&demo_data.ShowAppLayout); }
    if (demo_data.ShowAppPropertyEditor)    { ShowExampleAppPropertyEditor(&demo_data.ShowAppPropertyEditor, &demo_data); }
    if (demo_data.ShowAppSimpleOverlay)     { ShowExampleAppSimpleOverlay(&demo_data.ShowAppSimpleOverlay); }
    if (demo_data.ShowAppAutoResize)        { ShowExampleAppAutoResize(&demo_data.ShowAppAutoResize); }
    if (demo_data.ShowAppConstrainedResize) { ShowExampleAppConstrainedResize(&demo_data.ShowAppConstrainedResize); }
    if (demo_data.ShowAppFullscreen)        { ShowExampleAppFullscreen(&demo_data.ShowAppFullscreen); }
    if (demo_data.ShowAppLongText)          { ShowExampleAppLongText(&demo_data.ShowAppLongText); }
    if (demo_data.ShowAppWindowTitles)      { ShowExampleAppWindowTitles(&demo_data.ShowAppWindowTitles); }

    // Dear ImGui Tools (accessible from the "Tools" menu)
    if (demo_data.ShowMetrics)              { ImGui::ShowMetricsWindow(&demo_data.ShowMetrics); }
    if (demo_data.ShowDebugLog)             { ImGui::ShowDebugLogWindow(&demo_data.ShowDebugLog); }
    if (demo_data.ShowIDStackTool)          { ImGui::ShowIDStackToolWindow(&demo_data.ShowIDStackTool); }
    if (demo_data.ShowAbout)                { ImGui::ShowAboutWindow(&demo_data.ShowAbout); }
    if (demo_data.ShowStyleEditor)
    {
        ImGui::Begin("Dear ImGui Style Editor", &demo_data.ShowStyleEditor);
        ImGui::ShowStyleEditor();
        ImGui::End();
    }

    // Demonstrate the various window flags. Typically you would just use the default!
    static bool no_titlebar = false;
    static bool no_scrollbar = false;
    static bool no_menu = false;
    static bool no_move = false;
    static bool no_resize = false;
    static bool no_collapse = false;
    static bool no_close = false;
    static bool no_nav = false;
    static bool no_background = false;
    static bool no_bring_to_front = false;
    static bool unsaved_document = false;

    ImGuiWindowFlags window_flags = 0;
    if (no_titlebar)        window_flags |= ImGuiWindowFlags_NoTitleBar;
    if (no_scrollbar)       window_flags |= ImGuiWindowFlags_NoScrollbar;
    if (!no_menu)           window_flags |= ImGuiWindowFlags_MenuBar;
    if (no_move)            window_flags |= ImGuiWindowFlags_NoMove;
    if (no_resize)          window_flags |= ImGuiWindowFlags_NoResize;
    if (no_collapse)        window_flags |= ImGuiWindowFlags_NoCollapse;
    if (no_nav)             window_flags |= ImGuiWindowFlags_NoNav;
    if (no_background)      window_flags |= ImGuiWindowFlags_NoBackground;
    if (no_bring_to_front)  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
    if (unsaved_document)   window_flags |= ImGuiWindowFlags_UnsavedDocument;

    // We specify a default position/size in case there's no data in the .ini file.
    // We only do it to make the demo applications a little more welcoming, but typically this isn't required.
    const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + 650, main_viewport->WorkPos.y + 20), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(550, 680), ImGuiCond_FirstUseEver);

    // Most "big" widgets share a common width settings by default. See 'Demo->Layout->Widgets Width' for details.
    ImGui::PushItemWidth(ImGui::GetFontSize() * -12);           // e.g. Leave a fixed amount of width for labels (by passing a negative value), the rest goes to widgets.
    //ImGui::PushItemWidth(-ImGui::GetWindowWidth() * 0.35f);   // e.g. Use 2/3 of the space for widgets and 1/3 for labels (right align)

    // Menu Bar
    DemoWindowMenuBar(&demo_data);

    ImGui::Text("dear imgui says hello! (%s) (%d)", IMGUI_VERSION, IMGUI_VERSION_NUM);
    ImGui::Spacing();

    IMGUI_DEMO_MARKER("Help");
    if (ImGui::CollapsingHeader("Help"))
    {
        ImGui::SeparatorText("ABOUT THIS DEMO:");
        ImGui::BulletText("Sections below are demonstrating many aspects of the library.");
        ImGui::BulletText("The \"Examples\" menu above leads to more demo contents.");
        ImGui::BulletText("The \"Tools\" menu above gives access to: About Box, Style Editor,\n"
                          "and Metrics/Debugger (general purpose Dear ImGui debugging tool).");

        ImGui::SeparatorText("PROGRAMMER GUIDE:");
        ImGui::BulletText("See the ShowDemoWindow() code in imgui_demo.cpp. <- you are here!");
        ImGui::BulletText("See comments in imgui.cpp.");
        ImGui::BulletText("See example applications in the examples/ folder.");
        ImGui::BulletText("Read the FAQ at ");
        ImGui::SameLine(0, 0);
        ImGui::TextLinkOpenURL("https://www.dearimgui.com/faq/");
        ImGui::BulletText("Set 'io.ConfigFlags |= NavEnableKeyboard' for keyboard controls.");
        ImGui::BulletText("Set 'io.ConfigFlags |= NavEnableGamepad' for gamepad controls.");

        ImGui::SeparatorText("USER GUIDE:");
        ImGui::ShowUserGuide();
    }

    IMGUI_DEMO_MARKER("Configuration");
    if (ImGui::CollapsingHeader("Configuration"))
    {
        ImGuiIO& io = ImGui::GetIO();

        if (ImGui::TreeNode("Configuration##2"))
        {
            ImGui::SeparatorText("General");
            ImGui::CheckboxFlags("io.ConfigFlags: NavEnableKeyboard",    &io.ConfigFlags, ImGuiConfigFlags_NavEnableKeyboard);
            ImGui::SameLine(); HelpMarker("Enable keyboard controls.");
            ImGui::CheckboxFlags("io.ConfigFlags: NavEnableGamepad",     &io.ConfigFlags, ImGuiConfigFlags_NavEnableGamepad);
            ImGui::SameLine(); HelpMarker("Enable gamepad controls. Require backend to set io.BackendFlags |= ImGuiBackendFlags_HasGamepad.\n\nRead instructions in imgui.cpp for details.");
            ImGui::CheckboxFlags("io.ConfigFlags: NoMouse",              &io.ConfigFlags, ImGuiConfigFlags_NoMouse);
            ImGui::SameLine(); HelpMarker("Instruct dear imgui to disable mouse inputs and interactions.");

            // The "NoMouse" option can get us stuck with a disabled mouse! Let's provide an alternative way to fix it:
            if (io.ConfigFlags & ImGuiConfigFlags_NoMouse)
            {
                if (fmodf((float)ImGui::GetTime(), 0.40f) < 0.20f)
                {
                    ImGui::SameLine();
                    ImGui::Text("<<PRESS SPACE TO DISABLE>>");
                }
                // Prevent both being checked
                if (ImGui::IsKeyPressed(ImGuiKey_Space) || (io.ConfigFlags & ImGuiConfigFlags_NoKeyboard))
                    io.ConfigFlags &= ~ImGuiConfigFlags_NoMouse;
            }

            ImGui::CheckboxFlags("io.ConfigFlags: NoMouseCursorChange",  &io.ConfigFlags, ImGuiConfigFlags_NoMouseCursorChange);
            ImGui::SameLine(); HelpMarker("Instruct backend to not alter mouse cursor shape and visibility.");
            ImGui::CheckboxFlags("io.ConfigFlags: NoKeyboard", &io.ConfigFlags, ImGuiConfigFlags_NoKeyboard);
            ImGui::SameLine(); HelpMarker("Instruct dear imgui to disable keyboard inputs and interactions.");

            ImGui::Checkbox("io.ConfigInputTrickleEventQueue", &io.ConfigInputTrickleEventQueue);
            ImGui::SameLine(); HelpMarker("Enable input queue trickling: some types of events submitted during the same frame (e.g. button down + up) will be spread over multiple frames, improving interactions with low framerates.");
            ImGui::Checkbox("io.MouseDrawCursor", &io.MouseDrawCursor);
            ImGui::SameLine(); HelpMarker("Instruct Dear ImGui to render a mouse cursor itself. Note that a mouse cursor rendered via your application GPU rendering path will feel more laggy than hardware cursor, but will be more in sync with your other visuals.\n\nSome desktop applications may use both kinds of cursors (e.g. enable software cursor only when resizing/dragging something).");

            ImGui::SeparatorText("Keyboard/Gamepad Navigation");
            ImGui::Checkbox("io.ConfigNavSwapGamepadButtons", &io.ConfigNavSwapGamepadButtons);
            ImGui::Checkbox("io.ConfigNavMoveSetMousePos", &io.ConfigNavMoveSetMousePos);
            ImGui::SameLine(); HelpMarker("Directional/tabbing navigation teleports the mouse cursor. May be useful on TV/console systems where moving a virtual mouse is difficult");
            ImGui::Checkbox("io.ConfigNavCaptureKeyboard", &io.ConfigNavCaptureKeyboard);
            ImGui::Checkbox("io.ConfigNavEscapeClearFocusItem", &io.ConfigNavEscapeClearFocusItem);
            ImGui::SameLine(); HelpMarker("Pressing Escape clears focused item.");
            ImGui::Checkbox("io.ConfigNavEscapeClearFocusWindow", &io.ConfigNavEscapeClearFocusWindow);
            ImGui::SameLine(); HelpMarker("Pressing Escape clears focused window.");
            ImGui::Checkbox("io.ConfigNavCursorVisibleAuto", &io.ConfigNavCursorVisibleAuto);
            ImGui::SameLine(); HelpMarker("Using directional navigation key makes the cursor visible. Mouse click hides the cursor.");
            ImGui::Checkbox("io.ConfigNavCursorVisibleAlways", &io.ConfigNavCursorVisibleAlways);
            ImGui::SameLine(); HelpMarker("Navigation cursor is always visible.");

            ImGui::SeparatorText("Windows");
            ImGui::Checkbox("io.ConfigWindowsResizeFromEdges", &io.ConfigWindowsResizeFromEdges);
            ImGui::SameLine(); HelpMarker("Enable resizing of windows from their edges and from the lower-left corner.\nThis requires ImGuiBackendFlags_HasMouseCursors for better mouse cursor feedback.");
            ImGui::Checkbox("io.ConfigWindowsMoveFromTitleBarOnly", &io.ConfigWindowsMoveFromTitleBarOnly);
            ImGui::Checkbox("io.ConfigWindowsCopyContentsWithCtrlC", &io.ConfigWindowsCopyContentsWithCtrlC); // [EXPERIMENTAL]
            ImGui::SameLine(); HelpMarker("*EXPERIMENTAL* CTRL+C copy the contents of focused window into the clipboard.\n\nExperimental because:\n- (1) has known issues with nested Begin/End pairs.\n- (2) text output quality varies.\n- (3) text output is in submission order rather than spatial order.");
            ImGui::Checkbox("io.ConfigScrollbarScrollByPage", &io.ConfigScrollbarScrollByPage);
            ImGui::SameLine(); HelpMarker("Enable scrolling page by page when clicking outside the scrollbar grab.\nWhen disabled, always scroll to clicked location.\nWhen enabled, Shift+Click scrolls to clicked location.");

            ImGui::SeparatorText("Widgets");
            ImGui::Checkbox("io.ConfigInputTextCursorBlink", &io.ConfigInputTextCursorBlink);
            ImGui::SameLine(); HelpMarker("Enable blinking cursor (optional as some users consider it to be distracting).");
            ImGui::Checkbox("io.ConfigInputTextEnterKeepActive", &io.ConfigInputTextEnterKeepActive);
            ImGui::SameLine(); HelpMarker("Pressing Enter will keep item active and select contents (single-line only).");
            ImGui::Checkbox("io.ConfigDragClickToInputText", &io.ConfigDragClickToInputText);
            ImGui::SameLine(); HelpMarker("Enable turning DragXXX widgets into text input with a simple mouse click-release (without moving).");
            ImGui::Checkbox("io.ConfigMacOSXBehaviors", &io.ConfigMacOSXBehaviors);
            ImGui::SameLine(); HelpMarker("Swap Cmd<>Ctrl keys, enable various MacOS style behaviors.");
            ImGui::Text("Also see Style->Rendering for rendering options.");

            // Also read: https://github.com/ocornut/imgui/wiki/Error-Handling
            ImGui::SeparatorText("Error Handling");

            ImGui::Checkbox("io.ConfigErrorRecovery", &io.ConfigErrorRecovery);
            ImGui::SameLine(); HelpMarker(
                "Options to configure how we handle recoverable errors.\n"
                "- Error recovery is not perfect nor guaranteed! It is a feature to ease development.\n"
                "- You not are not supposed to rely on it in the course of a normal application run.\n"
                "- Possible usage: facilitate recovery from errors triggered from a scripting language or after specific exceptions handlers.\n"
                "- Always ensure that on programmers seat you have at minimum Asserts or Tooltips enabled when making direct imgui API call! "
                "Otherwise it would severely hinder your ability to catch and correct mistakes!");
            ImGui::Checkbox("io.ConfigErrorRecoveryEnableAssert", &io.ConfigErrorRecoveryEnableAssert);
            ImGui::Checkbox("io.ConfigErrorRecoveryEnableDebugLog", &io.ConfigErrorRecoveryEnableDebugLog);
            ImGui::Checkbox("io.ConfigErrorRecoveryEnableTooltip", &io.ConfigErrorRecoveryEnableTooltip);
            if (!io.ConfigErrorRecoveryEnableAssert && !io.ConfigErrorRecoveryEnableDebugLog && !io.ConfigErrorRecoveryEnableTooltip)
                io.ConfigErrorRecoveryEnableAssert = io.ConfigErrorRecoveryEnableDebugLog = io.ConfigErrorRecoveryEnableTooltip = true;

            // Also read: https://github.com/ocornut/imgui/wiki/Debug-Tools
            ImGui::SeparatorText("Debug");
            ImGui::Checkbox("io.ConfigDebugIsDebuggerPresent", &io.ConfigDebugIsDebuggerPresent);
            ImGui::SameLine(); HelpMarker("Enable various tools calling IM_DEBUG_BREAK().\n\nRequires a debugger being attached, otherwise IM_DEBUG_BREAK() options will appear to crash your application.");
            ImGui::Checkbox("io.ConfigDebugHighlightIdConflicts", &io.ConfigDebugHighlightIdConflicts);
            ImGui::SameLine(); HelpMarker("Highlight and show an error message when multiple items have conflicting identifiers.");
            ImGui::BeginDisabled();
            ImGui::Checkbox("io.ConfigDebugBeginReturnValueOnce", &io.ConfigDebugBeginReturnValueOnce);
            ImGui::EndDisabled();
            ImGui::SameLine(); HelpMarker("First calls to Begin()/BeginChild() will return false.\n\nTHIS OPTION IS DISABLED because it needs to be set at application boot-time to make sense. Showing the disabled option is a way to make this feature easier to discover.");
            ImGui::Checkbox("io.ConfigDebugBeginReturnValueLoop", &io.ConfigDebugBeginReturnValueLoop);
            ImGui::SameLine(); HelpMarker("Some calls to Begin()/BeginChild() will return false.\n\nWill cycle through window depths then repeat. Windows should be flickering while running.");
            ImGui::Checkbox("io.ConfigDebugIgnoreFocusLoss", &io.ConfigDebugIgnoreFocusLoss);
            ImGui::SameLine(); HelpMarker("Option to deactivate io.AddFocusEvent(false) handling. May facilitate interactions with a debugger when focus loss leads to clearing inputs data.");
            ImGui::Checkbox("io.ConfigDebugIniSettings", &io.ConfigDebugIniSettings);
            ImGui::SameLine(); HelpMarker("Option to save .ini data with extra comments (particularly helpful for Docking, but makes saving slower).");

            ImGui::TreePop();
            ImGui::Spacing();
        }

        IMGUI_DEMO_MARKER("Configuration/Backend Flags");
        if (ImGui::TreeNode("Backend Flags"))
        {
            HelpMarker(
                "Those flags are set by the backends (imgui_impl_xxx files) to specify their capabilities.\n"
                "Here we expose them as read-only fields to avoid breaking interactions with your backend.");

            // FIXME: Maybe we need a BeginReadonly() equivalent to keep label bright?
            ImGui::BeginDisabled();
            ImGui::CheckboxFlags("io.BackendFlags: HasGamepad",           &io.BackendFlags, ImGuiBackendFlags_HasGamepad);
            ImGui::CheckboxFlags("io.BackendFlags: HasMouseCursors",      &io.BackendFlags, ImGuiBackendFlags_HasMouseCursors);
            ImGui::CheckboxFlags("io.BackendFlags: HasSetMousePos",       &io.BackendFlags, ImGuiBackendFlags_HasSetMousePos);
            ImGui::CheckboxFlags("io.BackendFlags: RendererHasVtxOffset", &io.BackendFlags, ImGuiBackendFlags_RendererHasVtxOffset);
            ImGui::EndDisabled();

            ImGui::TreePop();
            ImGui::Spacing();
        }

        IMGUI_DEMO_MARKER("Configuration/Style");
        if (ImGui::TreeNode("Style"))
        {
            ImGui::Checkbox("Style Editor", &demo_data.ShowStyleEditor);
            ImGui::SameLine();
            HelpMarker("The same contents can be accessed in 'Tools->Style Editor' or by calling the ShowStyleEditor() function.");
            ImGui::TreePop();
            ImGui::Spacing();
        }

        IMGUI_DEMO_MARKER("Configuration/Capture, Logging");
        if (ImGui::TreeNode("Capture/Logging"))
        {
            HelpMarker(
                "The logging API redirects all text output so you can easily capture the content of "
                "a window or a block. Tree nodes can be automatically expanded.\n"
                "Try opening any of the contents below in this window and then click one of the \"Log To\" button.");
            ImGui::LogButtons();

            HelpMarker("You can also call ImGui::LogText() to output directly to the log without a visual output.");
            if (ImGui::Button("Copy \"Hello, world!\" to clipboard"))
            {
                ImGui::LogToClipboard();
                ImGui::LogText("Hello, world!");
                ImGui::LogFinish();
            }
            ImGui::TreePop();
        }
    }

    IMGUI_DEMO_MARKER("Window options");
    if (ImGui::CollapsingHeader("Window options"))
    {
        if (ImGui::BeginTable("split", 3))
        {
            ImGui::TableNextColumn(); ImGui::Checkbox("No titlebar", &no_titlebar);
            ImGui::TableNextColumn(); ImGui::Checkbox("No scrollbar", &no_scrollbar);
            ImGui::TableNextColumn(); ImGui::Checkbox("No menu", &no_menu);
            ImGui::TableNextColumn(); ImGui::Checkbox("No move", &no_move);
            ImGui::TableNextColumn(); ImGui::Checkbox("No resize", &no_resize);
            ImGui::TableNextColumn(); ImGui::Checkbox("No collapse", &no_collapse);
            ImGui::TableNextColumn(); ImGui::Checkbox("No close", &no_close);
            ImGui::TableNextColumn(); ImGui::Checkbox("No nav", &no_nav);
            ImGui::TableNextColumn(); ImGui::Checkbox("No background", &no_background);
            ImGui::TableNextColumn(); ImGui::Checkbox("No bring to front", &no_bring_to_front);
            ImGui::TableNextColumn(); ImGui::Checkbox("Unsaved document", &unsaved_document);
            ImGui::EndTable();
        }
    }

    // All demo contents
    DemoWindowWidgets(&demo_data);
    DemoWindowLayout();
    DemoWindowPopups();
    DemoWindowTables();
    DemoWindowInputs();

    // End of ShowDemoWindow()
    ImGui::PopItemWidth();
}

void ImGuiDemoView::DrawSidebar(sf::RenderTarget& target) { 
    m_goToMainView = ImGui::Button("Return");
}

void ImGuiDemoView::DrawImpl(sf::RenderTarget& target) { ; }

void ImGuiDemoView::Update(float deltaTime) { ; }
void ImGuiDemoView::EventUpdate(const sf::Event& event) { ; }

bool ImGuiDemoView::GoToMainView() {
    return m_goToMainView;
}