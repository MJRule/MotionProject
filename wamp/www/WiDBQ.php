<?php

require_once "expireErr.php";
class WiDbQ{
	private $connectRs;
	private $rs;
	private $insert_id;
	private $dbRs = false;
	private $dbCreateQueries = array(" CREATE TABLE IF NOT EXISTS tblReg( RegId INT NOT NULL AUTO_INCREMENT PRIMARY KEY, FirstName VARCHAR(255), LastName VARCHAR(255), GUID VARCHAR(255) UNIQUE);"," CREATE TABLE IF NOT EXISTS tblUserQ( UserQId INT NOT NULL AUTO_INCREMENT PRIMARY KEY, RegId INT REFERENCES tblReg(RegId), StartTime  TIMESTAMP DEFAULT NOW(),EndTime TIMESTAMP);"," CREATE TABLE IF NOT EXISTS tblQ( QId INT NOT NULL AUTO_INCREMENT PRIMARY KEY, UserQId INT REFERENCES  tblUserQ(UserQId),	Command VARCHAR(1024) NOT NULL );");
	private $dbRegisterQueries = array();

	
	private function connectDb()
	{
		$this->connectRs = mysql_connect("localhost","WI","53211");
		//$this->connectRs = mysql_connect("localhost","udistance","distance");
		if(!$this->connectRs)
		{
			echo "Error connecting to the database server".mysql_error($this->connectRs);
		}
	    	$dbRs = mysql_select_db("WI",$this->connectRs);
		if(! $dbRs)
		{
			echo "Error selecting the WI queue database".mysql_error($this->connectRs);	
			
		}
	}
	
	private function query($pStrSQL)
	{
	  

		$this->rs = -1;
		
		$this->rs = mysql_query($pStrSQL,$this->connectRs);
	  	if( !$this->rs)
	  	{
		   echo "Error running query [$pStrSQL] ".mysql_error($this->connectRs)."<br>";  
		
	  	}	

		
	}
	
	private function dupCheck_query($pStrSQL)
	{
		$this->rs = -1;
		$result = "";
		$this->rs = mysql_query($pStrSQL,$this->connectRs);
	  	if( !$this->rs)
	  	{
		   $dupCheck = explode(" ",mysql_error($this->connectRs));
		   if($dupCheck[0] == "Duplicate")
			$result = "Duplicate";
		   else		
			echo "Error running query [$pStrSQL] ".mysql_error($this->connectRs)."<br>";  
		
	  	}
		return $result;
	}

	private function runQueries( $aryQueries)
	{
		foreach( $aryQueries as $sql)
		{
			$this->query($sql);
		}	
		
	}
	
	private function setLastInsertId($pStrTableName,$pStrIDName)
	{
		$this->query("SELECT $pStrIDName from $pStrTableName order by $pStrIDName DESC;");
		$insert_id_ary = mysql_fetch_assoc($this->rs);
		$this->insert_id = $insert_id_ary[$pStrIDName];	
		//echo "INSERT ID WAS ".$this->insert_id;
	}
	
	private function makeDb()
	{
		$this->runQueries($this->dbCreateQueries);
	}
	
	public function WiDbQ()
	{
		
		$this->connectDb();
		$this->makeDb();
		
	}
	
	
	public function Register($pStrFirstName, $pStrLastName, $pStrGUID)
	{
		// registers a user and creates a user Q entry - this supposes one Q per registration ...
		// returns the new or existing Q id 
		$resultQId = "null";
		
		$this->query("SELECT RegId,FirstName,LastName,GUID FROM tblReg WHERE FirstName = '$pStrFirstName' AND LastName = '$pStrLastName' AND GUID = '$pStrGUID'");
		$num = mysql_num_rows( $this->rs );
		
		if( $num == 0) 
		{
			$dup_result = $this->dupCheck_query("INSERT INTO tblReg(FirstName,LastName,GUID) VALUE ('$pStrFirstName','$pStrLastName','$pStrGUID')");
			
			if($dup_result == "Duplicate")
			{
				$resultQId = "null";
			}
			else
			{	
				$this->setLastInsertId('tblReg','RegId');
				$dup_result = $this->dupCheck_query("INSERT INTO tblUserQ(RegId) VALUE ($this->insert_id)");
				if($dup_result == "Duplicate")
				{
					$resultQId = "null";
				}
				else
					$resultQId = $this->insert_id;	
			}
		}
		else 
		{
			$ary = mysql_fetch_assoc($this->rs);
			if($ary['FirstName'] == $pStrFirstName && $ary['LastName'] == $pStrLastName && $ary['GUID'] == $pStrGUID )
                        { 
			  $resultQId = $ary['RegId'];
			}
		}
		
		return $resultQId;
	}
	
	public function connectReg($pStrFirstName, $pStrLastName, $pStrGUID)
	{
		$resultQId = "null";
		
		$this->query("SELECT RegId FROM tblReg WHERE FirstName = '$pStrFirstName' AND LastName = '$pStrLastName' AND RegId = '$pStrGUID'");
		$num = mysql_num_rows( $this->rs );
                if($num == 1)
		{
			$ary = mysql_fetch_assoc($this->rs);
		  	$resultQId = $ary['RegId'];			
		}
		
		return $resultQId;	
	}
	
	public function put($RegId,$Value)
	{
		$this->query("INSERT INTO tblQ SELECT null, tusr.UserQId , '$Value' FROM tblUserQ tusr WHERE tusr.RegId = $RegId");	
	}

	public function get($RegId)
	{
		$Result = "null";
		$this->query("SELECT Command,QId FROM tblQ WHERE UserQId = (SELECT UserQId FROM tblUserQ WHERE RegId = $RegId) ORDER BY QId DESC");
                if( mysql_num_rows($this->rs) > 0)
                {
			$ResultAry = mysql_fetch_assoc($this->rs);

                	$QId = $ResultAry['QId'];
                	$this->query("DELETE FROM tblQ WHERE QId = $QId");

                	$Result = $ResultAry['Command'];
		} 
		return $Result;
	}

	public function getlast($RegId)
	{
		$Result = "null";
		$this->query("SELECT Command,QId FROM tblQ WHERE UserQId = (SELECT UserQId FROM tblUserQ WHERE RegId = $RegId) ORDER BY QId DESC");
                if( mysql_num_rows($this->rs) > 0)
                {
			$cResult = mysql_fetch_assoc($this->rs);
			$ResultAry = $cResult;

                        while($cResult= mysql_fetch_assoc($this->rs))
                        {
				$ResultAry = $cResult;
				$QId = $ResultAry['QId'];
                	        $this->query("DELETE FROM tblQ WHERE QId = $QId");
			}

                	$Result = $ResultAry['Command'];
		} 
		return $Result;
	}
	
	public function showQ()
	{
		$Result = "null";
		$this->query("SELECT * from tblQ");
        if( mysql_num_rows($this->rs) > 0)
        {
			
		    while($Result += mysql_fetch_assoc($this->rs));

		} 
		return $Result;
		
	}
	
}

$WiQ = new WiDbQ();
?>

