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

//Necessary for retrieving common data from the DB
require_once('Apps/' . Cfg::$appTitle . '/Models/CommonModel.inc');
use Models\CommonModel as CommonModel;

//Include Controller class
require_once('Apps/' . Cfg::$appTitle . '/Controllers/HomeController.inc');
use Controllers\HomeController as Controller;

//The view for the Home page
class HomeView {
    function __construct(Controller $controller, Model $model)
    {
        //Retrieve header links
        $linkList = array();
        CommonModel::GetHeaderLinks($linkList);

        //Draw the view
        Theme::GuiBeginDraw();
        Theme::GuiDrawHeader($linkList);

        Theme::GuiDrawContent(new GuiBox(100, 200, 300, 400), "test1");
        Theme::GuiDrawContent(new GuiBox(50, 250, 250, 450), "test2");
        Theme::GuiDrawContent(new GuiBox(0, 0, 250, 250, GuiAlignment::GUI_ALIGN_RIGHT, GuiAlignment::GUI_ALIGN_BOTTOM), "test3");
        Theme::GuiDrawContent(new GuiBox(0, 0, 250, 250, GuiAlignment::GUI_ALIGN_CENTER, GuiAlignment::GUI_ALIGN_CENTER), "test4");
        Theme::GuiDrawContent(new GuiBox(), "test5");
        Theme::GuiDrawContent(new GuiBox(400, 100, 500, 2000), "test6", array('product', 'description'), 'id1');

        Theme::GuiDrawFooter();
        Theme::GuiEndDraw();
    }
}