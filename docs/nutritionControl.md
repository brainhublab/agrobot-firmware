# Nutrition control 

## Data model

- **dispensers** - represents the pumps that are attached to the endnode
  - `type` : array[4] 
  - `minimum value` : -
  - `maximum value` : -
  - `error value`: arr[] = {0}
  - `units` : array of dispensers 

- **nutrition_mode** - represents the mode of one dispenser
  - `type` : int 
  - `minimum value` : 0
  - `maximum value` : 2
  - `error value`: -1
  - `units`: modes `<0 = off, 1 = periodic, 2 = relative>`

- **target_concentration** - target concentration dpending on what we measure, will be used only on relative mode.
  - `type` : float 
  - `minimum value` : 0
  - `maximum value` : relative
  - `error value`: -1
  - `units` : relative

- **current_concentration** - geter for curent value
  - `type` : float 
  - `minimum value` : 0
  - `maximum value` : relative
  - `error value`: -1
  - `units` : relative