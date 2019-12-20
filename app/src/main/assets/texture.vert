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

#version 450

layout (push_constant) uniform PushConstants {
   mat4 mvp;
   mat2 preRotate;
} pushConstants;
layout (location = 0) in vec2 inVertPos;
layout (location = 1) in vec2 inTexPos;
layout (location = 0) out vec2 outTexPos;

void main() {
   outTexPos = inTexPos;
   vec4 clip = pushConstants.mvp * vec4(inVertPos, 0.0, 1.0);
   gl_Position = vec4(pushConstants.preRotate * vec2(clip.x, clip.y), clip.z, clip.w);
}
