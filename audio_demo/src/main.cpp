#include <memory>

#include <firesteel/app.hpp>
#include <../../packages/fs.audio/include/audio.hpp>
#include <../../packages/fs.io/include/os.hpp>
#include "../../packages/fs.audio/include/audio.hpp"
#include "../../external/imgui/imgui.h"

using namespace firesteel;

class AudioApp : public App {
    bool open = true;
    Audio a{ "res\\sound.wav", false, {"test", 100.f, 1.f} };

    virtual void initialize() override {
        //Initialize ImGui.
        window.gui_initialize();
        AudioManager::initialize();
    }

    virtual void update() override {
        //Do fullscreen.
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("AudioApp", &open);
        ImGui::PopStyleVar(3);
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard | ImGuiConfigFlags_NavEnableGamepad;
        ImGui::Text("Audio player");
        ImGui::TextWrapped(a.get_source().c_str());
        if(ImGui::Button("Browse...")) {
            OS::file_dialog dial{ a.get_source(), NULL, "All\0*.wav\0*.ogg\0*.mp3\0" };
            a.set_source(dial.open());
        }
        ImGui::Text("Playback");
        if(!a.is_playing()) a.stop();
        ImGui::Checkbox("Loop", &a.loop);
        if(ImGui::Button("Play")) a.play();
        if(ImGui::Button("Stop")) a.stop();
        ImGui::End();
    }

    virtual void on_shutdown() override {
        a.stop();
        a.remove();
        AudioManager::remove();
    }
};

int main() {
    //Create instance of app.
    auto app = std::make_unique<AudioApp>();
    int returnC = app->start(200, 180, "Audio demo");
    return 0;
}