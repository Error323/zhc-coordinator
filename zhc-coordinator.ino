#include <SPI.h>
#include <DueTimer.h>

#include "board.h"
#include "phy.h"
#include "tinymac.h"

uint32_t timer_tick_count = 0;
uint32_t next_mac_tick = 0;

void tick()
{
  timer_tick_count++;
}

/*!
 * TinyHAN receive handler.  Invoked when a packet is passed up to the
 * application.  Here, we simply turn the LED on or off depending on the
 * value of the first byte in the packet
 */
static void rx_handler(const tinymac_node_t *node, uint8_t type, const char *buf, size_t size)
{
  if (type == tinymacType_RawData) 
  {
    Serial.print("R: ");
    Serial.println(*((uint16_t*)buf));
  }
}

void setup()
{
  Serial.begin(9600);
  pinMode(TRX_SDN, OUTPUT);
  pinMode(nTRX_IRQ, INPUT);
  
	tinymac_params_t params;
  params.uuid = 0x7a6863ull; // zhc in hex
  params.coordinator = 1;
  params.flags = 0;
  params.beacon_interval = 6; // every 2^6 seconds
  params.beacon_offset = 0;

  Timer1.attachInterrupt(tick);
  Timer1.start(250000); // Calls every 250 ms

	TRX_ON();

	phy_init();
	tinymac_init(&params);
	tinymac_register_recv_cb(rx_handler);
  tinymac_permit_attach(1);
}

void loop()
{
  
  uint32_t now = timer_tick_count;

  if ((int32_t)(now - next_mac_tick) >= 0) 
  {
    next_mac_tick = now + 1;
    tinymac_tick_handler(NULL);
  }

  phy_event_handler();
}
