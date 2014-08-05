<?php
/**
 * Created by PhpStorm.
 * User: Bogdan
 * Date: 2/21/14
 * Time: 11:34 PM
 */

namespace Models;

//Include global config data
require_once('Resources/Config/cfg.inc');
use \Resources\Config\Cfg as Cfg;

//Necessary for retrieving common data from the DB
require_once('Apps/' . Cfg::$appTitle . '/Models/CommonModel.inc');

//The model for the Home page
class HomeModel extends CommonModel
{
    function __construct()
    {

    }
} 