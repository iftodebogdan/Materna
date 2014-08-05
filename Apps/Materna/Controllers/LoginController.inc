<?php
/**
 * Created by PhpStorm.
 * User: Sorrell
 * Date: 04/08/14
 * Time: 23:33
 */

namespace Controllers;

//Include global config data
require_once('Resources/Config/cfg.inc');
use \Resources\Config\Cfg as Cfg;

//Include Model class
require_once('Apps/' . Cfg::$appTitle . '/Models/LoginModel.inc');
use Models\LoginModel as Model;

//Include global controller
require_once('Apps/' . Cfg::$appTitle . '/Controllers/CommonController.inc');

class LoginController extends CommonController
{
	private $model;

	function __construct(Model $model)
	{
		$this->model = $model;
	}
} 