<?php
/**
 * Created by PhpStorm.
 * User: Bogdan
 * Date: 2/22/14
 * Time: 1:44 AM
 */

namespace Utils\Debug;

//Enable debug features
define('__DEBUG', true);

class DbgHelper {
    const NONE = -1;
    const MODEL = 0;
    const VIEW = 1;
    const CONTROLLER = 2;
    const RESOURCE = 3;
    const ERROR = 4;

    public static function printDebugMessage($message, $channel = DbgHelper::NONE)
    {
        if(__DEBUG)
        {
            $class = new \ReflectionClass('\Utils\Debug\DbgHelper');
            $constants = $class->getConstants();

            $constName = null;
            foreach ( $constants as $name => $value )
            {
                if ( $value == $channel )
                {
                    $constName = $name;
                    break;
                }
            }

            $bt = debug_backtrace();
            $caller = array_shift($bt);

            echo '<p>[' . strtoupper($constName) . '] ' . $message . ' in ' . $caller['file'] . ' at line ' . $caller['line'] . '</p>';
        }
    }
} 