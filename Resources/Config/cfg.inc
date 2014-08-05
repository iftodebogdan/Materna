<?php
/**
 * Created by PhpStorm.
 * User: Sorrell
 * Date: 23/04/14
 * Time: 23:17
 */

namespace Resources\Config;

//A class containing hard-coded configuration data
class Cfg{
	//App
    public static $locale       = "ro-ro";
    public static $appTitle     = "Materna";
    public static $appTheme     = "Materna";
    public static $appSupport   = "iftode.bogdan@gmail.com";

	//Database
    public static $cfgDbHost    = "localhost";
    public static $cfgDbUser    = "materna";
    public static $cfgDbPass    = "1123581321";
    public static $cfgDbSchema  = "materna";

	//Cryptography
	public static $encryptionKey    = "86c4498fed71ad229995c4abb633e0bd"; //md5("Materna")
	public static $algorithmCost    = 11;
	public static $permitSSL        = true;
}