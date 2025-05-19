LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := SDL2

LOCAL_C_INCLUDES := $(LOCAL_PATH)/include

LOCAL_SRC_FILES := \
    src/SDL.c \
    src/SDL_assert.c \
    src/SDL_error.c \
    src/SDL_hints.c \
    src/SDL_log.c \
    src/SDL_utils.c \
    src/SDL_list.c \
    src/SDL_guid.c \
    src/atomic/SDL_atomic.c \
    src/atomic/SDL_spinlock.c \
    src/audio/SDL_audio.c \
    src/audio/SDL_audiocvt.c \
    src/audio/SDL_audiodev.c \
    src/audio/SDL_audiotypecvt.c \
    src/audio/SDL_mixer.c \
    src/audio/SDL_wave.c \
    src/audio/android/SDL_androidaudio.c \
    src/core/android/SDL_android.c \
    src/cpuinfo/SDL_cpuinfo.c \
    src/events/SDL_clipboardevents.c \
    src/events/SDL_displayevents.c \
    src/events/SDL_dropevents.c \
    src/events/SDL_events.c \
    src/events/SDL_gesture.c \
    src/events/SDL_keyboard.c \
    src/events/SDL_mouse.c \
    src/events/SDL_quit.c \
    src/events/SDL_touch.c \
    src/events/SDL_windowevents.c \
    src/file/SDL_rwops.c \
    src/filesystem/android/SDL_sysfilesystem.c \
    src/haptic/SDL_haptic.c \
    src/haptic/android/SDL_syshaptic.c \
    src/joystick/SDL_joystick.c \
    src/joystick/android/SDL_sysjoystick.c \
    src/loadso/android/SDL_sysloadso.c \
    src/power/android/SDL_syspower.c \
    src/render/SDL_d3dmath.c \
    src/render/SDL_render.c \
    src/render/SDL_yuv_sw.c \
    src/render/opengles/SDL_render_gles.c \
    src/render/opengles2/SDL_render_gles2.c \
    src/sensor/SDL_sensor.c \
    src/sensor/android/SDL_androidsensor.c \
    src/stdlib/SDL_crc16.c \
    src/stdlib/SDL_crc32.c \
    src/stdlib/SDL_getenv.c \
    src/stdlib/SDL_iconv.c \
    src/stdlib/SDL_malloc.c \
    src/stdlib/SDL_qsort.c \
    src/stdlib/SDL_stdlib.c \
    src/stdlib/SDL_string.c \
    src/stdlib/SDL_strtokr.c \
    src/thread/SDL_thread.c \
    src/thread/generic/SDL_syscond.c \
    src/thread/generic/SDL_sysmutex.c \
    src/thread/generic/SDL_syssem.c \
    src/thread/generic/SDL_systhread.c \
    src/thread/generic/SDL_systls.c \
    src/timer/SDL_timer.c \
    src/timer/unix/SDL_systimer.c \
    src/video/SDL_blit.c \
    src/video/SDL_blit_0.c \
    src/video/SDL_blit_1.c \
    src/video/SDL_blit_A.c \
    src/video/SDL_blit_N.c \
    src/video/SDL_blit_auto.c \
    src/video/SDL_blit_copy.c \
    src/video/SDL_blit_slow.c \
    src/video/SDL_bmp.c \
    src/video/SDL_clipboard.c \
    src/video/SDL_egl.c \
    src/video/SDL_fillrect.c \
    src/video/SDL_pixels.c \
    src/video/SDL_rect.c \
    src/video/SDL_shape.c \
    src/video/SDL_stretch.c \
    src/video/SDL_surface.c \
    src/video/SDL_video.c \
    src/video/SDL_vulkan_utils.c \
    src/video/SDL_yuv.c \
    src/video/android/SDL_androidclipboard.c \
    src/video/android/SDL_androidevents.c \
    src/video/android/SDL_androidgl.c \
    src/video/android/SDL_androidkeyboard.c \
    src/video/android/SDL_androidmessagebox.c \
    src/video/android/SDL_androidmouse.c \
    src/video/android/SDL_androidtouch.c \
    src/video/android/SDL_androidvideo.c \
    src/video/android/SDL_androidvulkan.c \
    src/video/android/SDL_androidwindow.c

LOCAL_CFLAGS := -DGL_GLEXT_PROTOTYPES -DANDROID
LOCAL_LDLIBS := -ldl -lGLESv1_CM -lGLESv2 -llog

include $(BUILD_SHARED_LIBRARY) 