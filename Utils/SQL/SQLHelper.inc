<?php
/**
 * Created by PhpStorm.
 * User: Sorrell
 * Date: 24/04/14
 * Time: 01:34
 */

namespace Utils\SQL;

//Include config data
require_once('Resources/Config/cfg.inc');
use Resources\Config\Cfg as Cfg;

require_once('Utils/Debug/DbgHelper.inc');
use Utils\Debug\DbgHelper;

//A helper class for database querying
class SQLHelper {

    private $con;

    //Connect to a database according to the configuration data
    public function Connect()
    {
        $this->con = mysqli_connect(Cfg::$cfgDbHost, Cfg::$cfgDbUser, Cfg::$cfgDbPass, Cfg::$cfgDbSchema)
        or DbgHelper::PrintDbgMsgAndDie(mysqli_connect_error(), DbgHelper::SQL);
    }

    //Does a query and returns the results
    public function Query($query)
    {
	    if($this->con)
	    {
		    $start = microtime(true);
	        $ret = mysqli_query($this->con, $query)
	        or DbgHelper::PrintDbgMsg(mysqli_error($this->con), DbgHelper::SQL);
		    $time = microtime(true) - $start;
		    DbgHelper::PrintDbgMsg("Query \"$query\" took $time seconds", DbgHelper::SQL);
	    }
	    else
		    $ret = false;

        return $ret;
    }

    //Disconnects from the database
    public function Disconnect()
    {
	    if($this->con)
	    {
	        mysqli_close($this->con)
	        or DbgHelper::PrintDbgMsg(mysqli_error($this->con), DbgHelper::SQL) && false;
	    }
    }

	//Sanitize input
	public function Sanitize($string)
	{
		if($this->con)
			return mysqli_escape_string($this->con, $string);
		else
			return null;
	}
} 