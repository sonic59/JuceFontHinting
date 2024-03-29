/*
  ==============================================================================

   This file is part of the JUCE library - "Jules' Utility Class Extensions"
   Copyright 2004-11 by Raw Material Software Ltd.

  ------------------------------------------------------------------------------

   JUCE can be redistributed and/or modified under the terms of the GNU General
   Public License (Version 2), as published by the Free Software Foundation.
   A copy of the license is included in the JUCE distribution, or can be found
   online at www.gnu.org/licenses.

   JUCE is distributed in the hope that it will be useful, but WITHOUT ANY
   WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
   A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

  ------------------------------------------------------------------------------

   To release a closed-source product which uses JUCE, commercial licenses are
   available: visit www.rawmaterialsoftware.com/juce for more information.

  ==============================================================================
*/

namespace FontStyleHelpers
{
    static const char* getStyleName (const bool bold,
                                     const bool italic) noexcept
    {
        if (bold && ! italic)   return "Bold";
        if (italic && ! bold)   return "Italic";
        if (bold && italic)     return "Bold Italic";
        return "Regular";
    }

    static bool isBold (const String& style) noexcept
    {
        return style.containsWholeWordIgnoreCase ("Bold");
    }

    static bool isItalic (const String& style) noexcept
    {
        return style.containsWholeWordIgnoreCase ("Italic")
            || style.containsWholeWordIgnoreCase ("Oblique");
    }

    static bool isPlaceholderFamilyName (const String& family)
    {
        return family == Font::getDefaultSansSerifFontName()
            || family == Font::getDefaultSerifFontName()
            || family == Font::getDefaultMonospacedFontName();
    }

    static String getConcreteFamilyNameFromPlaceholder (const String& family)
    {
        const Font f (family, Font::getDefaultStyle(), 15.0f);
        return Font::getDefaultTypefaceForFont (f)->getName();
    }
}

//==============================================================================
Typeface::Typeface (const String& name_, const String& style_) noexcept
    : name (name_), style (style_)
{
}

Typeface::~Typeface()
{
}

Typeface::Ptr Typeface::getFallbackTypeface()
{
    const Font fallbackFont (Font::getFallbackFontName(), Font::getFallbackFontStyle(), 10.0f);
    return fallbackFont.getTypeface();
}

EdgeTable* Typeface::getEdgeTableForGlyph (int glyphNumber, const AffineTransform& transform)
{
    Path path;

    if (getOutlineForGlyph (glyphNumber, path) && ! path.isEmpty())
        return new EdgeTable (path.getBoundsTransformed (transform).getSmallestIntegerContainer().expanded (1, 0),
                              path, transform);

    return nullptr;
}

EdgeTable* Typeface::getEdgeTableForGlyph (float fontHeight, int glyphNumber, const AffineTransform& transform)
{
    return getEdgeTableForGlyph (glyphNumber, transform);
}
