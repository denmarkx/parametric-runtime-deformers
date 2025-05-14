#include "windowFramework.h"
#include "pandaFramework.h"

#include "deformers/sineDeformer.h"
#include "deformers/twistDeformer.h"
#include "imgui/panda3d_imgui_main.cxx"

typedef TwistDeformer TYPE_DEFORMER;

TYPE_DEFORMER* deformer;

static AsyncTask::DoneStatus do_task(GenericAsyncTask* task, void* data) {
    TYPE_DEFORMER* deformer = (TYPE_DEFORMER*)data;
    deformer->deform_all(0); // task->get_elapsed_time());
    return AsyncTask::DS_cont;
}

static void render_frame() {
    ImGui::SetNextWindowContentSize(ImVec2(250, 0.0));
    ImGui::Begin("Deformer Options", NULL, ImGuiWindowFlags_AlwaysAutoResize);
    auto func_map = deformer->options.func_map;

    std::string name;
    float* var_ptr = nullptr;
    double min, max;
    int i = 0;

    for (auto it = func_map.begin(); it != func_map.end(); it++) {
        var_ptr = it->second.first;
        min = it->second.second[0];
        max = it->second.second[1];
        ImGui::PushID(i);
        ImGui::Text(it->first.c_str());
        ImGui::SliderFloat("", var_ptr, min, max, "%.3f", ImGuiSliderFlags_NoInput);
        ImGui::PopID();
        i++;
    }

    ImGui::End();
}

int main() {

    PandaFramework* framework = new PandaFramework();
    framework->open_framework();
    
    WindowFramework* window = framework->open_window();

    NodePath np = window->load_model(framework->get_models(), "teapot.egg");
    np.reparent_to(window->get_render());

    deformer = new TYPE_DEFORMER(np, Axis::Z);
    deformer->deform_all();
    deformer->set_other(LPoint3f(-5, 5, 0));

    AsyncTaskManager* taskMgr = AsyncTaskManager::get_global_ptr();
    AsyncTask* deform_task = new GenericAsyncTask("deform_task", do_task, deformer);
    taskMgr->add(deform_task);
    window->enable_keyboard();
    window->setup_trackball();

    setup_p3d_imgui(window, render_frame);

    framework->main_loop();
    return 0;
}
