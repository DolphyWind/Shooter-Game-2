# CircleShape
Exports AttachableObject\<sf::CircleShape\> API to Lua. An attachable object is an object that can be attached to an entity. When an attachable object is attached to an entity, the origin of its coordinate system becomes that entity's global position.

### Methods
`CircleShape.new()`: Creates an empty circle shape with radius 0  
`CircleShape.new(radius)`: Creates a circle shape with given radius.  
`CircleShape.new(radius, pointCount: integer)`: Creates a circle shape with given radius and point count.  
`cshape:setRadius(newRadius)`: Sets `cshape`'s radius to newRadius.  
`cshape:getRadius()`: Returns `cshape`'s radius.  
`cshape:getPointCount()`: Returns the number of points used to compose the `cshape`.  
`cshape:getPoint(index: integer)`: Returns a point of the circle that corresponds to given index.  
`cshape:setTexture(texture: Texture)`: Sets the texture of `cshape`.  
`cshape:setTexture(texture: Texture, resetRect: bool)`: Set the texture of `cshape`.  
`cshape:setTextureRect(rect: IntRect)`: Sets the sub-rectangle of the texture that the `cshape` will display.  
`cshape:setFillColor(color: Color)`: Sets the fill color of the `cshape`.  
`cshape:setOutlineColor(color: Color)`: Sets the outline color of `cshape`.  
`cshape:setOutlineThickness(color: Color)`: Sets the outline thickness of `cshape`.  
`cshape:getTexture()`: Returns the texture of `cshape`.  
`cshape:getTextureRect()`: Returns the sub-rectangle of the texture displayed by the `cshape`.  
`cshape:getFillColor()`: Returns the fill color of `cshape`.  
`cshape:getOutlineColor()`: Returns the outline color of `cshape`.  
`cshape:getOutlineThickness()`: Returns the outline thickness of `cshape`.  
`cshape:getLocalBounds()`: Returns the local bounding rectangle of `cshape` as FloatRect.  
`cshape:getGlobalBounds()`: Returns the global bounding rectangle of `cshape` as FloatRect.  
`cshape:setPosition(x, y)`: Sets the position of the `cshape`.  
`cshape:setPosition(newPos: Vector2)`: Set the position of the `cshape`.  
`cshape:setRotation(angle)`: Sets the rotation of `cshape`.  
`cshape:setScale(x, y)`: Sets the scale of `cshape`.  
`cshape:setScale(newScale: Vector2)`: Set the scale of `cshape`.  
`cshape:setOrigin(x, y)`: Sets the origin of `cshape`.  
`cshape:setOrigin(newOrigin: Vector2)`: Sets the origin of `cshape`.  
`cshape:getLocalPosition()`: Returns the local position (Relative to attached entity) of `cshape` as Vector2.  
`cshape:getGlobalPosition()`: Returns the local position (Relative to world) of `cshape` as Vector2.  
`cshape:getRotation()`: Returns the rotation of `cshape`.  
`cshape:getScale()`: Returns the scale of `cshape` as Vector2.  
`cshape:getOrigin()`: Returns the origin point of `cshape` as Vector2.  
`cshape:move(offsetX, offsetY)`: Moves `cshape` by given offset.  
`cshape:move(offset: Vector2)`: Moves `cshape` by given offset.  
`cshape:rotate(angle)`: Rotates `cshape` by given angle.  
`cshape:scale(factorX, factorY)`: Scales `cshape` by given factor.  
`cshape:scale(factor: Vector2)`: Scales `cshape` by given factor.  
`cshape:getTransform()`: Get the combined transform of the `cshape`.  
`cshape:getInverseTransform()`: Get the inverse transform of the `cshape`.  
`cshape:attachTo(entity: Entity)`: Attaches `cshape` to given entity.  