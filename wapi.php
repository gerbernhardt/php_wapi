<?php
#
# WAPI: Interface for php_wapi.dll extension
# Filename: wapi.php
# Copyright (c) 2016 by German Bernhardt
# E-mail: <german.bernhardt@gmail.com>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License.
#
define('MOUSE_LEFTDOWN',hexdec('0x002'));
define('MOUSE_LEFTUP',hexdec('0x004'));

define('MOUSE_MIDDLEDOWN',hexdec('0x020'));
define('MOUSE_MIDDLEUP',hexdec('0x040'));

define('MOUSE_RIGHTDOWN',hexdec('0x08'));
define('MOUSE_RIGHTUP',hexdec('0x10'));

define('MOUSE_XDOWN',hexdec('0x080'));
define('MOUSE_XUP',hexdec('0x100'));
define('MOUSE_WHEEL',hexdec('0x800'));
define('MOUSE_HWHEEL',hexdec('0x01000'));//The wheel button is tilted.

// 0x07 : unassigned
define('VK_BACK',hexdec('0x08'));
define('VK_TAB',hexdec('0x09'));
// 0x0A - 0x0B : reserved
define('VK_CLEAR',hexdec('0x0C'));
define('VK_RETURN',hexdec('0x0D'));
define('VK_SHIFT',hexdec('0x10'));
define('VK_CONTROL',hexdec('0x11'));
define('VK_MENU',hexdec('0x12'));
define('VK_PAUSE',hexdec('0x13'));
define('VK_CAPITAL',hexdec('0x14'));
define('VK_KANA',hexdec('0x15'));
define('VK_HANGEUL',hexdec('0x15'));  // old name - should be here for compatibility
define('VK_HANGUL',hexdec('0x15'));
define('VK_JUNJA',hexdec('0x17'));
define('VK_FINAL',hexdec('0x18'));
define('VK_HANJA',hexdec('0x19'));
define('VK_KANJI',hexdec('0x19'));
define('VK_ESCAPE',hexdec('0x1B'));
define('VK_CONVERT',hexdec('0x1C'));
define('VK_NONCONVERT',hexdec('0x1D'));
define('VK_ACCEPT',hexdec('0x1E'));
define('VK_MODECHANGE',hexdec('0x1F'));
define('VK_SPACE',hexdec('0x20'));
define('VK_PRIOR',hexdec('0x21'));
define('VK_NEXT',hexdec('0x22'));
define('VK_END',hexdec('0x23'));
define('VK_HOME',hexdec('0x24'));
define('VK_LEFT',hexdec('0x25'));
define('VK_UP',hexdec('0x26'));
define('VK_RIGHT',hexdec('0x27'));
define('VK_DOWN',hexdec('0x28'));
define('VK_SELECT',hexdec('0x29'));
define('VK_PRINT',hexdec('0x2A'));
define('VK_EXECUTE',hexdec('0x2B'));
define('VK_SNAPSHOT',hexdec('0x2C'));
define('VK_INSERT',hexdec('0x2D'));
define('VK_DELETE',hexdec('0x2E'));
define('VK_HELP',hexdec('0x2F'));
// VK_0 - VK_9 are the same as ASCII '0' - '9' (0x30 - 0x39)
// 0x40 : unassigned
// VK_A - VK_Z are the same as ASCII 'A' - 'Z' (0x41 - 0x5A)
//Defining Virtual Keys 0-9
define('VK_0',hexdec('0x30'));
define('VK_1',hexdec('0x31'));
define('VK_2',hexdec('0x32'));
define('VK_3',hexdec('0x33'));
define('VK_4',hexdec('0x34'));
define('VK_5',hexdec('0x35'));
define('VK_6',hexdec('0x36'));
define('VK_7',hexdec('0x37'));
define('VK_8',hexdec('0x38'));
define('VK_9',hexdec('0x39'));
//Defining Virtual Keys A-Z
define('VK_A',hexdec('0x41'));
define('VK_B',hexdec('0x42'));
define('VK_C',hexdec('0x43'));
define('VK_D',hexdec('0x44'));
define('VK_E',hexdec('0x45'));
define('VK_F',hexdec('0x46'));
define('VK_G',hexdec('0x47'));
define('VK_H',hexdec('0x48'));
define('VK_I',hexdec('0x49'));
define('VK_J',hexdec('0x4A'));
define('VK_K',hexdec('0x4B'));
define('VK_L',hexdec('0x4C'));
define('VK_M',hexdec('0x4D'));
define('VK_N',hexdec('0x4E'));
define('VK_O',hexdec('0x4F'));
define('VK_P',hexdec('0x50'));
define('VK_Q',hexdec('0x51'));
define('VK_R',hexdec('0x52'));
define('VK_S',hexdec('0x53'));
define('VK_T',hexdec('0x54'));
define('VK_U',hexdec('0x55'));
define('VK_V',hexdec('0x56'));
define('VK_W',hexdec('0x57'));
define('VK_X',hexdec('0x58'));
define('VK_Y',hexdec('0x59'));
define('VK_Z',hexdec('0x5A'));

define('VK_LWIN',hexdec('0x5B'));
define('VK_RWIN',hexdec('0x5C'));
define('VK_APPS',hexdec('0x5D'));

// 0x5E : reserved
define('VK_SLEEP',hexdec('0x5F'));
define('VK_NUMPAD0',hexdec('0x60'));
define('VK_NUMPAD1',hexdec('0x61'));
define('VK_NUMPAD2',hexdec('0x62'));
define('VK_NUMPAD3',hexdec('0x63'));
define('VK_NUMPAD4',hexdec('0x64'));
define('VK_NUMPAD5',hexdec('0x65'));
define('VK_NUMPAD6',hexdec('0x66'));
define('VK_NUMPAD7',hexdec('0x67'));
define('VK_NUMPAD8',hexdec('0x68'));
define('VK_NUMPAD9',hexdec('0x69'));
define('VK_MULTIPLY',hexdec('0x6A'));
define('VK_ADD',hexdec('0x6B'));
define('VK_SEPARATOR',hexdec('0x6C'));
define('VK_SUBTRACT',hexdec('0x6D'));
define('VK_DECIMAL',hexdec('0x6E'));
define('VK_DIVIDE',hexdec('0x6F'));
define('VK_F1',hexdec('0x70'));
define('VK_F2',hexdec('0x71'));
define('VK_F3',hexdec('0x72'));
define('VK_F4',hexdec('0x73'));
define('VK_F5',hexdec('0x74'));
define('VK_F6',hexdec('0x75'));
define('VK_F7',hexdec('0x76'));
define('VK_F8',hexdec('0x77'));
define('VK_F9',hexdec('0x78'));
define('VK_F10',hexdec('0x79'));
define('VK_F11',hexdec('0x7A'));
define('VK_F12',hexdec('0x7B'));
define('VK_F13',hexdec('0x7C'));
define('VK_F14',hexdec('0x7D'));
define('VK_F15',hexdec('0x7E'));
define('VK_F16',hexdec('0x7F'));
define('VK_F17',hexdec('0x80'));
define('VK_F18',hexdec('0x81'));
define('VK_F19',hexdec('0x82'));
define('VK_F20',hexdec('0x83'));
define('VK_F21',hexdec('0x84'));
define('VK_F22',hexdec('0x85'));
define('VK_F23',hexdec('0x86'));
define('VK_F24',hexdec('0x87'));
// 0x88 - 0x8F : unassigned
define('VK_NUMLOCK',hexdec('0x90'));
define('VK_SCROLL',hexdec('0x91'));

// TO READ .BMP FILE
function imagecreatefrombmp($path){
 $file=fopen($path,'rb');
 $read=fread($file,10);
 while(!feof($file)&&($read<>'')) $read.=fread($file,1024);
 $temp=unpack("H*",$read);
 $hex=$temp[1];
 $header=substr($hex,0,108);
 if(substr($header,0,4)=='424d'){
  $header_parts=str_split($header,2);
  $width=hexdec($header_parts[19].$header_parts[18]);
  $height=hexdec($header_parts[23].$header_parts[22]);
  unset($header_parts);
 }
 $x=0;
 $y=1;
 $image=imagecreatetruecolor($width,$height);
 $body=substr($hex,108);
 $body_size=(strlen($body)/2);
 $header_size=($width*$height);
 $usePadding=($body_size>($header_size*3)+4);
 for($i=0;$i<$body_size;$i+=3){
  if($x>=$width){
   if($usePadding) $i+=$width%4;
   $x=0;
   $y++;
   if($y>$height) break;
  }
  $i_pos=$i*2;
  $r=hexdec($body[$i_pos+4].$body[$i_pos+5]);
  $g=hexdec($body[$i_pos+2].$body[$i_pos+3]);
  $b=hexdec($body[$i_pos].$body[$i_pos+1]);
  $color=imagecolorallocate($image,$r,$g,$b);
  imagesetpixel($image,$x,$height-$y,$color);
  $x++;
 }
 unset($body);
 return $image;
}

// COMPARE IMAGES!
function image_compare($img1,$img2){
 $xmin=ImageSX($img1);$xmax=0;
 $ymin=ImageSY($img1);$ymax=0;
 for($j=0;$j<ImageSY($img1);$j++){
  for($i=0;$i<ImageSX($img1);$i++){
   $rgb1=imagecolorat($img1,$i,$j);
   $rgb2=imagecolorat($img2,$i,$j);
   if($rgb1!=$rgb2){
    return false;
    //$xmin=($i<$xmin)?$i:$xmin;$ymin=($j<$ymin)?$j:$ymin;$xmax=($i>$xmax)?$i:$xmax;$ymax=($j>$ymax)?$j:$ymax;
   }
  }
 }
 //REMARCAR RECUADRO ROJO DE MOVIMIENTO!
 //$red=imagecolorallocate($img2,255,0,0);imagerectangle($img2,$xmin,$ymin,$xmax,$ymax,$red);imagepng($img2,'result.png');
 return true;
}

?>
