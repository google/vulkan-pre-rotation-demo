/*
 * Copyright 2019 Google LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <android_native_app_glue.h>

#include <mutex>

#include "Renderer.h"

class Engine {
public:
    explicit Engine() : mIsRendererReady(false) {}
    bool isReady();
    void drawFrame();
    void onInitWindow(ANativeWindow* window, AAssetManager* assetManager);
    void onWindowResized(uint32_t width, uint32_t height);
    void onTermWindow();
    uint32_t getDelayMillis(int64_t frameTimeNanos);

private:
    // mLock protects all members below
    std::mutex mLock;
    Renderer mRenderer;
    bool mIsRendererReady;

    // defer 13ms to target 60Hz on a 60Hz display or 45Hz on a 90Hz display
    static constexpr const uint32_t kDelayMillis = 13;
};
