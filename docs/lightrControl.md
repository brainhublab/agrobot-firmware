# Light control

## Data model

- **lightmode** - control the behavior of the lights
  - `type` : int 
  - `minimum value` : 0
  - `maximum value` : 3
  - `error value`: -1
  - `units`: modes `<0 = off, 1 = solar, 2 = on timer, 3 = continuos>`

- **target_brightness** - represents the maximum brightness 
  - `type` : int 
  - `minimum value` : 0
  - `maximum value` : 100
  - `error value`: -1
  - `units` : %

- **current_time** - datetime needed for modes 
  - `type` : datetime 
  - `minimum value` : -
  - `maximum value` : -
  - `error value`: -1
  - `units` : `dd:MM:yyyy:H:M:S`

- **clock** - variable that says to the microcontroller which clock to use `internal` or `external`
  - `type` : boolean 
  - `minimum value` : 0
  - `maximum value` : 1
  - `error value`: -1
  - `units` : flag

- **light_intensity_map** - represents the brightness map in solar mode
  - `type` : array[24] 
  - `minimum value` : 0
  - `maximum value` : 100
  - `error value`: arr[] = {0}
  - `units` : %

- **current_brightness** - the current brightness
  - `type` : int 
  - `minimum value` : 0
  - `maximum value` : 100
  - `error value`: -1
  - `units` : %