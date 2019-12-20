# Vulkan Pre-rotation Demo

## After git clone

1. git submodule init
2. git submodule update

## What's covered?

1. Detect all surface rotations in Android 10+(easier if landscape only without resizing).
2. Handle swapchain recreation.
3. Fix the shaders in clipping space with a simple 2x2 matrix.
4. NativityActivity, AChoreographer, etc.

## What's not covered?

1. Detect surface rotation in Android Pie and below, which can be fixed by either calling vkGetPhysicalDeviceSurfaceCapabilitiesKHR or the jni Display.getRotation() once a while.
2. Fix advanced shader features like dfdx and dfdy, which can be fixed by mapping the intended derivative to +-dfdx or +-dfdy according to preTransform pushed to the shader.
3. Other miscellaneous.

