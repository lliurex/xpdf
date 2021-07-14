//========================================================================
//
// config.h
//
// Copyright 1996-2014 Glyph & Cog, LLC
// Copyright 2018-2020 Adam Sampson <ats@offog.org>
//
//========================================================================

#ifndef CONFIG_H
#define CONFIG_H

#include <goo/GooString.h>
#include <memory>
#include <string>

//------------------------------------------------------------------------
// version
//------------------------------------------------------------------------

// xpdf version
#define xpdfVersion          "3.04"
#define xpdfVersionNum       3.04
#define xpdfMajorVersion     3
#define xpdfMinorVersion     4
#define xpdfUpdateVersion    0
#define xpdfMajorVersionStr  "3"
#define xpdfMinorVersionStr  "4"
#define xpdfUpdateVersionStr "0"

// copyright notice
#undef xpdfCopyright
#define xpdfCopyright "Copyright 1996-2014 Glyph & Cog, LLC\n" \
    "Copyright 2014-2020 xpopple contributors"

//------------------------------------------------------------------------
// paper size
//------------------------------------------------------------------------

// default paper size (in points) for PostScript output
#ifdef A4_PAPER
#define defPaperWidth  595    // ISO A4 (210x297 mm)
#define defPaperHeight 842
#else
#define defPaperWidth  612    // American letter (8.5x11")
#define defPaperHeight 792
#endif

//------------------------------------------------------------------------
// config file (xpdfrc) path
//------------------------------------------------------------------------

// user config file name, relative to the user's home directory
#define xpdfUserConfigFile ".xpdfrc"

// system config file name (set via the configure script)
#define xpdfSysConfigFile SYSTEM_XPDFRC

//------------------------------------------------------------------------
// X-related constants
//------------------------------------------------------------------------

// default maximum size of color cube to allocate
#define defaultRGBCube 5

//------------------------------------------------------------------------
// Poppler backwards compatibility
//------------------------------------------------------------------------

// Poppler has fixed various const correctness problems in the xpdf API;
// 0.64.0 in particular introduced a number of new constraints. In many
// cases xpopple's code can be written to work either way, but where
// this isn't possible, PCONST means "const after 0.64.0".
#ifdef POPPLER_64_CONST_API
#define PCONST const
#else
#define PCONST
#endif

// 0.72.0 removed GooString::getCString.
#ifdef GOOSTRING_NO_GETCSTRING
#define getCString c_str
#endif

// From 0.86.0, some methods started returning std::string rather than
// (non-owning) GooString *. toString adapts either to std::string.
static inline std::string toString(const std::string &s) {
  return s;
}
static inline std::string toString(PCONST GooString *s) {
  return std::string(s->getCString(), s->getLength());
}

// Make an owning GooString pointer or unique_ptr from a std::string.
static inline GooString *makeGooString(const std::string &s) {
  return new GooString(s.c_str(), s.size());
}
static inline GooString *makeGooString(const std::string *s) {
  if (!s) {
    return NULL;
  }
  return makeGooString(*s);
}
static inline std::unique_ptr<GooString>
makeGooStringPtr(const std::string &s) {
  return std::unique_ptr<GooString>(makeGooString(s));
}
static inline std::unique_ptr<GooString>
makeGooStringPtr(const std::string *s) {
  return std::unique_ptr<GooString>(makeGooString(s));
}

#endif
