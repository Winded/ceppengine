#ifndef __glextQCOM_h_
#define __glextQCOM_h_
/*
** Copyright (C) 2009-2010 QUALCOMM Incorporated.
** All Rights Reserved. QUALCOMM Proprietary and Confidential.
*/

#ifndef __glext_h_
#   include <GLES/glext.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* GL_AMD_EGL_image_external_layout_specifier */
#ifndef GL_AMD_EGL_image_external_layout_specifier
#define GL_AMD_EGL_image_external_layout_specifier 1
// YUV format
#define GL_YUV_AMD                                           0x8BC7
// YUV types
#define GL_YUYV_AMD                                          0x8BC8
#define GL_UYVY_AMD                                          0x8BC9
#define GL_NV21_AMD                                          0x8BCA
#define GL_YV12_AMD                                          0x8BCB
#define GL_NV12_TILED_AMD                                    0x8BCC
// YUV samplers
#define GL_SAMPLER_EXTERNAL_YUYV_AMD                         0x8BCD
#define GL_SAMPLER_EXTERNAL_UYVY_AMD                         0x8BCE
#define GL_SAMPLER_EXTERNAL_NV21_AMD                         0x8BCF
#define GL_SAMPLER_EXTERNAL_YV12_AMD                         0x8BD0
#define GL_SAMPLER_EXTERNAL_NV12_TILED_AMD                   0x8BD1
#endif

/* GL_OES_egl_image_external (DRAFT) */
#ifndef GL_OES_EGL_image_external
#define GL_OES_EGL_image_external 1
#define GL_TEXTURE_EXTERNAL_OES                              0x8D65
#define GL_SAMPLER_EXTERNAL_OES                              0x8D66
#define GL_TEXTURE_BINDING_EXTERNAL_OES                      0x8D67
#define GL_REQUIRED_TEXTURE_IMAGE_UNITS_OES                  0x8D68
#endif

/* QCOM_binning_control */
#ifndef GL_QCOM_BINNING_CONTROL
#define GL_QCOM_BINNING_CONTROL 1
#define GL_BINNING_CONTROL_HINT_QCOM                         0x8FB0
#define GL_CPU_OPTIMIZED_QCOM                                0x8FB1
#define GL_GPU_OPTIMIZED_QCOM                                0x8FB2
#endif

/* EXT_texture_compression_s3tc */
#ifndef GL_EXT_texture_compression_s3tc
#define GL_COMPRESSED_RGB_S3TC_DXT1_EXT                  0x83F0
#define GL_COMPRESSED_RGBA_S3TC_DXT1_EXT                 0x83F1
#define GL_COMPRESSED_RGBA_S3TC_DXT3_EXT                 0x83F2
#define GL_COMPRESSED_RGBA_S3TC_DXT5_EXT                 0x83F3
#endif

#ifndef GL_QCOM_get_device_hw_flags
#define GL_QCOM_get_device_hw_flags 1
#define GL_GET_DEVICE_HW_FLAGS_QCOM                      0x8FB5
#define GL_HW_FLAG_HW_NONE_QCOM 0x0           
#define GL_HW_FLAG_HW_FOG_QCOM  0x1           
#endif

#ifdef __cplusplus
}
#endif

#endif /* __glextQCOM_h_ */

