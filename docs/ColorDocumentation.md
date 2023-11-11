# Color
Exports `sf::Color` API to lua. It represents rgba colors.

### Fields
`r`: R component of the color.  
`g`: G component of the color.  
`b`: B component of the color.  
`a`: A component of the color.  

### Operators
`+`: Adds two colors component-wise.  
`-`: Substracts two colors component-wise.  
`*`: Scales the color by a scale factor.  
`/`: Shrinks the color by a shrinking factor.  
`==`: Compares two colors.  

### Methods
`Color.new()`: Creates an empty color. RGBA(0, 0, 0, 0)  
`Color.new(other: Color)`: Creates a new Color that has the same components with the given color  
`Color.new(hex: integer)`: Creates a new Color by treating given integer as a hex representation of a color.  
`Color.new(r, g, b)`: Creates a new Color by given r, g, b values. Sets a component to 255.  
`Color.new(r, g, b, a)`: Creates a new Color by given r, g, b, a values.  
`color:toHex()`: Returns the hex representation of `color`.  
`color:toGrayScale()`: Creates a gray scale version of `color`.  
`color:mixColors(other: Color)`: Mixes `color` and `other` and returns it. Finds the average of each component.  