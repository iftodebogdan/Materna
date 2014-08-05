<?php
/**
 * Created by PhpStorm.
 * User: Bogdan
 * Date: 2/22/14
 * Time: 1:44 AM
 */

namespace Utils\Debug;

//Enable debug features
if(!defined('__DEBUG'))
    define('__DEBUG', true);

if(__DEBUG)
	error_reporting(E_ALL);
else
	error_reporting(0);

//Activate assert and make it quiet
assert_options(ASSERT_ACTIVE, 1);
assert_options(ASSERT_WARNING, 0);
assert_options(ASSERT_QUIET_EVAL, 1);

//Include Cfg class to access configuration data
require_once('Resources/Config/cfg.inc');
use \Resources\Config\Cfg as Cfg;

//Include PerformanceHelper class for server benchmarking
require_once('Utils/Performance/PerformanceHelper.inc');
use \Utils\Performance\PerformanceHelper as PerformanceHelper;

//Debug helper class for printing helpful messages and such
class DbgHelper {
    //constants used for debug messages (errors, warnings, etc.)
    const NONE          = -1;   //for unknown  or generic message types
    const SYSTEM        =  0;   //for system errors
    const ASSERT        =  1;   //for asserts
    const MODEL         =  2;   //for messages related to Models
    const VIEW          =  3;   //for messages related to Views
    const CONTROLLER    =  4;   //for messages related to Controllers
    const RESOURCE      =  5;   //for messages related to resources
    const SQL           =  6;   //for messages related to SQL
    const ERROR         =  7;   //for generic errors
    const APP           =  8;   //for app errors
    const GUI           =  9;   //for GUI errors

	private static $outputBuffer = "";

    //internal function which returns the channel name
    private static function GetChannelName($channel)
    {
        $class = new \ReflectionClass('\Utils\Debug\DbgHelper');
        $constants = $class->getConstants();

        $channelName = 'ERROR';
        foreach ( $constants as $name => $value )
        {
            if ( $value == $channel )
            {
                $channelName = $name;
                break;
            }
        }

        return $channelName;
    }

    //internal function which formats the debug message
    private static function BuildDbgMsg(&$message, $channel)
    {
        $bt = debug_backtrace(DEBUG_BACKTRACE_IGNORE_ARGS)[1];
        $message = '<p>[' . strtoupper(DbgHelper::GetChannelName($channel)) . '] ' . $message . ' [in ' . $bt['file'] . ' at line ' . $bt['line'] . ']</p>';
    }

    //Displays a debug message
    public static function PrintDbgMsg($message, $channel = DbgHelper::NONE)
    {
        if(__DEBUG)
        {
            self::BuildDbgMsg($message, $channel);
            //echo $message;
			self::$outputBuffer .= $message;
        }
    }

    //Displays a debug message and dies
    public static function PrintDbgMsgAndDie($message, $channel = DbgHelper::NONE, $printStackTrace = true)
    {
        if(__DEBUG)
        {
            self::BuildDbgMsg($message, $channel);

            if($printStackTrace)
            {
                $e = new \Exception;
                //echo '<pre>';
	            self::$outputBuffer .= '<pre>';
                //echo $e->getTraceAsString();
	            self::$outputBuffer .= $e->getTraceAsString();
                //echo '</pre>';
				self::$outputBuffer .= '</pre>';
            }
			self::$outputBuffer .= $message;

	        self::FlushDbgOutputBuffer();
            die(/*$message*/);
        }
        else
            die("<p>Something went wrong. Please contact <a href='mailto:" . Cfg::$appSupport . "'>support.</a></p>");
    }

    //Assert callback function
    public static function AssertCallbackFunc($file, $line, $code, $desc = null)
    {
        if(__DEBUG)
        {
            //echo "<p>[" . DbgHelper::GetChannelName(DbgHelper::ASSERT) . "] " . "Assertion failed at $file:$line: $code";
	        self::$outputBuffer .= "<p>[" . DbgHelper::GetChannelName(DbgHelper::ASSERT) . "] " . "Assertion failed at $file:$line: $code";
            if ($desc)
                //echo ": $desc";
	            self::$outputBuffer .= ": $desc";
            //echo "</p>";
	        self::$outputBuffer .= "</p>";

	        self::FlushDbgOutputBuffer();
            die();
        }
        else
            die("<p>Something went wrong. Please contact <a href='mailto:" . Cfg::$appSupport . "'>support.</a></p>");
    }

	//Flush the output buffer
	public static function FlushDbgOutputBuffer()
	{
		if(__DEBUG)
			echo self::$outputBuffer;
	}

	//Server benchmark
	public static function RunBenchmark()
	{
		$old_error_reporting = error_reporting(0);
		try {
			PerformanceHelper::RunBenchmark();
		} catch (\Exception $e) {

		}
		error_reporting($old_error_reporting);
	}
}

//Setup assert callback function
assert_options(ASSERT_CALLBACK, 'Utils\Debug\DbgHelper::AssertCallbackFunc');