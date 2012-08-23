<?php

$policy = "<cross-domain-policy>\n<allow-access-from domain=\"*\" to-ports=\"*\" />\n</cross-domain-policy>";

$socket0 = stream_socket_server("tcp://192.168.21.150:9000", $errno, $errstr);

$conn1 = stream_socket_accept($socket0,48000);
echo "got socket 0 , connected to 0 \n";

//$socket1 = stream_socket_server("tcp://192.168.21.150:9001", $errno, $errstr);

//$conn2 = stream_socket_accept($socket1,48000);
//echo "got socket 1, connected to 1 \n";

while(1)
{
  $read = fread($conn1,2048);
  //if($read != "")
  
  echo $read."\n";
  
  // echo "sent message:".$read."\n"; 
  
//  fwrite( $conn2, $read);
    
}

fclose($conn1);
//fclose($conn2);

fclose($socket0);
//fclose($socket1);


































?>