#include <editor/editor_imgui_sdl.h>

#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_sdl.h>

namespace bones
{
  ImGuiEditor::ImGuiEditor(SDL_Window* wnd, SDL_GLContext ctx)
  {
    // create context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO(); (void)io;

    // enable controls
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		// io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
		// io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
		// io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

    // set style/fonts
    // ImGui::StyleColorsDark();
    // io.Fonts->AddFontFromFileTTF("resources/fonts/DroidSans.ttf", 15.0f);

    // set platform/renderer bindings
    ImGui_ImplSDL2_InitForOpenGL(wnd, ctx);

    const char* glsl_version = "#version 330";
    ImGui_ImplOpenGL3_Init(glsl_version);
  }

  ImGuiEditor::~ImGuiEditor()
  {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
  }

  void ImGuiEditor::render()
  {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    bool show_demo_window = true;
    ImGui::ShowDemoWindow(&show_demo_window);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  }
}