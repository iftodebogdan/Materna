<?php
/**
 * Created by PhpStorm.
 * User: Sorrell
 * Date: 05/08/14
 * Time: 01:25
 */

namespace Views;

//Include global config data
require_once('Resources/Config/cfg.inc');
use \Resources\Config\Cfg as Cfg;

//Include theme class
require_once('Apps/' . Cfg::$appTitle . '/Resources/Themes/' . Cfg::$appTheme . 'Theme.inc');
use Resources\Themes\GuiAlignment;
use Resources\Themes\GuiBox;
use Resources\Themes\Theme as Theme;

//Include Model class
require_once('Apps/' . Cfg::$appTitle . '/Models/LogoutModel.inc');
use Models\LogoutModel as Model;

//Include Controller class
require_once('Apps/' . Cfg::$appTitle . '/Controllers/LogoutController.inc');
use Controllers\LogoutController as Controller;

//Include debugging helper class
require_once('Utils/Debug/DbgHelper.inc');
use \Utils\Debug\DbgHelper as DbgHelper;

//Include localised string resources
require_once('Apps/' . Cfg::$appTitle . '/Resources/Strings/' . Cfg::$locale . '.inc');
use Resources\Strings\Locale as Locale;

//Include cryptography helpers
require_once('Utils/Cryptography/CryptographyHelper.inc');
use Utils\Cryptography\CryptographyHelper;

//Include BaseView
require_once('Views/ViewBase.inc');

class LogoutView extends ViewBase
{
	private $linkList;

	function Init()
	{
		CryptographyHelper::RequireSSL(false);

		//Retrieve header links
		$this->linkList= array();
		Model::GetHeaderLinks($this->linkList);
	}

	function Draw()
	{
		//Draw the view
		Controller::LogoutUser();
		header("Location:Home");
	}
} 