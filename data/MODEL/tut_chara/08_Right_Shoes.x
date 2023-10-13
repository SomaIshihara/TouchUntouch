xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 225;
 -2.26752;5.78316;2.19796;,
 -0.80592;4.35680;3.25778;,
 -0.73742;5.71378;2.94006;,
 -2.36088;4.28404;2.43360;,
 -0.87295;2.95019;3.59092;,
 -3.23582;4.44515;0.63183;,
 -3.20093;5.91234;0.37585;,
 -3.58414;4.57047;-1.75525;,
 -2.57471;2.84602;2.80077;,
 -0.95069;0.43353;4.04682;,
 -3.43249;2.77387;0.82668;,
 -3.57183;2.78716;-1.69434;,
 -3.14424;3.08823;-4.14650;,
 -2.61388;0.37305;3.19262;,
 -0.95292;-1.14783;3.93398;,
 -2.53525;-1.18996;3.18034;,
 -3.36754;0.12366;1.22012;,
 -3.39967;-0.72751;-3.09447;,
 -3.14838;-1.44131;1.34293;,
 -2.99646;-2.01299;-1.70447;,
 -3.10444;-3.12119;-4.84768;,
 -3.87107;-2.40080;-7.65110;,
 -3.19239;-3.34903;-5.58712;,
 -3.33352;-3.61864;-6.91997;,
 -3.65237;-3.82058;-8.31593;,
 -3.57904;1.03288;-4.68630;,
 -3.68538;0.00330;-6.80758;,
 -4.33858;-3.02826;-10.55435;,
 -3.97245;-3.82186;-10.49685;,
 -2.42615;2.40835;-7.30909;,
 -3.67550;-1.01549;-8.75848;,
 -4.16344;-3.20546;-12.35899;,
 -4.04265;-3.80073;-12.28841;,
 -3.15988;-3.61257;-14.95483;,
 -3.95804;-2.19527;-11.81782;,
 -3.23758;-2.97808;-14.95852;,
 -1.98736;-3.39900;-16.64014;,
 -2.82373;-2.16276;-15.13636;,
 -1.33091;-2.46435;-17.57170;,
 -1.16206;-3.15443;-17.64159;,
 -0.11716;-3.00893;-18.09721;,
 -2.76349;-0.98454;-11.13866;,
 -0.13227;2.27698;-8.83663;,
 -2.10275;3.93171;-6.36190;,
 -2.93459;4.71263;-4.01268;,
 -1.82449;5.07557;-5.92076;,
 -1.75660;6.27790;-5.60254;,
 -0.10140;4.31808;-7.31256;,
 -0.06561;5.16299;-6.67708;,
 -0.08176;6.31082;-6.24341;,
 1.60945;6.18791;-5.49223;,
 1.73638;5.07721;-5.91173;,
 2.71760;4.87148;-3.79559;,
 2.82060;3.08923;-3.99051;,
 1.91529;3.97035;-6.38907;,
 2.20472;2.58453;-7.18614;,
 3.31818;1.04343;-4.57507;,
 3.10914;2.93480;-1.44416;,
 3.16228;4.81534;-1.42991;,
 2.39295;3.01083;1.08498;,
 2.45863;4.83876;0.94800;,
 1.12691;3.59007;2.83995;,
 1.11435;5.78341;2.56727;,
 -0.73742;5.71378;2.94006;,
 -0.80592;4.35680;3.25778;,
 -0.87295;2.95019;3.59092;,
 2.11473;0.18465;1.36776;,
 0.81734;0.41019;3.26799;,
 -0.95069;0.43353;4.04682;,
 -0.95292;-1.14783;3.93398;,
 0.74955;-1.18880;3.21212;,
 1.84997;-1.43975;1.40697;,
 2.94919;-0.39110;-1.62835;,
 2.45676;-2.01299;-1.70447;,
 2.98186;-3.07790;-4.92183;,
 3.64457;-1.64945;-5.67707;,
 3.16324;-3.31547;-5.63340;,
 3.59136;0.00526;-6.83910;,
 4.03521;-2.42793;-7.75866;,
 3.50841;-3.61864;-6.98136;,
 3.96141;-3.82058;-8.40852;,
 2.42190;1.33927;-8.41747;,
 4.45243;-3.02826;-10.70257;,
 4.25146;-3.82186;-10.64205;,
 3.80878;-0.97658;-8.88362;,
 2.60542;-0.97534;-11.22158;,
 4.24149;-3.20546;-12.55568;,
 4.10641;-3.80073;-12.48059;,
 2.97337;-3.61257;-15.16384;,
 3.97938;-2.19527;-11.98937;,
 3.12408;-2.97808;-15.17119;,
 1.81576;-3.39900;-16.80815;,
 2.98909;-2.16917;-14.92511;,
 1.88593;-2.68393;-16.79849;,
 0.94182;-3.15443;-17.74296;,
 2.03193;-1.32724;-14.03231;,
 1.80986;-1.93475;-16.42787;,
 0.94578;-2.41073;-17.74357;,
 -0.11568;-2.24009;-18.13928;,
 0.92727;-1.67819;-17.32585;,
 -1.15230;-1.67010;-17.21782;,
 0.96393;-1.51092;-16.29497;,
 -0.11603;-1.49198;-17.60448;,
 -0.11304;-1.27439;-16.74168;,
 -1.22582;-1.51092;-16.18349;,
 -0.14725;-1.26784;-14.63864;,
 -1.98777;-1.32724;-13.90426;,
 -0.16621;-0.66589;-12.40210;,
 -0.17864;0.64396;-10.75555;,
 1.91618;-4.88237;-1.68902;,
 -2.83377;-3.61850;-1.69292;,
 2.11136;-3.61850;-1.69292;,
 -2.70202;-4.88237;-1.69076;,
 0.93592;-4.09307;-17.92554;,
 -1.16433;-4.09307;-17.82280;,
 -0.10516;-3.97802;-18.31183;,
 1.79393;-4.34948;-16.93837;,
 -1.99181;-4.34948;-16.76820;,
 -3.08453;-4.59394;-15.03165;,
 2.95702;-4.59394;-15.23748;,
 -3.91294;-4.82409;-12.29499;,
 4.06153;-4.82409;-12.48175;,
 4.06372;-4.83429;-10.59123;,
 -3.88179;-4.83429;-10.44751;,
 -3.50369;-4.83365;-8.20564;,
 3.79714;-4.83365;-8.29196;,
 3.37565;-4.66098;-6.88505;,
 -3.20649;-4.66098;-6.82807;,
 2.95575;-4.38483;-5.52125;,
 -3.10227;-4.38576;-5.48434;,
 2.73795;-4.22242;-4.81290;,
 -3.03788;-4.22196;-4.77568;,
 -2.53525;-1.18996;3.18034;,
 -0.95292;-1.14783;3.93398;,
 0.74955;-1.18880;3.21212;,
 -3.14838;-1.44131;1.34293;,
 1.84997;-1.43975;1.40697;,
 -2.99646;-2.01299;-1.70447;,
 2.45676;-2.01299;-1.70447;,
 -3.10444;-3.12119;-4.84768;,
 2.98186;-3.07790;-4.92183;,
 -3.19239;-3.34903;-5.58712;,
 3.16324;-3.31547;-5.63340;,
 -3.33352;-3.61864;-6.91997;,
 3.50841;-3.61864;-6.98136;,
 -3.65237;-3.82058;-8.31593;,
 3.96141;-3.82058;-8.40852;,
 -3.97245;-3.82186;-10.49685;,
 4.25146;-3.82186;-10.64205;,
 4.10641;-3.80073;-12.48059;,
 -4.04265;-3.80073;-12.28841;,
 2.97337;-3.61257;-15.16384;,
 -3.15988;-3.61257;-14.95483;,
 -1.98736;-3.39900;-16.64014;,
 1.81576;-3.39900;-16.80815;,
 0.94182;-3.15443;-17.74296;,
 -1.16206;-3.15443;-17.64159;,
 -0.11716;-3.00893;-18.09721;,
 -0.95179;-3.02415;3.69967;,
 0.74955;-1.18880;3.21212;,
 -0.95292;-1.14783;3.93398;,
 0.65932;-3.04190;3.04302;,
 0.43480;-4.88249;2.58162;,
 -0.90302;-4.88249;3.16760;,
 1.59339;-3.12942;1.36222;,
 1.84997;-1.43975;1.40697;,
 1.33120;-4.88371;1.15011;,
 2.11136;-3.61850;-1.69292;,
 1.91618;-4.88237;-1.68902;,
 2.45676;-2.01299;-1.70447;,
 2.98186;-3.07790;-4.92183;,
 2.73795;-4.22242;-4.81290;,
 3.16324;-3.31547;-5.63340;,
 2.95575;-4.38483;-5.52125;,
 3.50841;-3.61864;-6.98136;,
 3.37565;-4.66098;-6.88505;,
 3.96141;-3.82058;-8.40852;,
 3.79714;-4.83365;-8.29196;,
 4.06372;-4.83429;-10.59123;,
 4.25146;-3.82186;-10.64205;,
 4.06153;-4.82409;-12.48175;,
 4.10641;-3.80073;-12.48059;,
 2.95702;-4.59394;-15.23748;,
 2.97337;-3.61257;-15.16384;,
 1.79393;-4.34948;-16.93837;,
 1.81576;-3.39900;-16.80815;,
 0.93592;-4.09307;-17.92554;,
 0.94182;-3.15443;-17.74296;,
 -0.10516;-3.97802;-18.31183;,
 -0.11716;-3.00893;-18.09721;,
 -1.16206;-3.15443;-17.64159;,
 -1.16433;-4.09307;-17.82280;,
 -1.98736;-3.39900;-16.64014;,
 -1.99181;-4.34948;-16.76820;,
 -3.15988;-3.61257;-14.95483;,
 -3.08453;-4.59394;-15.03165;,
 -4.04265;-3.80073;-12.28841;,
 -3.91294;-4.82409;-12.29499;,
 -3.97245;-3.82186;-10.49685;,
 -3.88179;-4.83429;-10.44751;,
 -3.65237;-3.82058;-8.31593;,
 -3.50369;-4.83365;-8.20564;,
 -3.20649;-4.66098;-6.82807;,
 -3.33352;-3.61864;-6.91997;,
 -3.10227;-4.38576;-5.48434;,
 -3.19239;-3.34903;-5.58712;,
 -3.03788;-4.22196;-4.77568;,
 -3.10444;-3.12119;-4.84768;,
 -2.83377;-3.61850;-1.69292;,
 -2.99646;-2.01299;-1.70447;,
 -3.14838;-1.44131;1.34293;,
 -2.97378;-3.12942;1.34177;,
 -2.53525;-1.18996;3.18034;,
 -2.66113;-4.88371;1.15389;,
 -2.70202;-4.88237;-1.69076;,
 -2.06214;-4.88249;2.58880;,
 -2.35188;-3.04190;3.04995;,
 -0.95292;-1.14783;3.93398;,
 -0.95179;-3.02415;3.69967;,
 -0.90302;-4.88249;3.16760;,
 -2.06214;-4.88249;2.58880;,
 0.43480;-4.88249;2.58162;,
 -0.90302;-4.88249;3.16760;,
 -2.66113;-4.88371;1.15389;,
 1.33120;-4.88371;1.15011;;
 
 282;
 3;0,1,2;,
 3;1,0,3;,
 3;3,4,1;,
 3;0,5,3;,
 3;5,0,6;,
 3;6,7,5;,
 3;4,3,8;,
 3;8,9,4;,
 3;5,10,3;,
 3;10,8,3;,
 3;11,5,7;,
 3;5,11,10;,
 3;7,12,11;,
 3;9,8,13;,
 3;13,14,9;,
 3;14,13,15;,
 3;16,8,10;,
 3;8,16,13;,
 3;13,16,15;,
 3;10,11,16;,
 3;17,16,11;,
 3;15,16,18;,
 3;16,17,18;,
 3;18,17,19;,
 3;17,20,19;,
 3;21,20,17;,
 3;20,21,22;,
 3;23,22,21;,
 3;24,23,21;,
 3;17,11,25;,
 3;12,25,11;,
 3;25,26,17;,
 3;21,17,26;,
 3;27,24,21;,
 3;24,27,28;,
 3;12,29,25;,
 3;29,26,25;,
 3;21,26,30;,
 3;30,27,21;,
 3;26,29,30;,
 3;27,31,28;,
 3;32,28,31;,
 3;33,32,31;,
 3;27,30,34;,
 3;31,27,34;,
 3;31,35,33;,
 3;36,33,35;,
 3;35,31,37;,
 3;37,31,34;,
 3;35,38,36;,
 3;35,37,38;,
 3;38,39,36;,
 3;38,40,39;,
 3;34,30,41;,
 3;41,30,29;,
 3;42,41,29;,
 3;43,42,29;,
 3;29,12,43;,
 3;44,43,12;,
 3;43,44,45;,
 3;44,46,45;,
 3;45,47,43;,
 3;42,43,47;,
 3;46,48,45;,
 3;47,45,48;,
 3;46,49,48;,
 3;50,48,49;,
 3;48,50,51;,
 3;48,51,47;,
 3;50,52,51;,
 3;51,52,53;,
 3;54,47,51;,
 3;54,42,47;,
 3;51,53,54;,
 3;42,54,55;,
 3;53,55,54;,
 3;55,53,56;,
 3;56,53,57;,
 3;53,58,57;,
 3;57,58,59;,
 3;58,60,59;,
 3;61,59,60;,
 3;60,62,61;,
 3;63,61,62;,
 3;61,63,64;,
 3;65,61,64;,
 3;66,57,59;,
 3;59,61,66;,
 3;65,67,61;,
 3;66,61,67;,
 3;67,65,68;,
 3;69,67,68;,
 3;67,69,70;,
 3;67,70,66;,
 3;66,70,71;,
 3;57,66,72;,
 3;66,71,72;,
 3;72,71,73;,
 3;73,74,72;,
 3;57,72,56;,
 3;75,72,74;,
 3;75,56,72;,
 3;75,74,76;,
 3;56,75,77;,
 3;56,77,55;,
 3;75,76,78;,
 3;75,78,77;,
 3;79,78,76;,
 3;80,78,79;,
 3;77,81,55;,
 3;42,55,81;,
 3;80,82,78;,
 3;83,82,80;,
 3;84,77,78;,
 3;77,84,81;,
 3;82,84,78;,
 3;85,42,81;,
 3;85,81,84;,
 3;82,83,86;,
 3;87,86,83;,
 3;88,86,87;,
 3;82,89,84;,
 3;84,89,85;,
 3;82,86,89;,
 3;86,88,90;,
 3;90,88,91;,
 3;86,92,89;,
 3;86,90,92;,
 3;91,93,90;,
 3;94,93,91;,
 3;92,95,89;,
 3;89,95,85;,
 3;90,96,92;,
 3;96,90,93;,
 3;92,96,95;,
 3;93,94,97;,
 3;97,96,93;,
 3;97,94,40;,
 3;98,97,40;,
 3;38,98,40;,
 3;96,97,99;,
 3;98,99,97;,
 3;100,98,38;,
 3;37,100,38;,
 3;101,95,96;,
 3;99,101,96;,
 3;99,98,102;,
 3;100,102,98;,
 3;102,103,99;,
 3;103,101,99;,
 3;103,102,100;,
 3;100,37,104;,
 3;104,103,100;,
 3;103,105,101;,
 3;95,101,105;,
 3;103,104,105;,
 3;104,37,106;,
 3;106,105,104;,
 3;37,34,106;,
 3;106,34,41;,
 3;105,107,95;,
 3;105,106,107;,
 3;41,107,106;,
 3;107,85,95;,
 3;41,108,107;,
 3;85,107,108;,
 3;41,42,108;,
 3;85,108,42;,
 3;109,110,111;,
 3;110,109,112;,
 3;113,114,115;,
 3;116,114,113;,
 3;114,116,117;,
 3;116,118,117;,
 3;118,116,119;,
 3;119,120,118;,
 3;120,119,121;,
 3;120,121,122;,
 3;120,122,123;,
 3;122,124,123;,
 3;124,122,125;,
 3;124,125,126;,
 3;124,126,127;,
 3;127,126,128;,
 3;127,128,129;,
 3;129,128,130;,
 3;129,130,131;,
 3;111,131,130;,
 3;131,111,110;,
 3;132,133,134;,
 3;134,135,132;,
 3;135,134,136;,
 3;136,137,135;,
 3;137,136,138;,
 3;139,137,138;,
 3;140,139,138;,
 3;140,141,139;,
 3;141,140,142;,
 3;142,143,141;,
 3;143,142,144;,
 3;144,145,143;,
 3;145,144,146;,
 3;146,147,145;,
 3;147,146,148;,
 3;149,147,148;,
 3;149,150,147;,
 3;150,149,151;,
 3;151,152,150;,
 3;151,153,152;,
 3;153,151,154;,
 3;155,153,154;,
 3;153,155,156;,
 3;155,157,156;,
 3;158,159,160;,
 3;158,161,159;,
 3;158,162,161;,
 3;162,158,163;,
 3;161,164,159;,
 3;162,164,161;,
 3;165,159,164;,
 3;164,162,166;,
 3;164,167,165;,
 3;166,167,164;,
 3;168,167,166;,
 3;169,165,167;,
 3;167,170,169;,
 3;170,167,171;,
 3;171,172,170;,
 3;172,171,173;,
 3;173,174,172;,
 3;174,173,175;,
 3;175,176,174;,
 3;176,175,177;,
 3;178,176,177;,
 3;179,176,178;,
 3;180,179,178;,
 3;181,179,180;,
 3;182,181,180;,
 3;181,182,183;,
 3;183,182,184;,
 3;185,183,184;,
 3;186,185,184;,
 3;185,186,187;,
 3;188,187,186;,
 3;187,188,189;,
 3;190,189,188;,
 3;190,188,191;,
 3;191,192,190;,
 3;192,191,193;,
 3;193,194,192;,
 3;194,193,195;,
 3;196,194,195;,
 3;195,197,196;,
 3;197,198,196;,
 3;198,197,199;,
 3;199,200,198;,
 3;200,199,201;,
 3;201,202,200;,
 3;202,203,200;,
 3;204,203,202;,
 3;203,204,205;,
 3;204,206,205;,
 3;206,207,205;,
 3;208,207,206;,
 3;207,208,209;,
 3;209,208,210;,
 3;211,210,208;,
 3;210,211,212;,
 3;213,211,208;,
 3;214,213,208;,
 3;215,211,213;,
 3;216,212,211;,
 3;211,215,216;,
 3;217,212,216;,
 3;216,218,217;,
 3;218,216,215;,
 3;219,218,215;,
 3;220,221,222;,
 3;223,221,220;,
 3;223,224,221;,
 3;112,224,223;,
 3;224,112,109;;
 
 MeshMaterialList {
  1;
  282;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\KR_Univ\\_17.png";
   }
  }
 }
 MeshNormals {
  194;
  -0.698347;0.162728;0.697016;,
  0.020609;0.194768;0.980633;,
  -0.167456;0.221181;0.960748;,
  -0.705845;0.208025;0.677132;,
  -0.054027;0.206004;0.977059;,
  -0.953426;0.093570;0.286747;,
  -0.948555;0.076175;0.307312;,
  -0.999143;0.011629;0.039715;,
  -0.722384;0.167851;0.670811;,
  -0.117777;0.075994;0.990128;,
  -0.956299;0.108015;0.271707;,
  -0.999538;0.030402;0.000345;,
  -0.946767;0.203402;-0.249518;,
  -0.688051;0.016137;0.725483;,
  -0.086073;-0.084257;0.992720;,
  -0.820379;-0.089877;0.564713;,
  -0.973871;-0.037382;0.224002;,
  -0.989689;-0.125351;0.069308;,
  -0.984083;-0.141371;0.107679;,
  -0.984228;-0.172943;0.037237;,
  -0.979696;-0.153886;0.128509;,
  -0.981454;-0.124035;0.146164;,
  -0.977181;-0.155997;0.144157;,
  -0.969294;-0.173003;0.174755;,
  -0.961832;-0.191698;0.195270;,
  -0.980689;0.171107;-0.094720;,
  -0.978926;0.195517;-0.058958;,
  -0.998267;-0.042137;0.041089;,
  -0.973375;-0.222721;0.054195;,
  -0.788660;0.477842;-0.386888;,
  -0.909441;0.394139;-0.132556;,
  -0.978217;0.004422;-0.207538;,
  -0.973849;-0.144728;-0.175132;,
  -0.891010;-0.073399;-0.448010;,
  -0.797400;0.569559;-0.199387;,
  -0.873380;0.089410;-0.478762;,
  -0.798155;0.006539;-0.602416;,
  -0.730992;0.595827;-0.332628;,
  -0.660474;0.141918;-0.737315;,
  -0.572591;0.074593;-0.816441;,
  -0.042414;0.052650;-0.997712;,
  -0.505025;0.757032;-0.414552;,
  0.036351;0.692889;-0.720127;,
  -0.700883;0.416993;-0.578687;,
  -0.876710;0.229878;-0.422535;,
  -0.610932;0.375834;-0.696787;,
  -0.561610;0.265557;-0.783628;,
  -0.006494;0.556667;-0.830710;,
  0.008352;0.435602;-0.900101;,
  0.032337;0.353648;-0.934820;,
  0.588464;0.331559;-0.737414;,
  0.700123;0.349183;-0.622815;,
  0.899836;0.173099;-0.400414;,
  0.953041;0.203564;-0.224218;,
  0.678493;0.439974;-0.588277;,
  0.783798;0.481513;-0.392181;,
  0.981948;0.188480;-0.015911;,
  0.992511;0.003758;0.122096;,
  0.988369;-0.023620;0.150228;,
  0.913429;-0.023470;0.406320;,
  0.866357;0.027527;0.498666;,
  0.573349;0.092939;0.814023;,
  0.523763;0.108047;0.844984;,
  0.891382;-0.069385;0.447910;,
  0.549094;0.012717;0.835664;,
  0.676411;-0.100609;0.729620;,
  0.924200;-0.179109;0.337303;,
  0.961836;-0.156664;0.224341;,
  0.940431;-0.248169;0.232382;,
  0.936571;-0.233915;0.260996;,
  0.974348;-0.091683;0.205524;,
  0.933442;-0.202602;0.296039;,
  0.949453;0.309344;-0.053336;,
  0.980848;-0.042542;0.190072;,
  0.940803;-0.152443;0.302740;,
  0.964924;-0.157148;0.210302;,
  0.665356;0.610424;-0.429750;,
  0.998542;0.052869;0.010928;,
  0.982304;-0.187289;0.001019;,
  0.876968;0.458782;-0.142986;,
  0.455945;0.784254;-0.420784;,
  0.964972;0.003291;-0.262333;,
  0.957068;-0.112105;-0.267309;,
  0.867449;-0.094540;-0.488462;,
  0.767670;0.605790;-0.209048;,
  0.848037;0.072393;-0.524968;,
  0.775885;-0.011953;-0.630761;,
  0.759227;0.549585;-0.348612;,
  0.757795;0.117591;-0.641809;,
  0.547845;0.075596;-0.833157;,
  0.344731;0.914836;-0.210323;,
  0.654288;0.606027;-0.452370;,
  0.555982;0.199624;-0.806867;,
  -0.040180;0.358576;-0.932635;,
  0.422736;0.757191;-0.497953;,
  -0.465596;0.748251;-0.472589;,
  0.277507;0.950475;-0.139955;,
  -0.023957;0.829209;-0.558425;,
  -0.003815;0.990150;-0.139958;,
  -0.310750;0.940478;-0.137605;,
  -0.008398;0.992191;-0.124445;,
  -0.354247;0.911585;-0.208620;,
  -0.018210;0.934893;-0.354463;,
  -0.022840;0.772052;-0.635148;,
  0.000188;-0.002381;-0.999997;,
  0.000000;-0.003089;-0.999995;,
  0.000377;-0.001673;-0.999999;,
  -0.012137;-0.968656;-0.248110;,
  -0.012449;-0.967000;-0.254472;,
  -0.011753;-0.968979;-0.246863;,
  -0.008510;-0.981280;-0.192398;,
  -0.008726;-0.980938;-0.194124;,
  -0.004691;-0.992468;-0.122418;,
  -0.003186;-0.994768;-0.102107;,
  -0.001261;-0.999007;-0.044546;,
  -0.001030;-0.999033;-0.043961;,
  -0.000054;-0.999997;-0.002587;,
  -0.000047;-0.999997;-0.002616;,
  0.000633;-0.998085;0.061854;,
  0.000726;-0.998114;0.061375;,
  0.001415;-0.988905;0.148546;,
  0.001391;-0.984627;0.174666;,
  0.001536;-0.978164;0.207828;,
  0.001420;-0.976274;0.216533;,
  0.001346;-0.977026;0.213118;,
  0.000841;-0.979280;0.202510;,
  0.040635;-0.215466;0.975666;,
  0.649909;-0.180625;0.738236;,
  0.637723;-0.242478;0.731104;,
  -0.023280;-0.275746;0.960949;,
  0.899509;-0.162162;0.405693;,
  0.935915;-0.170416;0.308255;,
  -0.960955;-0.156282;0.228343;,
  -0.978499;-0.162495;0.127026;,
  -0.707823;-0.259690;0.656922;,
  -0.664955;-0.182258;0.724304;,
  0.000574;-0.981554;0.191183;,
  0.000000;-0.981374;0.192107;,
  0.000578;0.995371;-0.096107;,
  0.000190;0.998419;-0.056216;,
  0.000867;0.993963;-0.109709;,
  0.001488;0.988324;-0.152358;,
  0.001167;0.985876;-0.167472;,
  0.000687;0.972409;-0.233283;,
  -0.003541;0.960814;-0.277171;,
  -0.006991;0.949427;-0.313911;,
  -0.009432;0.950961;-0.309167;,
  -0.008116;0.962785;-0.270147;,
  -0.005311;0.969343;-0.245653;,
  -0.003291;0.982374;-0.186897;,
  -0.001656;0.985798;-0.167925;,
  -0.001002;0.995485;-0.094910;,
  -0.000577;0.998877;-0.047368;,
  0.000116;0.999985;0.005524;,
  0.000096;0.999985;0.005450;,
  0.000705;0.999524;0.030852;,
  0.001446;0.998710;0.050765;,
  0.003493;0.995123;0.098580;,
  0.003408;0.994982;0.099999;,
  0.008152;0.982461;0.186291;,
  0.008158;0.982769;0.184656;,
  0.012986;0.960991;0.276276;,
  0.014093;0.956166;0.292484;,
  0.016279;0.941059;0.337849;,
  0.961893;-0.176418;0.208897;,
  0.968514;-0.148950;0.199485;,
  0.944638;-0.167463;0.282162;,
  0.943802;-0.131575;0.303193;,
  0.946306;-0.100876;0.307132;,
  0.969195;-0.133329;0.207086;,
  0.982543;-0.168087;0.079727;,
  0.983893;-0.090154;-0.154358;,
  0.896187;0.000644;-0.443676;,
  0.803947;0.052816;-0.592351;,
  0.637399;0.126806;-0.760028;,
  -0.039969;0.202578;-0.978450;,
  -0.683826;0.128915;-0.718167;,
  -0.821998;0.047249;-0.567526;,
  -0.920368;-0.063538;-0.385858;,
  -0.990295;-0.112187;-0.082035;,
  -0.989139;-0.098646;0.108961;,
  -0.973354;-0.121695;0.194350;,
  -0.976406;-0.109065;0.186375;,
  -0.990214;-0.087159;0.108994;,
  -0.992523;-0.060625;0.105936;,
  -0.994246;-0.106223;0.013851;,
  -0.994512;-0.103643;0.014248;,
  0.000001;-1.000000;0.000422;,
  0.000001;-1.000000;0.000564;,
  0.000000;-1.000000;0.000000;,
  0.000001;-1.000000;0.000407;,
  0.000000;-1.000000;-0.000031;,
  -0.000000;-1.000000;-0.000471;,
  0.000000;-1.000000;-0.000472;;
  282;
  3;0,2,1;,
  3;2,0,3;,
  3;3,4,2;,
  3;0,5,3;,
  3;5,0,6;,
  3;6,7,5;,
  3;4,3,8;,
  3;8,9,4;,
  3;5,10,3;,
  3;10,8,3;,
  3;11,5,7;,
  3;5,11,10;,
  3;7,12,11;,
  3;9,8,13;,
  3;13,14,9;,
  3;14,13,15;,
  3;16,8,10;,
  3;8,16,13;,
  3;13,16,15;,
  3;10,11,16;,
  3;17,16,11;,
  3;15,16,18;,
  3;16,17,18;,
  3;18,17,19;,
  3;17,20,19;,
  3;21,20,17;,
  3;20,21,22;,
  3;23,22,21;,
  3;24,23,21;,
  3;17,11,25;,
  3;12,25,11;,
  3;25,26,17;,
  3;21,17,26;,
  3;27,24,21;,
  3;24,27,28;,
  3;12,29,25;,
  3;29,26,25;,
  3;21,26,30;,
  3;30,27,21;,
  3;26,29,30;,
  3;27,31,28;,
  3;32,28,31;,
  3;33,32,31;,
  3;27,30,34;,
  3;31,27,34;,
  3;31,35,33;,
  3;36,33,35;,
  3;35,31,37;,
  3;37,31,34;,
  3;35,38,36;,
  3;35,37,38;,
  3;38,39,36;,
  3;38,40,39;,
  3;34,30,41;,
  3;41,30,29;,
  3;42,41,29;,
  3;43,42,29;,
  3;29,12,43;,
  3;44,43,12;,
  3;43,44,45;,
  3;44,46,45;,
  3;45,47,43;,
  3;42,43,47;,
  3;46,48,45;,
  3;47,45,48;,
  3;46,49,48;,
  3;50,48,49;,
  3;48,50,51;,
  3;48,51,47;,
  3;50,52,51;,
  3;51,52,53;,
  3;54,47,51;,
  3;54,42,47;,
  3;51,53,54;,
  3;42,54,55;,
  3;53,55,54;,
  3;55,53,56;,
  3;56,53,57;,
  3;53,58,57;,
  3;57,58,59;,
  3;58,60,59;,
  3;61,59,60;,
  3;60,62,61;,
  3;1,61,62;,
  3;61,1,2;,
  3;4,61,2;,
  3;63,57,59;,
  3;59,61,63;,
  3;4,64,61;,
  3;63,61,64;,
  3;64,4,9;,
  3;14,64,9;,
  3;64,14,65;,
  3;64,65,63;,
  3;63,65,66;,
  3;57,63,67;,
  3;63,66,67;,
  3;67,66,68;,
  3;68,69,67;,
  3;57,67,56;,
  3;70,67,69;,
  3;70,56,67;,
  3;70,69,71;,
  3;56,70,72;,
  3;56,72,55;,
  3;70,71,73;,
  3;70,73,72;,
  3;74,73,71;,
  3;75,73,74;,
  3;72,76,55;,
  3;42,55,76;,
  3;75,77,73;,
  3;78,77,75;,
  3;79,72,73;,
  3;72,79,76;,
  3;77,79,73;,
  3;80,42,76;,
  3;80,76,79;,
  3;77,78,81;,
  3;82,81,78;,
  3;83,81,82;,
  3;77,84,79;,
  3;79,84,80;,
  3;77,81,84;,
  3;81,83,85;,
  3;85,83,86;,
  3;81,87,84;,
  3;81,85,87;,
  3;86,88,85;,
  3;89,88,86;,
  3;87,90,84;,
  3;84,90,80;,
  3;85,91,87;,
  3;91,85,88;,
  3;87,91,90;,
  3;88,89,92;,
  3;92,91,88;,
  3;92,89,40;,
  3;93,92,40;,
  3;38,93,40;,
  3;91,92,94;,
  3;93,94,92;,
  3;95,93,38;,
  3;37,95,38;,
  3;96,90,91;,
  3;94,96,91;,
  3;94,93,97;,
  3;95,97,93;,
  3;97,98,94;,
  3;98,96,94;,
  3;98,97,95;,
  3;95,37,99;,
  3;99,98,95;,
  3;98,100,96;,
  3;90,96,100;,
  3;98,99,100;,
  3;99,37,101;,
  3;101,100,99;,
  3;37,34,101;,
  3;101,34,41;,
  3;100,102,90;,
  3;100,101,102;,
  3;41,102,101;,
  3;102,80,90;,
  3;41,103,102;,
  3;80,102,103;,
  3;41,42,103;,
  3;80,103,42;,
  3;104,104,105;,
  3;104,104,106;,
  3;107,109,108;,
  3;110,109,107;,
  3;109,110,111;,
  3;110,112,111;,
  3;112,110,113;,
  3;113,114,112;,
  3;114,113,115;,
  3;114,115,116;,
  3;114,116,117;,
  3;116,118,117;,
  3;118,116,119;,
  3;118,119,120;,
  3;118,120,121;,
  3;121,120,122;,
  3;121,122,123;,
  3;123,122,124;,
  3;123,124,125;,
  3;136,125,124;,
  3;125,136,137;,
  3;138,139,140;,
  3;140,141,138;,
  3;141,140,142;,
  3;142,143,141;,
  3;143,142,144;,
  3;145,143,144;,
  3;146,145,144;,
  3;146,147,145;,
  3;147,146,148;,
  3;148,149,147;,
  3;149,148,150;,
  3;150,151,149;,
  3;151,150,152;,
  3;152,153,151;,
  3;153,152,154;,
  3;155,153,154;,
  3;155,156,153;,
  3;156,155,157;,
  3;157,158,156;,
  3;157,159,158;,
  3;159,157,160;,
  3;161,159,160;,
  3;159,161,162;,
  3;161,163,162;,
  3;126,65,14;,
  3;126,127,65;,
  3;126,128,127;,
  3;128,126,129;,
  3;127,130,65;,
  3;128,130,127;,
  3;66,65,130;,
  3;130,128,131;,
  3;130,164,66;,
  3;131,164,130;,
  3;165,164,131;,
  3;68,66,164;,
  3;164,69,68;,
  3;69,164,166;,
  3;166,71,69;,
  3;71,166,167;,
  3;167,74,71;,
  3;74,167,168;,
  3;168,75,74;,
  3;75,168,169;,
  3;170,75,169;,
  3;78,75,170;,
  3;171,78,170;,
  3;82,78,171;,
  3;172,82,171;,
  3;82,172,83;,
  3;83,172,173;,
  3;86,83,173;,
  3;174,86,173;,
  3;86,174,89;,
  3;175,89,174;,
  3;89,175,40;,
  3;39,40,175;,
  3;39,175,176;,
  3;176,36,39;,
  3;36,176,177;,
  3;177,33,36;,
  3;33,177,178;,
  3;32,33,178;,
  3;178,179,32;,
  3;179,28,32;,
  3;28,179,180;,
  3;180,24,28;,
  3;24,180,181;,
  3;181,182,24;,
  3;182,23,24;,
  3;183,23,182;,
  3;23,183,22;,
  3;183,184,22;,
  3;184,20,22;,
  3;185,20,184;,
  3;20,185,19;,
  3;19,185,18;,
  3;132,18,185;,
  3;18,132,15;,
  3;133,132,185;,
  3;186,133,185;,
  3;134,132,133;,
  3;135,15,132;,
  3;132,134,135;,
  3;14,15,135;,
  3;135,126,14;,
  3;126,135,134;,
  3;129,126,134;,
  3;187,188,189;,
  3;190,188,187;,
  3;190,191,188;,
  3;192,191,190;,
  3;191,192,193;;
 }
 MeshTextureCoords {
  225;
  0.102238;0.572574;,
  0.027127;0.594017;,
  0.027127;0.572574;,
  0.099329;0.593510;,
  0.027116;0.614907;,
  0.178071;0.592724;,
  0.181091;0.572574;,
  0.257707;0.592921;,
  0.095873;0.616317;,
  0.027116;0.646194;,
  0.167415;0.618932;,
  0.245550;0.621820;,
  0.327168;0.624529;,
  0.085614;0.648211;,
  0.027116;0.662040;,
  0.080976;0.666275;,
  0.145674;0.653956;,
  0.246746;0.674834;,
  0.135763;0.674284;,
  0.196373;0.688836;,
  0.227909;0.716703;,
  0.294696;0.736428;,
  0.233686;0.725400;,
  0.244173;0.741188;,
  0.255399;0.758887;,
  0.312792;0.659918;,
  0.340791;0.696337;,
  0.312533;0.779672;,
  0.276540;0.787826;,
  0.411275;0.661573;,
  0.353027;0.732985;,
  0.327728;0.805634;,
  0.298781;0.812757;,
  0.337974;0.848077;,
  0.357808;0.787782;,
  0.365124;0.838187;,
  0.381731;0.870252;,
  0.395445;0.831341;,
  0.442834;0.868196;,
  0.434402;0.884979;,
  0.499941;0.889162;,
  0.404868;0.762754;,
  0.498860;0.680689;,
  0.417826;0.623629;,
  0.340076;0.596266;,
  0.422879;0.598204;,
  0.424074;0.571955;,
  0.499931;0.623625;,
  0.499931;0.600036;,
  0.499941;0.572574;,
  0.575808;0.571955;,
  0.575674;0.597254;,
  0.658235;0.592256;,
  0.670749;0.623236;,
  0.578235;0.623382;,
  0.583607;0.656284;,
  0.685912;0.660159;,
  0.752162;0.620447;,
  0.740152;0.590200;,
  0.832467;0.618932;,
  0.821811;0.592724;,
  0.902109;0.607958;,
  0.897644;0.572574;,
  0.972777;0.572574;,
  0.972777;0.594017;,
  0.972766;0.614907;,
  0.854208;0.653956;,
  0.914267;0.648211;,
  0.972766;0.646194;,
  0.972766;0.662040;,
  0.918906;0.666275;,
  0.864119;0.674284;,
  0.778440;0.662784;,
  0.803508;0.688836;,
  0.771973;0.716703;,
  0.717530;0.706357;,
  0.766314;0.725223;,
  0.656838;0.695905;,
  0.705488;0.737286;,
  0.755709;0.741188;,
  0.744483;0.758887;,
  0.584804;0.692423;,
  0.688270;0.780231;,
  0.723342;0.787826;,
  0.646049;0.733439;,
  0.591969;0.763067;,
  0.672395;0.806080;,
  0.701101;0.812757;,
  0.661908;0.848077;,
  0.642432;0.789036;,
  0.635298;0.838193;,
  0.618151;0.870252;,
  0.611325;0.827052;,
  0.595656;0.856660;,
  0.565480;0.884979;,
  0.570583;0.806319;,
  0.579282;0.843555;,
  0.550629;0.869360;,
  0.499931;0.871754;,
  0.541482;0.854007;,
  0.456363;0.853065;,
  0.542244;0.837626;,
  0.499931;0.855855;,
  0.499931;0.842444;,
  0.453851;0.836737;,
  0.499931;0.812226;,
  0.431713;0.805509;,
  0.499931;0.775122;,
  0.499931;0.733872;,
  0.918558;0.864108;,
  0.825733;0.837755;,
  0.923143;0.837755;,
  0.826665;0.864108;,
  0.904998;0.690442;,
  0.847157;0.690442;,
  0.875957;0.686571;,
  0.927263;0.699371;,
  0.826719;0.699371;,
  0.811148;0.712545;,
  0.945002;0.712545;,
  0.804564;0.734670;,
  0.959943;0.734670;,
  0.961715;0.752015;,
  0.806997;0.752015;,
  0.814607;0.773017;,
  0.956662;0.773017;,
  0.948397;0.786305;,
  0.820741;0.786305;,
  0.939617;0.800233;,
  0.823014;0.800233;,
  0.935024;0.807520;,
  0.824203;0.807520;,
  0.159139;0.884700;,
  0.129715;0.890477;,
  0.097599;0.884883;,
  0.173335;0.864108;,
  0.081442;0.864108;,
  0.174267;0.837755;,
  0.076857;0.837755;,
  0.175797;0.807520;,
  0.064976;0.807520;,
  0.177026;0.799984;,
  0.060323;0.800138;,
  0.179259;0.786305;,
  0.051603;0.786305;,
  0.185393;0.773017;,
  0.043339;0.773017;,
  0.193004;0.752015;,
  0.038285;0.752015;,
  0.040057;0.734670;,
  0.195435;0.734670;,
  0.054998;0.712545;,
  0.188853;0.712545;,
  0.173281;0.699371;,
  0.072737;0.699371;,
  0.095002;0.690442;,
  0.152843;0.690442;,
  0.124043;0.686571;,
  0.978881;0.948542;,
  0.944719;0.911006;,
  0.978881;0.911006;,
  0.944719;0.948542;,
  0.944719;0.989856;,
  0.978881;0.989856;,
  0.904247;0.948542;,
  0.904247;0.911006;,
  0.904247;0.989856;,
  0.838715;0.948542;,
  0.838715;0.989856;,
  0.838715;0.911006;,
  0.775940;0.911006;,
  0.775940;0.948542;,
  0.760488;0.911006;,
  0.760685;0.948542;,
  0.731530;0.911006;,
  0.731530;0.948542;,
  0.704175;0.911006;,
  0.704175;0.948542;,
  0.660344;0.948542;,
  0.660344;0.911006;,
  0.625491;0.948542;,
  0.625491;0.911006;,
  0.581898;0.948542;,
  0.581898;0.911006;,
  0.553069;0.948542;,
  0.553069;0.911006;,
  0.527515;0.948542;,
  0.527515;0.911006;,
  0.499969;0.948542;,
  0.499969;0.911006;,
  0.472423;0.911006;,
  0.472423;0.948542;,
  0.446869;0.911006;,
  0.446869;0.948542;,
  0.418040;0.911006;,
  0.418040;0.948542;,
  0.374448;0.911006;,
  0.374448;0.948542;,
  0.339595;0.911006;,
  0.339595;0.948542;,
  0.295764;0.911006;,
  0.295764;0.948542;,
  0.268408;0.948542;,
  0.268408;0.911006;,
  0.239253;0.948542;,
  0.239773;0.911006;,
  0.223999;0.948542;,
  0.223999;0.911006;,
  0.161223;0.948542;,
  0.161223;0.911006;,
  0.095692;0.911006;,
  0.095692;0.948542;,
  0.055219;0.911006;,
  0.095692;0.989856;,
  0.161223;0.989856;,
  0.055219;0.989856;,
  0.055219;0.948542;,
  0.021058;0.911006;,
  0.021058;0.948542;,
  0.021058;0.989856;,
  0.845496;0.895973;,
  0.893310;0.896001;,
  0.870285;0.900084;,
  0.835286;0.884700;,
  0.908905;0.884418;;
 }
}