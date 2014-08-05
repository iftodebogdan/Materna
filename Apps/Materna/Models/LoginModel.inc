<?php
/**
 * Created by PhpStorm.
 * User: Sorrell
 * Date: 04/08/14
 * Time: 23:32
 */

namespace Models;

//Include global config data
require_once('Resources/Config/cfg.inc');
use \Resources\Config\Cfg as Cfg;

//Include SQL helpers
require_once('Utils/SQL/SQLHelper.inc');
use Utils\SQL\SQLHelper as SQLHelper;

//Include cryptography helpers
require_once('Utils/Cryptography/CryptographyHelper.inc');
use Utils\Cryptography\CryptographyHelper;

//Necessary for retrieving common data from the DB
require_once('Apps/' . Cfg::$appTitle . '/Models/CommonModel.inc');

//Include debugging helper class
require_once('Utils/Debug/DbgHelper.inc');
use \Utils\Debug\DbgHelper as DbgHelper;

class LoginModel extends CommonModel
{

} 