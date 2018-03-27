; Music converted from music7.xrns 2018-03-28 02:33:03

%define MUSIC_LENGTH 1176
%define TOTAL_SAMPLES 8716288
%define MAX_TOTAL_INSTRUMENT_SAMPLES 26673152

%define SAMPLES_PER_TICK 6963
%define TICKS_PER_SECOND 6.333333333

%define NUM_TRACKS_WITH_REVERB 2
%define NUM_TRACKS_WITHOUT_REVERB 4

%define REVERB_NUM_DELAYS   166
%define REVERB_MIN_DELAY    1792
%define REVERB_MAX_DELAY    4864
%define REVERB_ADD_DELAY    0
%define REVERB_RANDOMSEED   65536
%define REVERB_MAX_DECAY    0.869785648
%define REVERB_DECAY_MUL    1.000028682
%define REVERB_FILTER_HIGH  0x3EF25A0D ; 0.473343283
%define REVERB_FILTER_LOW   0x3C23D70A ; 0.010000000
%define REVERB_DAMPEN_HIGH  0x3EFAE147 ; 0.489999980
%define REVERB_DAMPEN_LOW   0x3C23D70A ; 0.010000000
%define REVERB_VOLUME_LEFT  0x3D9898F9 ; 0.074510522
%define REVERB_VOLUME_RIGHT 0x3D9898F9 ; 0.074510522


	section iparam data align=4

_InstrumentParams:
.i00:
	; 00|VST: Oidos ()
	dd	10,3,73,48,0xBD8B3FB8,0x3F800000,0x3F800000,0xBF28F44D,0x3E4AE4E6,0xC2F00000,0x3F75D390,0x3F800000,0xBD52DAB9,0xB2960940,0xB9B3BAB2,0x3F800089,1114112,0xB86DC55B,0x3808155B,0x43000000
.i01:
	; 01|Single_violin_01
	dd	10,8,22,49,0x00000000,0x3F800000,0x3F75C302,0xBF028DD0,0x3D95EF14,0xC2866649,0x424D718F,0x3E8005D7,0xBD26BB86,0x380EA601,0x391D4F5F,0x3FC893BA,917504,0xB8367CA2,0x3885DF8E,0x41D00000
.i02:
	; 02|tsih
	dd	40,10,50,56,0xBDAC04D8,0x3F800000,0xBF50E552,0xBECCCA98,0x3F1ACC23,0x41829121,0x4243D7D5,0x3F800000,0xBF800000,0xA344C3FA,0xA344C3FA,0x3F800077,1245184,0xB83E3772,0x3985DF93,0x44800000
.i03:
	; 03|swoosh
	dd	24,30,39,100,0x00000000,0x3F800000,0x3F302126,0xBD23C9A0,0x425CDE11,0xC2F00000,0x41CF5D43,0x3F800000,0xBC6DFEDC,0xB595AED5,0xA38B5A58,0x3F80006C,262144,0xB7800000,0x37CD8A69,0x44800000
.i04:
	; 04|Deep_rumble
	dd	15,25,37,10,0x00000000,0x3F800000,0x3D75C8E0,0xC0599992,0x370333F3,0xC1621E06,0x421EB63D,0x3DB397ED,0xBE2A3183,0xB84FB45D,0xB84FB45D,0x3F8225A4,458752,0xB8C38D6E,0x3841F773,0x45300000
.i05:
	; 05|bassen
	dd	4,1,66,32,0xBDBC6898,0x3F800000,0x3F800000,0x3D1FD8B0,0x00000000,0xC2F00000,0x41C7AEB6,0x3DC75789,0xBE61A2E7,0xB54880E0,0x3997641A,0x3FD66035,65536,0xB91B397E,0x3ACE65DF,0x46800000



	section itones data align=1

_InstrumentTones:
.i00:
	; 00|VST: Oidos ()
	db	12,13,4,5,1,3,1,1,5,3,2,1,1,1,2,2,1,2,-123
.i01:
	; 01|Single_violin_01
	db	7,1,13,1,4,3,3,3,1,1,1,1,1,1,1,1,1,1,1,2,2,2,1,2,2,1,1,1,4,-122
.i02:
	; 02|tsih
	db	12,7,29,3,-127
.i03:
	; 03|swoosh
	db	12,3,9,1,23,1,-127
.i04:
	; 04|Deep_rumble
	db	24,-128
.i05:
	; 05|bassen
	db	12,2,3,-128


	section trdata data align=1

_TrackData:
.t_Track01_1:
	; Track 01, column 1
	db	0,1,64,1,64,3,127,1,127,4,127,-128
.t_Track01_2:
	; Track 01, column 2
	db	0,4,64,4,127,1,127,2,127,1,127,-128
.t_Track01_3:
	; Track 01, column 3
	db	0,13,127,1,127,-128
.t_Track01_4:
	; Track 01, column 4
	db	0,14,127,1,127,1,127,-128
.t_Track01_5:
	; Track 01, column 5
	db	0,15,127,2,127,-128
.t_Track01_6:
	; Track 01, column 6
	db	0,0,127,3,127,4,47,-128
.t_Track02_1:
	; Track 02, column 1
	db	0,0,127,2,127,3,127,1,127,2,127,2,127,1,127,1,127,-128
.t_Track02_2:
	; Track 02, column 2
	db	0,1,127,3,107,3,127,4,127,1,127,1,127,4,127,1,127,-128
.t_Track02_3:
	; Track 02, column 3
	db	0,3,127,6,127,4,127,4,127,1,127,1,127,4,127,1,48,-128
.t_Track02_4:
	; Track 02, column 4
	db	0,11,127,4,127,4,127,1,127,1,127,5,48,-128
.t_Track02_5:
	; Track 02, column 5
	db	0,14,127,4,127,2,127,1,127,1,127,1,127,5,32,-128
.t_Track02_6:
	; Track 02, column 6
	db	0,16,127,3,127,2,127,3,127,1,127,2,127,-128
.t_Track02_7:
	; Track 02, column 7
	db	0,22,64,4,64,1,64,-128
.t_tsihtrak_1:
	; tsihtrak, column 1
	db	0,0,16,2,4,1,3,-128
.t_tsihtrak_2:
	; tsihtrak, column 2
	db	0,1,16,-128
.t_Track04_1:
	; Track 04, column 1
	db	0,0,1,0,4,1,3,1,1,0,2,2,2,-128
.t_Track04_2:
	; Track 04, column 2
	db	0,0,2,0,4,3,1,0,2,2,2,-128
.t_Track05_1:
	; Track 05, column 1
	db	0,0,1,0,2,0,4,-128
.t_Track07_1:
	; Track 07, column 1
	db	0,0,1,1,1,1,1,-128

	section notelen data align=1

_NoteLengths:
	; Track 01, column 1
L_Track01_1:
	db	12,76
	; Position 2, pattern 2
	db	64
	; Position 3, pattern 3
	db	64
	; Position 4, pattern 3
	db	64
	; Position 5, pattern 3
	db	64
	; Position 6, pattern 3
	db	64
	; Position 7, pattern 4
	db	-2,64
	; Position 12, pattern 9
	db	63,97
	; Position 14, pattern 11
	db	29,67
	; Position 16, pattern 2
	db	64
	; Position 17, pattern 12
	db	64
	; Position 18, pattern 13
	db	0

	; Track 01, column 2
L_Track01_2:
	db	12,76
	; Position 2, pattern 2
	db	64
	; Position 3, pattern 3
	db	64
	; Position 4, pattern 3
	db	64
	; Position 5, pattern 3
	db	64
	; Position 6, pattern 3
	db	64
	; Position 7, pattern 4
	db	-2,71
	; Position 12, pattern 9
	db	56,73
	; Position 14, pattern 11
	db	24,4,25
	db	0

	; Track 01, column 3
L_Track01_3:
	db	-1,152
	; Position 3, pattern 3
	db	64
	; Position 4, pattern 3
	db	64
	; Position 5, pattern 3
	db	64
	; Position 6, pattern 3
	db	64
	; Position 7, pattern 4
	db	-2,83
	; Position 12, pattern 9
	db	44,81
	; Position 14, pattern 11
	db	17,7,15
	db	0

	; Track 01, column 4
L_Track01_4:
	db	-3,246
	; Position 12, pattern 9
	db	33,105
	; Position 14, pattern 11
	db	7,8,6
	db	0

	; Track 01, column 5
L_Track01_5:
	db	-3,252
	; Position 12, pattern 9
	db	-1,139
	; Position 14, pattern 11
	db	8
	db	0

	; Track 01, column 6
L_Track01_6:
	db	-2,216
	; Position 8, pattern 5
	db	36,28
	; Position 9, pattern 6
	db	36,28
	; Position 10, pattern 7
	db	36,-1,155
	; Position 12, pattern 9
	db	0

	; Track 02, column 1
L_Track02_1:
	db	24
	; Position 1, pattern 1
	db	64
	; Position 2, pattern 2
	db	64
	; Position 3, pattern 3
	db	-2,0
	; Position 7, pattern 4
	db	64
	; Position 8, pattern 5
	db	64
	; Position 9, pattern 6
	db	64
	; Position 10, pattern 7
	db	-1,128
	; Position 12, pattern 9
	db	64
	; Position 13, pattern 10
	db	64
	; Position 14, pattern 11
	db	32,32
	; Position 15, pattern 1
	db	64
	; Position 16, pattern 2
	db	64
	; Position 17, pattern 12
	db	64
	; Position 18, pattern 13
	db	0

	; Track 02, column 2
L_Track02_2:
	db	24
	; Position 1, pattern 1
	db	64
	; Position 2, pattern 2
	db	64
	; Position 3, pattern 3
	db	64
	; Position 4, pattern 3
	db	64
	; Position 5, pattern 3
	db	64
	; Position 6, pattern 3
	db	100
	; Position 7, pattern 4
	db	28
	; Position 8, pattern 5
	db	36,28
	; Position 9, pattern 6
	db	36,64
	; Position 10, pattern 7
	db	94
	; Position 12, pattern 9
	db	64
	; Position 13, pattern 10
	db	64
	; Position 14, pattern 11
	db	30,32
	; Position 15, pattern 1
	db	64
	; Position 16, pattern 2
	db	64
	; Position 17, pattern 12
	db	64
	; Position 18, pattern 13
	db	0

	; Track 02, column 3
L_Track02_3:
	db	24
	; Position 1, pattern 1
	db	64
	; Position 2, pattern 2
	db	76
	; Position 3, pattern 3
	db	32,32
	; Position 4, pattern 3
	db	32,32
	; Position 5, pattern 3
	db	32,32
	; Position 6, pattern 3
	db	32,84
	; Position 8, pattern 5
	db	64
	; Position 9, pattern 6
	db	68
	; Position 10, pattern 7
	db	-1,128
	; Position 12, pattern 9
	db	64
	; Position 13, pattern 10
	db	64
	; Position 14, pattern 11
	db	28,32
	; Position 15, pattern 1
	db	64
	; Position 16, pattern 2
	db	64
	; Position 17, pattern 12
	db	64
	; Position 18, pattern 13
	db	0

	; Track 02, column 4
L_Track02_4:
	db	24
	; Position 1, pattern 1
	db	64
	; Position 2, pattern 2
	db	76
	; Position 3, pattern 3
	db	32,32
	; Position 4, pattern 3
	db	32,32
	; Position 5, pattern 3
	db	32,32
	; Position 6, pattern 3
	db	32,84
	; Position 8, pattern 5
	db	-1,134
	; Position 10, pattern 7
	db	-1,128
	; Position 12, pattern 9
	db	64
	; Position 13, pattern 10
	db	64
	; Position 14, pattern 11
	db	26,32
	; Position 15, pattern 1
	db	64
	; Position 16, pattern 2
	db	64
	; Position 17, pattern 12
	db	64
	; Position 18, pattern 13
	db	0

	; Track 02, column 5
L_Track02_5:
	db	24
	; Position 1, pattern 1
	db	64
	; Position 2, pattern 2
	db	64
	; Position 3, pattern 3
	db	-2,202
	; Position 10, pattern 7
	db	126
	; Position 12, pattern 9
	db	64
	; Position 13, pattern 10
	db	64
	; Position 14, pattern 11
	db	16,40
	; Position 15, pattern 1
	db	64
	; Position 16, pattern 2
	db	64
	; Position 17, pattern 12
	db	64
	; Position 18, pattern 13
	db	0

	; Track 02, column 6
L_Track02_6:
	db	24
	; Position 1, pattern 1
	db	64
	; Position 2, pattern 2
	db	64
	; Position 3, pattern 3
	db	-3,76
	; Position 12, pattern 9
	db	62
	; Position 13, pattern 10
	db	64
	; Position 14, pattern 11
	db	18,4,32
	; Position 15, pattern 1
	db	64
	; Position 16, pattern 2
	db	64
	; Position 17, pattern 12
	db	64
	; Position 18, pattern 13
	db	0

	; Track 02, column 7
L_Track02_7:
	db	93
	; Position 2, pattern 2
	db	3,7,-4,118
	; Position 16, pattern 2
	db	3,7,57
	; Position 17, pattern 12
	db	37
	db	0

	; tsihtrak, column 1
L_tsihtrak_1:
	db	24
	; Position 1, pattern 1
	db	64
	; Position 2, pattern 2
	db	64
	; Position 3, pattern 3
	db	-2,0
	; Position 7, pattern 4
	db	64
	; Position 8, pattern 5
	db	64
	; Position 9, pattern 6
	db	64
	; Position 10, pattern 7
	db	-1,128
	; Position 12, pattern 9
	db	-1,192
	; Position 15, pattern 1
	db	64
	; Position 16, pattern 2
	db	64
	; Position 17, pattern 12
	db	64
	; Position 18, pattern 13
	db	0

	; tsihtrak, column 2
L_tsihtrak_2:
	db	-2,188
	; Position 7, pattern 4
	db	64
	; Position 8, pattern 5
	db	64
	; Position 9, pattern 6
	db	-1,168
	; Position 12, pattern 9
	db	0

	; Track 04, column 1
L_Track04_1:
	db	62
	; Position 1, pattern 1
	db	18,1,13
	; Position 2, pattern 2
	db	15,19,5,11,-3,36
	; Position 11, pattern 8
	db	8,8,14,6
	; Position 12, pattern 9
	db	24,16,20,-1,170
	; Position 15, pattern 1
	db	18,1,13
	; Position 16, pattern 2
	db	15,19,5,11,29
	; Position 17, pattern 12
	db	19,4,20
	; Position 18, pattern 13
	db	0

	; Track 04, column 2
L_Track04_2:
	db	65
	; Position 1, pattern 1
	db	17,11
	; Position 2, pattern 2
	db	17,23,3,12,-3,32
	; Position 11, pattern 8
	db	13,6,13,24
	; Position 12, pattern 9
	db	24,-1,189
	; Position 15, pattern 1
	db	17,11
	; Position 16, pattern 2
	db	17,23,3,12,26
	; Position 17, pattern 12
	db	22,4,16
	; Position 18, pattern 13
	db	0

	; Track 05, column 1
L_Track05_1:
	db	-1,152
	; Position 3, pattern 3
	db	64
	; Position 4, pattern 3
	db	64
	; Position 5, pattern 3
	db	64
	; Position 6, pattern 3
	db	64
	; Position 7, pattern 4
	db	-2,0
	; Position 11, pattern 8
	db	32,32
	; Position 12, pattern 9
	db	64
	; Position 13, pattern 10
	db	64
	; Position 14, pattern 11
	db	64
	; Position 15, pattern 1
	db	0

	; Track 07, column 1
L_Track07_1:
	db	-1,152
	; Position 3, pattern 3
	db	4,4,2,4,4,4,2,3,1,4,4,4,2,4,4,4,2,4,4
	; Position 4, pattern 3
	db	4,4,2,4,4,4,2,3,1,4,4,4,2,4,4,4,2,4,4
	; Position 5, pattern 3
	db	4,4,2,4,4,4,2,3,1,4,4,4,2,4,4,4,2,4,4
	; Position 6, pattern 3
	db	4,4,2,4,4,4,2,3,1,4,4,4,2,4,4,4,2,4,4
	; Position 7, pattern 4
	db	0


	section notesamp data align=1

_NoteSamples:
	; Track 01, column 1
S_Track01_1:
	db	0,1
	; Position 2, pattern 2
	db	2
	; Position 3, pattern 3
	db	5
	; Position 4, pattern 3
	db	5
	; Position 5, pattern 3
	db	5
	; Position 6, pattern 3
	db	5
	; Position 7, pattern 4
	db	0
	; Position 12, pattern 9
	db	3,0
	; Position 14, pattern 11
	db	4,0
	; Position 16, pattern 2
	db	2
	; Position 17, pattern 12
	db	2
	; Position 18, pattern 13
	db	0

	; Track 01, column 2
S_Track01_2:
	db	0,1
	; Position 2, pattern 2
	db	0
	; Position 3, pattern 3
	db	2
	; Position 4, pattern 3
	db	2
	; Position 5, pattern 3
	db	2
	; Position 6, pattern 3
	db	2
	; Position 7, pattern 4
	db	0
	; Position 12, pattern 9
	db	5,0
	; Position 14, pattern 11
	db	3,0,4,0

	; Track 01, column 3
S_Track01_3:
	db	0
	; Position 3, pattern 3
	db	1
	; Position 4, pattern 3
	db	1
	; Position 5, pattern 3
	db	1
	; Position 6, pattern 3
	db	1
	; Position 7, pattern 4
	db	0
	; Position 12, pattern 9
	db	2,0
	; Position 14, pattern 11
	db	1,0,1,0

	; Track 01, column 4
S_Track01_4:
	db	0
	; Position 12, pattern 9
	db	2,0
	; Position 14, pattern 11
	db	3,0,1,0

	; Track 01, column 5
S_Track01_5:
	db	0
	; Position 12, pattern 9
	db	2
	; Position 14, pattern 11
	db	1,0

	; Track 01, column 6
S_Track01_6:
	db	0
	; Position 8, pattern 5
	db	2,1
	; Position 9, pattern 6
	db	2,1
	; Position 10, pattern 7
	db	3,1
	; Position 12, pattern 9
	db	0

	; Track 02, column 1
S_Track02_1:
	db	0
	; Position 1, pattern 1
	db	4
	; Position 2, pattern 2
	db	5
	; Position 3, pattern 3
	db	0
	; Position 7, pattern 4
	db	1
	; Position 8, pattern 5
	db	1
	; Position 9, pattern 6
	db	1
	; Position 10, pattern 7
	db	2
	; Position 12, pattern 9
	db	6
	; Position 13, pattern 10
	db	8
	; Position 14, pattern 11
	db	6,7
	; Position 15, pattern 1
	db	4
	; Position 16, pattern 2
	db	5
	; Position 17, pattern 12
	db	3
	; Position 18, pattern 13
	db	0

	; Track 02, column 2
S_Track02_2:
	db	0
	; Position 1, pattern 1
	db	3
	; Position 2, pattern 2
	db	4
	; Position 3, pattern 3
	db	2
	; Position 4, pattern 3
	db	2
	; Position 5, pattern 3
	db	2
	; Position 6, pattern 3
	db	2
	; Position 7, pattern 4
	db	1
	; Position 8, pattern 5
	db	0,1
	; Position 9, pattern 6
	db	0,1
	; Position 10, pattern 7
	db	1
	; Position 12, pattern 9
	db	7
	; Position 13, pattern 10
	db	7
	; Position 14, pattern 11
	db	6,8
	; Position 15, pattern 1
	db	3
	; Position 16, pattern 2
	db	4
	; Position 17, pattern 12
	db	5
	; Position 18, pattern 13
	db	0

	; Track 02, column 3
S_Track02_3:
	db	0
	; Position 1, pattern 1
	db	2
	; Position 2, pattern 2
	db	3
	; Position 3, pattern 3
	db	4,7
	; Position 4, pattern 3
	db	4,7
	; Position 5, pattern 3
	db	4,7
	; Position 6, pattern 3
	db	4,7
	; Position 8, pattern 5
	db	1
	; Position 9, pattern 6
	db	1
	; Position 10, pattern 7
	db	8
	; Position 12, pattern 9
	db	6
	; Position 13, pattern 10
	db	6
	; Position 14, pattern 11
	db	5,7
	; Position 15, pattern 1
	db	2
	; Position 16, pattern 2
	db	3
	; Position 17, pattern 12
	db	4
	; Position 18, pattern 13
	db	0

	; Track 02, column 4
S_Track02_4:
	db	0
	; Position 1, pattern 1
	db	1
	; Position 2, pattern 2
	db	2
	; Position 3, pattern 3
	db	4,5
	; Position 4, pattern 3
	db	4,5
	; Position 5, pattern 3
	db	4,5
	; Position 6, pattern 3
	db	4,5
	; Position 8, pattern 5
	db	0
	; Position 10, pattern 7
	db	6
	; Position 12, pattern 9
	db	5
	; Position 13, pattern 10
	db	5
	; Position 14, pattern 11
	db	4,4
	; Position 15, pattern 1
	db	1
	; Position 16, pattern 2
	db	2
	; Position 17, pattern 12
	db	3
	; Position 18, pattern 13
	db	0

	; Track 02, column 5
S_Track02_5:
	db	0
	; Position 1, pattern 1
	db	1
	; Position 2, pattern 2
	db	2
	; Position 3, pattern 3
	db	0
	; Position 10, pattern 7
	db	7
	; Position 12, pattern 9
	db	5
	; Position 13, pattern 10
	db	6
	; Position 14, pattern 11
	db	4,0
	; Position 15, pattern 1
	db	1
	; Position 16, pattern 2
	db	2
	; Position 17, pattern 12
	db	3
	; Position 18, pattern 13
	db	0

	; Track 02, column 6
S_Track02_6:
	db	0
	; Position 1, pattern 1
	db	1
	; Position 2, pattern 2
	db	2
	; Position 3, pattern 3
	db	0
	; Position 12, pattern 9
	db	6
	; Position 13, pattern 10
	db	4
	; Position 14, pattern 11
	db	4,5,0
	; Position 15, pattern 1
	db	1
	; Position 16, pattern 2
	db	2
	; Position 17, pattern 12
	db	3
	; Position 18, pattern 13
	db	0

	; Track 02, column 7
S_Track02_7:
	db	0
	; Position 2, pattern 2
	db	1,3,0
	; Position 16, pattern 2
	db	1,3,0
	; Position 17, pattern 12
	db	2,0

	; tsihtrak, column 1
S_tsihtrak_1:
	db	0
	; Position 1, pattern 1
	db	2
	; Position 2, pattern 2
	db	3
	; Position 3, pattern 3
	db	0
	; Position 7, pattern 4
	db	1
	; Position 8, pattern 5
	db	1
	; Position 9, pattern 6
	db	1
	; Position 10, pattern 7
	db	1
	; Position 12, pattern 9
	db	0
	; Position 15, pattern 1
	db	2
	; Position 16, pattern 2
	db	3
	; Position 17, pattern 12
	db	3
	; Position 18, pattern 13
	db	0

	; tsihtrak, column 2
S_tsihtrak_2:
	db	0
	; Position 7, pattern 4
	db	1
	; Position 8, pattern 5
	db	1
	; Position 9, pattern 6
	db	1
	; Position 12, pattern 9
	db	0

	; Track 04, column 1
S_Track04_1:
	db	0
	; Position 1, pattern 1
	db	6,0,3
	; Position 2, pattern 2
	db	0,5,0,4,0
	; Position 11, pattern 8
	db	5,0,4,0
	; Position 12, pattern 9
	db	2,0,1,0
	; Position 15, pattern 1
	db	6,0,3
	; Position 16, pattern 2
	db	0,5,0,4,0
	; Position 17, pattern 12
	db	5,0,4
	; Position 18, pattern 13
	db	0

	; Track 04, column 2
S_Track04_2:
	db	0
	; Position 1, pattern 1
	db	5,2
	; Position 2, pattern 2
	db	0,4,0,3,0
	; Position 11, pattern 8
	db	4,0,3,0
	; Position 12, pattern 9
	db	1,0
	; Position 15, pattern 1
	db	5,2
	; Position 16, pattern 2
	db	0,4,0,3,0
	; Position 17, pattern 12
	db	4,0,3
	; Position 18, pattern 13
	db	0

	; Track 05, column 1
S_Track05_1:
	db	0
	; Position 3, pattern 3
	db	3
	; Position 4, pattern 3
	db	3
	; Position 5, pattern 3
	db	3
	; Position 6, pattern 3
	db	3
	; Position 7, pattern 4
	db	0
	; Position 11, pattern 8
	db	1,2
	; Position 12, pattern 9
	db	3
	; Position 13, pattern 10
	db	3
	; Position 14, pattern 11
	db	3
	; Position 15, pattern 1
	db	0

	; Track 07, column 1
S_Track07_1:
	db	0
	; Position 3, pattern 3
	db	1,2,1,2,1,2,1,3,0,1,1,2,1,2,1,2,1,3,1
	; Position 4, pattern 3
	db	1,2,1,2,1,2,1,3,0,1,1,2,1,2,1,2,1,3,1
	; Position 5, pattern 3
	db	1,2,1,2,1,2,1,3,0,1,1,2,1,2,1,2,1,3,1
	; Position 6, pattern 3
	db	1,2,1,2,1,2,1,3,0,1,1,2,1,2,1,2,1,3,1
	; Position 7, pattern 4
	db	0

