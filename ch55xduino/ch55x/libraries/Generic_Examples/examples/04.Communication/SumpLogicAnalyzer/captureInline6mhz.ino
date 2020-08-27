/*void captureInline6mhz() {

  //  basic trigger, wait until all trigger conditions are met on port.
  //  this needs further testing, but basic tests work as expected.

  //  disable interrupts during capture to maintain precision.
  //  we cannot afford any timing interference so we absolutely
  //  cannot have any interrupts firing.

  EA = 0;

  //prepare R0 DPTR
  __asm__("  mov r0,#_swapByte       \n"
          "  inc _XBUS_AUX       \n"  //select DPTR1
          "  mov dptr,#(_logicdata-0)       \n"
          "  dec _XBUS_AUX       \n"  //select DPTR0 , set it back
         );

  if (trigger) {
    while ((trigger_values ^ P1) & trigger);
  }

  //P1 is at address 0x90, but it can not be indirectly accessed, because it is on "top" of the ram

  //a5-> MOVX @DPTR1,A & INC DPTR1

#define INLINE_CAPTURE1   __asm__("  mov a,_P1 \n  swap a \n mov @r0,a \n " );
#define INLINE_CAPTURE2   __asm__("  mov a,_P1 \n  xchd A,@r0 \n  .db #0xa5 \n" );

  //===768 pairs
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 4
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 8
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 12
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 16
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 20
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 24
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 28
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 32
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 36
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 40
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 44
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 48
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 52
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 56
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 60
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 64
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 68
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 72
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 76
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 80
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 84
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 88
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 92
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 96
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 100
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 104
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 108
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 112
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 116
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 120
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 124
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 128
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 132
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 136
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 140
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 144
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 148
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 152
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 156
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 160
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 164
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 168
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 172
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 176
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 180
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 184
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 188
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 192
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 196
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 200
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 204
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 208
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 212
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 216
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 220
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 224
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 228
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 232
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 236
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 240
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 244
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 248
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 252
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 256
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 260
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 264
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 268
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 272
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 276
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 280
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 284
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 288
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 292
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 296
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 300
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 304
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 308
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 312
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 316
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 320
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 324
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 328
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 332
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 336
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 340
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 344
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 348
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 352
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 356
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 360
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 364
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 368
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 372
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 376
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 380
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 384
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 388
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 392
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 396
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 400
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 404
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 408
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 412
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 416
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 420
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 424
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 428
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 432
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 436
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 440
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 444
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 448
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 452
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 456
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 460
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 464
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 468
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 472
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 476
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 480
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 484
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 488
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 492
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 496
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 500
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 504
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 508
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 512
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 516
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 520
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 524
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 528
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 532
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 536
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 540
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 544
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 548
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 552
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 556
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 560
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 564
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 568
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 572
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 576
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 580
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 584
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 588
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 592
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 596
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 600
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 604
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 608
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 612
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 616
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 620
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 624
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 628
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 632
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 636
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 640
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 644
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 648
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 652
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 656
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 660
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 664
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 668
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 672
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 676
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 680
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 684
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 688
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 692
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 696
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 700
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 704
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 708
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 712
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 716
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 720
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 724
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 728
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 732
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 736
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 740
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 744
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 748
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 752
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 756
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 760
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 764
  INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; INLINE_CAPTURE1; INLINE_CAPTURE2; //pair 768
  //===768 pairs end


  // re-enable interrupts now that we're done sampling.
  EA = 1;

  //   dump the samples back to the SUMP client.  nothing special
  //   is done for any triggers, this is effectively the 0/100 buffer split.

  //pulseview use reversed order

  for (unsigned int i = 0 ; i < readCount; i++ ) {
    unsigned int rev_i = readCount - i - 1;
    if ((rev_i & 1) == 0) {
      USBSerial_write(logicdata[rev_i / 2] & 0x0F);
    } else {
      USBSerial_write((logicdata[rev_i / 2]) >> 4);
    }
  }

}*/
