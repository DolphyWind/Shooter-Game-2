# Glyph
Exports `sf::Glyph` API to Lua. `sf::Glyph` is a structure that describes a glyph.  

### Operators
`==`: Checks whether the two glyphs are equal.  

### Methods
`Glyph.new()`: Creates a new glyph object.  

### Fields
`advance`: Offset to move horizontally to the next character.  
`bounds`: Bounding rectangle of the glyph as FloatRect, in coordinates relative to the baseline.  
`textureRect`: Texture coordinates of the glyph inside the font's texture as IntRect.