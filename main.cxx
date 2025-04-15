#include "windowFramework.h"
#include "pandaFramework.h"

#include "deformer.h"

int main() {

    PandaFramework* framework = new PandaFramework();
    framework->open_framework();
    
    WindowFramework* window = framework->open_window();

    NodePath np = window->load_model(framework->get_models(), "teapot.egg");
    np.reparent_to(window->get_render());

    Deformer *deformer = new Deformer(np);
    deformer->deform_all();

    window->setup_trackball();
    framework->main_loop();
    return 0;
}
