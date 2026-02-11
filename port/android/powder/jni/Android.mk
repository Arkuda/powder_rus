# Copyright (C) 2009 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
LOCAL_PATH := $(call my-dir)

POWDERROOT := $(abspath $(LOCAL_PATH)/../../../..)

include $(CLEAR_VARS)

LOCAL_MODULE    := powder-jni

LOCAL_C_INCLUDES := $(POWDERROOT)/port/sdl/include \
                   $(POWDERROOT)/port/sdl/include/SDL2 \
                   $(LOCAL_PATH) \
                   $(POWDERROOT)/port/android/powder/jni

LOCAL_CPPFLAGS := -DLINUX -DANDROID \
                 -I$(POWDERROOT)/port/sdl/include \
                 -I$(POWDERROOT)/port/sdl/include/SDL2 \
                 -I$(LOCAL_PATH) \
                 -I$(POWDERROOT)/port/android/powder/jni

# NOTE: cyrillic helpers are implemented in gfxengine.cpp.
# Keep jni/cyrillic.cpp out of LOCAL_SRC_FILES to avoid duplicate symbols.
LOCAL_SRC_FILES := powder-jni.cpp \
                   android_main.cpp \
                   hamfake_android.cpp \
                   $(POWDERROOT)/main.cpp \
                   $(POWDERROOT)/thread.cpp \
                   $(POWDERROOT)/thread_linux.cpp \
                   $(POWDERROOT)/port/sdl/hamfake.cpp \
                   $(POWDERROOT)/action.cpp \
                   $(POWDERROOT)/assert.cpp \
                   $(POWDERROOT)/ai.cpp \
                   $(POWDERROOT)/artifact.cpp \
                   $(POWDERROOT)/bmp.cpp \
                   $(POWDERROOT)/build.cpp \
                   $(POWDERROOT)/buf.cpp \
                   $(POWDERROOT)/control.cpp \
                   $(POWDERROOT)/creature.cpp \
                   $(POWDERROOT)/dpdf_table.cpp \
                   $(POWDERROOT)/encyc_support.cpp \
                   $(POWDERROOT)/gfxengine.cpp \
                   $(POWDERROOT)/grammar.cpp \
                   $(POWDERROOT)/hiscore.cpp \
                   $(POWDERROOT)/input.cpp \
                   $(POWDERROOT)/intrinsic.cpp \
                   $(POWDERROOT)/item.cpp \
                   $(POWDERROOT)/map.cpp \
                   $(POWDERROOT)/mobref.cpp \
                   $(POWDERROOT)/msg.cpp \
                   $(POWDERROOT)/name.cpp \
                   $(POWDERROOT)/piety.cpp \
                   $(POWDERROOT)/rand.cpp \
                   $(POWDERROOT)/signpost.cpp \
                   $(POWDERROOT)/smokestack.cpp \
                   $(POWDERROOT)/speed.cpp \
                   $(POWDERROOT)/sramstream.cpp \
                   $(POWDERROOT)/stylus.cpp \
                   $(POWDERROOT)/victory.cpp \
                   $(POWDERROOT)/encyclopedia.cpp \
                   $(POWDERROOT)/glbdef.cpp \
                   $(POWDERROOT)/credits.cpp \
                   $(POWDERROOT)/license.cpp \
                   $(POWDERROOT)/localization.cpp \
                   $(POWDERROOT)/gfx/all_bitmaps.cpp \
                   $(POWDERROOT)/rooms/allrooms.cpp \
                   $(POWDERROOT)/port/sdl/src/SDL.c \
                   $(POWDERROOT)/port/sdl/src/SDL_assert.c \
                   $(POWDERROOT)/port/sdl/src/SDL_error.c \
                   $(POWDERROOT)/port/sdl/src/SDL_hints.c \
                   $(POWDERROOT)/port/sdl/src/SDL_log.c \
                   $(POWDERROOT)/port/sdl/src/SDL_utils.c \
                   $(POWDERROOT)/port/sdl/src/SDL_list.c \
                   $(POWDERROOT)/port/sdl/src/SDL_guid.c \
                   $(POWDERROOT)/port/sdl/src/atomic/SDL_atomic.c \
                   $(POWDERROOT)/port/sdl/src/atomic/SDL_spinlock.c \
                   $(POWDERROOT)/port/sdl/src/audio/SDL_audio.c \
                   $(POWDERROOT)/port/sdl/src/audio/SDL_audiocvt.c \
                   $(POWDERROOT)/port/sdl/src/audio/SDL_audiodev.c \
                   $(POWDERROOT)/port/sdl/src/audio/SDL_audiotypecvt.c \
                   $(POWDERROOT)/port/sdl/src/audio/SDL_mixer.c \
                   $(POWDERROOT)/port/sdl/src/audio/SDL_wave.c \
                   $(POWDERROOT)/port/sdl/src/audio/android/SDL_androidaudio.c \
                   $(POWDERROOT)/port/sdl/src/core/android/SDL_android.c \
                   $(POWDERROOT)/port/sdl/src/cpuinfo/SDL_cpuinfo.c \
                   $(POWDERROOT)/port/sdl/src/events/SDL_clipboardevents.c \
                   $(POWDERROOT)/port/sdl/src/events/SDL_displayevents.c \
                   $(POWDERROOT)/port/sdl/src/events/SDL_dropevents.c \
                   $(POWDERROOT)/port/sdl/src/events/SDL_events.c \
                   $(POWDERROOT)/port/sdl/src/events/SDL_gesture.c \
                   $(POWDERROOT)/port/sdl/src/events/SDL_keyboard.c \
                   $(POWDERROOT)/port/sdl/src/events/SDL_mouse.c \
                   $(POWDERROOT)/port/sdl/src/events/SDL_quit.c \
                   $(POWDERROOT)/port/sdl/src/events/SDL_touch.c \
                   $(POWDERROOT)/port/sdl/src/events/SDL_windowevents.c \
                   $(POWDERROOT)/port/sdl/src/file/SDL_rwops.c \
                   $(POWDERROOT)/port/sdl/src/filesystem/android/SDL_sysfilesystem.c \
                   $(POWDERROOT)/port/sdl/src/haptic/SDL_haptic.c \
                   $(POWDERROOT)/port/sdl/src/haptic/android/SDL_syshaptic.c \
                   $(POWDERROOT)/port/sdl/src/joystick/SDL_joystick.c \
                   $(POWDERROOT)/port/sdl/src/joystick/android/SDL_sysjoystick.c \
                   $(POWDERROOT)/port/sdl/src/loadso/android/SDL_sysloadso.c \
                   $(POWDERROOT)/port/sdl/src/power/android/SDL_syspower.c \
                   $(POWDERROOT)/port/sdl/src/render/SDL_d3dmath.c \
                   $(POWDERROOT)/port/sdl/src/render/SDL_render.c \
                   $(POWDERROOT)/port/sdl/src/render/SDL_yuv_sw.c \
                   $(POWDERROOT)/port/sdl/src/render/opengles/SDL_render_gles.c \
                   $(POWDERROOT)/port/sdl/src/render/opengles2/SDL_render_gles2.c \
                   $(POWDERROOT)/port/sdl/src/sensor/SDL_sensor.c \
                   $(POWDERROOT)/port/sdl/src/sensor/android/SDL_androidsensor.c \
                   $(POWDERROOT)/port/sdl/src/stdlib/SDL_crc16.c \
                   $(POWDERROOT)/port/sdl/src/stdlib/SDL_crc32.c \
                   $(POWDERROOT)/port/sdl/src/stdlib/SDL_getenv.c \
                   $(POWDERROOT)/port/sdl/src/stdlib/SDL_iconv.c \
                   $(POWDERROOT)/port/sdl/src/stdlib/SDL_malloc.c \
                   $(POWDERROOT)/port/sdl/src/stdlib/SDL_qsort.c \
                   $(POWDERROOT)/port/sdl/src/stdlib/SDL_stdlib.c \
                   $(POWDERROOT)/port/sdl/src/stdlib/SDL_string.c \
                   $(POWDERROOT)/port/sdl/src/stdlib/SDL_strtokr.c \
                   $(POWDERROOT)/port/sdl/src/thread/SDL_thread.c \
                   $(POWDERROOT)/port/sdl/src/thread/generic/SDL_syscond.c \
                   $(POWDERROOT)/port/sdl/src/thread/generic/SDL_sysmutex.c \
                   $(POWDERROOT)/port/sdl/src/thread/generic/SDL_syssem.c \
                   $(POWDERROOT)/port/sdl/src/thread/generic/SDL_systhread.c \
                   $(POWDERROOT)/port/sdl/src/thread/generic/SDL_systls.c \
                   $(POWDERROOT)/port/sdl/src/timer/SDL_timer.c \
                   $(POWDERROOT)/port/sdl/src/timer/unix/SDL_systimer.c \
                   $(POWDERROOT)/port/sdl/src/video/SDL_blit.c \
                   $(POWDERROOT)/port/sdl/src/video/SDL_blit_0.c \
                   $(POWDERROOT)/port/sdl/src/video/SDL_blit_1.c \
                   $(POWDERROOT)/port/sdl/src/video/SDL_blit_A.c \
                   $(POWDERROOT)/port/sdl/src/video/SDL_blit_N.c \
                   $(POWDERROOT)/port/sdl/src/video/SDL_blit_auto.c \
                   $(POWDERROOT)/port/sdl/src/video/SDL_blit_copy.c \
                   $(POWDERROOT)/port/sdl/src/video/SDL_blit_slow.c \
                   $(POWDERROOT)/port/sdl/src/video/SDL_bmp.c \
                   $(POWDERROOT)/port/sdl/src/video/SDL_clipboard.c \
                   $(POWDERROOT)/port/sdl/src/video/SDL_egl.c \
                   $(POWDERROOT)/port/sdl/src/video/SDL_fillrect.c \
                   $(POWDERROOT)/port/sdl/src/video/SDL_pixels.c \
                   $(POWDERROOT)/port/sdl/src/video/SDL_rect.c \
                   $(POWDERROOT)/port/sdl/src/video/SDL_shape.c \
                   $(POWDERROOT)/port/sdl/src/video/SDL_stretch.c \
                   $(POWDERROOT)/port/sdl/src/video/SDL_surface.c \
                   $(POWDERROOT)/port/sdl/src/video/SDL_video.c \
                   $(POWDERROOT)/port/sdl/src/video/SDL_vulkan_utils.c \
                   $(POWDERROOT)/port/sdl/src/video/SDL_yuv.c \
                   $(POWDERROOT)/port/sdl/src/video/android/SDL_androidclipboard.c \
                   $(POWDERROOT)/port/sdl/src/video/android/SDL_androidevents.c \
                   $(POWDERROOT)/port/sdl/src/video/android/SDL_androidgl.c \
                   $(POWDERROOT)/port/sdl/src/video/android/SDL_androidkeyboard.c \
                   $(POWDERROOT)/port/sdl/src/video/android/SDL_androidmessagebox.c \
                   $(POWDERROOT)/port/sdl/src/video/android/SDL_androidmouse.c \
                   $(POWDERROOT)/port/sdl/src/video/android/SDL_androidtouch.c \
                   $(POWDERROOT)/port/sdl/src/video/android/SDL_androidvideo.c \
                   $(POWDERROOT)/port/sdl/src/video/android/SDL_androidvulkan.c \
                   $(POWDERROOT)/port/sdl/src/video/android/SDL_androidwindow.c

LOCAL_CFLAGS := -DGL_GLEXT_PROTOTYPES -DANDROID
LOCAL_LDLIBS := -ldl -lGLESv1_CM -lGLESv2 -llog

include $(BUILD_SHARED_LIBRARY)
