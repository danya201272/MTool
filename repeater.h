#if LWIP_FEATURES && !LWIP_IPV6

#define HAVE_NETDUMP 0

#endif

#include <lwip/napt.h>
#include <lwip/dns.h>
#include <lwip/napt.h>
#include <lwip/dns.h>
#include <LwipDhcpServer.h>
#include <WiFiClient.h>

#define NAPT 1000
#define NAPT_PORT 10

#if HAVE_NETDUMP
#include <NetDump.h>
void dump(int netif_idx, const char* data, size_t len, int out, int success) {
  (void)success;
  Serial.print(out ? F("out ") : F(" in "));
  Serial.printf("%d ", netif_idx);

 
  {
    netDump(Serial, data, len);
   
  }
}
#endif
