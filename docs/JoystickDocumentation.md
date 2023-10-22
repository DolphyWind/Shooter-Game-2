# Joystick
Exports `sfex::Keyboard` API to Lua. Allows reading joystick input from user.  

### Methods
`Joystick.isConnected(joystickId: integer)`: Returns true if the joystick with given id is connected. Returns false otherwise.  
`Joystick.getButtonCount(joystickId: integer)`: Returns the number of buttons on the joystick with given id.  
`Joystick.hasAxis(joystickId: integer, axis: integer)`: Returns true if the joystick with given id has the given axis.  
`Joystick.getButton(joystickId: integer, buttonId)`: Returns true if the given button is being pressed on the given joystick. Returns false otherwise.  
`Joystick.getButtonDown(joystickId: integer, buttonId)`: Returns true if the given button is pressed in the current frame on the given joystick. Returns false otherwise.  
`Joystick.getButtonUp(joystickId: integer, buttonId)`: Returns true if the given button is released in the current frame on the given joystick. Returns false otherwise.  
`Joystick.getAxisPosition(axis: integer)`: Returns the position of the given axis between `-1` and `1`.  
`Joystick.getAxisPosition(axis: integer, minSensitivity)`: Returns the position of the given axis between `-1` and `1`. It ignores the values between `-minSensitivity` and `minSenitivity`.  

### Static Members
`Joystick.Axis_X`: X axis on the joystick.  
`Joystick.Axis_Y`: Y axis on the joystick.  
`Joystick.Axis_Z`: Z axis on the joystick.  
`Joystick.Axis_R`: R axis on the joystick.  
`Joystick.Axis_U`: U axis on the joystick.  
`Joystick.Axis_V`: V axis on the joystick.  
`Joystick.AxisPov_X`: X axis of point-of-view hat on the joystick.  
`Joystick.AxisPov_Y`: Y axis of point-of-view hat on the joystick.  

`Joystick.Count`: The maximum number of supported joysticks.  
`Joystick.AxisCount`: The maximum number of supported axes.  
`Joystick.ButtonCount`: The maximum number of supported buttons.  