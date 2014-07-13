<?php
/**
 * Created by PhpStorm.
 * User: Bogdan
 * Date: 2/22/14
 * Time: 12:12 AM
 */

namespace Resources\Strings;

//Include debugging helper class
require_once('Utils/Debug/DbgHelper.inc');
use \Utils\Debug\DbgHelper as DbgHelper;

//Include Cfg class to access configuration data
require_once('Resources/Config/cfg.inc');
use \Resources\Config\Cfg as Cfg;

//Include base class for Locale
require_once('Resources/Strings/LocaleBase.inc');

//Check if the correct locale is loaded
if(strcmp(Cfg::$locale, "ro-ro") == 0)
{
    class Locale extends LocaleBase {
        //set a localised string for each string ID
        static $szPromotions   = "Promotii";
        static $szClothing     = "Articole imbracaminte";
        static $szFootwear     = "Articole incaltaminte";
        static $szToys         = "Jucarii";
        static $szFurniture    = "Mobilier camera copilului";
        static $szBaptism      = "Articole botez";
        static $szContact      = "Contact";
    }
}
else
    //Wrong locale loaded, print a helpful debug message and die
    DbgHelper::PrintDbgMsgAndDie('Locale "' . Cfg::$locale . '" found in cfg.inc, but "' . basename(__FILE__) . '" has been loaded instead!', DbgHelper::RESOURCE);