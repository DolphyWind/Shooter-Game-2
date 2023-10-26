# ContextSettings
Exports `sf::ContextSettings` API to Lua. ContextSettings is the structure defining the settings of the OpenGL context attached to a window.  

### Fields
`depthBits`: Bits of the depth buffer.  
`stencilBits`: Bits of the stencil buffer.  
`antialiasingLevel`: Level of antialiasing.  
`majorVersion`: Major number of the context version to create.  
`minorVersion`: Minor number of the context version to create.  
`attributeFlags`: The attribute flags to create the context with.  
`sRgbCapable`: Whether the context framebuffer is sRGB capable.  

### Static Fields
`Attribute_Default`: Non-debug, compatibility context.  
`Attribute_Core`: Core attribute.  
`Attribute_Debug`: Debug attribute.  

### Methods
`ContextSettings.new(depth: integer=0, stencil: integer=0, antialiasing: integer=0, major: integer=0, minor: integer=0, attributes: integer=ContextSettings.Attribute_Default, srgb: bool=false)`: Creates new ContextSettings object.  