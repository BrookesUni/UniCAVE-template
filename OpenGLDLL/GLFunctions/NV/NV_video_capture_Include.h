#define GLI_INCLUDE_GL_NV_VIDEO_CAPTURE

enum Main {

  GL_VIDEO_BUFFER_NV                                = 0x9020,
  GL_VIDEO_BUFFER_BINDING_NV                        = 0x9021,
  GL_FIELD_UPPER_NV                                 = 0x9022,
  GL_FIELD_LOWER_NV                                 = 0x9023,
  GL_NUM_VIDEO_CAPTURE_STREAMS_NV                   = 0x9024,
  GL_NEXT_VIDEO_CAPTURE_BUFFER_STATUS_NV            = 0x9025,
  GL_VIDEO_CAPTURE_TO_422_SUPPORTED_NV              = 0x9026,
  GL_LAST_VIDEO_CAPTURE_STATUS_NV                   = 0x9027,
  GL_VIDEO_BUFFER_PITCH_NV                          = 0x9028,
  GL_VIDEO_COLOR_CONVERSION_MATRIX_NV               = 0x9029,
  GL_VIDEO_COLOR_CONVERSION_MAX_NV                  = 0x902A,
  GL_VIDEO_COLOR_CONVERSION_MIN_NV                  = 0x902B,
  GL_VIDEO_COLOR_CONVERSION_OFFSET_NV               = 0x902C,
  GL_VIDEO_BUFFER_INTERNAL_FORMAT_NV                = 0x902D,
  GL_PARTIAL_SUCCESS_NV                             = 0x902E,
  GL_SUCCESS_NV                                     = 0x902F,
  GL_FAILURE_NV                                     = 0x9030,
  GL_YCBYCR8_422_NV                                 = 0x9031,
  GL_YCBAYCR8A_4224_NV                              = 0x9032,
  GL_Z6Y10Z6CB10Z6Y10Z6CR10_422_NV                  = 0x9033,
  GL_Z6Y10Z6CB10Z6A10Z6Y10Z6CR10Z6A10_4224_NV       = 0x9034,
  GL_Z4Y12Z4CB12Z4Y12Z4CR12_422_NV                  = 0x9035,
  GL_Z4Y12Z4CB12Z4A12Z4Y12Z4CR12Z4A12_4224_NV       = 0x9036,
  GL_Z4Y12Z4CB12Z4CR12_444_NV                       = 0x9037,
  GL_VIDEO_CAPTURE_FRAME_WIDTH_NV                   = 0x9038,
  GL_VIDEO_CAPTURE_FRAME_HEIGHT_NV                  = 0x9039,
  GL_VIDEO_CAPTURE_FIELD_UPPER_HEIGHT_NV            = 0x903A,
  GL_VIDEO_CAPTURE_FIELD_LOWER_HEIGHT_NV            = 0x903B,
  GL_VIDEO_CAPTURE_SURFACE_ORIGIN_NV                = 0x903C,

};

void glBeginVideoCaptureNV(GLuint video_capture_slot);
void glBindVideoCaptureStreamBufferNV(GLuint video_capture_slot, GLuint stream, GLenum[Main] frame_region, GLintptr offset);
void glBindVideoCaptureStreamTextureNV(GLuint video_capture_slot, GLuint stream, GLenum[Main] frame_region, GLenum[Main] target, GLuint texture);
void glEndVideoCaptureNV(GLuint video_capture_slot);
void glGetVideoCaptureivNV(GLuint video_capture_slot, GLenum[Main] pname, GLint * params);
void glGetVideoCaptureStreamivNV(GLuint video_capture_slot, GLuint stream, GLenum[Main] pname, GLint * params);
void glGetVideoCaptureStreamfvNV(GLuint video_capture_slot, GLuint stream, GLenum[Main] pname, GLfloat * params);
void glGetVideoCaptureStreamdvNV(GLuint video_capture_slot, GLuint stream, GLenum[Main] pname, GLdouble * params);
GLenum glVideoCaptureNV(GLuint video_capture_slot, GLuint * sequence_num, GLuint64 * capture_time);
void glVideoCaptureStreamParameterivNV(GLuint video_capture_slot, GLuint stream, GLenum[Main] pname, const GLint * params);
void glVideoCaptureStreamParameterfvNV(GLuint video_capture_slot, GLuint stream, GLenum[Main] pname, const GLfloat * params);
void glVideoCaptureStreamParameterdvNV(GLuint video_capture_slot, GLuint stream, GLenum[Main] pname, const GLdouble * params);
