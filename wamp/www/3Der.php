<?php
require_once "expireErr.php";
require_once "WiDBQ.php";


// == THE CODE STARTS HERE


if( $_REQUEST["cmd"] && $_REQUEST["Value"])
{
 $theCmd = $_REQUEST["cmd"];
 $theChoice = rand ( 0 , 2 );
 
 if($theCmd == "get")
 {
   $Id = $_REQUEST["Value"];
   
   
   echo $WiQ->get($Id);

 }
 else if($theCmd == "getlast")
 {
   $Id = $_REQUEST["Value"];
   $value = "";
   $first = "";
   while( ($value = $WiQ->get($Id))!= "null")
   {
     if($first == "")
       $first = $value;

     
   }
   echo $first;

 }
 else if($theCmd == "put")
 {
    $IdCommand = explode(",",$_REQUEST["Value"],2);
       	
    $WiQ->put($IdCommand[0], $IdCommand[1]);
    echo "regId=$IdCommand[0]";		
 }
 else if( $theCmd == "reg")
 {
 	$Data = explode(",",$_REQUEST["Value"],3);
    
 	echo "reg=".$WiQ->Register($Data[0], $Data[1], $Data[2]);
 }
 else if( $theCmd == "connect")
 {
 	$Data = explode(",",$_REQUEST["Value"],3);
    
 	echo "regId=".$WiQ->connectReg($Data[0], $Data[1], $Data[2]);
 }
 else
 {
 	echo "regId=null";	
 }
 
}
else
 echo "?";

?>