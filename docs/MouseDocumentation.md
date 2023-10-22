# Mouse
Exports `sfex::Mouse` API to Lua. Allows reading mouse input from user.

### Methods
`Mouse.getButton(button: integer)`: Returns true if the given button is being pressed. Returns false otherwise.  
`Mouse.getButtonDown(button: integer)`: Returns true if the given button is pressed in the current frame. Returns false otherwise.  
`Mouse.getButtoUp(button: integer)`: Returns true if the given button is released in the current frame. Returns false otherwise.  
`Mouse.getPosition()`: Returns the mouse position as Vector2.  
`Mouse.getPosition(window: RenderWindow)`: Returns the mouse position relative to given window.  
`Mouse.setPosition(position: Vector2)`: Sets the mouse position to given position.  
`Mouse.setPosition(position: Vector2, window: RenderWindow)`: Sets the mouse position to given position relative to given window.  

### Static Members
`Mouse.left`: Left mouse button.  
`Mouse.middle`: Middle mouse button.  
`Mouse.right`: Right mouse button.  
`Mouse.xbutton1`: The first extra mouse button.  
`Mouse.xbutton2`: The second extra mouse button.  