; ============================================
; Keypad Test [Hap, 2006].ch8
; ============================================

; Entry point
0200: 124E    JP     24E

; Embedded data (not executable instructions)
0202: 0819    SYS    819
0204: 0101    SYS    101
0206: 0801    SYS    801
0208: 0F01    SYS    F01
020A: 0109    SYS    109
020C: 0809    SYS    809
020E: 0F09    SYS    F09
0210: 0111    SYS    111
0212: 0811    SYS    811
0214: 0F11    SYS    F11
0216: 0119    SYS    119
0218: 0F19    SYS    F19
021A: 1601    JP     601
021C: 1609    JP     609
021E: 1611    JP     611
0220: 1619    JP     619
0222: FCFC    DATA   FC FC
0224: FCFC    DATA   FC FC
0226: FCFC    DATA   FC FC
0228: FC00    DATA   FC 00

; ============================================
; Subroutine: shift left, then add I
; ============================================

022A: A202    LD     I, 202
022C: 820E    SHL    V2, V0
022E: F21E    ADD    I, V2
0230: 8206    SHR    V2, V0
0232: F165    LD     V0-V1, [I]
0234: 00EE    RET

; ============================================
; Subroutine: shift left, then store
; ============================================

0236: A202    LD     I, 202
0238: 820E    SHL    V2, V0
023A: F21E    ADD    I, V2
023C: 8206    SHR    V2, V0
023E: F155    LD     [I], V0-V1
0240: 00EE    RET

; ============================================
; Subroutine: wait for delay timer
; ============================================

0242: 6F10    LD     VF, 10
0244: FF15    LD     DT, VF

0246: FF07    LD     VF, DT
0248: 3F00    SE     VF, 00
024A: 1246    JP     246
024C: 00EE    RET

; ============================================
; Main program
; ============================================

024E: 00E0    CLS
0250: 6200    LD     V2, 00

; Draw keypad test sprites
0252: 222A    CALL   22A
0254: F229    LD     F, V2
0256: D015    DRW    V0, V1, 5
0258: 70FF    ADD    V0, FF
025A: 71FF    ADD    V1, FF
025C: 2236    CALL   236
025E: 7201    ADD    V2, 01
0260: 3210    SE     V2, 10
0262: 1252    JP     252

; Wait for key
0264: F20A    LD     V2, K

; Draw pressed key
0266: 222A    CALL   22A
0268: A222    LD     I, 222
026A: D017    DRW    V0, V1, 7
026C: 2242    CALL   242
026E: D017    DRW    V0, V1, 7
0270: 1264    JP     264