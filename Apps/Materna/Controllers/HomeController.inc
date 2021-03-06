<?php
/**
 * Created by PhpStorm.
 * User: Bogdan
 * Date: 2/21/14
 * Time: 11:34 PM
 */

namespace Controllers;

//Include global config data
require_once('Resources/Config/cfg.inc');
use \Resources\Config\Cfg as Cfg;

//Include Model class
require_once('Apps/' . Cfg::$appTitle . '/Models/HomeModel.inc');
use Models\HomeModel as Model;

//Include global controller
require_once('Apps/' . Cfg::$appTitle . '/Controllers/CommonController.inc');

//The controller for the Home page
class HomeController extends CommonController
{
	private $model;

    function __construct(Model $model)
    {
		$this->model = $model;
    }
}
