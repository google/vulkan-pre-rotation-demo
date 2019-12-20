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

#include <android/choreographer.h>
#include <android_native_app_glue.h>

#include "Engine.h"
#include "Utils.h"

static void onChoreographer(int64_t frameTimeNanos, void* data) {
    if (!data) {
        return;
    }

    auto engine = static_cast<Engine*>(data);
    if (!engine->isReady()) {
        return;
    }

    AChoreographer_postFrameCallbackDelayed64(AChoreographer_getInstance(), onChoreographer, engine,
                                              engine->getDelayMillis(frameTimeNanos));

    engine->drawFrame();
}

static void handleAppCmd(android_app* app, int32_t cmd) {
    auto engine = static_cast<Engine*>(app->userData);
    switch (cmd) {
        case APP_CMD_INIT_WINDOW:
            engine->onInitWindow(app->window, app->activity->assetManager);
            AChoreographer_postFrameCallback64(AChoreographer_getInstance(), onChoreographer,
                                               engine);
            break;
        case APP_CMD_TERM_WINDOW:
            engine->onTermWindow();
            break;
        default:
            break;
    }
}

static void handleNativeWindowResized(ANativeActivity* activity, ANativeWindow* window) {
    auto engine = static_cast<Engine*>(static_cast<android_app*>(activity->instance)->userData);
    const int32_t width = ANativeWindow_getWidth(window);
    const int32_t height = ANativeWindow_getHeight(window);
    ALOGD("%s: W[%d], H[%d]", __FUNCTION__, width, height);

    if (width < 0 || height < 0) {
        return;
    }
    engine->onWindowResized((uint32_t)width, (uint32_t)height);
}

void android_main(android_app* app) {
    Engine engine;

    app->userData = &engine;
    app->onAppCmd = handleAppCmd;
    app->activity->callbacks->onNativeWindowResized = handleNativeWindowResized;

    if (AChoreographer_getInstance() == nullptr) {
        return;
    }

    while (true) {
        int events;
        android_poll_source* source;

        while (ALooper_pollAll(-1, nullptr, &events, (void**)&source) >= 0) {
            if (source != nullptr) {
                source->process(app, source);
            }

            if (app->destroyRequested != 0) {
                ALOGD("Destroy requested");
                engine.onTermWindow();
                return;
            }
        }
    }
}
