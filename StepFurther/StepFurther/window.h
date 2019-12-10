#pragma once
#include "scene.h"

namespace zjl {
static bool			is_rotating_view = false;
static Scene		scene;
static double		xpos, ypos;
static const int	default_viewport_width = 1200;
static const int	default_viewport_height = 800;
static const int	toolset_region_width = 250;
static int			current_viewport_width = default_viewport_width;
static int			current_viewport_height = default_viewport_height;
static std::string  current_working_directory;
static float		frame_time = 0.0;


int ShowWindow();

}


