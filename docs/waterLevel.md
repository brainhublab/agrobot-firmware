# Water level end node

## Data model


- **valve** - indicates how many percent the  valve is open
  - `type` : int 
  - `minimum value` : 0
  - `maximum value` : 100
  - `error value`: -1
  - `units`: %
  
- **level_target** - water level target for auto control
  - `type` : int 
  - `minimum value` : 0
  - `maximum value` : 100
  - `error value`: -1
  - `units` : %

- **PID** - values for tunning pid, they will be automaticaly set on callibration but can be tuned manualy.
  - **kp** - is proportional to the current value.
    - `type` : float 
    - `minimum value` : 0
    - `maximum value` : relative
    - `error value`: -1 
    - `units` : coeficient

  - **ki** - accounts for past values.
    - `type` : float 
    - `minimum value` : 0
    - `maximum value` : relative
    - `error value`: -1 
    - `units` : coeficient

  - **kd** - is a best estimate.
    - `type` : float 
    - `minimum value` : 0
    - `maximum value` : relative
    - `error value`: -1 
    - `units` : coeficient

If the flow sensors are attached on the output there will be twho more data variables that are the same as datatype

- **flow_in / flow_out** - represents the sensor that measures fluid flow on input of the tank and on the output
  - `type` : float 
  - `minimum value` : 0
  - `maximum value` : relative
  - `error value`: -1
  - `units`: l/h,