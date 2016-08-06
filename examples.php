<?php
include('wapi.php');

//$text = open||save
//$filter = "Text File \0*.txt\0"
wapi_dialog($text,$filter);

$text=wapi_get_clipboard();
wapi_set_clipboard($text);

//$text="{DELAY=200}@rnotepad~{appactivate Notepad}{DELAY 100}Hello!!!!{BEEP 1999 1000}{ESC}% {DOWN 5}";
//$text="{DELAY=200}@rcalc~{DELAY 100}{appactivate Calculator}1500{PLUS}1*600~";
//$text="{DELAY=200}@rcmd~{DELAY 500}dir/w~cd ..~dir/w~title I love Shell line!~cd\\~exit";
//$text="{DELAY=200}@rcmd~title Hola como estas~exit~";
$text="{DELAY=200}{NUMLOCK}{CAPSLOCK}{SCROLL}{SCROLL}{CAPSLOCK}{NUMLOCK}";
for($i=0;$i<5;$i++) wapi_sendkeys($text);

$state=wapi_get_key_state('VK_A');
$pos=wapi_get_cursor_pos();
wapi_set_cursor_pos(20,20);
wapi_mouse_event($flag,$x,$y,$wheel,0);
//$flag=MOUSE_LEFTDOWN
//$flag=MOUSE_LEFTDOWN && $x=100 && $y=-50
//$flag=MOUSE_WHEEL && $wheel=100 || -100

wapi_set_window('active',$handle);// active,foreground,focus,enable,disable
$id=wapi_get_window_process_id($handle);
$handle=wapi_get_window_text('Notepad');
$handle=wapi_get_window('desktop');// active,console,desktop,foregound, or FindWindow('texto')
wapi_screenshot($handle,$path,$x,$y,$width,$height);

?>
