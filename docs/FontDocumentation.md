# Font
Exports `sf::Font` API to Lua. Font allows you to load and manipulate character fonts.  

### Methods
`Font.new()`: Creates a new empty font object.  
`Font.new(other: Font)`: Creates a copy of given font object.  
`font:loadFromFile(filename: str)`: Loads the font from the given file. Returns true if the loading was successfull. Returns false otherwise.  
`font:getFontFamily()`: Returns the name of the font family.  
`font:getGlyph(codePoint: integer, characterSize: integer, bold: boolean, outlineThickness=0)`: Returns a glyph from the font.  
`font:getKenning(first: integer, second: integer, characterSize: integer)`: Get the kerning offset of two glyphs.  
`font:getLineSpacing(charcterSize: integer)`: Get the line spacing.  
`font:getUnderlinePosition(characterSize: integer)`: Get the position of the underline.  
`font:getUnderlineThickness(characterSize: integer)`: Get the thickness of the underline.  