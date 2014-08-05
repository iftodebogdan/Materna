<?php
/**
 * Created by PhpStorm.
 * User: Bogdan
 * Date: 2/21/14
 * Time: 11:34 PM
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
require_once('Apps/' . Cfg::$appTitle . '/Models/HomeModel.inc');
use Models\HomeModel as Model;

//Include Controller class
require_once('Apps/' . Cfg::$appTitle . '/Controllers/HomeController.inc');
use Controllers\HomeController as Controller;

//Include debugging helper class
require_once('Utils/Debug/DbgHelper.inc');
use \Utils\Debug\DbgHelper as DbgHelper;

//Include cryptography helpers
require_once('Utils/Cryptography/CryptographyHelper.inc');
use Utils\Cryptography\CryptographyHelper;

//Include BaseView
require_once('Views/ViewBase.inc');

//The view for the Home page
class HomeView extends ViewBase
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
		if(empty($this->linkList))
			DbgHelper::PrintDbgMsgAndDie("HomeView: header link list is empty!", DbgHelper::GUI);

		Theme::GuiBeginDraw();
		Theme::GuiDrawHeader($this->linkList);

		Theme::GuiDrawContent(new GuiBox(0, 300, 900, 1250, GuiAlignment::GUI_ALIGN_CENTER, GuiAlignment::GUI_ALIGN_TOP), "<table border=\"1\" width=\"100%\" height=\"100%\"><tr><td>test1</td></tr></table>");
		Theme::GuiDrawContent(new GuiBox(100, 200, 300, 400), "test2");
		Theme::GuiDrawContent(new GuiBox(50, 250, 250, 450), "test3");
		Theme::GuiDrawContent(new GuiBox(0, 0, 250, 250, GuiAlignment::GUI_ALIGN_RIGHT, GuiAlignment::GUI_ALIGN_BOTTOM), "test4");
		Theme::GuiDrawContent(new GuiBox(0, 0, 50, 50), "test5");
		Theme::GuiDrawContent(new GuiBox(400, 100, 500, 2000), "test6", array('product', 'description'), 'id1');

		Theme::GuiDrawFooter();
		Theme::GuiEndDraw();
	}
}