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

//Debug helper class for printing helpful messages and such
class DbgHelper {
    //constants used for debug messages (errors, warnings, etc.)
    const NONE          = -1;   //for unknown  or generic message types
    const SYSTEM        =  0;   //for system errors
    const MODEL         =  1;   //for messages related to Models
    const VIEW          =  2;   //for messages related to Views
    const CONTROLLER    =  3;   //for messages related to Controllers
    const RESOURCE      =  4;   //for messages related to resources
    const SQL           =  5;   //for messages related to SQL
    const ERROR         =  6;   //for generic errors
    const APP           =  7;   //for app errors

    //internal function which formats the debug message
    private static function buildDbgMsg(&$message, $channel)
    {
        $class = new \ReflectionClass('\Utils\Debug\DbgHelper');
        $constants = $class->getConstants();

        $constName = 'ERROR';
        foreach ( $constants as $name => $value )
        {
            if ( $value == $channel )
            {
                $constName = $name;
                break;
            }
        }

        $bt = debug_backtrace(DEBUG_BACKTRACE_IGNORE_ARGS)[1];
        $message = '<p>[' . strtoupper($constName) . '] ' . $message . ' in ' . $bt['file'] . ' at line ' . $bt['line'] . '</p>';
    }

    //Displays a debug message
    public static function printDbgMsg($message, $channel = DbgHelper::NONE)
    {
        if(__DEBUG)
        {
            self::buildDbgMsg($message, $channel);
            echo $message;
        }
    }

    //Displays a debug message and dies
    public static function printDbgMsgAndDie($message, $channel = DbgHelper::NONE, $printStackTrace = true)
    {
        if(__DEBUG)
        {
            self::buildDbgMsg($message, $channel);

            if($printStackTrace)
            {
                $e = new \Exception;
                echo '<pre>';
                echo $e->getTraceAsString();
                echo '</pre>';
            }

            die($message);
        }
    }
} 