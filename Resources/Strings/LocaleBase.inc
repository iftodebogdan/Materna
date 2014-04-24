<?php
/**
 * Created by PhpStorm.
 * User: Sorrell
 * Date: 24/04/14
 * Time: 18:46
 */

namespace Resources\Strings;

//Include debugging helper class
require_once('Utils/Debug/DbgHelper.inc');
use \Utils\Debug\DbgHelper as DbgHelper;

//The base class for all Locale classes
abstract class LocaleBase {
    //Returns a localised string based on its string ID
    public static function ReturnStrById($id)
    {
        //check if the string ID exists
        if(property_exists('\\Resources\\Strings\\Locale', $id))
            return static::$$id;
        else
            //string ID not found, print a helpful debug message and return null
            DbgHelper::printDbgMsg('String ID "' . $id . '" is invalid!', DbgHelper::RESOURCE);

        return null;
    }
}
