<a id="library"></a>

# gbj\_appdefer
This is an application library for PlatformIO projects. It encapsulates the functionality of `postponed action`. The encapsulation provides following advantages:
* Functionality is hidden from the main sketch.
* The library follows the principle `separation of concerns`.
* The library is reusable for various projects without need to code timers.
* Update in library is valid for all involved projects.
* It specifies (inherits from) the parent application library `gbj_appcore`.
* It utilizes funcionality and error handling from the parent class.


## Fundamental functionality
* The library creates internal one-shot timer, which executes input procedure (handler) after provided time interval.
* The defering is useful mainly for postponed reconnecting to wifi or restarting microcontroller from the built-in webserver to give it a chance to redirect to the main webpage and suppress the web browser to repeate that action at its refresh mode.


<a id="dependency"></a>

## Dependency
* **gbj\_appcore**: Parent library for all application libraries loaded from the file `gbj_appcore.h`.
* **gbj\_serial\_debug**: Auxilliary library for debug serial output loaded from the file `gbj_serial_debug.h`. It enables to exclude serial outputs from final compilation.
* **gbj\_timer**: Library for executing internal timer within an instance object loaded from the file `gbj_timer.h`.

#### Arduino platform
* **Arduino.h**: Main include file for the Arduino SDK.
* **inttypes.h**: Integer type conversions. This header file includes the exact-width integer definitions and extends them with additional facilities provided by the implementation.

#### Espressif platform
* **Arduino.h**: Main include file for the Arduino platform.

#### Particle platform
* **Particle.h**: Includes alternative (C++) data type definitions.


<a id="interface"></a>

## Custom data types
* [Handler](#handler)

## Interface
* [gbj_appdefer()](#gbj_appdefer)
* [run()](#run)
* [start()](#start)
* [getPeriod()](#getPeriod)


<a id="handler"></a>

## Handler

#### Description
The template or the signature of a callback function, which is called at the end of the timer interval in order to execute some useful action.
* A handler is just a bare function without any input parameters and returning nothing.
* A handler can be declared just as `void` type.

#### Syntax
    typedef void Handler()

#### Parameters
None

#### Returns
None

[Back to interface](#interface)


<a id="gbj_appdefer"></a>

## gbj\_appdefer()

#### Description
Constructor creates the class instance object and initiates internal resources.
* It inputs operational parameters.
* It creates an internal one-shot timer.

#### Syntax
    gbj_appdefer(unsigned long timerPeriod, Handler *timerHandler)

#### Parameters
* **timerPeriod**: The duration of postpone interval in milliseconds.
  * *Valid values*: non-negative integer 0 ~ 2^32 - 1
  * *Default value*: none


* **timerHandler**: Pointer to a procedure that is called at the end of the timer period. If no handler is provided, the timer just runs without any useful action.
  * *Valid values*: valid address space
  * *Default value*: 0

#### Returns
Object managing deferred actions.

[Back to interface](#interface)


<a id="run"></a>

## run()

#### Description
The execution method as a wrapper of the internal timer's execution method.
* It should be called frequently, usually in the loop function of a main sketch.

[Back to interface](#interface)


<a id="start"></a>

## start()

#### Description
The overloaded method starts the one-shot timer with the current time interval.
* The method without input argument or zero-valued one uses current time interval either from the constructor or previous calling this method.
* The method with numerical input argument sets new timer interval in milliseconds and starts timer.
* The method with textual input argument sets new timer interval in seconds. It is useful with conjunction with a project data hub, which data has always string data type.

#### Syntax
    void setPeriod(unsigned long period)
    void setPeriod(String periodSec)

#### Parameters
* **period**: The duration of new postpone interval in milliseconds.
  * *Valid values*: 0 ~ 2^32 - 1
  * *Default value*: none


* **periodSec**: The duration of new postpone interval in seconds declared as string.
  * *Valid values*: String
  * *Default value*: none

#### Returns
None

#### See also
[getPeriod()](#getPeriod)

[Back to interface](#interface)


<a id="getPeriod"></a>

## getPeriod()

#### Description
The method returns current time interval of the internal timer.

#### Syntax
    unsigned long getPeriod()

#### Parameters
None

#### Returns
Current timer period in milliseconds.

#### See also
[gbj_appdefer()](#gbj_appdefer)

[start()](#start)

[Back to interface](#interface)
