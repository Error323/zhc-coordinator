#ifndef TELEGRAM_H_
#define TELEGRAM_H_

#define ZHC_INFO  1
#define ZHC_REG   2
#define ZHC_DEREG 3
#define MAGIC 0x55423CE7

struct msg_t
{
  uint32_t magic;
  uint16_t size;
  uint16_t type;
  uint64_t uuid;
} PACKED;

#endif // TELEGRAM_H_
