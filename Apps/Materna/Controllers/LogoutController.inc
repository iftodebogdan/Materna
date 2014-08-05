<?php
/**
 * Created by PhpStorm.
 * User: Sorrell
 * Date: 05/08/14
 * Time: 01:26
 */

namespace Controllers;

//Include global config data
require_once('Resources/Config/cfg.inc');
use \Resources\Config\Cfg as Cfg;

//Include Model class
require_once('Apps/' . Cfg::$appTitle . '/Models/LogoutModel.inc');
use Models\LogoutModel as Model;

//Include global controller
require_once('Apps/' . Cfg::$appTitle . '/Controllers/CommonController.inc');

class LogoutController extends CommonController
{
	private $model;

	function __construct(Model $model)
	{
		$this->model = $model;
	}
} 