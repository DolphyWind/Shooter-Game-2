# Text
Exports `AttachableObject<sf::Text>` API to Lua. An attachable object is an object that can be attached to an entity. When an attachable object is attached to an entity, the origin of its coordinate system becomes that entity's global position.  

### Methods
`Text.new()`: Creates an empty text object.  
`Text.new(str: string, font: Font)`: Creates a text with given text and font.  
`Text.new(str: string, font: Font, charsize: integer)`: Creates a text with given text, font and character size.  
`text:setString(str: string)`: Sets the string of the text.  
`text:setFont(font: Font)`: Sets the font of the text.  
`text:setCharacterSize(charsize: integer)`: Sets the character size of the text.  
`text:setLineSpacing(spacingFactor)`: Sets the line spacing of the text.  
`text:setLetterSpacing(spacingFactor)`: Sets the letter spacing of the text.  
`text:setStyle(style: integer)`: Sets the style of the text.  
`text:getString()`: Returns the string of text.  
`text:getFont()`: Returns the font of text.  
`text:getCharacterSize()`: Returns the character size of text.  
`text:getLetterSpacing()`: Returns the letter spacing of text.  
`text:getLineSpacing()`: Returns the line spacing of text.  
`text:getStyle()`: Returns the style of text.  
`text:findCharacterPos(intex: integer)`: Returns the position of the character at given index as Vector2.  
`text:setFillColor(color: Color)`: Sets the fill color of the `text`.  
`text:setOutlineColor(color: Color)`: Sets the outline color of `text`.  
`text:setOutlineThickness(color: Color)`: Sets the outline thickness of `text`.  
`text:getFillColor()`: Returns the fill color of `text`.  
`text:getOutlineColor()`: Returns the outline color of `text`.  
`text:getOutlineThickness()`: Returns the outline thickness of `text`.  
`text:getLocalBounds()`: Returns the local bounding rectangle of `text` as FloatRect.  
`text:getGlobalBounds()`: Returns the global bounding rectangle of `text` as FloatRect.  
`text:setPosition(x, y)`: Sets the position of the `text`.  
`text:setPosition(newPos: Vector2)`: Set the position of the `text`.  
`text:setRotation(angle)`: Sets the rotation of `text`.  
`text:setScale(x, y)`: Sets the scale of `text`.  
`text:setScale(newScale: Vector2)`: Set the scale of `text`.  
`text:setOrigin(x, y)`: Sets the origin of `text`.  
`text:setOrigin(newOrigin: Vector2)`: Sets the origin of `text`.  
`text:getLocalPosition()`: Returns the local position (Relative to attached entity) of `text` as Vector2.  
`text:getGlobalPosition()`: Returns the local position (Relative to world) of `text` as Vector2.  
`text:getRotation()`: Returns the rotation of `text`.  
`text:getScale()`: Returns the scale of `text` as Vector2.  
`text:getOrigin()`: Returns the origin point of `text` as Vector2.  
`text:move(offsetX, offsetY)`: Moves `text` by given offset.  
`text:move(offset: Vector2)`: Moves `text` by given offset.  
`text:rotate(angle)`: Rotates `text` by given angle.  
`text:scale(factorX, factorY)`: Scales `text` by given factor.  
`text:scale(factor: Vector2)`: Scales `text` by given factor.  
`text:getTransform()`: Get the combined transform of the `text`.  
`text:getInverseTransform()`: Get the inverse transform of the `text`.  
`text:attachTo(entity: Entity)`: Attaches `text` to given entity.  

### Static Members
`Text.Style_Regular`: An integer representing regular style.    
`Text.Style_Bold`: An integer representing bold style.    
`Text.Style_Italic`: An integer representing italic style.    
`Text.Style_Underlined`: An integer representing underlined style.    
`Text.Style_StrikeThrough`: An integer representing strikethrough style.    