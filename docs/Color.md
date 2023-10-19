# Color
Color exports SFML's sf::Color API to lua. It represents rgba colors.

### Fields
`r`: R component of the color.  
`g`: G component of the color.  
`b`: B component of the color.  
`a`: A component of the color.  

### Methods
`Color.new()`: Creates an empty color. RGBA(0, 0, 0, 0)  
`Color.new(other)`: Creates a new Color that has the same components with the given color  
`Color.new(hex)`: Creates a new Color by treating given integer as a hex representation of a color.  
`Color.new(r, g, b)`: Creates a new Color by given r, g, b values. Sets a component to 255.  
`Color.new(r, g, b, a)`: Creates a new Color by given r, g, b, a values.  
`color:toHex()`: Returns the hex representation of `color`.  
`color:toGrayScale()`: Creates a gray scale version of `color`.  
`color:mixColors(other)`: Mixes `color` and `other` and returns it. Finds the average of each component.  