#include "Led.h"
using namespace std;

map<int, Led *> Led::leds_mapping = {
        { 1, new Led(1, "QUANT INDICATOR", Led::OFF, false) },
        { 2, new Led(2, "HEADPHONE INDICATOR", Led::OFF, false, false) },
        {3, new Led(3, "MASTER INDICATOR", Led::OFF, false)},
        {4, new Led(4, "SNAP INDICATOR", Led::OFF, false, false)},
        {5, new Led(5, "WARNING INDICATOR", Led::OFF, false, false)},
        {6, new Led(6, "MASTER BUTTON", Led::OFF, false)},
        {7, new Led(7, "SNAP BUTTON", Led::OFF, false)},
        {8, new Led(8, "REC", Led::OFF, false)},
        {9, new Led(9, "SIZE", Led::OFF, false)},
        {10, new Led(10, "QUANT BUTTON", Led::OFF, false)},
        {11, new Led(11, "BROWSE", Led::OFF, false)},
        {12, new Led(12, "PLAY", Led::OFF, false)},
        {13, new Led(13, "UNDO", Led::OFF, false)},
        {14, new Led(14, "CH1 >", Led::OFF, false)},
        {15, new Led(15, "CH1 <", Led::OFF, false)},
        {16, new Led(16, "CH1 VOL METER 1", Led::OFF, false, false)},
        {17, new Led(17, "CH1 VOL METER 2", Led::OFF, false, false)},
        {18, new Led(18, "CH1 VOL METER 3", Led::OFF, false, false)},
        {19, new Led(19, "CH1 VOL METER 4", Led::OFF, false, false)},
        {20, new Led(20, "CH1 VOL METER 5", Led::OFF, false, false)},
        {21, new Led(21, "CH1 VOL METER 6", Led::OFF, false, false)},
        {22, new Led(22, "CH1 VOL METER CLIP", Led::OFF, false, false)},
        {23, new Led(23, "CH1 ACTIVE", Led::OFF, false)},
        {24, new Led(24, "CH1 EARPHONES", Led::OFF, false)},
        {25, new Led(25, "CH1 FX1 ENABLE", Led::OFF, false)},
        {26, new Led(26, "CH1 FX2 ENABLE", Led::OFF, false)},
        {27, new Led(27, "CH2 >", Led::OFF, false)},
        {28, new Led(28, "CH2 <", Led::OFF, false)},
        {29, new Led(29, "CH2 VOL METER 1", Led::OFF, false, false)},
        {30, new Led(30, "CH2 VOL METER 2", Led::OFF, false, false)},
        {31, new Led(31, "CH2 VOL METER 3", Led::OFF, false, false)},
        {32, new Led(32, "CH2 VOL METER 4", Led::OFF, false, false)},
        {33, new Led(33, "CH2 VOL METER 5", Led::OFF, false, false)},
        {34, new Led(34, "CH2 VOL METER 6", Led::OFF, false, false)},
        {35, new Led(35, "CH2 VOL METER CLIP", Led::OFF, false, false)},
        {36, new Led(36, "CH2 ACTIVE", Led::OFF, false)},
        {37, new Led(37, "CH2 EARPHONES", Led::OFF, false)},
        {38, new Led(38, "CH2 FX1 ENABLE", Led::OFF, false)},
        {39, new Led(39, "CH2 FX2 ENABLE", Led::OFF, false)},
        {40, new Led(40, "CH3 >", Led::OFF, false, false)},
        {41, new Led(41, "CH3 <", Led::OFF, false, false)},
        {42, new Led(42, "CH3 VOL METER 1", Led::OFF, false, false)},
        {43, new Led(43, "CH3 VOL METER 2", Led::OFF, false, false)},
        {44, new Led(44, "CH3 VOL METER 3", Led::OFF, false, false)},
        {45, new Led(45, "CH3 VOL METER 4", Led::OFF, false, false)},
        {46, new Led(46, "CH3 VOL METER 5", Led::OFF, false, false)},
        {47, new Led(47, "CH3 VOL METER 6", Led::OFF, false, false)},
        {48, new Led(48, "CH3 VOL METER CLIP", Led::OFF, false, false)},
        {49, new Led(49, "CH3 ACTIVE", Led::OFF, false, false)},
        {50, new Led(50, "CH3 EARPHONES", Led::OFF, false)},
        {51, new Led(51, "CH3 FX1 ENABLE", Led::OFF, false)},
        {52, new Led(52, "CH3 FX2 ENABLE", Led::OFF, false)},
        {53, new Led(53, "CH4 >", Led::OFF, false, false)},
        {54, new Led(54, "CH4 <", Led::OFF, false, false)},
        {55, new Led(55, "CH1 VOL METER 1", Led::OFF, false, false)},
        {56, new Led(56, "CH1 VOL METER 2", Led::OFF, false, false)},
        {57, new Led(57, "CH1 VOL METER 3", Led::OFF, false, false)},
        {58, new Led(58, "CH1 VOL METER 4", Led::OFF, false, false)},
        {59, new Led(59, "CH1 VOL METER 5", Led::OFF, false, false)},
        {60, new Led(60, "CH1 VOL METER 6", Led::OFF, false, false)},
        {64, new Led(61, "CH1 VOL METER CLIP", Led::OFF, false, false)},
        {62, new Led(62, "CH4 ACTIVE", Led::OFF, false, false)},
        {63, new Led(63, "CH4 EARPHONES", Led::OFF, false)},
        {64, new Led(64, "CH4 FX1 ENABLE", Led::OFF, false)},
        {65, new Led(65, "CH4 FX2 ENABLE", Led::OFF, false)},
        {66, new Led(66, "CH1 / CH3 HOTCUE 1 BLUE", Led::OFF, false)},
        {67, new Led(67, "CH1 / CH3 HOTCUE 1 GREEN", Led::OFF, false)},
        {68, new Led(68, "CH1 / CH3 HOTCUE 2 BLUE", Led::OFF, false)},
        {69, new Led(69, "CH1 / CH3 HOTCUE 2 GREEN", Led::OFF, false)},
        {70, new Led(70, "CH1 / CH3 HOTCUE 3 BLUE", Led::OFF, false)},
        {71, new Led(71, "CH1 / CH3 HOTCUE 3 GREEN", Led::OFF, false)},
        {72, new Led(72, "CH1 / CH3 HOTCUE 4 BLUE", Led::OFF, false)},
        {73, new Led(73, "CH1 / CH3 HOTCUE 4 GREEN", Led::OFF, false)},
        {74, new Led(74, "CH1 / CH3 LOAD BUTTON ", Led::OFF, false)},
        {75, new Led(75, "CH1 / CH3 TOGGLE", Led::OFF, false)},
        {76, new Led(76, "CH1 / CH3 IN", Led::OFF, false)},
        {77, new Led(77, "CH1 / CH3 OUT", Led::OFF, false)},
        {78, new Led(78, "CH1 / CH3 SHIFT", Led::OFF, false)},
        {79, new Led(79, "CH1 / CH3 SYNC", Led::OFF, false)},
        {80, new Led(80, "CH1 / CH3 CUE", Led::OFF, false)},
        {81, new Led(81, "CH1 / CH3 PLAY", Led::OFF, false)},
        {82, new Led(82, "CH2 / CH4 TEMPO UP", Led::OFF, false)},
        {83, new Led(83, "CH2 / CH4 TEMPO DOWN", Led::OFF, false)},
        {84, new Led(84, "CH1 / CH3 MASTER", Led::OFF, false, false)},
        {85, new Led(85, "CH1 / CH3 KEYLOCK", Led::OFF, false, false)},
        {86, new Led(62, "CH1 DECK A", Led::OFF, false)},
        {87, new Led(87, "CH3 DECK C", Led::OFF, false, false)},
        {88, new Led(88, "CH1 / CH3 SAMPLES", Led::OFF, false, false)},
        {89, new Led(89, "CH1 / CH3 ON AIR", Led::OFF, false, false)},
        {90, new Led(90, "CH1 / CH3 SAMPLE 1", Led::OFF, false)},
        {91, new Led(91, "CH1 / CH3 SAMPLE 2", Led::OFF, false)},
        {92, new Led(92, "CH1 / CH3 SAMPLE 3", Led::OFF, false)},
        {93, new Led(93, "CH1 / CH3 SAMPLE 4", Led::OFF, false)},
        {94, new Led(94, "CH1 / CH3 DIGIT1 A", Led::OFF, false, false)},
        {95, new Led(95, "CH1 / CH3 DIGIT1 B", Led::OFF, false, false)},
        {96, new Led(96, "CH1 / CH3 DIGIT1 C", Led::OFF, false, false)},
        {97, new Led(97, "CH1 / CH3 DIGIT1 D", Led::OFF, false, false)},
        {98, new Led(98, "CH1 / CH3 DIGIT1 E", Led::OFF, false, false)},
        {99, new Led(99, "CH1 / CH3 DIGIT1 F", Led::OFF, false, false)},
        {100, new Led(100, "CH1 / CH3 DIGIT1 G", Led::OFF, false, false)},
        {101, new Led(101, "CH1 / CH3 DIGIT1 DOT", Led::OFF, false, false)},
        {102, new Led(102, "CH1 / CH3 DIGIT2 A", Led::OFF, false, false)},
        {103, new Led(103, "CH1 / CH3 DIGIT2 B", Led::OFF, false, false)},
        {104, new Led(104, "CH1 / CH3 DIGIT2 C", Led::OFF, false, false)},
        {105, new Led(105, "CH1 / CH3 DIGIT2 D", Led::OFF, false, false)},
        {106, new Led(106, "CH1 / CH3 DIGIT2 E", Led::OFF, false, false)},
        {107, new Led(107, "CH1 / CH3 DIGIT2 F", Led::OFF, false, false)},
        {108, new Led(108, "CH1 / CH3 DIGIT2 G", Led::OFF, false, false)},
        {109, new Led(109, "CH1 / CH3 DIGIT2 DOT", Led::OFF, false, false)},
        {110, new Led(110, "CH2 / CH4 HOTCUE 1 BLUE", Led::OFF, false)},
        {111, new Led(111, "CH2 / CH4 HOTCUE 1 GREEN", Led::OFF, false)},
        {112, new Led(112, "CH2 / CH4 HOTCUE 2 BLUE", Led::OFF, false)},
        {113, new Led(113, "CH2 / CH4 HOTCUE 2 GREEN", Led::OFF, false)},
        {114, new Led(114, "CH2 / CH4 HOTCUE 3 BLUE", Led::OFF, false)},
        {115, new Led(115, "CH2 / CH4 HOTCUE 3 GREEN", Led::OFF, false)},
        {116, new Led(116, "CH2 / CH4 HOTCUE 4 BLUE", Led::OFF, false)},
        {117, new Led(117, "CH2 / CH4 HOTCUE 4 GREEN", Led::OFF, false)},
        {118, new Led(118, "CH2 / CH4 LOAD BUTTON", Led::OFF, false)},
        {119, new Led(119, "CH2 / CH4 TOGGLE", Led::OFF, false)},
        {120, new Led(120, "CH2 / CH4 IN", Led::OFF, false)},
        {121, new Led(121, "CH2 / CH4 OUT", Led::OFF, false)},
        {122, new Led(122, "CH2 / CH4 SHIFT", Led::OFF, false)},
        {123, new Led(123, "CH2 / CH4 SYNC", Led::OFF, false)},
        {124, new Led(124, "CH2 / CH4 CUE", Led::OFF, false)},
        {125, new Led(125, "CH2 / CH4 PLAY", Led::OFF, false)},
        {126, new Led(126, "CH2 / CH4 TEMPO UP", Led::OFF, false)},
        {127, new Led(127, "CH2 / CH4 TEMPO DOWN", Led::OFF, false)},
        {128, new Led(128, "CH2 / CH4 MASTER", Led::OFF, false, false)},
        {129, new Led(129, "CH2 / CH4 KEYLOCK", Led::OFF, false, false)},
        {130, new Led(130, "CH2 DECK B", Led::OFF, false)},
        {131, new Led(131, "CH4 DECK D", Led::OFF, false, false)},
        {132, new Led(132, "CH2 / CH4 SAMPLES", Led::OFF, false, false)},
        {133, new Led(133, "CH2 / CH4 ON AIR", Led::OFF, false, false)},
        {134, new Led(134, "CH2 / CH4 SAMPLE 1", Led::OFF, false)},
        {135, new Led(135, "CH2 / CH4 SAMPLE 2", Led::OFF, false)},
        {136, new Led(136, "CH2 / CH4 SAMPLE 3", Led::OFF, false)},
        {137, new Led(137, "CH2 / CH4 SAMPLE 4", Led::OFF, false)},
        {138, new Led(138, "CH2 / CH4 DIGIT1 A", Led::OFF, false, false)},
        {139, new Led(139, "CH2 / CH4 DIGIT1 B", Led::OFF, false, false)},
        {140, new Led(140, "CH2 / CH4 DIGIT1 C", Led::OFF, false, false)},
        {141, new Led(141, "CH2 / CH4 DIGIT1 D", Led::OFF, false, false)},
        {142, new Led(142, "CH2 / CH4 DIGIT1 E", Led::OFF, false, false)},
        {143, new Led(143, "CH2 / CH4 DIGIT1 F", Led::OFF, false, false)},
        {144, new Led(144, "CH2 / CH4 DIGIT1 G", Led::OFF, false, false)},
        {145, new Led(145, "CH2 / CH4 DIGIT1 DOT", Led::OFF, false, false)},
        {146, new Led(146, "CH2 / CH4 DIGIT2 A", Led::OFF, false, false)},
        {147, new Led(147, "CH2 / CH4 DIGIT3 B", Led::OFF, false, false)},
        {148, new Led(148, "CH2 / CH4 DIGIT4 C", Led::OFF, false, false)},
        {149, new Led(149, "CH2 / CH4 DIGIT5 D", Led::OFF, false, false)},
        {150, new Led(150, "CH2 / CH4 DIGIT6 E", Led::OFF, false, false)},
        {151, new Led(151, "CH2 / CH4 DIGIT7 F", Led::OFF, false, false)},
        {152, new Led(152, "CH2 / CH4 DIGIT8 G", Led::OFF, false, false)},
        {153, new Led(153, "CH2 / CH4 DIGIT9 DOT", Led::OFF, false, false)},
        {154, new Led(154, "FX1 DRY WET", Led::OFF, false)},
        {155, new Led(155, "FX1 EFFECT 1", Led::OFF, false)},
        {156, new Led(156, "FX1 EFFECT 2", Led::OFF, false)},
        {157, new Led(157, "FX1 EFFECT 3", Led::OFF, false)},
        {158, new Led(158, "FX1 MODE", Led::OFF, false)},
        {159, new Led(159, "FX2 DRY WET", Led::OFF, false)},
        {160, new Led(160, "FX2 EFFECT 1", Led::OFF, false)},
        {161, new Led(161, "FX2 EFFECT 2", Led::OFF, false)},
        {162, new Led(162, "FX2 EFFECT 3", Led::OFF, false)},
        {163, new Led(163, "FX2 MODE", Led::OFF, false)},
};

Led::Led(int in_code, string in_name, int in_value, bool in_is_meter, bool in_by_default) {
    code = in_code;
    name = in_name;
    value = in_value;
    is_meter = in_is_meter;
    by_default = in_by_default;
}

Led::Led(){
    code = value = -1;
    name = "";
    is_meter = by_default = false;
}