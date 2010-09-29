#define SG_BUILD_LIBRARY
#include <siege/util/color.h>

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

SGbool SG_EXPORT _sgColorInit(void)
{
    _sg_colNum = 652;
    _sg_colFlags = malloc(_sg_colNum * sizeof(SGubyte));
    _sg_colNames = malloc(_sg_colNum * sizeof(char*));
    _sg_colValues = malloc(_sg_colNum * sizeof(SGColor));

    size_t i = 0;
    _sg_colFlags[i] = 3; _sg_colNames[i] = "snow"; _sg_colValues[i++] = sgColor3ub(255, 250, 250);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "GhostWhite"; _sg_colValues[i++] = sgColor3ub(248, 248, 255);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "WhiteSmoke"; _sg_colValues[i++] = sgColor3ub(245, 245, 245);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "gainsboro"; _sg_colValues[i++] = sgColor3ub(220, 220, 220);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "FloralWhite"; _sg_colValues[i++] = sgColor3ub(255, 250, 240);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "OldLace"; _sg_colValues[i++] = sgColor3ub(253, 245, 230);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "linen"; _sg_colValues[i++] = sgColor3ub(250, 240, 230);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "AntiqueWhite"; _sg_colValues[i++] = sgColor3ub(250, 235, 215);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "PapayaWhip"; _sg_colValues[i++] = sgColor3ub(255, 239, 213);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "BlanchedAlmond"; _sg_colValues[i++] = sgColor3ub(255, 235, 205);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "bisque"; _sg_colValues[i++] = sgColor3ub(255, 228, 196);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "PeachPuff"; _sg_colValues[i++] = sgColor3ub(255, 218, 185);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "NavajoWhite"; _sg_colValues[i++] = sgColor3ub(255, 222, 173);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "moccasin"; _sg_colValues[i++] = sgColor3ub(255, 228, 181);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "cornsilk"; _sg_colValues[i++] = sgColor3ub(255, 248, 220);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "ivory"; _sg_colValues[i++] = sgColor3ub(255, 255, 240);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "LemonChiffon"; _sg_colValues[i++] = sgColor3ub(255, 250, 205);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "seashell"; _sg_colValues[i++] = sgColor3ub(255, 245, 238);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "honeydew"; _sg_colValues[i++] = sgColor3ub(240, 255, 240);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "MintCream"; _sg_colValues[i++] = sgColor3ub(245, 255, 250);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "azure"; _sg_colValues[i++] = sgColor3ub(240, 255, 255);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "AliceBlue"; _sg_colValues[i++] = sgColor3ub(240, 248, 255);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "lavender"; _sg_colValues[i++] = sgColor3ub(230, 230, 250);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "LavenderBlush"; _sg_colValues[i++] = sgColor3ub(255, 240, 245);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "MistyRose"; _sg_colValues[i++] = sgColor3ub(255, 228, 225);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "white"; _sg_colValues[i++] = sgColor3ub(255, 255, 255);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "black"; _sg_colValues[i++] = sgColor3ub(0, 0, 0);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "DarkSlateGray"; _sg_colValues[i++] = sgColor3ub(47, 79, 79);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "DarkSlateGrey"; _sg_colValues[i++] = sgColor3ub(47, 79, 79);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "DimGray"; _sg_colValues[i++] = sgColor3ub(105, 105, 105);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "DimGrey"; _sg_colValues[i++] = sgColor3ub(105, 105, 105);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "SlateGray"; _sg_colValues[i++] = sgColor3ub(112, 128, 144);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "SlateGrey"; _sg_colValues[i++] = sgColor3ub(112, 128, 144);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "LightSlateGray"; _sg_colValues[i++] = sgColor3ub(119, 136, 153);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "LightSlateGrey"; _sg_colValues[i++] = sgColor3ub(119, 136, 153);
    //_sg_colFlags[i] = 3; _sg_colNames[i] = "gray"; _sg_colValues[i++] = sgColor3ub(190, 190, 190);
    //_sg_colFlags[i] = 3; _sg_colNames[i] = "grey"; _sg_colValues[i++] = sgColor3ub(190, 190, 190);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "LightGrey"; _sg_colValues[i++] = sgColor3ub(211, 211, 211);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "LightGray"; _sg_colValues[i++] = sgColor3ub(211, 211, 211);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "MidnightBlue"; _sg_colValues[i++] = sgColor3ub(25, 25, 112);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "navy"; _sg_colValues[i++] = sgColor3ub(0, 0, 128);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "NavyBlue"; _sg_colValues[i++] = sgColor3ub(0, 0, 128);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "CornflowerBlue"; _sg_colValues[i++] = sgColor3ub(100, 149, 237);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "DarkSlateBlue"; _sg_colValues[i++] = sgColor3ub(72, 61, 139);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "SlateBlue"; _sg_colValues[i++] = sgColor3ub(106, 90, 205);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "MediumSlateBlue"; _sg_colValues[i++] = sgColor3ub(123, 104, 238);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "LightSlateBlue"; _sg_colValues[i++] = sgColor3ub(132, 112, 255);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "MediumBlue"; _sg_colValues[i++] = sgColor3ub(0, 0, 205);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "RoyalBlue"; _sg_colValues[i++] = sgColor3ub(65, 105, 225);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "blue"; _sg_colValues[i++] = sgColor3ub(0, 0, 255);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "DodgerBlue"; _sg_colValues[i++] = sgColor3ub(30, 144, 255);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "DeepSkyBlue"; _sg_colValues[i++] = sgColor3ub(0, 191, 255);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "SkyBlue"; _sg_colValues[i++] = sgColor3ub(135, 206, 235);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "LightSkyBlue"; _sg_colValues[i++] = sgColor3ub(135, 206, 250);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "SteelBlue"; _sg_colValues[i++] = sgColor3ub(70, 130, 180);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "LightSteelBlue"; _sg_colValues[i++] = sgColor3ub(176, 196, 222);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "LightBlue"; _sg_colValues[i++] = sgColor3ub(173, 216, 230);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "PowderBlue"; _sg_colValues[i++] = sgColor3ub(176, 224, 230);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "PaleTurquoise"; _sg_colValues[i++] = sgColor3ub(175, 238, 238);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "DarkTurquoise"; _sg_colValues[i++] = sgColor3ub(0, 206, 209);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "MediumTurquoise"; _sg_colValues[i++] = sgColor3ub(72, 209, 204);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "turquoise"; _sg_colValues[i++] = sgColor3ub(64, 224, 208);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "cyan"; _sg_colValues[i++] = sgColor3ub(0, 255, 255);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "LightCyan"; _sg_colValues[i++] = sgColor3ub(224, 255, 255);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "CadetBlue"; _sg_colValues[i++] = sgColor3ub(95, 158, 160);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "MediumAquamarine"; _sg_colValues[i++] = sgColor3ub(102, 205, 170);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "aquamarine"; _sg_colValues[i++] = sgColor3ub(127, 255, 212);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "DarkGreen"; _sg_colValues[i++] = sgColor3ub(0, 100, 0);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "DarkOliveGreen"; _sg_colValues[i++] = sgColor3ub(85, 107, 47);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "DarkSeaGreen"; _sg_colValues[i++] = sgColor3ub(143, 188, 143);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "SeaGreen"; _sg_colValues[i++] = sgColor3ub(46, 139, 87);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "MediumSeaGreen"; _sg_colValues[i++] = sgColor3ub(60, 179, 113);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "LightSeaGreen"; _sg_colValues[i++] = sgColor3ub(32, 178, 170);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "PaleGreen"; _sg_colValues[i++] = sgColor3ub(152, 251, 152);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "SpringGreen"; _sg_colValues[i++] = sgColor3ub(0, 255, 127);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "LawnGreen"; _sg_colValues[i++] = sgColor3ub(124, 252, 0);
    //_sg_colFlags[i] = 3; _sg_colNames[i] = "green"; _sg_colValues[i++] = sgColor3ub(0, 255, 0);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "chartreuse"; _sg_colValues[i++] = sgColor3ub(127, 255, 0);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "MediumSpringGreen"; _sg_colValues[i++] = sgColor3ub(0, 250, 154);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "GreenYellow"; _sg_colValues[i++] = sgColor3ub(173, 255, 47);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "LimeGreen"; _sg_colValues[i++] = sgColor3ub(50, 205, 50);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "YellowGreen"; _sg_colValues[i++] = sgColor3ub(154, 205, 50);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "ForestGreen"; _sg_colValues[i++] = sgColor3ub(34, 139, 34);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "OliveDrab"; _sg_colValues[i++] = sgColor3ub(107, 142, 35);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "DarkKhaki"; _sg_colValues[i++] = sgColor3ub(189, 183, 107);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "khaki"; _sg_colValues[i++] = sgColor3ub(240, 230, 140);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "PaleGoldenrod"; _sg_colValues[i++] = sgColor3ub(238, 232, 170);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "LightGoldenrodYellow"; _sg_colValues[i++] = sgColor3ub(250, 250, 210);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "LightYellow"; _sg_colValues[i++] = sgColor3ub(255, 255, 224);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "yellow"; _sg_colValues[i++] = sgColor3ub(255, 255, 0);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "gold"; _sg_colValues[i++] = sgColor3ub(255, 215, 0);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "LightGoldenrod"; _sg_colValues[i++] = sgColor3ub(238, 221, 130);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "goldenrod"; _sg_colValues[i++] = sgColor3ub(218, 165, 32);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "DarkGoldenrod"; _sg_colValues[i++] = sgColor3ub(184, 134, 11);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "RosyBrown"; _sg_colValues[i++] = sgColor3ub(188, 143, 143);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "IndianRed"; _sg_colValues[i++] = sgColor3ub(205, 92, 92);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "SaddleBrown"; _sg_colValues[i++] = sgColor3ub(139, 69, 19);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "sienna"; _sg_colValues[i++] = sgColor3ub(160, 82, 45);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "peru"; _sg_colValues[i++] = sgColor3ub(205, 133, 63);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "burlywood"; _sg_colValues[i++] = sgColor3ub(222, 184, 135);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "beige"; _sg_colValues[i++] = sgColor3ub(245, 245, 220);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "wheat"; _sg_colValues[i++] = sgColor3ub(245, 222, 179);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "SandyBrown"; _sg_colValues[i++] = sgColor3ub(244, 164, 96);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "tan"; _sg_colValues[i++] = sgColor3ub(210, 180, 140);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "chocolate"; _sg_colValues[i++] = sgColor3ub(210, 105, 30);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "firebrick"; _sg_colValues[i++] = sgColor3ub(178, 34, 34);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "brown"; _sg_colValues[i++] = sgColor3ub(165, 42, 42);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "DarkSalmon"; _sg_colValues[i++] = sgColor3ub(233, 150, 122);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "salmon"; _sg_colValues[i++] = sgColor3ub(250, 128, 114);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "LightSalmon"; _sg_colValues[i++] = sgColor3ub(255, 160, 122);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "orange"; _sg_colValues[i++] = sgColor3ub(255, 165, 0);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "DarkOrange"; _sg_colValues[i++] = sgColor3ub(255, 140, 0);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "coral"; _sg_colValues[i++] = sgColor3ub(255, 127, 80);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "LightCoral"; _sg_colValues[i++] = sgColor3ub(240, 128, 128);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "tomato"; _sg_colValues[i++] = sgColor3ub(255, 99, 71);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "OrangeRed"; _sg_colValues[i++] = sgColor3ub(255, 69, 0);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "red"; _sg_colValues[i++] = sgColor3ub(255, 0, 0);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "HotPink"; _sg_colValues[i++] = sgColor3ub(255, 105, 180);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "DeepPink"; _sg_colValues[i++] = sgColor3ub(255, 20, 147);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "pink"; _sg_colValues[i++] = sgColor3ub(255, 192, 203);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "LightPink"; _sg_colValues[i++] = sgColor3ub(255, 182, 193);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "PaleVioletRed"; _sg_colValues[i++] = sgColor3ub(219, 112, 147);
    //_sg_colFlags[i] = 3; _sg_colNames[i] = "maroon"; _sg_colValues[i++] = sgColor3ub(176, 48, 96);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "MediumVioletRed"; _sg_colValues[i++] = sgColor3ub(199, 21, 133);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "VioletRed"; _sg_colValues[i++] = sgColor3ub(208, 32, 144);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "magenta"; _sg_colValues[i++] = sgColor3ub(255, 0, 255);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "violet"; _sg_colValues[i++] = sgColor3ub(238, 130, 238);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "plum"; _sg_colValues[i++] = sgColor3ub(221, 160, 221);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "orchid"; _sg_colValues[i++] = sgColor3ub(218, 112, 214);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "MediumOrchid"; _sg_colValues[i++] = sgColor3ub(186, 85, 211);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "DarkOrchid"; _sg_colValues[i++] = sgColor3ub(153, 50, 204);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "DarkViolet"; _sg_colValues[i++] = sgColor3ub(148, 0, 211);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "BlueViolet"; _sg_colValues[i++] = sgColor3ub(138, 43, 226);
    //_sg_colFlags[i] = 3; _sg_colNames[i] = "purple"; _sg_colValues[i++] = sgColor3ub(160, 32, 240);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "MediumPurple"; _sg_colValues[i++] = sgColor3ub(147, 112, 219);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "thistle"; _sg_colValues[i++] = sgColor3ub(216, 191, 216);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "snow1"; _sg_colValues[i++] = sgColor3ub(255, 250, 250);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "snow2"; _sg_colValues[i++] = sgColor3ub(238, 233, 233);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "snow3"; _sg_colValues[i++] = sgColor3ub(205, 201, 201);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "snow4"; _sg_colValues[i++] = sgColor3ub(139, 137, 137);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "seashell1"; _sg_colValues[i++] = sgColor3ub(255, 245, 238);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "seashell2"; _sg_colValues[i++] = sgColor3ub(238, 229, 222);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "seashell3"; _sg_colValues[i++] = sgColor3ub(205, 197, 191);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "seashell4"; _sg_colValues[i++] = sgColor3ub(139, 134, 130);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "AntiqueWhite1"; _sg_colValues[i++] = sgColor3ub(255, 239, 219);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "AntiqueWhite2"; _sg_colValues[i++] = sgColor3ub(238, 223, 204);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "AntiqueWhite3"; _sg_colValues[i++] = sgColor3ub(205, 192, 176);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "AntiqueWhite4"; _sg_colValues[i++] = sgColor3ub(139, 131, 120);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "bisque1"; _sg_colValues[i++] = sgColor3ub(255, 228, 196);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "bisque2"; _sg_colValues[i++] = sgColor3ub(238, 213, 183);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "bisque3"; _sg_colValues[i++] = sgColor3ub(205, 183, 158);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "bisque4"; _sg_colValues[i++] = sgColor3ub(139, 125, 107);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "PeachPuff1"; _sg_colValues[i++] = sgColor3ub(255, 218, 185);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "PeachPuff2"; _sg_colValues[i++] = sgColor3ub(238, 203, 173);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "PeachPuff3"; _sg_colValues[i++] = sgColor3ub(205, 175, 149);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "PeachPuff4"; _sg_colValues[i++] = sgColor3ub(139, 119, 101);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "NavajoWhite1"; _sg_colValues[i++] = sgColor3ub(255, 222, 173);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "NavajoWhite2"; _sg_colValues[i++] = sgColor3ub(238, 207, 161);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "NavajoWhite3"; _sg_colValues[i++] = sgColor3ub(205, 179, 139);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "NavajoWhite4"; _sg_colValues[i++] = sgColor3ub(139, 121, 94);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "LemonChiffon1"; _sg_colValues[i++] = sgColor3ub(255, 250, 205);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "LemonChiffon2"; _sg_colValues[i++] = sgColor3ub(238, 233, 191);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "LemonChiffon3"; _sg_colValues[i++] = sgColor3ub(205, 201, 165);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "LemonChiffon4"; _sg_colValues[i++] = sgColor3ub(139, 137, 112);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "cornsilk1"; _sg_colValues[i++] = sgColor3ub(255, 248, 220);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "cornsilk2"; _sg_colValues[i++] = sgColor3ub(238, 232, 205);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "cornsilk3"; _sg_colValues[i++] = sgColor3ub(205, 200, 177);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "cornsilk4"; _sg_colValues[i++] = sgColor3ub(139, 136, 120);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "ivory1"; _sg_colValues[i++] = sgColor3ub(255, 255, 240);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "ivory2"; _sg_colValues[i++] = sgColor3ub(238, 238, 224);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "ivory3"; _sg_colValues[i++] = sgColor3ub(205, 205, 193);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "ivory4"; _sg_colValues[i++] = sgColor3ub(139, 139, 131);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "honeydew1"; _sg_colValues[i++] = sgColor3ub(240, 255, 240);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "honeydew2"; _sg_colValues[i++] = sgColor3ub(224, 238, 224);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "honeydew3"; _sg_colValues[i++] = sgColor3ub(193, 205, 193);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "honeydew4"; _sg_colValues[i++] = sgColor3ub(131, 139, 131);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "LavenderBlush1"; _sg_colValues[i++] = sgColor3ub(255, 240, 245);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "LavenderBlush2"; _sg_colValues[i++] = sgColor3ub(238, 224, 229);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "LavenderBlush3"; _sg_colValues[i++] = sgColor3ub(205, 193, 197);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "LavenderBlush4"; _sg_colValues[i++] = sgColor3ub(139, 131, 134);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "MistyRose1"; _sg_colValues[i++] = sgColor3ub(255, 228, 225);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "MistyRose2"; _sg_colValues[i++] = sgColor3ub(238, 213, 210);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "MistyRose3"; _sg_colValues[i++] = sgColor3ub(205, 183, 181);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "MistyRose4"; _sg_colValues[i++] = sgColor3ub(139, 125, 123);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "azure1"; _sg_colValues[i++] = sgColor3ub(240, 255, 255);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "azure2"; _sg_colValues[i++] = sgColor3ub(224, 238, 238);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "azure3"; _sg_colValues[i++] = sgColor3ub(193, 205, 205);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "azure4"; _sg_colValues[i++] = sgColor3ub(131, 139, 139);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "SlateBlue1"; _sg_colValues[i++] = sgColor3ub(131, 111, 255);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "SlateBlue2"; _sg_colValues[i++] = sgColor3ub(122, 103, 238);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "SlateBlue3"; _sg_colValues[i++] = sgColor3ub(105, 89, 205);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "SlateBlue4"; _sg_colValues[i++] = sgColor3ub(71, 60, 139);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "RoyalBlue1"; _sg_colValues[i++] = sgColor3ub(72, 118, 255);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "RoyalBlue2"; _sg_colValues[i++] = sgColor3ub(67, 110, 238);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "RoyalBlue3"; _sg_colValues[i++] = sgColor3ub(58, 95, 205);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "RoyalBlue4"; _sg_colValues[i++] = sgColor3ub(39, 64, 139);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "blue1"; _sg_colValues[i++] = sgColor3ub(0, 0, 255);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "blue2"; _sg_colValues[i++] = sgColor3ub(0, 0, 238);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "blue3"; _sg_colValues[i++] = sgColor3ub(0, 0, 205);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "blue4"; _sg_colValues[i++] = sgColor3ub(0, 0, 139);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "DodgerBlue1"; _sg_colValues[i++] = sgColor3ub(30, 144, 255);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "DodgerBlue2"; _sg_colValues[i++] = sgColor3ub(28, 134, 238);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "DodgerBlue3"; _sg_colValues[i++] = sgColor3ub(24, 116, 205);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "DodgerBlue4"; _sg_colValues[i++] = sgColor3ub(16, 78, 139);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "SteelBlue1"; _sg_colValues[i++] = sgColor3ub(99, 184, 255);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "SteelBlue2"; _sg_colValues[i++] = sgColor3ub(92, 172, 238);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "SteelBlue3"; _sg_colValues[i++] = sgColor3ub(79, 148, 205);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "SteelBlue4"; _sg_colValues[i++] = sgColor3ub(54, 100, 139);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "DeepSkyBlue1"; _sg_colValues[i++] = sgColor3ub(0, 191, 255);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "DeepSkyBlue2"; _sg_colValues[i++] = sgColor3ub(0, 178, 238);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "DeepSkyBlue3"; _sg_colValues[i++] = sgColor3ub(0, 154, 205);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "DeepSkyBlue4"; _sg_colValues[i++] = sgColor3ub(0, 104, 139);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "SkyBlue1"; _sg_colValues[i++] = sgColor3ub(135, 206, 255);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "SkyBlue2"; _sg_colValues[i++] = sgColor3ub(126, 192, 238);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "SkyBlue3"; _sg_colValues[i++] = sgColor3ub(108, 166, 205);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "SkyBlue4"; _sg_colValues[i++] = sgColor3ub(74, 112, 139);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "LightSkyBlue1"; _sg_colValues[i++] = sgColor3ub(176, 226, 255);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "LightSkyBlue2"; _sg_colValues[i++] = sgColor3ub(164, 211, 238);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "LightSkyBlue3"; _sg_colValues[i++] = sgColor3ub(141, 182, 205);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "LightSkyBlue4"; _sg_colValues[i++] = sgColor3ub(96, 123, 139);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "SlateGray1"; _sg_colValues[i++] = sgColor3ub(198, 226, 255);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "SlateGray2"; _sg_colValues[i++] = sgColor3ub(185, 211, 238);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "SlateGray3"; _sg_colValues[i++] = sgColor3ub(159, 182, 205);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "SlateGray4"; _sg_colValues[i++] = sgColor3ub(108, 123, 139);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "LightSteelBlue1"; _sg_colValues[i++] = sgColor3ub(202, 225, 255);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "LightSteelBlue2"; _sg_colValues[i++] = sgColor3ub(188, 210, 238);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "LightSteelBlue3"; _sg_colValues[i++] = sgColor3ub(162, 181, 205);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "LightSteelBlue4"; _sg_colValues[i++] = sgColor3ub(110, 123, 139);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "LightBlue1"; _sg_colValues[i++] = sgColor3ub(191, 239, 255);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "LightBlue2"; _sg_colValues[i++] = sgColor3ub(178, 223, 238);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "LightBlue3"; _sg_colValues[i++] = sgColor3ub(154, 192, 205);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "LightBlue4"; _sg_colValues[i++] = sgColor3ub(104, 131, 139);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "LightCyan1"; _sg_colValues[i++] = sgColor3ub(224, 255, 255);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "LightCyan2"; _sg_colValues[i++] = sgColor3ub(209, 238, 238);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "LightCyan3"; _sg_colValues[i++] = sgColor3ub(180, 205, 205);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "LightCyan4"; _sg_colValues[i++] = sgColor3ub(122, 139, 139);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "PaleTurquoise1"; _sg_colValues[i++] = sgColor3ub(187, 255, 255);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "PaleTurquoise2"; _sg_colValues[i++] = sgColor3ub(174, 238, 238);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "PaleTurquoise3"; _sg_colValues[i++] = sgColor3ub(150, 205, 205);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "PaleTurquoise4"; _sg_colValues[i++] = sgColor3ub(102, 139, 139);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "CadetBlue1"; _sg_colValues[i++] = sgColor3ub(152, 245, 255);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "CadetBlue2"; _sg_colValues[i++] = sgColor3ub(142, 229, 238);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "CadetBlue3"; _sg_colValues[i++] = sgColor3ub(122, 197, 205);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "CadetBlue4"; _sg_colValues[i++] = sgColor3ub(83, 134, 139);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "turquoise1"; _sg_colValues[i++] = sgColor3ub(0, 245, 255);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "turquoise2"; _sg_colValues[i++] = sgColor3ub(0, 229, 238);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "turquoise3"; _sg_colValues[i++] = sgColor3ub(0, 197, 205);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "turquoise4"; _sg_colValues[i++] = sgColor3ub(0, 134, 139);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "cyan1"; _sg_colValues[i++] = sgColor3ub(0, 255, 255);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "cyan2"; _sg_colValues[i++] = sgColor3ub(0, 238, 238);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "cyan3"; _sg_colValues[i++] = sgColor3ub(0, 205, 205);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "cyan4"; _sg_colValues[i++] = sgColor3ub(0, 139, 139);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "DarkSlateGray1"; _sg_colValues[i++] = sgColor3ub(151, 255, 255);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "DarkSlateGray2"; _sg_colValues[i++] = sgColor3ub(141, 238, 238);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "DarkSlateGray3"; _sg_colValues[i++] = sgColor3ub(121, 205, 205);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "DarkSlateGray4"; _sg_colValues[i++] = sgColor3ub(82, 139, 139);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "aquamarine1"; _sg_colValues[i++] = sgColor3ub(127, 255, 212);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "aquamarine2"; _sg_colValues[i++] = sgColor3ub(118, 238, 198);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "aquamarine3"; _sg_colValues[i++] = sgColor3ub(102, 205, 170);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "aquamarine4"; _sg_colValues[i++] = sgColor3ub(69, 139, 116);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "DarkSeaGreen1"; _sg_colValues[i++] = sgColor3ub(193, 255, 193);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "DarkSeaGreen2"; _sg_colValues[i++] = sgColor3ub(180, 238, 180);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "DarkSeaGreen3"; _sg_colValues[i++] = sgColor3ub(155, 205, 155);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "DarkSeaGreen4"; _sg_colValues[i++] = sgColor3ub(105, 139, 105);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "SeaGreen1"; _sg_colValues[i++] = sgColor3ub(84, 255, 159);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "SeaGreen2"; _sg_colValues[i++] = sgColor3ub(78, 238, 148);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "SeaGreen3"; _sg_colValues[i++] = sgColor3ub(67, 205, 128);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "SeaGreen4"; _sg_colValues[i++] = sgColor3ub(46, 139, 87);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "PaleGreen1"; _sg_colValues[i++] = sgColor3ub(154, 255, 154);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "PaleGreen2"; _sg_colValues[i++] = sgColor3ub(144, 238, 144);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "PaleGreen3"; _sg_colValues[i++] = sgColor3ub(124, 205, 124);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "PaleGreen4"; _sg_colValues[i++] = sgColor3ub(84, 139, 84);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "SpringGreen1"; _sg_colValues[i++] = sgColor3ub(0, 255, 127);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "SpringGreen2"; _sg_colValues[i++] = sgColor3ub(0, 238, 118);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "SpringGreen3"; _sg_colValues[i++] = sgColor3ub(0, 205, 102);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "SpringGreen4"; _sg_colValues[i++] = sgColor3ub(0, 139, 69);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "green1"; _sg_colValues[i++] = sgColor3ub(0, 255, 0);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "green2"; _sg_colValues[i++] = sgColor3ub(0, 238, 0);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "green3"; _sg_colValues[i++] = sgColor3ub(0, 205, 0);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "green4"; _sg_colValues[i++] = sgColor3ub(0, 139, 0);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "chartreuse1"; _sg_colValues[i++] = sgColor3ub(127, 255, 0);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "chartreuse2"; _sg_colValues[i++] = sgColor3ub(118, 238, 0);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "chartreuse3"; _sg_colValues[i++] = sgColor3ub(102, 205, 0);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "chartreuse4"; _sg_colValues[i++] = sgColor3ub(69, 139, 0);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "OliveDrab1"; _sg_colValues[i++] = sgColor3ub(192, 255, 62);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "OliveDrab2"; _sg_colValues[i++] = sgColor3ub(179, 238, 58);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "OliveDrab3"; _sg_colValues[i++] = sgColor3ub(154, 205, 50);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "OliveDrab4"; _sg_colValues[i++] = sgColor3ub(105, 139, 34);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "DarkOliveGreen1"; _sg_colValues[i++] = sgColor3ub(202, 255, 112);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "DarkOliveGreen2"; _sg_colValues[i++] = sgColor3ub(188, 238, 104);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "DarkOliveGreen3"; _sg_colValues[i++] = sgColor3ub(162, 205, 90);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "DarkOliveGreen4"; _sg_colValues[i++] = sgColor3ub(110, 139, 61);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "khaki1"; _sg_colValues[i++] = sgColor3ub(255, 246, 143);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "khaki2"; _sg_colValues[i++] = sgColor3ub(238, 230, 133);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "khaki3"; _sg_colValues[i++] = sgColor3ub(205, 198, 115);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "khaki4"; _sg_colValues[i++] = sgColor3ub(139, 134, 78);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "LightGoldenrod1"; _sg_colValues[i++] = sgColor3ub(255, 236, 139);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "LightGoldenrod2"; _sg_colValues[i++] = sgColor3ub(238, 220, 130);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "LightGoldenrod3"; _sg_colValues[i++] = sgColor3ub(205, 190, 112);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "LightGoldenrod4"; _sg_colValues[i++] = sgColor3ub(139, 129, 76);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "LightYellow1"; _sg_colValues[i++] = sgColor3ub(255, 255, 224);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "LightYellow2"; _sg_colValues[i++] = sgColor3ub(238, 238, 209);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "LightYellow3"; _sg_colValues[i++] = sgColor3ub(205, 205, 180);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "LightYellow4"; _sg_colValues[i++] = sgColor3ub(139, 139, 122);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "yellow1"; _sg_colValues[i++] = sgColor3ub(255, 255, 0);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "yellow2"; _sg_colValues[i++] = sgColor3ub(238, 238, 0);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "yellow3"; _sg_colValues[i++] = sgColor3ub(205, 205, 0);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "yellow4"; _sg_colValues[i++] = sgColor3ub(139, 139, 0);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gold1"; _sg_colValues[i++] = sgColor3ub(255, 215, 0);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gold2"; _sg_colValues[i++] = sgColor3ub(238, 201, 0);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gold3"; _sg_colValues[i++] = sgColor3ub(205, 173, 0);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gold4"; _sg_colValues[i++] = sgColor3ub(139, 117, 0);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "goldenrod1"; _sg_colValues[i++] = sgColor3ub(255, 193, 37);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "goldenrod2"; _sg_colValues[i++] = sgColor3ub(238, 180, 34);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "goldenrod3"; _sg_colValues[i++] = sgColor3ub(205, 155, 29);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "goldenrod4"; _sg_colValues[i++] = sgColor3ub(139, 105, 20);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "DarkGoldenrod1"; _sg_colValues[i++] = sgColor3ub(255, 185, 15);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "DarkGoldenrod2"; _sg_colValues[i++] = sgColor3ub(238, 173, 14);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "DarkGoldenrod3"; _sg_colValues[i++] = sgColor3ub(205, 149, 12);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "DarkGoldenrod4"; _sg_colValues[i++] = sgColor3ub(139, 101, 8);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "RosyBrown1"; _sg_colValues[i++] = sgColor3ub(255, 193, 193);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "RosyBrown2"; _sg_colValues[i++] = sgColor3ub(238, 180, 180);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "RosyBrown3"; _sg_colValues[i++] = sgColor3ub(205, 155, 155);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "RosyBrown4"; _sg_colValues[i++] = sgColor3ub(139, 105, 105);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "IndianRed1"; _sg_colValues[i++] = sgColor3ub(255, 106, 106);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "IndianRed2"; _sg_colValues[i++] = sgColor3ub(238, 99, 99);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "IndianRed3"; _sg_colValues[i++] = sgColor3ub(205, 85, 85);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "IndianRed4"; _sg_colValues[i++] = sgColor3ub(139, 58, 58);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "sienna1"; _sg_colValues[i++] = sgColor3ub(255, 130, 71);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "sienna2"; _sg_colValues[i++] = sgColor3ub(238, 121, 66);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "sienna3"; _sg_colValues[i++] = sgColor3ub(205, 104, 57);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "sienna4"; _sg_colValues[i++] = sgColor3ub(139, 71, 38);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "burlywood1"; _sg_colValues[i++] = sgColor3ub(255, 211, 155);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "burlywood2"; _sg_colValues[i++] = sgColor3ub(238, 197, 145);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "burlywood3"; _sg_colValues[i++] = sgColor3ub(205, 170, 125);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "burlywood4"; _sg_colValues[i++] = sgColor3ub(139, 115, 85);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "wheat1"; _sg_colValues[i++] = sgColor3ub(255, 231, 186);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "wheat2"; _sg_colValues[i++] = sgColor3ub(238, 216, 174);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "wheat3"; _sg_colValues[i++] = sgColor3ub(205, 186, 150);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "wheat4"; _sg_colValues[i++] = sgColor3ub(139, 126, 102);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "tan1"; _sg_colValues[i++] = sgColor3ub(255, 165, 79);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "tan2"; _sg_colValues[i++] = sgColor3ub(238, 154, 73);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "tan3"; _sg_colValues[i++] = sgColor3ub(205, 133, 63);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "tan4"; _sg_colValues[i++] = sgColor3ub(139, 90, 43);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "chocolate1"; _sg_colValues[i++] = sgColor3ub(255, 127, 36);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "chocolate2"; _sg_colValues[i++] = sgColor3ub(238, 118, 33);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "chocolate3"; _sg_colValues[i++] = sgColor3ub(205, 102, 29);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "chocolate4"; _sg_colValues[i++] = sgColor3ub(139, 69, 19);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "firebrick1"; _sg_colValues[i++] = sgColor3ub(255, 48, 48);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "firebrick2"; _sg_colValues[i++] = sgColor3ub(238, 44, 44);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "firebrick3"; _sg_colValues[i++] = sgColor3ub(205, 38, 38);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "firebrick4"; _sg_colValues[i++] = sgColor3ub(139, 26, 26);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "brown1"; _sg_colValues[i++] = sgColor3ub(255, 64, 64);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "brown2"; _sg_colValues[i++] = sgColor3ub(238, 59, 59);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "brown3"; _sg_colValues[i++] = sgColor3ub(205, 51, 51);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "brown4"; _sg_colValues[i++] = sgColor3ub(139, 35, 35);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "salmon1"; _sg_colValues[i++] = sgColor3ub(255, 140, 105);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "salmon2"; _sg_colValues[i++] = sgColor3ub(238, 130, 98);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "salmon3"; _sg_colValues[i++] = sgColor3ub(205, 112, 84);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "salmon4"; _sg_colValues[i++] = sgColor3ub(139, 76, 57);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "LightSalmon1"; _sg_colValues[i++] = sgColor3ub(255, 160, 122);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "LightSalmon2"; _sg_colValues[i++] = sgColor3ub(238, 149, 114);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "LightSalmon3"; _sg_colValues[i++] = sgColor3ub(205, 129, 98);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "LightSalmon4"; _sg_colValues[i++] = sgColor3ub(139, 87, 66);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "orange1"; _sg_colValues[i++] = sgColor3ub(255, 165, 0);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "orange2"; _sg_colValues[i++] = sgColor3ub(238, 154, 0);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "orange3"; _sg_colValues[i++] = sgColor3ub(205, 133, 0);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "orange4"; _sg_colValues[i++] = sgColor3ub(139, 90, 0);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "DarkOrange1"; _sg_colValues[i++] = sgColor3ub(255, 127, 0);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "DarkOrange2"; _sg_colValues[i++] = sgColor3ub(238, 118, 0);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "DarkOrange3"; _sg_colValues[i++] = sgColor3ub(205, 102, 0);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "DarkOrange4"; _sg_colValues[i++] = sgColor3ub(139, 69, 0);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "coral1"; _sg_colValues[i++] = sgColor3ub(255, 114, 86);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "coral2"; _sg_colValues[i++] = sgColor3ub(238, 106, 80);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "coral3"; _sg_colValues[i++] = sgColor3ub(205, 91, 69);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "coral4"; _sg_colValues[i++] = sgColor3ub(139, 62, 47);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "tomato1"; _sg_colValues[i++] = sgColor3ub(255, 99, 71);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "tomato2"; _sg_colValues[i++] = sgColor3ub(238, 92, 66);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "tomato3"; _sg_colValues[i++] = sgColor3ub(205, 79, 57);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "tomato4"; _sg_colValues[i++] = sgColor3ub(139, 54, 38);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "OrangeRed1"; _sg_colValues[i++] = sgColor3ub(255, 69, 0);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "OrangeRed2"; _sg_colValues[i++] = sgColor3ub(238, 64, 0);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "OrangeRed3"; _sg_colValues[i++] = sgColor3ub(205, 55, 0);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "OrangeRed4"; _sg_colValues[i++] = sgColor3ub(139, 37, 0);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "red1"; _sg_colValues[i++] = sgColor3ub(255, 0, 0);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "red2"; _sg_colValues[i++] = sgColor3ub(238, 0, 0);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "red3"; _sg_colValues[i++] = sgColor3ub(205, 0, 0);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "red4"; _sg_colValues[i++] = sgColor3ub(139, 0, 0);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "DeepPink1"; _sg_colValues[i++] = sgColor3ub(255, 20, 147);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "DeepPink2"; _sg_colValues[i++] = sgColor3ub(238, 18, 137);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "DeepPink3"; _sg_colValues[i++] = sgColor3ub(205, 16, 118);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "DeepPink4"; _sg_colValues[i++] = sgColor3ub(139, 10, 80);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "HotPink1"; _sg_colValues[i++] = sgColor3ub(255, 110, 180);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "HotPink2"; _sg_colValues[i++] = sgColor3ub(238, 106, 167);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "HotPink3"; _sg_colValues[i++] = sgColor3ub(205, 96, 144);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "HotPink4"; _sg_colValues[i++] = sgColor3ub(139, 58, 98);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "pink1"; _sg_colValues[i++] = sgColor3ub(255, 181, 197);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "pink2"; _sg_colValues[i++] = sgColor3ub(238, 169, 184);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "pink3"; _sg_colValues[i++] = sgColor3ub(205, 145, 158);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "pink4"; _sg_colValues[i++] = sgColor3ub(139, 99, 108);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "LightPink1"; _sg_colValues[i++] = sgColor3ub(255, 174, 185);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "LightPink2"; _sg_colValues[i++] = sgColor3ub(238, 162, 173);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "LightPink3"; _sg_colValues[i++] = sgColor3ub(205, 140, 149);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "LightPink4"; _sg_colValues[i++] = sgColor3ub(139, 95, 101);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "PaleVioletRed1"; _sg_colValues[i++] = sgColor3ub(255, 130, 171);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "PaleVioletRed2"; _sg_colValues[i++] = sgColor3ub(238, 121, 159);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "PaleVioletRed3"; _sg_colValues[i++] = sgColor3ub(205, 104, 137);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "PaleVioletRed4"; _sg_colValues[i++] = sgColor3ub(139, 71, 93);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "maroon1"; _sg_colValues[i++] = sgColor3ub(255, 52, 179);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "maroon2"; _sg_colValues[i++] = sgColor3ub(238, 48, 167);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "maroon3"; _sg_colValues[i++] = sgColor3ub(205, 41, 144);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "maroon4"; _sg_colValues[i++] = sgColor3ub(139, 28, 98);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "VioletRed1"; _sg_colValues[i++] = sgColor3ub(255, 62, 150);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "VioletRed2"; _sg_colValues[i++] = sgColor3ub(238, 58, 140);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "VioletRed3"; _sg_colValues[i++] = sgColor3ub(205, 50, 120);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "VioletRed4"; _sg_colValues[i++] = sgColor3ub(139, 34, 82);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "magenta1"; _sg_colValues[i++] = sgColor3ub(255, 0, 255);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "magenta2"; _sg_colValues[i++] = sgColor3ub(238, 0, 238);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "magenta3"; _sg_colValues[i++] = sgColor3ub(205, 0, 205);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "magenta4"; _sg_colValues[i++] = sgColor3ub(139, 0, 139);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "orchid1"; _sg_colValues[i++] = sgColor3ub(255, 131, 250);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "orchid2"; _sg_colValues[i++] = sgColor3ub(238, 122, 233);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "orchid3"; _sg_colValues[i++] = sgColor3ub(205, 105, 201);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "orchid4"; _sg_colValues[i++] = sgColor3ub(139, 71, 137);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "plum1"; _sg_colValues[i++] = sgColor3ub(255, 187, 255);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "plum2"; _sg_colValues[i++] = sgColor3ub(238, 174, 238);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "plum3"; _sg_colValues[i++] = sgColor3ub(205, 150, 205);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "plum4"; _sg_colValues[i++] = sgColor3ub(139, 102, 139);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "MediumOrchid1"; _sg_colValues[i++] = sgColor3ub(224, 102, 255);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "MediumOrchid2"; _sg_colValues[i++] = sgColor3ub(209, 95, 238);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "MediumOrchid3"; _sg_colValues[i++] = sgColor3ub(180, 82, 205);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "MediumOrchid4"; _sg_colValues[i++] = sgColor3ub(122, 55, 139);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "DarkOrchid1"; _sg_colValues[i++] = sgColor3ub(191, 62, 255);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "DarkOrchid2"; _sg_colValues[i++] = sgColor3ub(178, 58, 238);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "DarkOrchid3"; _sg_colValues[i++] = sgColor3ub(154, 50, 205);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "DarkOrchid4"; _sg_colValues[i++] = sgColor3ub(104, 34, 139);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "purple1"; _sg_colValues[i++] = sgColor3ub(155, 48, 255);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "purple2"; _sg_colValues[i++] = sgColor3ub(145, 44, 238);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "purple3"; _sg_colValues[i++] = sgColor3ub(125, 38, 205);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "purple4"; _sg_colValues[i++] = sgColor3ub(85, 26, 139);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "MediumPurple1"; _sg_colValues[i++] = sgColor3ub(171, 130, 255);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "MediumPurple2"; _sg_colValues[i++] = sgColor3ub(159, 121, 238);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "MediumPurple3"; _sg_colValues[i++] = sgColor3ub(137, 104, 205);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "MediumPurple4"; _sg_colValues[i++] = sgColor3ub(93, 71, 139);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "thistle1"; _sg_colValues[i++] = sgColor3ub(255, 225, 255);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "thistle2"; _sg_colValues[i++] = sgColor3ub(238, 210, 238);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "thistle3"; _sg_colValues[i++] = sgColor3ub(205, 181, 205);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "thistle4"; _sg_colValues[i++] = sgColor3ub(139, 123, 139);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray0"; _sg_colValues[i++] = sgColor3ub(0, 0, 0);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey0"; _sg_colValues[i++] = sgColor3ub(0, 0, 0);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray1"; _sg_colValues[i++] = sgColor3ub(3, 3, 3);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey1"; _sg_colValues[i++] = sgColor3ub(3, 3, 3);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray2"; _sg_colValues[i++] = sgColor3ub(5, 5, 5);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey2"; _sg_colValues[i++] = sgColor3ub(5, 5, 5);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray3"; _sg_colValues[i++] = sgColor3ub(8, 8, 8);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey3"; _sg_colValues[i++] = sgColor3ub(8, 8, 8);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray4"; _sg_colValues[i++] = sgColor3ub(10, 10, 10);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey4"; _sg_colValues[i++] = sgColor3ub(10, 10, 10);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray5"; _sg_colValues[i++] = sgColor3ub(13, 13, 13);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey5"; _sg_colValues[i++] = sgColor3ub(13, 13, 13);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray6"; _sg_colValues[i++] = sgColor3ub(15, 15, 15);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey6"; _sg_colValues[i++] = sgColor3ub(15, 15, 15);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray7"; _sg_colValues[i++] = sgColor3ub(18, 18, 18);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey7"; _sg_colValues[i++] = sgColor3ub(18, 18, 18);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray8"; _sg_colValues[i++] = sgColor3ub(20, 20, 20);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey8"; _sg_colValues[i++] = sgColor3ub(20, 20, 20);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray9"; _sg_colValues[i++] = sgColor3ub(23, 23, 23);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey9"; _sg_colValues[i++] = sgColor3ub(23, 23, 23);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray10"; _sg_colValues[i++] = sgColor3ub(26, 26, 26);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey10"; _sg_colValues[i++] = sgColor3ub(26, 26, 26);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray11"; _sg_colValues[i++] = sgColor3ub(28, 28, 28);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey11"; _sg_colValues[i++] = sgColor3ub(28, 28, 28);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray12"; _sg_colValues[i++] = sgColor3ub(31, 31, 31);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey12"; _sg_colValues[i++] = sgColor3ub(31, 31, 31);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray13"; _sg_colValues[i++] = sgColor3ub(33, 33, 33);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey13"; _sg_colValues[i++] = sgColor3ub(33, 33, 33);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray14"; _sg_colValues[i++] = sgColor3ub(36, 36, 36);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey14"; _sg_colValues[i++] = sgColor3ub(36, 36, 36);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray15"; _sg_colValues[i++] = sgColor3ub(38, 38, 38);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey15"; _sg_colValues[i++] = sgColor3ub(38, 38, 38);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray16"; _sg_colValues[i++] = sgColor3ub(41, 41, 41);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey16"; _sg_colValues[i++] = sgColor3ub(41, 41, 41);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray17"; _sg_colValues[i++] = sgColor3ub(43, 43, 43);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey17"; _sg_colValues[i++] = sgColor3ub(43, 43, 43);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray18"; _sg_colValues[i++] = sgColor3ub(46, 46, 46);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey18"; _sg_colValues[i++] = sgColor3ub(46, 46, 46);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray19"; _sg_colValues[i++] = sgColor3ub(48, 48, 48);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey19"; _sg_colValues[i++] = sgColor3ub(48, 48, 48);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray20"; _sg_colValues[i++] = sgColor3ub(51, 51, 51);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey20"; _sg_colValues[i++] = sgColor3ub(51, 51, 51);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray21"; _sg_colValues[i++] = sgColor3ub(54, 54, 54);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey21"; _sg_colValues[i++] = sgColor3ub(54, 54, 54);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray22"; _sg_colValues[i++] = sgColor3ub(56, 56, 56);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey22"; _sg_colValues[i++] = sgColor3ub(56, 56, 56);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray23"; _sg_colValues[i++] = sgColor3ub(59, 59, 59);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey23"; _sg_colValues[i++] = sgColor3ub(59, 59, 59);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray24"; _sg_colValues[i++] = sgColor3ub(61, 61, 61);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey24"; _sg_colValues[i++] = sgColor3ub(61, 61, 61);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray25"; _sg_colValues[i++] = sgColor3ub(64, 64, 64);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey25"; _sg_colValues[i++] = sgColor3ub(64, 64, 64);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray26"; _sg_colValues[i++] = sgColor3ub(66, 66, 66);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey26"; _sg_colValues[i++] = sgColor3ub(66, 66, 66);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray27"; _sg_colValues[i++] = sgColor3ub(69, 69, 69);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey27"; _sg_colValues[i++] = sgColor3ub(69, 69, 69);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray28"; _sg_colValues[i++] = sgColor3ub(71, 71, 71);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey28"; _sg_colValues[i++] = sgColor3ub(71, 71, 71);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray29"; _sg_colValues[i++] = sgColor3ub(74, 74, 74);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey29"; _sg_colValues[i++] = sgColor3ub(74, 74, 74);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray30"; _sg_colValues[i++] = sgColor3ub(77, 77, 77);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey30"; _sg_colValues[i++] = sgColor3ub(77, 77, 77);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray31"; _sg_colValues[i++] = sgColor3ub(79, 79, 79);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey31"; _sg_colValues[i++] = sgColor3ub(79, 79, 79);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray32"; _sg_colValues[i++] = sgColor3ub(82, 82, 82);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey32"; _sg_colValues[i++] = sgColor3ub(82, 82, 82);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray33"; _sg_colValues[i++] = sgColor3ub(84, 84, 84);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey33"; _sg_colValues[i++] = sgColor3ub(84, 84, 84);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray34"; _sg_colValues[i++] = sgColor3ub(87, 87, 87);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey34"; _sg_colValues[i++] = sgColor3ub(87, 87, 87);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray35"; _sg_colValues[i++] = sgColor3ub(89, 89, 89);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey35"; _sg_colValues[i++] = sgColor3ub(89, 89, 89);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray36"; _sg_colValues[i++] = sgColor3ub(92, 92, 92);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey36"; _sg_colValues[i++] = sgColor3ub(92, 92, 92);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray37"; _sg_colValues[i++] = sgColor3ub(94, 94, 94);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey37"; _sg_colValues[i++] = sgColor3ub(94, 94, 94);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray38"; _sg_colValues[i++] = sgColor3ub(97, 97, 97);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey38"; _sg_colValues[i++] = sgColor3ub(97, 97, 97);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray39"; _sg_colValues[i++] = sgColor3ub(99, 99, 99);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey39"; _sg_colValues[i++] = sgColor3ub(99, 99, 99);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray40"; _sg_colValues[i++] = sgColor3ub(102, 102, 102);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey40"; _sg_colValues[i++] = sgColor3ub(102, 102, 102);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray41"; _sg_colValues[i++] = sgColor3ub(105, 105, 105);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey41"; _sg_colValues[i++] = sgColor3ub(105, 105, 105);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray42"; _sg_colValues[i++] = sgColor3ub(107, 107, 107);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey42"; _sg_colValues[i++] = sgColor3ub(107, 107, 107);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray43"; _sg_colValues[i++] = sgColor3ub(110, 110, 110);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey43"; _sg_colValues[i++] = sgColor3ub(110, 110, 110);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray44"; _sg_colValues[i++] = sgColor3ub(112, 112, 112);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey44"; _sg_colValues[i++] = sgColor3ub(112, 112, 112);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray45"; _sg_colValues[i++] = sgColor3ub(115, 115, 115);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey45"; _sg_colValues[i++] = sgColor3ub(115, 115, 115);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray46"; _sg_colValues[i++] = sgColor3ub(117, 117, 117);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey46"; _sg_colValues[i++] = sgColor3ub(117, 117, 117);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray47"; _sg_colValues[i++] = sgColor3ub(120, 120, 120);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey47"; _sg_colValues[i++] = sgColor3ub(120, 120, 120);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray48"; _sg_colValues[i++] = sgColor3ub(122, 122, 122);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey48"; _sg_colValues[i++] = sgColor3ub(122, 122, 122);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray49"; _sg_colValues[i++] = sgColor3ub(125, 125, 125);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey49"; _sg_colValues[i++] = sgColor3ub(125, 125, 125);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray50"; _sg_colValues[i++] = sgColor3ub(127, 127, 127);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey50"; _sg_colValues[i++] = sgColor3ub(127, 127, 127);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray51"; _sg_colValues[i++] = sgColor3ub(130, 130, 130);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey51"; _sg_colValues[i++] = sgColor3ub(130, 130, 130);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray52"; _sg_colValues[i++] = sgColor3ub(133, 133, 133);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey52"; _sg_colValues[i++] = sgColor3ub(133, 133, 133);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray53"; _sg_colValues[i++] = sgColor3ub(135, 135, 135);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey53"; _sg_colValues[i++] = sgColor3ub(135, 135, 135);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray54"; _sg_colValues[i++] = sgColor3ub(138, 138, 138);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey54"; _sg_colValues[i++] = sgColor3ub(138, 138, 138);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray55"; _sg_colValues[i++] = sgColor3ub(140, 140, 140);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey55"; _sg_colValues[i++] = sgColor3ub(140, 140, 140);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray56"; _sg_colValues[i++] = sgColor3ub(143, 143, 143);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey56"; _sg_colValues[i++] = sgColor3ub(143, 143, 143);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray57"; _sg_colValues[i++] = sgColor3ub(145, 145, 145);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey57"; _sg_colValues[i++] = sgColor3ub(145, 145, 145);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray58"; _sg_colValues[i++] = sgColor3ub(148, 148, 148);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey58"; _sg_colValues[i++] = sgColor3ub(148, 148, 148);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray59"; _sg_colValues[i++] = sgColor3ub(150, 150, 150);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey59"; _sg_colValues[i++] = sgColor3ub(150, 150, 150);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray60"; _sg_colValues[i++] = sgColor3ub(153, 153, 153);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey60"; _sg_colValues[i++] = sgColor3ub(153, 153, 153);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray61"; _sg_colValues[i++] = sgColor3ub(156, 156, 156);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey61"; _sg_colValues[i++] = sgColor3ub(156, 156, 156);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray62"; _sg_colValues[i++] = sgColor3ub(158, 158, 158);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey62"; _sg_colValues[i++] = sgColor3ub(158, 158, 158);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray63"; _sg_colValues[i++] = sgColor3ub(161, 161, 161);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey63"; _sg_colValues[i++] = sgColor3ub(161, 161, 161);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray64"; _sg_colValues[i++] = sgColor3ub(163, 163, 163);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey64"; _sg_colValues[i++] = sgColor3ub(163, 163, 163);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray65"; _sg_colValues[i++] = sgColor3ub(166, 166, 166);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey65"; _sg_colValues[i++] = sgColor3ub(166, 166, 166);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray66"; _sg_colValues[i++] = sgColor3ub(168, 168, 168);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey66"; _sg_colValues[i++] = sgColor3ub(168, 168, 168);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray67"; _sg_colValues[i++] = sgColor3ub(171, 171, 171);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey67"; _sg_colValues[i++] = sgColor3ub(171, 171, 171);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray68"; _sg_colValues[i++] = sgColor3ub(173, 173, 173);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey68"; _sg_colValues[i++] = sgColor3ub(173, 173, 173);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray69"; _sg_colValues[i++] = sgColor3ub(176, 176, 176);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey69"; _sg_colValues[i++] = sgColor3ub(176, 176, 176);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray70"; _sg_colValues[i++] = sgColor3ub(179, 179, 179);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey70"; _sg_colValues[i++] = sgColor3ub(179, 179, 179);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray71"; _sg_colValues[i++] = sgColor3ub(181, 181, 181);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey71"; _sg_colValues[i++] = sgColor3ub(181, 181, 181);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray72"; _sg_colValues[i++] = sgColor3ub(184, 184, 184);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey72"; _sg_colValues[i++] = sgColor3ub(184, 184, 184);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray73"; _sg_colValues[i++] = sgColor3ub(186, 186, 186);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey73"; _sg_colValues[i++] = sgColor3ub(186, 186, 186);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray74"; _sg_colValues[i++] = sgColor3ub(189, 189, 189);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey74"; _sg_colValues[i++] = sgColor3ub(189, 189, 189);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray75"; _sg_colValues[i++] = sgColor3ub(191, 191, 191);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey75"; _sg_colValues[i++] = sgColor3ub(191, 191, 191);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray76"; _sg_colValues[i++] = sgColor3ub(194, 194, 194);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey76"; _sg_colValues[i++] = sgColor3ub(194, 194, 194);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray77"; _sg_colValues[i++] = sgColor3ub(196, 196, 196);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey77"; _sg_colValues[i++] = sgColor3ub(196, 196, 196);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray78"; _sg_colValues[i++] = sgColor3ub(199, 199, 199);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey78"; _sg_colValues[i++] = sgColor3ub(199, 199, 199);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray79"; _sg_colValues[i++] = sgColor3ub(201, 201, 201);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey79"; _sg_colValues[i++] = sgColor3ub(201, 201, 201);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray80"; _sg_colValues[i++] = sgColor3ub(204, 204, 204);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey80"; _sg_colValues[i++] = sgColor3ub(204, 204, 204);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray81"; _sg_colValues[i++] = sgColor3ub(207, 207, 207);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey81"; _sg_colValues[i++] = sgColor3ub(207, 207, 207);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray82"; _sg_colValues[i++] = sgColor3ub(209, 209, 209);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey82"; _sg_colValues[i++] = sgColor3ub(209, 209, 209);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray83"; _sg_colValues[i++] = sgColor3ub(212, 212, 212);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey83"; _sg_colValues[i++] = sgColor3ub(212, 212, 212);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray84"; _sg_colValues[i++] = sgColor3ub(214, 214, 214);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey84"; _sg_colValues[i++] = sgColor3ub(214, 214, 214);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray85"; _sg_colValues[i++] = sgColor3ub(217, 217, 217);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey85"; _sg_colValues[i++] = sgColor3ub(217, 217, 217);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray86"; _sg_colValues[i++] = sgColor3ub(219, 219, 219);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey86"; _sg_colValues[i++] = sgColor3ub(219, 219, 219);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray87"; _sg_colValues[i++] = sgColor3ub(222, 222, 222);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey87"; _sg_colValues[i++] = sgColor3ub(222, 222, 222);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray88"; _sg_colValues[i++] = sgColor3ub(224, 224, 224);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey88"; _sg_colValues[i++] = sgColor3ub(224, 224, 224);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray89"; _sg_colValues[i++] = sgColor3ub(227, 227, 227);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey89"; _sg_colValues[i++] = sgColor3ub(227, 227, 227);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray90"; _sg_colValues[i++] = sgColor3ub(229, 229, 229);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey90"; _sg_colValues[i++] = sgColor3ub(229, 229, 229);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray91"; _sg_colValues[i++] = sgColor3ub(232, 232, 232);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey91"; _sg_colValues[i++] = sgColor3ub(232, 232, 232);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray92"; _sg_colValues[i++] = sgColor3ub(235, 235, 235);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey92"; _sg_colValues[i++] = sgColor3ub(235, 235, 235);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray93"; _sg_colValues[i++] = sgColor3ub(237, 237, 237);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey93"; _sg_colValues[i++] = sgColor3ub(237, 237, 237);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray94"; _sg_colValues[i++] = sgColor3ub(240, 240, 240);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey94"; _sg_colValues[i++] = sgColor3ub(240, 240, 240);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray95"; _sg_colValues[i++] = sgColor3ub(242, 242, 242);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey95"; _sg_colValues[i++] = sgColor3ub(242, 242, 242);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray96"; _sg_colValues[i++] = sgColor3ub(245, 245, 245);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey96"; _sg_colValues[i++] = sgColor3ub(245, 245, 245);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray97"; _sg_colValues[i++] = sgColor3ub(247, 247, 247);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey97"; _sg_colValues[i++] = sgColor3ub(247, 247, 247);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray98"; _sg_colValues[i++] = sgColor3ub(250, 250, 250);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey98"; _sg_colValues[i++] = sgColor3ub(250, 250, 250);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray99"; _sg_colValues[i++] = sgColor3ub(252, 252, 252);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey99"; _sg_colValues[i++] = sgColor3ub(252, 252, 252);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "gray100"; _sg_colValues[i++] = sgColor3ub(255, 255, 255);
    _sg_colFlags[i] = 1; _sg_colNames[i] = "grey100"; _sg_colValues[i++] = sgColor3ub(255, 255, 255);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "DarkGrey"; _sg_colValues[i++] = sgColor3ub(169, 169, 169);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "DarkGray"; _sg_colValues[i++] = sgColor3ub(169, 169, 169);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "DarkBlue"; _sg_colValues[i++] = sgColor3ub(0, 0, 139);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "DarkCyan"; _sg_colValues[i++] = sgColor3ub(0, 139, 139);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "DarkMagenta"; _sg_colValues[i++] = sgColor3ub(139, 0, 139);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "DarkRed"; _sg_colValues[i++] = sgColor3ub(139, 0, 0);
    _sg_colFlags[i] = 3; _sg_colNames[i] = "LightGreen"; _sg_colValues[i++] = sgColor3ub(144, 238, 144);

    return SG_TRUE;
}
SGbool SG_EXPORT _sgColorDeinit(void)
{
    free(_sg_colFlags);
    free(_sg_colNames);
    free(_sg_colValues);

    return SG_TRUE;
}

void SG_EXPORT _sgColorPreprocess(char* buf, size_t buflen, char* name)
{
    size_t i, j;
    for(i = 0; name[i] && (j < (buflen - 1)); i++)
    {
        if(name[i] == ' ')
            continue;
        buf[j] = tolower(name[i]);

        j++;
    }
    buf[j] = 0;
}
SGColor SG_EXPORT _sgColorValue(char* name, SGubyte flag)
{
    char buf[256];
    size_t i;

    for(i = 0; i < _sg_colNum; i++)
    {
        if(!(_sg_colFlags[i] & flag))
            continue;

        // can be removed once the colors above are filtered
        _sgColorPreprocess(buf, sizeof(buf), _sg_colNames[i]);

        if(strcmp(name, buf) == 0)
            return _sg_colValues[i];
    }

    return sgColorNan();
}

SGColor SG_EXPORT sgColor4f(float r, float g, float b, float a)
{
    SGColor c = {r, g, b, a};
    return c;
}
SGColor SG_EXPORT sgColor3f(float r, float g, float b)
{
    return sgColor4f(r, g, b, 1.0);
}
SGColor SG_EXPORT sgColor2f(float g, float a)
{
    return sgColor4f(g, g, g, a);
}
SGColor SG_EXPORT sgColor1f(float g)
{
    return sgColor4f(g, g, g, 1.0);
}
SGColor SG_EXPORT sgColor4fv(float* f)
{
    return sgColor4f(f[0], f[1], f[2], f[3]);
}
SGColor SG_EXPORT sgColor3fv(float* f)
{
    return sgColor4f(f[0], f[1], f[2], 1.0);
}
SGColor SG_EXPORT sgColor2fv(float* f)
{
    return sgColor4f(f[0], f[0], f[0], f[1]);
}
SGColor SG_EXPORT sgColor1fv(float* f)
{
    return sgColor4f(f[0], f[0], f[0], 1.0);
}
SGColor SG_EXPORT sgColor4ub(SGubyte r, SGubyte g, SGubyte b, SGubyte a)
{
    return sgColor4f(r / 255.0, g / 255.0, b / 255.0, a / 255.0);
}
SGColor SG_EXPORT sgColor3ub(SGubyte r, SGubyte g, SGubyte b)
{
    return sgColor4ub(r, g, b, 255);
}
SGColor SG_EXPORT sgColor2ub(SGubyte g, SGubyte a)
{
    return sgColor4ub(g, g, g, a);
}
SGColor SG_EXPORT sgColor1ub(SGubyte g)
{
    return sgColor4ub(g, g, g, 255);
}
SGColor SG_EXPORT sgColor4ubv(SGubyte* ub)
{
    return sgColor4ub(ub[0], ub[1], ub[2], ub[3]);
}
SGColor SG_EXPORT sgColor3ubv(SGubyte* ub)
{
    return sgColor4ub(ub[0], ub[1], ub[2], 255);
}
SGColor SG_EXPORT sgColor2ubv(SGubyte* ub)
{
    return sgColor4ub(ub[0], ub[0], ub[0], ub[1]);
}
SGColor SG_EXPORT sgColor1ubv(SGubyte* ub)
{
    return sgColor4ub(ub[0], ub[0], ub[0], 255);
}
SGColor SG_EXPORT sgColorRGBA(SGuint color)
{
    return sgColor4ub(color >> 24, color >> 16, color >> 8, color);
}
SGColor SG_EXPORT sgColorBGRA(SGuint color)
{
    return sgColor4ub(color >> 8, color >> 16, color >> 24, color);
}
SGColor SG_EXPORT sgColorARGB(SGuint color)
{
    return sgColor4ub(color >> 16, color >> 8, color, color >> 24);
}
SGColor SG_EXPORT sgColorABGR(SGuint color)
{
    return sgColor4ub(color, color >> 8, color >> 16, color >> 24);
}
SGColor SG_EXPORT sgColorRGB(SGuint color)
{
    return sgColor4ub(color >> 16, color >> 8, color, 255);
}
SGColor SG_EXPORT sgColorBGR(SGuint color)
{
    return sgColor4ub(color, color >> 8, color >> 16, 255);
}
SGColor SG_EXPORT sgColorX11(char* name)
{
    char bufn[256];
    _sgColorPreprocess(bufn, sizeof(bufn), name);

    // special cases
    if(strcmp(bufn, "gray") == 0)
        return sgColor3ub(190, 190, 190);
    else if(strcmp(bufn, "grey") == 0)
        return sgColor3ub(190, 190, 190);
    else if(strcmp(bufn, "green") == 0)
        return sgColor3ub(0, 255, 0);
    else if(strcmp(bufn, "maroon") == 0)
        return sgColor3ub(176, 48, 96);
    else if(strcmp(bufn, "purple") == 0)
        return sgColor3ub(160, 32, 240);

    return _sgColorValue(bufn, 1);
}
SGColor SG_EXPORT sgColorWeb(char* name)
{
    char bufn[256];
    _sgColorPreprocess(bufn, sizeof(bufn), name);

    // special cases
    if(strcmp(bufn, "gray") == 0)
        return sgColor3ub(127, 127, 127);
    else if(strcmp(bufn, "grey") == 0)
        return sgColor3ub(127, 127, 127);
    else if(strcmp(bufn, "green") == 0)
        return sgColor3ub(0, 127, 0);
    else if(strcmp(bufn, "maroon") == 0)
        return sgColor3ub(127, 0, 0);
    else if(strcmp(bufn, "purple") == 0)
        return sgColor3ub(127, 0, 127);

    return _sgColorValue(bufn, 2);
}
SGColor SG_EXPORT sgColorNan(void)
{
    return sgColor4f(SG_NAN, SG_NAN, SG_NAN, SG_NAN);
}

SGbool SG_EXPORT sgColorIsNan(SGColor c)
{
    return (c.r != c.r) || (c.g != c.g) || (c.b != c.b) || (c.a != c.a);
}

SGColor SG_EXPORT sgColorMix(SGColor a, SGColor b, float t)
{
    return sgColor4f(a.r + t * (b.r - a.r),
                     a.g + t * (b.g - a.g),
                     a.b + t * (b.b - a.b),
                     a.a + t * (b.a - a.a));
}
SGColor SG_EXPORT sgColorAdd1c(SGColor a, SGColor b)
{
    return sgColor4f(a.r + b.r,
                     a.g + b.g,
                     a.b + b.b,
                     a.a + b.a);
}
SGColor SG_EXPORT sgColorSub1c(SGColor a, SGColor b)
{
    return sgColor4f(a.r - b.r,
                     a.g - b.g,
                     a.b - b.b,
                     a.a - b.a);
}
SGColor SG_EXPORT sgColorMul1c(SGColor a, SGColor b)
{
    return sgColor4f(a.r * b.r,
                     a.g * b.g,
                     a.b * b.b,
                     a.a * b.a);
}
SGColor SG_EXPORT sgColorDiv1c(SGColor a, SGColor b)
{
    return sgColor4f(a.r / b.r,
                     a.g / b.g,
                     a.b / b.b,
                     a.a / b.a);
}
