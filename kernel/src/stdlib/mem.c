#include "include/stdlib.h"

/* Copy [count] bytes of data from [src] to [dest].
   Return [dest].
 */
uint8 *memcpy(uint8 *dest, const uint8 *src, uint32 count)
{
  const uint8 *sp = (const uint8 *)src;
  uint8 *dp = (uint8 *)dest;
  for(; count != 0; count--) *dp++ = *sp++;
  return dest;
}

/* Copy [count] words of data from [src] to [dest].
   Return [dest].
 */
uint16 *memcpyw(uint16 *dest, const uint16 *src, uint32 count)
{
    const uint16 *sp = (const uint16 *)src;
    uint16 *dp = (uint16 *)dest;
    for(; count != 0; count--) *dp++ = *sp++;
    return dest;
}

/* Set [count] bytes in [dest] to [val].
   Return [dest].
 */
uint8 *memset(uint8 *dest, uint8 val, uint32 count)
{
  uint8 *temp = (uint8 *)dest;
  for( ; count != 0; count--) *temp++ = val;
  return dest;
}

/* Set [count] words in [dest] to [val].
   Return [dest].
 */
uint16 *memsetw(uint16 *dest, uint16 val, uint32 count)
{
  uint16 *temp = (uint16 *)dest;
  for( ; count != 0; count--) *temp++ = val;
  return dest;
}
