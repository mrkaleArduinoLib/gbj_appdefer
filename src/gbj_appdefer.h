/*
  NAME:
  gbj_appdefer

  DESCRIPTION:
  Application library defers executing a procedure (handler).
  - Internal one-shot timer is utilized for postponing.
  - The defering is useful for postponed reconnecting to wifi or restarting
  microcontroller from the built-in webserver to give it a chance to redirect
  to a main page and suppress the web browser repeate that action.

  LICENSE:
  This program is free software; you can redistribute it and/or modify
  it under the terms of the license GNU GPL v3
  http://www.gnu.org/licenses/gpl-3.0.html (related to original code) and MIT
  License (MIT) for added code.

  CREDENTIALS:
  Author: Libor Gabaj
 */
#ifndef GBJ_APPDEFER_H
#define GBJ_APPDEFER_H

#if defined(__AVR__)
  #include <Arduino.h>
  #include <inttypes.h>
#elif defined(ESP8266) || defined(ESP32)
  #include <Arduino.h>
#elif defined(PARTICLE)
  #include <Particle.h>
#endif
#include "gbj_appcore.h"
#include "gbj_serial_debug.h"
#include "gbj_timer.h"

#undef SERIAL_PREFIX
#define SERIAL_PREFIX "gbj_appdefer"

class gbj_appdefer : public gbj_appcore
{
public:
  typedef void Handler();

  /*
    Constructor

    DESCRIPTION:
    Constructor creates the class instance object and sets operational
    parameters.

    PARAMETERS:
    timerPeriod - The duration of postpone interval in milliseconds.
      - Data type: non-negative integer
      - Default value: none
      - Limited range: 0 ~ 2^32 - 1

    timerHandler - Pointer to a procedure within a sketch that receives
      no parameters and returns no value, and is called after the timer's
      interval.
      If no handler is provided, the timer just runs.
      - Data type: Handler
      - Default value: 0
      - Limited range: system address range

    RETURN: object
  */
  inline gbj_appdefer(unsigned long timerPeriod, Handler *timerHandler = 0)
  {
    timer_ = new gbj_timer(timerPeriod, timerHandler);
    timer_->halt();
  }

  /*
    Start one-shot timer.

    DESCRIPTION:
    The method enables running the timer.

    PARAMETERS:
    period - New postpone interval in milliseconds. If is zero, the current
    interval is used from previous start or from constructor.
      - Data type: non-negative integer
      - Default value: 0
      - Limited range: 0 ~ 2^32 - 1
    period - New postpone interval inputed as String in seconds.
      - Data type: String
      - Default value: none
      - Limited range: none

    RETURN: none
  */
  inline void start(unsigned long period = 0)
  {
    if (period && period != timer_->getPeriod())
    {
      timer_->setPeriod(period);
    }
    timer_->resume();
  }
  inline void start(String periodSec)
  {
    start(1000 * (unsigned long)periodSec.toInt());
  }

  /*
    Processing.

    DESCRIPTION:
    The method should be called in an application sketch loop.
    It processes main functionality and is controlled by the internal timer.

    PARAMETERS: None

    RETURN: none
  */
  inline void run()
  {
    if (timer_->run())
    {
      timer_->halt();
      SERIAL_TITLE("Action");
    }
  }

  // Getters
  inline unsigned long getPeriod() { return timer_->getPeriod(); }

private:
  gbj_timer *timer_;
};

#endif
