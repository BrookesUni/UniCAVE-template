#define GLI_INCLUDE_GL_SGIX_RESAMPLE

enum Main {

  // Unsure about this - spec and extension registery differ
  //GL_PACK_RESAMPLE_SGIX       = 0x842E,
  //GL_UNPACK_RESAMPLE_SGIX     = 0x842F,
  //GL_RESAMPLE_REPLICATE_SGIX  = 0x8433,
  //GL_RESAMPLE_ZERO_FILL_SGIX  = 0x8434,

  //GL_PACK_RESAMPLE_SGIX            = 0x842C,
  //GL_UNPACK_RESAMPLE_SGIX          = 0x842D,
  //GL_RESAMPLE_REPLICATE_SGIX       = 0x842E,
  //GL_RESAMPLE_ZERO_FILL_SGIX       = 0x842F,
  GL_RESAMPLE_DECIMATE_SGIX        = 0x8430,

};

