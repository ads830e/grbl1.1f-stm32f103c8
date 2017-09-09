/*
  serial.c - Low level functions for sending and recieving bytes via the serial port
  Part of Grbl

  Copyright (c) 2011-2016 Sungeun K. Jeon for Gnea Research LLC
  Copyright (c) 2009-2011 Simen Svale Skogsrud

  Grbl is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Grbl is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Grbl.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "grbl.h"

// Returns the number of bytes available in the RX serial buffer.
uint8_t serial_get_rx_buffer_available()
{
  uint8_t ret=HW_USB_get_rx_buffer_count();
  if(ret>=128) return 0;
  else return 128-ret;
}

// Returns the number of bytes used in the RX serial buffer.
// NOTE: Deprecated. Not used unless classic status reports are enabled in config.h.
uint8_t serial_get_rx_buffer_count()
{
  return HW_USB_get_rx_buffer_count();
}

// Returns the number of bytes used in the TX serial buffer.
// NOTE: Not used except for debugging and ensuring no TX bottlenecks.
uint8_t serial_get_tx_buffer_count()
{
  return 0;
}

void serial_init()
{
  // Set baud rate
}

// Writes one byte to the TX serial buffer. Called by main program.
void serial_write(uint8_t data) {
  // Calculate next head
  HW_USB_write(data);
}

// Fetches the first byte in the serial read buffer. Called by main program.
uint8_t serial_read()
{
  return HW_USB_read();
}

void serial_reset_read_buffer()
{
  HW_USB_reset_read_buffer();
}
