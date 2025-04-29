#include "windowFramework.h"
#include "pandaFramework.h"

#include "deformers/sineDeformer.h"

static AsyncTask::DoneStatus do_task(GenericAsyncTask* task, void* data) {
    SineDeformer* deformer = (SineDeformer*)data;
    deformer->deform_all(task->get_elapsed_time());
    return AsyncTask::DS_cont;
}

int main() {

    PandaFramework* framework = new PandaFramework();
    framework->open_framework();
    
    WindowFramework* window = framework->open_window();

    NodePath np = window->load_model(framework->get_models(), "teapot.egg");
    np.reparent_to(window->get_render());

    SineDeformer *deformer = new SineDeformer(np);
    deformer->deform_all(0.0);

    AsyncTaskManager* taskMgr = AsyncTaskManager::get_global_ptr();
    AsyncTask* deform_task = new GenericAsyncTask("deform_task", do_task, deformer);
    taskMgr->add(deform_task);

    window->setup_trackball();
    framework->main_loop();
    return 0;
}
