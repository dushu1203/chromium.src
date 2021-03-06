// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_GPU_COMPOSITOR_UTIL_H_
#define CONTENT_BROWSER_GPU_COMPOSITOR_UTIL_H_

#include "base/values.h"
#include "content/common/content_export.h"

namespace content {

// Note: When adding a function here, please make sure the logic is not
// duplicated in the renderer.

// Returns true if the virtual viewport model of pinch-to-zoom is on (via
// flags, or platform default).
CONTENT_EXPORT bool IsPinchVirtualViewportEnabled();

// Returns true if delegated-renderer is on (via flags, or platform default).
CONTENT_EXPORT bool IsDelegatedRendererEnabled();

// Returns true if impl-side painting is on (via flags, or platform default)
// for the renderer.
CONTENT_EXPORT bool IsImplSidePaintingEnabled();

// Returns true if gpu rasterization is on (via flags) for the renderer.
CONTENT_EXPORT bool IsGpuRasterizationEnabled();

// Returns true if force-gpu-rasterization is on (via flags) for the renderer.
CONTENT_EXPORT bool IsForceGpuRasterizationEnabled();

// Returns the number of raster threads to use for compositing.
CONTENT_EXPORT int NumberOfRendererRasterThreads();

// Returns the number of raster threads to use for compositing that are forced
// by the command line.
CONTENT_EXPORT int ForceNumberOfRendererRasterThreads();

// Returns true if using cc Surfaces is allowed.
CONTENT_EXPORT bool UseSurfacesEnabled();

CONTENT_EXPORT base::DictionaryValue* GetFeatureStatus();
CONTENT_EXPORT base::Value* GetProblems();
CONTENT_EXPORT std::vector<std::string> GetDriverBugWorkarounds();

}  // namespace content

#endif  // CONTENT_BROWSER_GPU_COMPOSITOR_UTIL_H_
