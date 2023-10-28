# RectangleShape
Exports `AttachableObject<sf::RectangleShape>` API to Lua. An attachable object is an object that can be attached to an entity. When an attachable object is attached to an entity, the origin of its coordinate system becomes that entity's global position.

### Methods
`RectangleShape.new()`: Creates an empty rectangle shape with size (0, 0)  
`RectangleShape.new(size: Vector2)`: Creates a rectangle shape with given size.  
`rshape:setSize(newSize: Vector2)`: Sets `rshape`'s size to newSize.  
`rshape:getSize()`: Returns `rshape`'s size as Vector2.  
`rshape:getPointCount()`: Returns the number of points used to compose the `rshape`.  
`rshape:getPoint(index: integer)`: Returns a point of the `rshape` that corresponds to given index.  
`rshape:setTexture(texture: Texture)`: Sets the texture of `rshape`.  
`rshape:setTexture(texture: Texture, resetRect: bool)`: Set the texture of `rshape`.  
`rshape:setTextureRect(rect: IntRect)`: Sets the sub-rectangle of the texture that the `rshape` will display.  
`rshape:setFillColor(color: Color)`: Sets the fill color of the `rshape`.  
`rshape:setOutlineColor(color: Color)`: Sets the outline color of `rshape`.  
`rshape:setOutlineThickness(color: Color)`: Sets the outline thickness of `rshape`.  
`rshape:getTexture()`: Returns the texture of `rshape`.  
`rshape:getTextureRect()`: Returns the sub-rectangle of the texture displayed by the `rshape`.  
`rshape:getFillColor()`: Returns the fill color of `rshape`.  
`rshape:getOutlineColor()`: Returns the outline color of `rshape`.  
`rshape:getOutlineThickness()`: Returns the outline thickness of `rshape`.  
`rshape:getLocalBounds()`: Returns the local bounding rectangle of `rshape` as FloatRect.  
`rshape:getGlobalBounds()`: Returns the global bounding rectangle of `rshape` as FloatRect.  
`rshape:setPosition(x, y)`: Sets the position of the `rshape`.  
`rshape:setPosition(newPos: Vector2)`: Set the position of the `rshape`.  
`rshape:setRotation(angle)`: Sets the rotation of `rshape`.  
`rshape:setScale(x, y)`: Sets the scale of `rshape`.  
`rshape:setScale(newScale: Vector2)`: Set the scale of `rshape`.  
`rshape:setOrigin(x, y)`: Sets the origin of `rshape`.  
`rshape:setOrigin(newOrigin: Vector2)`: Sets the origin of `rshape`.  
`rshape:getLocalPosition()`: Returns the local position (Relative to attached entity) of `rshape` as Vector2.  
`rshape:getGlobalPosition()`: Returns the local position (Relative to world) of `rshape` as Vector2.  
`rshape:getRotation()`: Returns the rotation of `rshape`.  
`rshape:getScale()`: Returns the scale of `rshape` as Vector2.  
`rshape:getOrigin()`: Returns the origin point of `rshape` as Vector2.  
`rshape:move(offsetX, offsetY)`: Moves `rshape` by given offset.  
`rshape:move(offset: Vector2)`: Moves `rshape` by given offset.  
`rshape:rotate(angle)`: Rotates `rshape` by given angle.  
`rshape:scale(factorX, factorY)`: Scales `rshape` by given factor.  
`rshape:scale(factor: Vector2)`: Scales `rshape` by given factor.  
`rshape:getTransform()`: Get the combined transform of the `rshape`.  
`rshape:getInverseTransform()`: Get the inverse transform of the `rshape`.  
`rshape:attachTo(entity: Entity)`: Attaches `rshape` to given entity.  