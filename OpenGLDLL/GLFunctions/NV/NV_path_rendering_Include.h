#define GLI_INCLUDE_NV_PATH_RENDERING

enum Main {

  GL_PATH_FORMAT_SVG_NV                             = 0x9070,
  GL_PATH_FORMAT_PS_NV                              = 0x9071,

  GL_STANDARD_FONT_NAME_NV                          = 0x9072,
  GL_SYSTEM_FONT_NAME_NV                            = 0x9073,
  GL_FILE_NAME_NV                                   = 0x9074,

  GL_SKIP_MISSING_GLYPH_NV                          = 0x90A9,
  GL_USE_MISSING_GLYPH_NV                           = 0x90AA,

  GL_PATH_STROKE_WIDTH_NV                           = 0x9075,
  GL_PATH_INITIAL_END_CAP_NV                        = 0x9077,
  GL_PATH_TERMINAL_END_CAP_NV                       = 0x9078,
  GL_PATH_JOIN_STYLE_NV                             = 0x9079,
  GL_PATH_MITER_LIMIT_NV                            = 0x907A,
  GL_PATH_INITIAL_DASH_CAP_NV                       = 0x907C,
  GL_PATH_TERMINAL_DASH_CAP_NV                      = 0x907D,
  GL_PATH_DASH_OFFSET_NV                            = 0x907E,
  GL_PATH_CLIENT_LENGTH_NV                          = 0x907F,
  GL_PATH_DASH_OFFSET_RESET_NV                      = 0x90B4,

  GL_PATH_FILL_MODE_NV                              = 0x9080,
  GL_PATH_FILL_MASK_NV                              = 0x9081,
  GL_PATH_FILL_COVER_MODE_NV                        = 0x9082,
  GL_PATH_STROKE_COVER_MODE_NV                      = 0x9083,
  GL_PATH_STROKE_MASK_NV                            = 0x9084,

  GL_PATH_END_CAPS_NV                               = 0x9076,
  GL_PATH_DASH_CAPS_NV                              = 0x907B,

  GL_COUNT_UP_NV                                    = 0x9088,
  GL_COUNT_DOWN_NV                                  = 0x9089,

  //PRIMARY_COLOR                                   0x8577  // from OpenGL 1.3
  //PRIMARY_COLOR_NV                                0x852C  // from NV_register_combiners
  //SECONDARY_COLOR_NV                              0x852D  // from NV_register_combiners

  GL_PATH_OBJECT_BOUNDING_BOX_NV                    = 0x908A,

  GL_CONVEX_HULL_NV                                 = 0x908B,
  GL_BOUNDING_BOX_NV                                = 0x908D,

  GL_TRANSLATE_X_NV                                 = 0x908E,
  GL_TRANSLATE_Y_NV                                 = 0x908F,
  GL_TRANSLATE_2D_NV                                = 0x9090,
  GL_TRANSLATE_3D_NV                                = 0x9091,
  GL_AFFINE_2D_NV                                   = 0x9092,
  GL_AFFINE_3D_NV                                   = 0x9094,
  GL_TRANSPOSE_AFFINE_2D_NV                         = 0x9096,
  GL_TRANSPOSE_AFFINE_3D_NV                         = 0x9098,

  GL_UTF8_NV                                        = 0x909A,
  GL_UTF16_NV                                       = 0x909B,

  GL_BOUNDING_BOX_OF_BOUNDING_BOXES_NV              = 0x909C,

  GL_PATH_COMMAND_COUNT_NV                          = 0x909D,
  GL_PATH_COORD_COUNT_NV                            = 0x909E,
  GL_PATH_DASH_ARRAY_COUNT_NV                       = 0x909F,

  GL_PATH_COMPUTED_LENGTH_NV                        = 0x90A0,

  GL_PATH_FILL_BOUNDING_BOX_NV                      = 0x90A1,
  GL_PATH_STROKE_BOUNDING_BOX_NV                    = 0x90A2,

  GL_SQUARE_NV                                      = 0x90A3,
  GL_ROUND_NV                                       = 0x90A4,
  GL_TRIANGULAR_NV                                  = 0x90A5,

  GL_BEVEL_NV                                       = 0x90A6,
  GL_MITER_REVERT_NV                                = 0x90A7,
  GL_MITER_TRUNCATE_NV                              = 0x90A8,

  GL_MOVE_TO_RESETS_NV                              = 0x90B5,
  GL_MOVE_TO_CONTINUES_NV                           = 0x90B6,

  GL_PATH_ERROR_POSITION_NV                         = 0x90AB,
  GL_PATH_FOG_GEN_MODE_NV                           = 0x90AC,

  GL_PATH_STENCIL_FUNC_NV                           = 0x90B7,
  GL_PATH_STENCIL_REF_NV                            = 0x90B8,
  GL_PATH_STENCIL_VALUE_MASK_NV                     = 0x90B9,

  GL_PATH_STENCIL_DEPTH_OFFSET_FACTOR_NV            = 0x90BD,
  GL_PATH_STENCIL_DEPTH_OFFSET_UNITS_NV             = 0x90BE,

  GL_PATH_COVER_DEPTH_FUNC_NV                       = 0x90BF,

  GL_ACCUM_ADJACENT_PAIRS_NV                        = 0x90AD,
  GL_ADJACENT_PAIRS_NV                              = 0x90AE,
  GL_FIRST_TO_REST_NV                               = 0x90AF,
  GL_PATH_GEN_MODE_NV                               = 0x90B0,
  GL_PATH_GEN_COEFF_NV                              = 0x90B1,
  GL_PATH_GEN_COLOR_FORMAT_NV                       = 0x90B2,
  GL_PATH_GEN_COMPONENTS_NV                         = 0x90B3,

};


enum Mask_FontStyle {

  GL_BOLD_BIT_NV                                    = 0x01,
  GL_ITALIC_BIT_NV                                  = 0x02,
  
};  
  
enum Mask_PathMetrics {  
  // per-glyph metrics
  GL_GLYPH_WIDTH_BIT_NV                             = 0x01,
  GL_GLYPH_HEIGHT_BIT_NV                            = 0x02,
  GL_GLYPH_HORIZONTAL_BEARING_X_BIT_NV              = 0x04,
  GL_GLYPH_HORIZONTAL_BEARING_Y_BIT_NV              = 0x08,
  GL_GLYPH_HORIZONTAL_BEARING_ADVANCE_BIT_NV        = 0x10,
  GL_GLYPH_VERTICAL_BEARING_X_BIT_NV                = 0x20,
  GL_GLYPH_VERTICAL_BEARING_Y_BIT_NV                = 0x40,
  GL_GLYPH_VERTICAL_BEARING_ADVANCE_BIT_NV          = 0x80,
  GL_GLYPH_HAS_KERNING_NV                           = 0x100,

  // per-font face metrics
  GL_FONT_X_MIN_BOUNDS_NV                           = 0x00010000,
  GL_FONT_Y_MIN_BOUNDS_NV                           = 0x00020000,
  GL_FONT_X_MAX_BOUNDS_NV                           = 0x00040000,
  GL_FONT_Y_MAX_BOUNDS_NV                           = 0x00080000,
  GL_FONT_UNITS_PER_EM_NV                           = 0x00100000,
  GL_FONT_ASCENDER_NV                               = 0x00200000,
  GL_FONT_DESCENDER_NV                              = 0x00400000,
  GL_FONT_HEIGHT_NV                                 = 0x00800000,
  GL_FONT_MAX_ADVANCE_WIDTH_NV                      = 0x01000000,
  GL_FONT_MAX_ADVANCE_HEIGHT_NV                     = 0x02000000,
  GL_FONT_UNDERLINE_POSITION_NV                     = 0x04000000,
  GL_FONT_UNDERLINE_THICKNESS_NV                    = 0x08000000,
  GL_FONT_HAS_KERNING_NV                            = 0x10000000,

};

        
void glPathCommandsNV(GLuint path, GLsizei numCommands, const GLubyte *commands, GLsizei numCoords, GLenum[Main] coordType, const void *coords);
void glPathCoordsNV(GLuint path, GLsizei numCoords, GLenum[Main] coordType, const void *coords);

void glPathSubCommandsNV(GLuint path, GLsizei commandStart, GLsizei commandsToDelete, GLsizei numCommands, const GLubyte *commands, GLsizei numCoords, GLenum[Main] coordType, const void *coords);
void glPathSubCoordsNV(GLuint path,GLsizei coordStart,GLsizei numCoords, GLenum[Main] coordType,const void *coords);

void glPathStringNV(GLuint path, GLenum[Main] format,GLsizei length, const void *pathString);

void glPathGlyphsNV(GLuint firstPathName,GLenum[Main] fontTarget,const void *fontName,GLbitfield[Mask_FontStyle] fontStyle,GLsizei numGlyphs, GLenum[Main] type,const void *charcodes,GLenum[Main] handleMissingGlyphs,GLuint pathParameterTemplate,GLfloat emScale);
void glPathGlyphRangeNV(GLuint firstPathName,GLenum[Main] fontTarget,const void *fontName,GLbitfield[Mask_FontStyle] fontStyle,GLuint firstGlyph,GLsizei numGlyphs,GLenum[Main] handleMissingGlyphs,GLuint pathParameterTemplate,GLfloat emScale);

void glWeightPathsNV(GLuint resultPath,GLsizei numPaths,const GLuint * paths, const GLfloat *weights);
void glCopyPathNV(GLuint resultPath, GLuint srcPath);
void glInterpolatePathsNV(GLuint resultPath,GLuint pathA, GLuint pathB,GLfloat weight);
void glTransformPathNV(GLuint resultPath,GLuint srcPath, GLenum[Main] transformType,const GLfloat *transformValues);

void glPathParameterivNV(GLuint path, GLenum[Main] pname, const GLint *value);
void glPathParameteriNV(GLuint path, GLenum[Main] pname, GLint value);
void glPathParameterfvNV(GLuint path, GLenum[Main] pname, const GLfloat *value);
void glPathParameterfNV(GLuint path, GLenum[Main] pname, GLfloat value);

void glPathDashArrayNV(GLuint path,GLsizei dashCount, const GLfloat *dashArray);

GLuint glGenPathsNV(GLsizei range);
void glDeletePathsNV(GLuint path, GLsizei range);
GLboolean glIsPathNV(GLuint path);

void glPathStencilFuncNV(GLenum[Main] func, GLint ref, GLuint mask);
void glPathStencilDepthOffsetNV(GLfloat factor, GLint units);

void glStencilFillPathNV(GLuint path,GLenum[Main] fillMode, GLuint mask);
void glStencilStrokePathNV(GLuint path,GLint reference, GLuint mask);
void glStencilFillPathInstancedNV(GLsizei numPaths,GLenum[Main] pathNameType, const void *paths,GLuint pathBase,GLenum[Main] fillMode, GLuint mask,GLenum[Main] transformType,const GLfloat *transformValues);
void glStencilStrokePathInstancedNV(GLsizei numPaths,GLenum[Main] pathNameType, const void *paths,GLuint pathBase,GLint reference, GLuint mask,GLenum[Main] transformType,const GLfloat *transformValues);

void glPathCoverDepthFuncNV(GLenum[Main] zfunc);

void glPathColorGenNV(GLenum[Main] color,GLenum[Main] genMode,GLenum[Main] colorFormat, const GLfloat *coeffs);
void glPathTexGenNV(GLenum[Main] texCoordSet,GLenum[Main] genMode,GLint components, const GLfloat *coeffs);
void glPathFogGenNV(GLenum[Main] genMode);

void glCoverFillPathNV(GLuint path, GLenum[Main] coverMode);
void glCoverStrokePathNV(GLuint name, GLenum[Main] coverMode);
void glCoverFillPathInstancedNV(GLsizei numPaths,GLenum[Main] pathNameType, const void *paths,GLuint pathBase,GLenum[Main] coverMode,GLenum[Main] transformType,const GLfloat *transformValues);

void glCoverStrokePathInstancedNV(GLsizei numPaths,GLenum[Main] pathNameType, const void *paths,GLuint pathBase,GLenum[Main] coverMode,GLenum[Main] transformType,const GLfloat *transformValues);

void glGetPathParameterivNV(GLuint name, GLenum[Main] param, GLint *value);
void glGetPathParameterfvNV(GLuint name, GLenum[Main] param, GLfloat *value);

void glGetPathCommandsNV(GLuint name, GLubyte *commands);
void glGetPathCoordsNV(GLuint name, GLfloat *coords);
void glGetPathDashArrayNV(GLuint name, GLfloat *dashArray);

void glGetPathMetricsNV(GLbitfield[Mask_PathMetrics] metricQueryMask,GLsizei numPaths,GLenum[Main] pathNameType, const void *paths,GLuint pathBase,GLsizei stride,GLfloat *metrics);
void glGetPathMetricRangeNV(GLbitfield[Mask_PathMetrics] metricQueryMask,GLuint fistPathName,GLsizei numPaths,GLsizei stride,GLfloat *metrics);

void glGetPathSpacingNV(GLenum[Main] pathListMode,GLsizei numPaths,GLenum[Main] pathNameType, const void *paths,GLuint pathBase,GLfloat advanceScale,GLfloat kerningScale,GLenum[Main] transformType,GLfloat *returnedSpacing);

void glGetPathColorGenivNV(GLenum[Main] color, GLenum[Main] pname, GLint *value);
void glGetPathColorGenfvNV(GLenum[Main] color, GLenum[Main] pname, GLfloat *value);
void glGetPathTexGenivNV(GLenum[Main] texCoordSet, GLenum[Main] pname, GLint *value);
void glGetPathTexGenfvNV(GLenum[Main] texCoordSet, GLenum[Main] pname, GLfloat *value);

GLboolean glIsPointInFillPathNV(GLuint path,GLuint mask, GLfloat x, GLfloat y);
GLboolean glIsPointInStrokePathNV(GLuint path,GLfloat x, GLfloat y);

GLfloat glGetPathLengthNV(GLuint path,GLsizei startSegment, GLsizei numSegments);

GLboolean glPointAlongPathNV(GLuint path,GLsizei startSegment, GLsizei numSegments,GLfloat distance,GLfloat *x, GLfloat *y,GLfloat *tangentX, GLfloat *tangentY);

