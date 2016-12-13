////////////////////////////////////////////////////////////////////////
// 
//  Project        ATI Handheld Graphics
//  Device         Asterix OpenGL ES driver
//
//
//                *** N O T *** F O R *** D I S T R I B U T I O N ***
//
// Copyright (C) 2009-2010 QUALCOMM Incorporated.
// All Rights Reserved. QUALCOMM Proprietary and Confidential.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef __gl_ati_extensions_h_
#define __gl_ati_extensions_h_

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus


//////////////////////////////////////////////////////////////////////////////
//
// GL_ALPHA_FACTOR_ATI
//
//////////////////////////////////////////////////////////////////////////////
#ifndef GL_ALPHA_FACTOR_ATI
#define GL_ALPHA_FACTOR_ATI								0x8c9f

GL_API void GL_APIENTRY	glAlphaFactorfATI(GLfloat alphafactor);
GL_API void GL_APIENTRY	glAlphaFactorxATI(GLfixed alphafactor);

#endif	/* GL_ALPHA_FACTOR_ATI */


//////////////////////////////////////////////////////////////////////////////
//
// GL_BUFFER_POINTER_ATI
//
//////////////////////////////////////////////////////////////////////////////
#ifndef GL_BUFFER_POINTER_ATI
#define GL_BUFFER_POINTER_ATI

#define GL_VERTEX_ARRAY_POINTER			  0x808E
#define GL_NORMAL_ARRAY_POINTER			  0x808F
#define GL_COLOR_ARRAY_POINTER			  0x8090
#define GL_TEXTURE_COORD_ARRAY_POINTER	  0x8092

GL_API void GL_APIENTRY	glGetPointerv (GLenum pname, GLvoid **params);
GL_API void GL_APIENTRY glGetBufferPointervATI(GLenum target, GLvoid **params);

#endif /* GL_BUFFER_POINTER_ATI */


//////////////////////////////////////////////////////////////////////////////
//
// GL_ATI_vertexshader_pipe_test
//
//////////////////////////////////////////////////////////////////////////////
#ifndef GL_ATI_vertexshader_pipe_test
#define GL_ATI_vertexshader_pipe_test

#define GL_VERTEXSHADER_FIELD_XYZW_ATI      0x00
#define GL_VERTEXSHADER_FIELD_NORMAL_ATI    0x01
#define GL_VERTEXSHADER_FIELD_RADIUS_ATI    0x02
#define GL_VERTEXSHADER_FIELD_DIFFUSE_ATI   0x10
#define GL_VERTEXSHADER_FIELD_SPECULAR_ATI  0x11
#define GL_VERTEXSHADER_FIELD_TEXTURE0_ATI  0x20
#define GL_VERTEXSHADER_FIELD_TEXTURE1_ATI  0x21

#define GL_VERTEXSHADER_COLOR_BGRA_ATI      0x00
#define GL_VERTEXSHADER_COLOR_RGBA_ATI      0x01

#define GL_VERTEXSHADER_DATAMODE_EMBED      0x00
#define GL_VERTEXSHADER_DATAMODE_INDEX      0x01
#define GL_VERTEXSHADER_DATAMODE_AUTOINDEX  0x02

#define GL_VERTEXSHADER_PRIMMODE_TRIANGLES  0x00
#define GL_VERTEXSHADER_PRIMMODE_TRISTRIP   0x01
#define GL_VERTEXSHADER_PRIMMODE_TRIFAN     0x02
#define GL_VERTEXSHADER_PRIMMODE_POINTS     0x03

GL_API GLboolean GL_APIENTRY
glCheckVertexShaderInputColorATI(
    GLenum          colorfmt);

typedef GLboolean
(*GLCHECKVERTEXSHADERINPUTCOLORATI)(
    GLenum          colorfmt);

GL_API GLboolean GL_APIENTRY    
glCheckVertexShaderInputFieldATI(
    GLenum          field,
    GLenum          type,
    GLenum          size);

typedef GLboolean    
(*GLCHECKVERTEXSHADERINPUTFIELDATI)(
    GLenum          field,
    GLenum          type,
    GLenum          size);

GL_API GLboolean GL_APIENTRY	
glSetVertexShaderInputFormatATI(
    GLuint          pitch,
    GLuint          numfields,
    const GLenum    *fields,
    const GLenum    *types,
    const GLenum    *sizes,
    GLenum          colorfmt,
    GLuint          *offsets);

typedef GLboolean	
(*GLSETVERTEXSHADERINPUTFORMATATI)(
    GLuint          pitch,
    GLuint          numfields,
    const GLenum    *fields,
    const GLenum    *types,
    const GLenum    *sizes,
    GLenum          colorfmt,
    GLuint          *offsets);

GL_API GLboolean GL_APIENTRY
glCheckVertexShaderOutputColorATI(
    GLenum          colorfmt);

typedef GLboolean
(*GLCHECKVERTEXSHADEROUTPUTCOLORATI)(
    GLenum          colorfmt);

GL_API GLboolean GL_APIENTRY    
glCheckVertexShaderOutputFieldATI(
    GLenum          field,
    GLenum          type,
    GLenum          size);

typedef GLboolean    
(*GLCHECKVERTEXSHADEROUTPUTFIELDATI)(
    GLenum          field,
    GLenum          type,
    GLenum          size);

GL_API GLboolean GL_APIENTRY	
glSetVertexShaderOutputFormatATI(
    GLuint          pitch,
    GLuint          numfields,
    const GLenum    *fields,
    const GLenum    *types,
    const GLenum    *sizes,
    GLenum          colorfmt,
    GLuint          *offsets);

typedef GLboolean	
(*GLSETVERTEXSHADEROUTPUTFORMATATI)(
    GLuint          pitch,
    GLuint          numfields,
    const GLenum    *fields,
    const GLenum    *types,
    const GLenum    *sizes,
    GLenum          colorfmt,
    GLuint          *offsets);

GL_API GLboolean GL_APIENTRY    
glCheckVertexShaderSetupValidATI(
    GLenum          primmode);

typedef GLboolean    
(*GLCHECKVERTEXSHADERSETUPVALIDATI)(
    GLenum          primmode);

GL_API void GL_APIENTRY
glSetVertexShaderGuardbandATI(
    GLuint          xguardband,
    GLuint          yguardband);

typedef void
(*GLSETVERTEXSHADERGUARDBANDATI)(
    GLuint          xguardband,
    GLuint          yguardband);

GL_API void GL_APIENTRY
glLoadVertexShaderState1fATI(
    GLuint          index,
    GLuint          pos,
    GLfloat         data);

typedef void
(*GLLOADVERTEXSHADERSTATE1FATI)(
    GLuint          index,
    GLuint          pos,
    GLfloat         data);

GL_API void GL_APIENTRY 
glLoadVertexShaderState4fvATI(
    GLuint          index,
    const GLfloat   *data);

typedef void 
(*GLLOADVERTEXSHADERSTATE4FVATI)(
    GLuint          index,
    const GLfloat   *data);

GL_API void GL_APIENTRY 
glLoadVertexShaderOffsetsATI(
    const GLuint    *data);

typedef void 
(*GLLOADVERTEXSHADEROFFSETSATI)(
    const GLuint    *data);

GL_API void GL_APIENTRY
glLoadVertexShaderUcodeATI(
    GLuint          numinstructions,
    const GLuint    *ucode);

typedef void
(*GLLOADVERTEXSHADERUCODEATI)(
    GLuint          numinstructions,
    const GLuint    *ucode);

GL_API GLuint GL_APIENTRY
glExecuteVertexShaderUcodeATI(
    GLuint          numvertices,
    const GLuint    *vertices,
    GLenum          datamode,
    GLenum          primmode);

typedef GLuint
(*GLEXECUTEVERTEXSHADERUCODEATI)(
    GLuint          numvertices,
    const GLuint    *vertices,
    GLenum          datamode,
    GLenum          primmode);

GL_API void GL_APIENTRY
glReadVertexShaderOutputATI(
    GLuint          numvertices,
    void            *vertexbuffer,
    void            *binbuffer,
    GLuint          clipcount,
    void            *clipbuffer);

typedef void
(*GLREADVERTEXSHADEROUTPUTATI)(
    GLuint          numvertices,
    void            *vertexbuffer,
    void            *binbuffer,
    GLuint          clipcount,
    void            *clipbuffer);

GL_API void GL_APIENTRY
glSetCurrentBinsATI(GLushort bins);

typedef void
(*GLSETCURRENTBINSATI)(GLushort bins);

#endif /* GL_ATI_vertexshader_pipe_test */


//////////////////////////////////////////////////////////////////////////////
//
// GL_MATRIX_ATI
//
//////////////////////////////////////////////////////////////////////////////
#ifndef GL_MATRIX_ATI
#define GL_MATRIX_ATI

#define GL_MATRIX_HINT_GENERAL_ATI		0	// general case
#define GL_MATRIX_HINT_ANISOSCALE_ATI	1	// 0001 bottom row
#define GL_MATRIX_HINT_ISOSCALE_ATI		2	// translates, rotates, scales where Sx = Sy = Sz
#define GL_MATRIX_HINT_TRANSROT_ATI		4	// translates & rotates only	
#define GL_MATRIX_HINT_IDENTITY_ATI		8	// identity
#define GL_MATRIX_HINT_SCALE_ONLY	   32	// or this in with scale only ISOSCALE or ANISOSCALE
											// on a Load. This only affects the texture path

GL_API void GL_APIENTRY glLoadMatrixfWithHintATI(const GLfloat *m, GLenum hint);
GL_API void GL_APIENTRY glMultMatrixfWithHintATI(const GLfloat *m, GLenum hint);
	
#endif /* GL_MATRIX_ATI */


//////////////////////////////////////////////////////////////////////////////
//
// GL_FLUSH_ATI
//
//////////////////////////////////////////////////////////////////////////////
#ifndef GL_FLUSH_ATI
#define GL_FLUSH_ATI

GL_API void GL_APIENTRY glFlushATI(void);
GL_API void GL_APIENTRY glFinishATI(void);

#endif /* GL_FLUSH_ATI */


//////////////////////////////////////////////////////////////////////////////
//
// GL_ATI_YUV_422
//
//////////////////////////////////////////////////////////////////////////////
#ifndef GL_ATI_YUV_422
#define GL_ATI_YUV_422

#define GL_YUV422_YUYV_ATI								0x8C94
#define GL_YUV422_UYVY_ATI								0x8C95

#endif	/* GL_ATI_YUV_422 */


//////////////////////////////////////////////////////////////////////////////
//
// GL_EARLY_Z_TEST_ATI
//
//////////////////////////////////////////////////////////////////////////////
#ifndef GL_EARLY_Z_TEST_ATI
#define GL_EARLY_Z_TEST_ATI

GL_API void GL_APIENTRY glEnableEarlyZ(void);
GL_API void GL_APIENTRY glDisableEarlyZ(void);

GL_API void GL_APIENTRY glEnableFastClear(void);
GL_API void GL_APIENTRY glDisableFastClear(void);

#endif /* GL_EARLY_Z_TEST_ATI */


//////////////////////////////////////////////////////////////////////////////
//
// GL_FOG_COORD_ATI - fog coord for JSR184 sprites.
//					- works only with glDrawTex***
//
//////////////////////////////////////////////////////////////////////////////
#ifndef GL_FOG_COORD_ATI
#define GL_FOG_COORD_ATI

#define GL_FOG_COORDINATE_SOURCE_EXT            0x8450
#define GL_FOG_COORDINATE_EXT                   0x8451
#define GL_FRAGMENT_DEPTH_EXT                   0x8452

GL_API void GL_APIENTRY glFogCoordf(GLfloat fogcoord);

#endif /* GL_FOG_COORD_ATI */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif	/* __gl_ati_extensions_h_ */

