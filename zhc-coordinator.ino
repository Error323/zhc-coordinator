#include <SPI.h>
#include <DueTimer.h>
#include <inttypes.h>

#include "board.h"
#include "phy.h"
#include "tinymac.h"
#include "telegram.h"

uint32_t timer_tick_count = 0;
uint32_t next_mac_tick = 0;
msg_t msg;

void tick()
{
  timer_tick_count++;
}


static void rx_handler(const tinymac_node_t *node, uint8_t type, const char *buf, size_t size)
{
  // Make sure we are the smartmeter node
  if (node->uuid >> 63)
  {
    msg.size = size;
    msg.uuid = node->uuid;
    msg.type = ZHC_INFO;
    SEND(msg, buf);
  }
}


static void reg_handler(const tinymac_node_t *node)
{
  SETP(LED);
  msg.size = 0;
  msg.uuid = node->uuid;
  msg.type = ZHC_REG;
  SEND0(msg);
}


static void dereg_handler(const tinymac_node_t *node)
{
  CLEARP(LED);
  msg.size = 0;
  msg.uuid = node->uuid;
  msg.type = ZHC_DEREG;
  SEND0(msg);
}


void setup()
{
  Serial.begin(115200);
  SerialUSB.begin(115200);
  pinMode(TRX_SDN, OUTPUT);
  pinMode(nTRX_IRQ, INPUT);
  pinMode(LED, OUTPUT);

  msg.magic = MAGIC;
	tinymac_params_t params;
  params.uuid = 0x7a6863ull; // zhc in hex
  params.coordinator = 1;
  params.flags = 0;
  params.beacon_interval = 6; // every 14 seconds
  params.beacon_offset = 0;

  Timer1.attachInterrupt(tick);
  Timer1.start(250000); // Calls every 250 ms

	TRX_ON();

	phy_init();
	tinymac_init(&params);
	tinymac_register_recv_cb(rx_handler);
  tinymac_register_reg_cb(reg_handler);
  tinymac_register_dereg_cb(dereg_handler);
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
