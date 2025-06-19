#include "config_deformer.h"
#include "dconfig.h"

Configure(config_surface_deformers);
NotifyCategoryDef(surface_deformers, "");

ConfigureFn(config_surface_deformers) {
  init_libsurfacedeformers();
}

void init_libsurfacedeformers() {
  static bool initialized = false;
  if (initialized) return;

  initialized = true;
  return;
}
