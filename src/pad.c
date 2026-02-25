#include "interop.h"
#include "string.h"
#include "pad.h"

// Default value for pad history
const PadHistory DefaultPadHistory = {
    0xFFFF,
    0x7F,
    0x7F,
    0x7F,
    0x7F,
    -1
};

// Local pad history
PadHistory LocalPadHistory[PAD_PORT_MAX * 2] = {
  {0xFFFF,0x7F,0x7F,0x7F,0x7F,0},
  {0xFFFF,0x7F,0x7F,0x7F,0x7F,1},
  {0xFFFF,0x7F,0x7F,0x7F,0x7F,0},
  {0xFFFF,0x7F,0x7F,0x7F,0x7F,1},
};

VariableAddress_t vaPadRingBitsOn = {
#if UYA_PAL
    .Lobby = 0x005c3120,
    .Bakisi = 0x004958d8,
    .Hoven = 0x004979f0,
    .OutpostX12 = 0x0048d2c8,
    .KorgonOutpost = 0x0048a998,
    .Metropolis = 0x00489db0,
    .BlackwaterCity = 0x00487648,
    .CommandCenter = 0x00487640,
    .BlackwaterDocks = 0x00489ec0,
    .AquatosSewers = 0x004891c0,
    .MarcadiaPalace = 0x00488b40,
#else
    .Lobby = 0x005c10d8,
    .Bakisi = 0x004938e8,
    .Hoven = 0x00495940,
    .OutpostX12 = 0x0048b258,
    .KorgonOutpost = 0x004889a8,
    .Metropolis = 0x00487dc0,
    .BlackwaterCity = 0x004855d8,
    .CommandCenter = 0x00485790,
    .BlackwaterDocks = 0x00487fd0,
    .AquatosSewers = 0x00487310,
    .MarcadiaPalace = 0x00486c50,
#endif
};
    

/*
 * NAME :		padUpdate
 * DESCRIPTION :
 * 			Processes pad state, registering when a button is pressed and released.
 * NOTES :
 *          This must be called every tick in order for pad functionality to work.
 * ARGS : 
 * RETURN :
 * AUTHOR :			
 */
void padUpdate(void)
{
    // Update local pad
    memcpy(LocalPadHistory+2, LocalPadHistory+0, 6);
    memcpy(LocalPadHistory+3, LocalPadHistory+1, 6);

    memcpy(LocalPadHistory, &P1_PAD->buffer.btns, 6);
    memcpy(LocalPadHistory+1, &P2_PAD->buffer.btns, 6);
}

/*
 * NAME :		padGetButton
 * DESCRIPTION :
 * 			Returns 1 when the user is pressing the given button combination.
 *          Returns negative on failure.
 * NOTES :
 * ARGS : 
 *          port:                       Which controller port to read.
 *          buttonMask:                 Buttons to check.
 * RETURN :
 * AUTHOR :			
 */
int padGetButton(int port, u16 buttonMask)
{
    switch (port)
    {
        case 0: return (P1_PAD->buffer.btns & buttonMask) == 0;
        case 1: return (P2_PAD->buffer.btns & buttonMask) == 0;
        default: return -1;
    }
}

/*
 * NAME :		padGetButtonDown
 * DESCRIPTION :
 * 			Returns 1 during the frame that the user starts pressing the given button combination.
 *          Returns negative on failure.
 * NOTES :
 * ARGS : 
 *          port:                       Which controller port to read.
 *          buttonMask:                 Buttons to check.
 * RETURN :
 * AUTHOR :			
 */
int padGetButtonDown(int port, u16 buttonMask)
{
    if (port < 0 || port >= PAD_PORT_MAX)
        return -1;

    return (LocalPadHistory[port + 0].btns & buttonMask) == 0 &&
            (LocalPadHistory[port + 2].btns & buttonMask) != 0;
}

/*
 * NAME :		padGetButtonUp
 * DESCRIPTION :
 * 			Returns 1 during the frame that the user releases the given button combination.
 *          Returns negative on failure.
 * NOTES :
 * ARGS : 
 *          port:                       Which controller port to read.
 *          buttonMask:                 Buttons to check.
 * RETURN :
 * AUTHOR :			
 */
int padGetButtonUp(int port, u16 buttonMask)
{
    if (port < 0 || port >= PAD_PORT_MAX)
        return -1;

    return (LocalPadHistory[port + 0].btns & buttonMask) != 0 &&
        (LocalPadHistory[port + 2].btns & buttonMask) == 0;
}

/*
 * NAME :		padResetInput
 * DESCRIPTION :
 * 			Resets the given ports inputs.
 * NOTES :
 * ARGS : 
 *          port:                       Which controller port to reset.
 * RETURN :
 * AUTHOR :			
 */
void padResetInput(int port)
{
    if (port < 0 || port >= PAD_PORT_MAX)
        return;

    PAD * pad = port ? P2_PAD : P1_PAD;

    u64 defaultValue = 0x7F7F7F7FFFFF7900;
    *(u64*)((u32)pad + 0x00) = defaultValue;
    *(u64*)((u32)pad + 0x80) = defaultValue;
}
