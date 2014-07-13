<?php
/**
 * Created by PhpStorm.
 * User: Bogdan
 * Date: 2/22/14
 * Time: 12:11 AM
 */

namespace Resources\Strings;

//Include helper class for debugging
require_once('Utils/Debug/DbgHelper.inc');
use \Utils\Debug\DbgHelper as DbgHelper;

//Include Cfg class to access configuration data
require_once('Resources/Config/cfg.inc');
use \Resources\Config\Cfg as Cfg;

//Include base class for Locale
require_once('LocaleBase.inc');

//Check if the correct locale is loaded
if(strcmp(Cfg::$locale, "en-us") == 0)
{
    class Locale extends LocaleBase {
        //set a localised string for each
        static $szPromotions   = "Promotions";
        static $szClothing     = "Clothing";
        static $szFootwear     = "Footwear";
        static $szToys         = "Toys";
        static $szFurniture    = "Furniture";
        static $szBaptism      = "Baptism";
        static $szContact      = "Contact";
    }
}
else
    //Wrong locale loaded, print a helpful debug message and die
    DbgHelper::PrintDbgMsgAndDie('Locale "' . Cfg::$locale . '" found in cfg.inc, but "' . basename(__FILE__) . '" has been loaded instead!', DbgHelper::RESOURCE);